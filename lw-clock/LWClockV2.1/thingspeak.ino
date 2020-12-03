#if (USE_BME280 == true || USE_DHT == true) 

void HTTPPost(uint8_t numFields, String fieldData[]){
  if (ESPclient.connect(tspeak_server, 80)) {
     // If you have multiple fields, make sure the sting does not exceed 1440 characters.
     //String postData= "api_key=" + writeAPIKey + "&field" + String(numField) + "=" + fieldData;
     String postData= "api_key=" + tspeak_wapi;
     for (uint8_t fieldNumber = 0; fieldNumber < numFields; fieldNumber++) {
          String fieldName = "field" + String(fieldNumber+1);
          postData += "&" + fieldName + "=" + fieldData[fieldNumber];
          
      }       
      // POST data via HTTP
      Serial.println("Connecting to ThingSpeak for update...");
      Serial.println();
      ESPclient.println("POST /update HTTP/1.1");
      ESPclient.println("Host: " + String(tspeak_server));
      ESPclient.println("Connection: close");
      ESPclient.println("Content-Type: application/x-www-form-urlencoded");
      ESPclient.println("Content-Length: " + String(postData.length()));
      ESPclient.println();
      ESPclient.println(postData);
      Serial.println(postData);
      String answer = getResponse();
      Serial.println(answer);
  }
  else {
    Serial.println("Connection Failed");
  }
}

String getResponse(){
  String response = "";
  unsigned startTime = millis();
  delay (200);
  while (!ESPclient.available() && ((millis()-startTime) < 5000)) {
        delay (5);
  }
  
  while (ESPclient.available()) { // Get response from server
     char charIn = ESPclient.read(); // Read a char from the buffer.
     response += charIn;     // Append the char to the string response.
  }
  ESPclient.stop();
  return response;
}


void sendTspeak() {
  #if USE_DHT == true
  String fieldData[2];  
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
  if (isnan(t) || isnan(h))  {
    Serial.println("Failed to read from DHT");
    fieldData[0] = "0"; 
    fieldData[1] = "0"; 
  }
  else {
    float hic = dht.computeHeatIndex(t, h, false);
    fieldData[0] = String(hic, 1); 
    fieldData[1] = String(h, 1); 
    Serial.print("Temperature: "); Serial.print(fieldData[0]); Serial.print("°C"); Serial.print(". Humidity: "); Serial.print(fieldData[1]); Serial.println("%");     
  }
  HTTPPost(2, fieldData);
  #endif //DHT
  #if USE_BME280 == true
  String fieldDataBME[3];  
  fieldDataBME[0] = getTempBME280(dataCorrect, 2);  
  fieldDataBME[1] = getHumBME280(dataCorrect, 2);
  fieldDataBME[2] = getPressBME280(hpa, 2);
  Serial.print("Temperature: "); Serial.print(fieldDataBME[0]); Serial.print("°C"); Serial.print(". Humidity: "); Serial.print(fieldDataBME[1]); Serial.print("%");
  Serial.print(". Pressure: ");Serial.print(fieldDataBME[2]); Serial.println("hPa");
  HTTPPost(3, fieldDataBME);
  #endif //BME280
}

#endif
