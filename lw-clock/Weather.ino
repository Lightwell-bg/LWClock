String GetWeather() {
  String weatherString;
  static String oldWeather = "Wait weather"+W_URL;
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print(F("No connection to weather server (No Wi-Fi) ")); Serial.println(W_URL); 
    weatherString = "*" + oldWeather;
    return weatherString; 
  }  
  Serial.print(F("connecting to ")); Serial.println(W_URL);
  String wStrURL = String("GET /data/2.5/weather?id=") + CITY_ID; 
  wStrURL += "&units=metric&appid=" + W_API;
  switch (lang) {
    case 0:
      wStrURL += "&lang=ru";
    break;
    case 1:
      wStrURL += "&lang=bg";
    break;
    case 2:
      wStrURL += "&lang=en";
    break;     
    default:
      wStrURL += "&lang=en";
    break;
  }  
  wStrURL += "\r\nHost: " + W_URL + "\r\nUser-Agent: ArduinoWiFi/1.1\r\nConnection: close\r\n\r\n";
  Serial.println(wStrURL);

  if (ESPclient.connect(W_URL.c_str(), 80)) {
    ESPclient.println(wStrURL);
  }
  else {
    Serial.print(F("Connection weather server failed")); Serial.println(W_URL);
    weatherString = "*" + oldWeather;
    return weatherString; 
  }
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(13) + 270;
  DynamicJsonDocument root(capacity);
  String answerWeather = ESPclient.readString();
  DeserializationError error = deserializeJson(root, answerWeather);
  if (error) {
    Serial.print(F("Json parsing failed! ")); Serial.print(F("deserializeJson() failed with code ")); Serial.println(error.c_str());    
    ESPclient.stop();
    weatherString = "*" + oldWeather;
    return weatherString; 
  }
  ESPclient.stop();  
  Serial.println(answerWeather);
  float coord_lon = root["coord"]["lon"]; // 27.47
  float coord_lat = root["coord"]["lat"]; // 42.51  
  weatherString = overboard[lang];
  JsonObject weather_0 = root["weather"][0];
  weatherString += weather_0["description"].as<String>();
  weatherString += temper[lang];
  JsonObject main = root["main"];
  float temp = main["temp"]; 
  weatherString += String(temp,1);
  uint8_t humidity = main["humidity"]; 
  uint16_t pressure = main["pressure"];
  weatherString += hum[lang];  weatherString += String(humidity);
  weatherString += pres[lang]; weatherString += String(pressure/1.3332239,0);
  weatherString += wind[lang];
  weatherString += root["wind"]["speed"].as<String>();
  weatherString += windsp[lang];    
  double deg = root["wind"]["deg"];
  if (deg >22.5 && deg <=67.5) weatherString += windir_table[lang][0];
  else if (deg >67.5 && deg <=112.5) weatherString += windir_table[lang][1];
  else if (deg >112.5 && deg <=157.5) weatherString += windir_table[lang][2];
  else if (deg >157.5 && deg <=202.5) weatherString += windir_table[lang][3];
  else if (deg >202.5 && deg <=247.5) weatherString += windir_table[lang][4];
  else if (deg >247.5 && deg <=292.5) weatherString += windir_table[lang][5];
  else if (deg >292.5 && deg <=337.5) weatherString += windir_table[lang][6];
  else weatherString += windir_table[lang][7];
  uint8_t clouds = root["clouds"]["all"];
  weatherString += cloudstxt[lang] + String(clouds) + "% ";
  Serial.print(F("Get weather: ")); Serial.println(weatherString); 
  oldWeather =  weatherString;
  return weatherString;
}

String GetWeatherForecast() {
  String weatherString;
  static String oldWeather = "Wait weather"+W_URL;
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print(F("No connection to weather server (No Wi-Fi) ")); Serial.println(W_URL); 
    weatherString = "*" + oldWeather;
    return weatherString;  
  }  
  Serial.print(F("connecting to ")); Serial.println(W_URL);
  String wStrURL = String("GET /data/2.5/forecast?id=") + CITY_ID; 
  wStrURL += "&units=metric&appid=" + W_API;
  switch (lang) {
    case 0:
      wStrURL += "&lang=ru";
    break;
    case 1:
      wStrURL += "&lang=bg";
    break;
    case 2:
      wStrURL += "&lang=en";
    break;     
    default:
      wStrURL += "&lang=en";
    break;
  }  
  wStrURL += "&cnt=1";
  wStrURL += "\r\nHost: " + W_URL + "\r\nUser-Agent: ArduinoWiFi/1.1\r\nConnection: close\r\n\r\n";
  Serial.println(wStrURL);
  if (ESPclient.connect(W_URL.c_str(), 80)) {
    ESPclient.println(wStrURL);
  }
  else {
    Serial.print(F("Connection weather server failed")); Serial.println(W_URL);
    weatherString = "*" + oldWeather;
    return weatherString; 
  }
  const size_t capacity = 2*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(2) + 4*JSON_OBJECT_SIZE(1) + 3*JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 3*JSON_OBJECT_SIZE(7) + 2*JSON_OBJECT_SIZE(8) + 540;
  DynamicJsonDocument root(capacity);
  String answerWeather = ESPclient.readString();
  DeserializationError error = deserializeJson(root, answerWeather);
  if (error) {
    Serial.print(F("Json parsing failed! ")); Serial.print(F("deserializeJson() failed with code ")); Serial.println(error.c_str());    
    ESPclient.stop();
    weatherString = "*" + oldWeather;
    return weatherString; 
  }
  ESPclient.stop();  
  Serial.println(answerWeather);
  weatherString = forecast[lang];
  JsonObject list = root["list"][0];
  JsonObject weather = root["list"][0]["weather"][0];
  weatherString += weather["description"].as<String>();
  float tempMin = list["main"]["temp_min"];
  float tempMax = list["main"]["temp_max"];  
  uint8_t humidity = list["main"]["humidity"];
  double pressure = list["main"]["pressure"].as<double>()/1.3332239;
  weatherString += tempermin[lang];
  weatherString += String(tempMin,1);
  weatherString += tempermax[lang];
  weatherString += String(tempMax,1);
  weatherString += hum[lang];  weatherString += String(humidity);
  weatherString += pres[lang]; weatherString += String(pressure,0);
  weatherString += wind[lang];
  double deg = list["wind"]["deg"];
  if (deg >22.5 && deg <=67.5) weatherString += windir_table[lang][0];
  else if (deg >67.5 && deg <=112.5) weatherString += windir_table[lang][1];
  else if (deg >112.5 && deg <=157.5) weatherString += windir_table[lang][2];
  else if (deg >157.5 && deg <=202.5) weatherString += windir_table[lang][3];
  else if (deg >202.5 && deg <=247.5) weatherString += windir_table[lang][4];
  else if (deg >247.5 && deg <=292.5) weatherString += windir_table[lang][5];
  else if (deg >292.5 && deg <=337.5) weatherString += windir_table[lang][6];
  else weatherString += windir_table[lang][7];
  weatherString += list["wind"]["speed"].as<String>();
  weatherString += windsp[lang];  
  Serial.print(F("Get weather forecast: ")); Serial.println(weatherString); 
  oldWeather =  weatherString;
  return weatherString;
}

String GetSea() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("No connection to weather server (No Wi-Fi)");
    return "";  
  }  
  Serial.print("connecting to "); Serial.println(WSea_URL);
  String wStrURL = String("GET /en/i/") + String(SEA_ID); 
  wStrURL += "/c/160x86/ HTTP/1.1";
  wStrURL += "\r\nHost: " + WSea_URL + "\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:36.0) Gecko/20100101 Firefox/36.0\r\nConnection: close\r\n\r\n";
  Serial.println(wStrURL);  
  if (ESPclient.connect(WSea_URL.c_str(), 80)) {
    ESPclient.println(wStrURL);
  }
  else {
    Serial.println("Weather server connection failed");
    return "";
  }
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
  uint16_t firstInt = response.indexOf("temp\">");
  uint16_t secondInt = response.indexOf("&deg",firstInt);
  String tempSea = response.substring(firstInt+6, secondInt);
  if (tempSea!="") return  String(tempersea[lang] + tempSea +"\xC2С"); else return "";
}
