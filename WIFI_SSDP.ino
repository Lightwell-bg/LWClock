void WIFI_init() {
  WiFi.mode(WIFI_STA);
  uint8_t tries = 10;
  WiFi.begin(ssid.c_str(), password.c_str());
  while (--tries && WiFi.status() != WL_CONNECTED)  {   
    Serial.print(F("."));
    //bounce(); // Animation of a bouncing ball
    delay(1000);
  }
  if (WiFi.status() != WL_CONNECTED)  {    // Run AP
    Serial.println(F("WiFi up AP"));
    StartAPMode();
    Serial.print(F("AP IP address: ")); Serial.println(WiFi.softAPIP());   
  }
  else {  
    Serial.println(F("WiFi connected"));
    Serial.print(F("IP address: "));    Serial.println(WiFi.localIP());
  }
}

bool StartAPMode() {
  WiFi.disconnect();   // Off WIFI
  WiFi.mode(WIFI_AP);   // Change mode
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // config
  WiFi.softAP(ssidAP.c_str(), passwordAP.c_str());
  return true;
}

void SSDP_init(void) {
  HTTP.on("/description.xml", HTTP_GET, []() {
    SSDP.schema(HTTP.client());
  });
  //Если версия  2.0.0 закаментируйте следующую строчку
  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName(SSDP_Name);
  SSDP.setSerialNumber("001788102201");
  SSDP.setURL("/");
  SSDP.setModelName(nName);
  SSDP.setModelNumber(nVersion);
  SSDP.setModelURL("http://"+(WiFi.status() != WL_CONNECTED ? WiFi.softAPIP() : WiFi.localIP()));
  SSDP.setManufacturer("LIGHTWELL");
  SSDP.setManufacturerURL("https://led-lightwell.eu");
  SSDP.begin();
}
