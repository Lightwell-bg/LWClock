static const char successResponse[] PROGMEM = 
  "<META http-equiv=\"refresh\" content=\"15;URL=/\">Update Success! Rebooting...";

String updateError = "";
String getUpdaterError();

void FS_init(void) {
  if(!LittleFS.begin()) { // Initialize SPIFFS
        Serial.println("An Error has occurred while mounting SPIFFS");
  }   
  Dir dir = LittleFS.openDir("/");
  while (dir.next()) {
    String fileName = dir.fileName();
    size_t fileSize = dir.fileSize();
  }
  HTTP.serveStatic("/", LittleFS, "/index.html");
  HTTP.onNotFound([]() {
    if(!handleFileRead(HTTP.uri()))
    HTTP.send(404, "text/plain", "FileNotFound");
    });  
  //HTTP pages for work with FFS
  //list directory
  HTTP.on("/list", HTTP_GET, handleFileList);
  //load editor
  HTTP.on("/edit", HTTP_GET, []() {
    if (!handleFileRead("/edit.htm")) HTTP.send(404, "text/plain", "FileNotFound");
  });
  //Create file
  HTTP.on("/edit", HTTP_PUT, handleFileCreate);
  //Del file
  HTTP.on("/edit", HTTP_DELETE, handleFileDelete);
  //first callback is called after the request has ended with all parsed arguments
  //second callback handles file uploads at that location
  HTTP.on("/edit", HTTP_POST, []() {
    HTTP.send(200, "text/plain", "");
  }, handleFileUpload);
  //called when the url is not defined here
  //use it to load content from SPIFFS
  HTTP.onNotFound([]() {
    if (!handleFileRead(HTTP.uri()))
      HTTP.send(404, "text/plain", "FileNotFound");
  });
  HTTP.on("/update", HTTP_POST, [](){ //For Update firmware and data.bin
    /*HTTP.sendHeader("Connection", "close");
      HTTP.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();*/
      if (Update.hasError()) {
        HTTP.send(200, F("text/html"), String(F("Update error: ")) + updateError);
      } else {
        HTTP.client().setNoDelay(true);
        HTTP.send_P(200, PSTR("text/html"), successResponse);
        delay(100);
        HTTP.client().stop();
        ESP.restart();
      }
  },[]() {
    HTTPUpload& upload = HTTP.upload();
    if(upload.status == UPLOAD_FILE_START) {
      Serial.setDebugOutput(true);
      WiFiUDP::stopAll();
      Serial.printf("Update: %s\n", upload.filename.c_str());
      //Serial.print("Size: "); Serial.println(upload.totalSize);
      //size_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
      size_t maxSketchSpace = ((size_t) &_FS_end - (size_t) &_FS_start); 
      //size_t content_len = upload.totalSize;
      //int cmd = (upload.filename.indexOf("spiffs") > -1) ? 100 : 0; //U_FS : U_FLASH;
      int cmd = (upload.filename.indexOf("littlefs") > -1 || upload.filename.indexOf("spiffs") > -1) ? U_FS : U_FLASH; //U_FS : U_FLASH;
      //if(!Update.begin(maxSketchSpace,cmd)) {//start with max available size
      if(!Update.begin(maxSketchSpace, cmd)) {//start with max available size
              //Update.printError(Serial);
              updateError = getUpdaterError();
      }
    }
    else if(upload.status == UPLOAD_FILE_WRITE) {
      if(Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        //Update.printError(Serial);
        updateError = getUpdaterError();
      }
    }
    else if(upload.status == UPLOAD_FILE_END) {
      if(Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        //Update.printError(Serial);
        updateError = getUpdaterError();
      }
      Serial.setDebugOutput(false);
    }
    yield();
  });  
}

String getUpdaterError() {
  Update.printError(Serial);
  StreamString str;
  Update.printError(str);
  return String(str.c_str());
}

String getContentType(String filename) {
  if (HTTP.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".json")) return "application/json";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool handleFileRead(String path) {
  if (path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (LittleFS.exists(pathWithGz) || LittleFS.exists(path)) {
    if (LittleFS.exists(pathWithGz))
      path += ".gz";
    File file = LittleFS.open(path, "r");
    size_t sent = HTTP.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void handleFileUpload() {
  if (HTTP.uri() != "/edit") return;
  HTTPUpload& upload = HTTP.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) filename = "/" + filename;
    fsUploadFile = LittleFS.open(filename, "w");
    filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile)
      fsUploadFile.close();
  }
}

void handleFileDelete() {
  if (HTTP.args() == 0) return HTTP.send(500, "text/plain", "BAD ARGS");
  String path = HTTP.arg(0);
  if (path == "/")
    return HTTP.send(500, "text/plain", "BAD PATH");
  if (!LittleFS.exists(path))
    return HTTP.send(404, "text/plain", "FileNotFound");
  LittleFS.remove(path);
  HTTP.send(200, "text/plain", "");
  path = String();
}

void handleFileCreate() {
  if (HTTP.args() == 0)
    return HTTP.send(500, "text/plain", "BAD ARGS");
  String path = HTTP.arg(0);
  if (path == "/")
    return HTTP.send(500, "text/plain", "BAD PATH");
  if (LittleFS.exists(path))
    return HTTP.send(500, "text/plain", "FILE EXISTS");
  File file = LittleFS.open(path, "w");
  if (file)
    file.close();
  else
    return HTTP.send(500, "text/plain", "CREATE FAILED");
  HTTP.send(200, "text/plain", "");
  path = String();

}

void handleFileList() {
  if (!HTTP.hasArg("dir")) {
    HTTP.send(500, "text/plain", "BAD ARGS");
    return;
  }
  String path = HTTP.arg("dir");
  Dir dir = LittleFS.openDir(path);
  path = String();
  String output = "[";
  while (dir.next()) {
    File entry = dir.openFile("r");
    if (output != "[") output += ',';
    bool isDir = false;
    output += "{\"type\":\"";
    output += (isDir) ? "dir" : "file";
    output += "\",\"name\":\"";
    output += String(entry.name()).substring(1);
    output += "\"}";
    entry.close();
  }
  output += "]";
  HTTP.send(200, "text/json", output);
}
