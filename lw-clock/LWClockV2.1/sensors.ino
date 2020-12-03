#if (USE_BME280 == true || USE_DHT == true) 

void init_sensor() {
#if USE_DHT == true
  dht.begin(); 
#endif //DHT
#if USE_BME280 == true // I2C D1, D2
  bme280.parameter.communication = 0;                  //Choose communication protocol
  bme280.parameter.I2CAddress = 0x76;                  //Choose I2C Address 0x77
  //0b00:     In sleep mode no measurements are performed, but power consumption is at a minimum
  //0b01:     In forced mode a single measured is performed and the device returns automatically to sleep mode
  //0b11:     In normal mode the sensor measures continually (default value)
  bme280.parameter.sensorMode = 0b11; 
  bme280.parameter.IIRfilter = 0b100;                    //Setup for IIR Filter
  bme280.parameter.humidOversampling = 0b101;            //Setup Humidity Oversampling
  bme280.parameter.tempOversampling = 0b101;             //Setup Temperature Ovesampling
  bme280.parameter.pressOversampling = 0b101;            //Setup Pressure Oversampling 
  bme280.parameter.pressureSeaLevel = 1013.25;           //default value of 1013.25 hPa
  bme280.parameter.tempOutsideCelsius = 15;              //default value of 15°C
  uint8_t tries = 10;
  while (--tries && bme280.init() != 0x60) {
    Serial.println(F("Ops! BME280 could not be found! Please check your connections."));
    delay(500);
  }
  if (tries > 0) {
    Serial.println(F("BME280 detected!"));
  }
#endif //BME280 
}

#if USE_DHT == true
String getTempDHT() {
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
  if (isnan(t) || isnan(h))  {
    Serial.println("Failed to read Temp from DHT");
    return "";
  }
  else {
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);
    String tempDHT = String(hic, 1); 
    Serial.print("Temperature: "); Serial.print(tempDHT); Serial.println("°C");     
    return tempDHT;      
  }
}

String getHumDHT() {
  float h = dht.readHumidity(); 
  if (isnan(h))  {
    Serial.println("Failed to read Hum from DHT");
    return "";
  }
  else {
    // Compute heat index in Celsius (isFahreheit = false)
    String humDHT = String(h, 0); 
    Serial.print("Humidity: "); Serial.print(humDHT); Serial.println("%");     
    return humDHT;      
  }
}
#endif //DHT

#if USE_BME280 == true // I2C D1, D2
String getTempBME280(bool correct, uint8_t pr) { //correct depending brightness and sign after point
  float tempBME = bme280.readTempC();
  uint8_t brightnow = 0; 
  Serial.print("Temperature: "); Serial.print(tempBME); Serial.println("°C"); 
  if (correct) {
      time_t tn = now();
      float nowtime = hour(tn)+float(minute(tn))/100;
      if (compTimeInt(dmodefrom, dmodeto, nowtime)) brightnow = brightd; else brightnow = brightn;  
      switch (brightnow) {
        case 0:
          tempBME = tempBME - 0.09;
        break;
        case 1:
          tempBME = tempBME - 0.57;
        break;
        case 2:
          tempBME = tempBME - 1.04;
        break;
        case 3:
          tempBME = tempBME - 1.66;
        break;
        case 4:
          tempBME = tempBME - 2;
        break;
        case 5:
          tempBME = tempBME - 2.67;
        break;
        case 6:
          tempBME = tempBME - 2.84;
        break;
        case 7:
          tempBME = tempBME - 3.29;
        break;
        case 8:
          tempBME = tempBME - 3.57;
        break;
        case 9:
          tempBME = tempBME - 4.21;
        break;
        case 10:
          tempBME = tempBME - 4.4;
        break;
        case 11:
          tempBME = tempBME - 4.98;
        break;
        case 12:
          tempBME = tempBME - 5.34;
        break;
        case 13:
          tempBME = tempBME - 5.72;
        break;
        case 14:
          tempBME = tempBME - 5.95;
        break;
        case 15:
          tempBME = tempBME - 6.38;
        break;
      } 
      Serial.print("Temperature cor: "); Serial.print(tempBME); Serial.println("°C");
  }    
  return String(tempBME, pr);
}

String getHumBME280(bool correct, uint8_t pr) { //correct depending brightness and sign after point
  float humBME = bme280.readHumidity();
  uint8_t brightnow = 0; 
  Serial.print("Humidity: "); Serial.print(humBME); Serial.println("%");
  if (correct) { 
      time_t tn = now();
      float nowtime = hour(tn)+float(minute(tn))/100;
      if (compTimeInt(dmodefrom, dmodeto, nowtime)) brightnow = brightd; else brightnow = brightn;  
      switch (brightnow) {
        case 0:
          humBME = humBME + 2.06;
        break;
        case 1:
          humBME = humBME + 3.52;
        break;
        case 2:
          humBME = humBME + 5.4;
        break;
        case 3:
          humBME = humBME + 8.05;
        break;
        case 4:
          humBME = humBME + 8.63;
        break;
        case 5:
          humBME = humBME +10.62;
        break;
        case 6:
          humBME = humBME + 11.05;
        break;
        case 7:
          humBME = humBME + 11.9;
        break;
        case 8:
          humBME = humBME + 12.96;
        break;
        case 9:
          humBME = humBME + 14.42;
        break;
        case 10:
          humBME = humBME + 15.07;
        break;
        case 11:
          humBME = humBME + 16.56;
        break;
        case 12:
          humBME = humBME + 16.83;
        break;
        case 13:
          humBME = humBME + 18.37;
        break;
        case 14:
          humBME = humBME + 18.82;
        break;
        case 15:
          humBME = humBME + 19.27;
        break;
      }  
      Serial.print("Humidity cor: "); Serial.print(humBME); Serial.println("%");  
  }
  return String(humBME, pr);  
}

String getPressBME280(bool hpa, uint8_t pr) { //unit of press and sign after point
  float pressBME = bme280.readPressure();
  Serial.print(F("Pressure "));Serial.print(pressBME);Serial.println(" hPa");
  Serial.print(F("Pressure "));Serial.print(pressBME*0.750062);Serial.println(" mm");
  Serial.print(F("Altitude in Meters:\t\t")); Serial.println(bme280.readAltitudeMeter());
  if (hpa) return String(pressBME, pr);
  else     return String(pressBME*0.750062, pr);  
}
#endif //BME280 

#endif
