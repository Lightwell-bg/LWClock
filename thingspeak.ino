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
  fieldDataBME[0] = bme280.readTempC(); 
  fieldDataBME[1] = bme280.readHumidity();
  fieldDataBME[2] = bme280.readPressure()*0.750062;
  Serial.print("Temperature: "); Serial.print(fieldDataBME[0]); Serial.print("°C"); Serial.print(". Humidity: "); Serial.print(fieldDataBME[1]); Serial.print("%");
  Serial.print(". Pressure: ");Serial.print(fieldDataBME[2]); Serial.println("hPa");
  HTTPPost(3, fieldDataBME);
  #endif //BME280
}

/*
#include <ThingSpeak.h>

char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 777492;
char* writeAPIKey = "BKVNM81OAXMRD96P";

//write2TSData( channelID , dataFieldOne , celsiusTemperature , dataFieldTwo , fahrenheitTemperature , dataFieldThree , millis() ); 
// Write the temperature in F, C, and time since starting.

int write2TSData(long TSChannel, unsigned int TSField1, float field1Data, unsigned int TSField2, float field2Data) {
  ThingSpeak.setField(TSField1, field1Data);
  ThingSpeak.setField(TSField2, field2Data);
  //ThingSpeak.setField(TSField3, field3Data);
   
  int writeSuccess = ThingSpeak.writeFields(TSChannel, writeAPIKey);
  return writeSuccess;
}

void sendTSpeak() {
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
  if (isnan(t) || isnan(h))  {
    Serial.println("Failed to read Temp from DHT");
  }
  else {
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print("Temperature: "); Serial.print(String(hic,1)); Serial.print("°C");Serial.print("Hum: "); Serial.println(String(h,1)); 
    write2TSData(channelID, 1, hic, 2, h);    
  }  
}*/
#endif
