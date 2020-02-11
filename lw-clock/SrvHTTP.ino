void server_httpinit(void) {
  HTTP.on("/configs.json", handle_ConfigJSON); // create configs.json for sending to WEB interface
  HTTP.on("/ssid", handle_Set_Ssid);     // Set WiFi config and SSDP
  HTTP.on("/Time", handle_Time);     // Sync Time
  HTTP.on("/TimeZone", handle_time_zone);    // Set time zone
  HTTP.on("/setntpserver", handle_ntp_server); // Set sync NTP
#if USE_RTC == true
  HTTP.on("/TimeNew", handle_TimeNew);     // Set new time 
#endif 
  HTTP.on("/ledsetup", handle_LedSetup); //speed, brightness, 
  HTTP.on("/texts", handle_Texts);     // Set stext
  HTTP.on("/ledoption", handle_LedOption);
  HTTP.on("/weather", handle_Weather);
  HTTP.on("/sea", handle_Sea);  
  HTTP.on("/weatherUpdate", handle_weather_update);
  HTTP.on("/lang", handle_Language);
  HTTP.on("/mqttSet", handle_MQTTSet);
  HTTP.on("/mqttOn", handle_MQTTOn);
  HTTP.on("/tspeakSet", handle_tspeakSet);
  HTTP.on("/tspeakOn", handle_tspeakOn); 
  HTTP.on("/setalarm", handle_set_alarm);
  HTTP.on("/Sensor", handle_Sensors);
  HTTP.on("/restart", handle_Restart);   // reset ESP
  HTTP.on("/resetConfig", handle_resetConfig);      
  HTTP.begin();  
}

void handle_ConfigJSON() { 
  P.displaySuspend(true);
  time_t tn = now();
  String root = "{}";  
  DynamicJsonDocument jsonDoc(5096);//4096
  DeserializationError error =  deserializeJson(jsonDoc, root);
  if (error) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(error.c_str());
      return;
  }     
  JsonObject json = jsonDoc.as<JsonObject>();    
  json["SSDP"] = myWIFI.getNameSSDP();
  json["ssidAP"] = myWIFI.getNameAPSSID();
  json["passwordAP"] = myWIFI.getPassAPSSID();
  json["ssid"] = myWIFI.getNameSSID();
  json["password"] = myWIFI.getPassSSID();
  json["ip"] = myWIFI.getDevStatusIP();
  json["timezone"] = timezone;
  json["time"] = GetTime(true);
  json["date"] = GetDate();
  json["date_day"] = day(tn);
  json["date_month"] = month(tn);
  json["date_year"] = year(tn);
  json["isDayLightSaving"] = (isDayLightSaving?"checked":"");
  json["use_sync"] = (useRTC?"":"checked");
  json["time_h"] = String(hour(tn));
  json["time_m"] = String(minute(tn));
  json["time_s"] = String(second(tn));    
  json["isLedClock"]=(isLedClock?"checked":"");json["isLedDate"]=(isLedDate?"checked":"");
  json["isLedWeather"]=(isLedWeather?"checked":"");json["isLedForecast"]=(isLedForecast?"checked":"");
  json["isLedSea"]=(isLedSea?"checked":"");
  json["weathFrom"] = weathFrom; json["weathTo"] = weathTo;
  json["fcastFrom"] = fcastFrom; json["fcastTo"] = fcastTo;
  json["clockFrom"] = clockFrom; json["clockTo"] = clockTo;
  json["dateFrom"] = dateFrom; json["dateTo"] = dateTo; 
  json["seaFrom"] = seaFrom; json["seaTo"] = seaTo;   
  json["ledText0"] = strText0;
  json["ledText1"] = strText1;
  json["ledText2"] = strText2;
  json["ledText3"] = strText3;
  json["isTxtOn0"]=(isTxtOn0?"checked":"");
  json["isTxtOn1"]=(isTxtOn1?"checked":"");
  json["isTxtOn2"]=(isTxtOn2?"checked":"");
  json["isTxtOn3"]=(isTxtOn3?"checked":"");
  json["txtFrom0"] = txtFrom0;
  json["txtFrom1"] = txtFrom1;
  json["txtFrom2"] = txtFrom2;
  json["txtFrom3"] = txtFrom3;
  json["txtTo0"] = txtTo0;
  json["txtTo1"] = txtTo1;
  json["txtTo2"] = txtTo2;
  json["txtTo3"] = txtTo3;
  json["isCrLine0"]=(isCrLine0?"checked":"");
  json["isCrLine1"]=(isCrLine1?"checked":"");
  json["isCrLine2"]=(isCrLine2?"checked":"");
  json["isCrLine3"]=(isCrLine3?"checked":"");
  json["global_start"] = global_start; json["global_stop"] = global_stop;
  json["fontUsed"] = fontUsed;
  json["brightd"] = brightd; json["brightn"] = brightn;
  json["speed_d"] = 28 - speedTicker;
  json["dmodefrom"] = dmodefrom; json["dmodeto"] = dmodeto;
  json["lang"] = (lang==0?"RU":lang==1?"BG":lang==2?"EN":"EN");
  json["weatherHost"] = W_URL;
  json["city_code"] = CITY_ID;
  json["w_api"] = W_API; 
  json["sea_id"] = SEA_ID;
  json["ntpserver"] = sNtpServerName;  
  json["mqttOn"]=(mqttOn?"checked":"");
  json["mqtt_server"] = mqtt_server;
  json["mqtt_port"] = mqtt_port;
  json["mqtt_user"] = mqtt_user;
  json["mqtt_pass"] = mqtt_pass;
  json["mqtt_name"] = mqtt_name;
  json["mqtt_sub_crline"] = mqtt_sub_crline;
  json["mqtt_pub_temp"] = mqtt_pub_temp;
  json["mqtt_pub_hum"] = mqtt_pub_hum;
  json["mqtt_pub_press"] = mqtt_pub_press;
#if USE_DHT == true
  json["temp_now"] = getTempDHT();
  json["hum_now"] = getHumDHT()+ "%";
#endif
#if USE_BME280 == true
  json["temp_now"] = getTempBME280();
  json["hum_now"] = getHumBME280() + "%  Press " + getPressBME280() + "mm";
#endif  
  json["isLedTHP"]=(isLedTHP?"checked":"");
  json["thpFrom"] = thpFrom; json["thpTo"] = thpTo;
  json["tspeakOn"] = (tspeakOn?"checked":"");
  json["tspeak_server"] = tspeak_server;
  json["tspeak_channal"] = tspeak_channal;
  json["tspeak_wapi"] = tspeak_wapi;   
  json["alarm1_h"] = myAlarm[0].alarm_h;
  json["alarm1_m"] = myAlarm[0].alarm_m;
  json["alarm1_stat"] = myAlarm[0].alarm_stat; 
  json["alarm2_h"] = myAlarm[1].alarm_h;
  json["alarm2_m"] = myAlarm[1].alarm_m;
  json["alarm2_stat"] = myAlarm[1].alarm_stat;        
  json["cVersion"] = cVersion;  
  root = "";
  serializeJson(json, root);
  HTTP.send(200, "text/json", root);
  P.displaySuspend(false);
}

void handle_Set_Ssid() {
  ssid = HTTP.arg("ssid").c_str();            
  password = HTTP.arg("password").c_str();   
  ssidAP = HTTP.arg("ssidAP").c_str();        
  passwordAP = HTTP.arg("passwordAP").c_str(); 
  SSDP_Name = HTTP.arg("ssdp").c_str();
  myWIFI.setConfigWIFI(ssid.c_str(), password.c_str(), SSDP_Name.c_str(), ssidAP.c_str(), passwordAP.c_str()); 
  //saveConfig();                        
  Serial.println("Set SSID: " + ssid + ", Set password: " + password + ", Set SSID AP: " + ssidAP + ", Set AP password: " + passwordAP + ", SSDP: " + SSDP_Name);
  HTTP.send(200, "text/plain", "OK");   
}

void handle_time_zone() {     
  timezone = HTTP.arg("timezone").toInt(); 
  isDayLightSaving = HTTP.arg("isDayLightSaving").toInt();
  saveConfig();
  timeSynch();
  Serial.println("NTP Time Zone: " + String(timezone) + ",  isDayLightSaving: " + String(isDayLightSaving));
  HTTP.send(200, "text/plain", "OK");
}

void handle_ntp_server() {               
  sNtpServerName = HTTP.arg("ntpserver").c_str(); 
#if USE_RTC == true
  HTTP.arg("use_sync").toInt()==1?useRTC=false:useRTC=true;
#endif
  saveConfig();
  timeSynch();
  //Serial.println("sNtpServerName: " + sNtpServerName + ", useRTC: " + useRTC);
  HTTP.send(200, "text/plain", "OK");
}

void handle_Time(){
  timeSynch();
  HTTP.send(200, "text/plain", "OK"); 
}

#if USE_RTC == true
  void handle_TimeNew(){
    uint8_t new_h = HTTP.arg("time_h").toInt(); 
    uint8_t new_m = HTTP.arg("time_m").toInt();
    uint8_t new_s = HTTP.arg("time_s").toInt();
    uint8_t new_day = HTTP.arg("date_day").toInt(); 
    uint8_t new_month = HTTP.arg("date_month").toInt();
    uint16_t new_year = HTTP.arg("date_year").toInt();    
    useRTC = true;
    setTime(new_h, new_m, new_s,new_day,new_month,new_year);
    rtc.adjust(DateTime(new_year, new_month, new_day, new_h, new_m, new_s));    
    saveConfig();
    timeSynch();
    HTTP.send(200, "text/plain", "OK"); 
  }
#endif

void handle_LedSetup() {               
  speedTicker = 28 - HTTP.arg("speed_d").toInt(); 
  brightd = HTTP.arg("brightd").toInt();
  brightn = HTTP.arg("brightn").toInt();
  dmodefrom = HTTP.arg("dmodefrom").toInt();
  dmodeto = HTTP.arg("dmodeto").toInt();
  fontUsed = HTTP.arg("fontUsed").toInt();
  (fontUsed==0?P.setFont(_6bite_rus):fontUsed==1?P.setFont(_5bite_rus):fontUsed==2?P.setFont(_font_rus):P.setFont(_6bite_rus));
  saveConfig();
  P.setIntensity(brightd);
  Serial.print("speedTicker ");Serial.println(speedTicker); Serial.print("brightd ");Serial.println(brightd);Serial.print("brightn ");Serial.println(brightn);
  Serial.print("dmodefrom ");Serial.println(dmodefrom);Serial.print("dmodeto ");Serial.println(dmodeto);
  HTTP.send(200, "text/plain", "OK");
}

void handle_LedOption() {
  HTTP.arg("isLedWeather").toInt()==1?isLedWeather=true:isLedWeather=false;
  HTTP.arg("isLedForecast").toInt()==1?isLedForecast=true:isLedForecast=false;
  HTTP.arg("isLedClock").toInt()==1?isLedClock=true:isLedClock=false;
  HTTP.arg("isLedDate").toInt()==1?isLedDate=true:isLedDate=false;
  HTTP.arg("isLedSea").toInt()==1?isLedSea=true:isLedSea=false;
  weathFrom = HTTP.arg("weathFrom").toFloat(); weathTo = HTTP.arg("weathTo").toFloat();
  fcastFrom = HTTP.arg("fcastFrom").toFloat(); fcastTo = HTTP.arg("fcastTo").toFloat();
  clockFrom = HTTP.arg("clockFrom").toFloat(); clockTo = HTTP.arg("clockTo").toFloat();
  dateFrom = HTTP.arg("dateFrom").toFloat(); dateTo = HTTP.arg("dateTo").toFloat();
  seaFrom = HTTP.arg("seaFrom").toFloat(); seaTo = HTTP.arg("seaTo").toFloat();
#if (USE_BME280 == true || USE_DHT == true)  
  HTTP.arg("isLedTHP").toInt()==1?isLedTHP=true:isLedTHP=false;
  thpFrom = HTTP.arg("thpFrom").toFloat(); thpTo = HTTP.arg("thpTo").toFloat();
#else
  isLedTHP=false; thpFrom = 25; thpTo = 25;
#endif
  saveConfig();                 
  (isLedWeather?strWeather = GetWeather():strWeather ="");
  (isLedForecast?strWeatherFcast = GetWeatherForecast():strWeatherFcast = "");
  (isLedSea?strSea = GetSea():strSea ="");
  HTTP.send(200, "text/plain", "OK"); 
}

void handle_Texts() {
  P.displaySuspend(true);
  strText0 = HTTP.arg("ledText0").c_str(); // 
  strText1 = HTTP.arg("ledText1").c_str(); // 
  strText2 = HTTP.arg("ledText2").c_str(); // 
  strText3 = HTTP.arg("ledText3").c_str(); //
  HTTP.arg("isTxtOn0").toInt()==1?isTxtOn0=true:isTxtOn0=false;
  HTTP.arg("isTxtOn1").toInt()==1?isTxtOn1=true:isTxtOn1=false;
  HTTP.arg("isTxtOn2").toInt()==1?isTxtOn2=true:isTxtOn2=false;
  HTTP.arg("isTxtOn3").toInt()==1?isTxtOn3=true:isTxtOn3=false;
  txtFrom0 = HTTP.arg("txtFrom0").toFloat();
  txtFrom1 = HTTP.arg("txtFrom1").toFloat();
  txtFrom2 = HTTP.arg("txtFrom2").toFloat();
  txtFrom3 = HTTP.arg("txtFrom3").toFloat();
  txtTo0 = HTTP.arg("txtTo0").toFloat();
  txtTo1 = HTTP.arg("txtTo1").toFloat();
  txtTo2 = HTTP.arg("txtTo2").toFloat();
  txtTo3 = HTTP.arg("txtTo3").toFloat();
  HTTP.arg("isCrLine0").toInt()==1?isCrLine0=true:isCrLine0=false;
  HTTP.arg("isCrLine1").toInt()==1?isCrLine1=true:isCrLine1=false;
  HTTP.arg("isCrLine2").toInt()==1?isCrLine2=true:isCrLine2=false;
  HTTP.arg("isCrLine3").toInt()==1?isCrLine3=true:isCrLine3=false;
  global_start = HTTP.arg("global_start").toFloat();
  global_stop = HTTP.arg("global_stop").toFloat();
  saveConfig();                 // Функция сохранения данных во Flash
  Serial.print("strText ");Serial.println(strText0);Serial.println(strText1);Serial.println(strText2);Serial.println(strText3);
  Serial.print("isTxtOn0 ");Serial.println(isTxtOn0);Serial.println(txtFrom0);Serial.println(txtTo0);Serial.println(isCrLine0);
  Serial.print("isTxtOn1 ");Serial.println(isTxtOn1);Serial.println(txtFrom1);Serial.println(txtTo1);Serial.println(isCrLine1);
  Serial.print("isTxtOn2 ");Serial.println(isTxtOn2);Serial.println(txtFrom2);Serial.println(txtTo2);Serial.println(isCrLine2);
  Serial.print("isTxtOn3 ");Serial.println(isTxtOn3);Serial.println(txtFrom3);Serial.println(txtTo3);Serial.println(isCrLine3);
  HTTP.send(200, "text/plain", "OK"); 
  P.displaySuspend(false);
}

void handle_Weather() {
  W_URL = HTTP.arg("weatherHost").c_str();
  CITY_ID = HTTP.arg("city_code").c_str(); 
  W_API = HTTP.arg("w_api").c_str();
  saveConfig();                
  strWeather = GetWeather(); delay(1000); strWeatherFcast = GetWeatherForecast();
  Serial.println("W_URL: " + W_URL + ", CITY_ID: " + CITY_ID + ", W_API: " + W_API);
  HTTP.send(200, "text/plain", "OK"); 
}

void handle_weather_update() {
  if(HTTP.arg("update") == "ok") {
    strWeather = GetWeather();
    delay(1000);
    strWeatherFcast = GetWeatherForecast();
    HTTP.send(200, "text/plain", "OK");
  }
}

void handle_Sea() {
  SEA_ID = HTTP.arg("seacity_id").c_str(); 
  saveConfig();                
  (isLedSea?strSea = GetSea():strSea ="");
  Serial.println("SEA_ID: " + SEA_ID);
  HTTP.send(200, "text/plain", "OK"); 
}

void handle_Language() {               
  if(HTTP.arg("lang") == "RU" && lang !=0) {
    lang = 0;
  }
  else if(HTTP.arg("lang") == "BG" && lang !=1) {
    lang = 1;
  }
  else if(HTTP.arg("lang") == "EN" && lang !=2) {
    lang = 2;
  }
  else {
    HTTP.send(200, "text/plain", "OK"); return;
  }
  Serial.print("Set lang: ");    Serial.println(HTTP.arg("lang").c_str());
  saveConfig();
  if (isLedWeather) {
    strWeather = GetWeather(); delay(1000); 
  }
  if (isLedForecast) {
    strWeatherFcast = GetWeatherForecast();
  }
  HTTP.send(200, "text/plain", "OK");
}

void handle_MQTTOn() {
    HTTP.arg("mqttOn").toInt()==1?mqttOn=true:mqttOn=false;
    saveConfig();                 
    Serial.println("mqttOn: " + mqttOn);
    HTTP.send(200, "text/plain", "OK");   
}

void handle_MQTTSet() {
    HTTP.arg("mqttOn").toInt()==1?mqttOn=true:mqttOn=false;
    mqtt_server = HTTP.arg("mqtt_server").c_str();
    mqtt_port = HTTP.arg("mqtt_port").toInt();
    mqtt_user = HTTP.arg("mqtt_user").c_str();
    mqtt_pass = HTTP.arg("mqtt_pass").c_str();
    mqtt_name = HTTP.arg("mqtt_name").c_str();
    mqtt_sub_crline = HTTP.arg("mqtt_sub_crline").c_str();
    mqtt_pub_temp = HTTP.arg("mqtt_pub_temp").c_str();
    mqtt_pub_hum = HTTP.arg("mqtt_pub_hum").c_str();
    mqtt_pub_press = HTTP.arg("mqtt_pub_press").c_str();
    saveConfig();                 
    Serial.println("mqtt_server: " + mqtt_server + ", mqtt_user: " + mqtt_user + ", mqtt_name: " + mqtt_name);
    HTTP.send(200, "text/plain", "OK"); 
}

void handle_tspeakSet() {
  HTTP.arg("tspeakOn").toInt()==1?tspeakOn=true:tspeakOn=false;
  tspeak_server = HTTP.arg("tspeak_server").c_str();
  tspeak_channal = HTTP.arg("tspeak_channal").toInt();
  tspeak_wapi = HTTP.arg("tspeak_wapi").c_str();
  saveConfig();                 
  Serial.println("tspeak_server: " + tspeak_server + ", tspeak_channal: " + tspeak_channal + ", tspeak_wapi: " + tspeak_wapi);
  HTTP.send(200, "text/plain", "OK"); 
}

void handle_tspeakOn() {
  HTTP.arg("tspeakOn").toInt()==1?tspeakOn=true:tspeakOn=false;
  saveConfig();                
  Serial.println("tspeakOn: " + tspeakOn);
  HTTP.send(200, "text/plain", "OK"); 
}  
void handle_Sensors() {
  strTHP = "";
  #if USE_DHT == true 
    strTHP = onboard[lang] + getTempDHT() + hum[lang] + getHumDHT() + "%";
  #endif   
  #if USE_BME280 == true
    strTHP = onboard[lang] + getTempBME280() + hum[lang] + getHumBME280() + pres[lang] + getPressBME280() + "mm";
  #endif  
  Serial.println(strTHP);
  lastTimePHT = millis();    
  HTTP.send(200, "text/plain", "OK");     
}

void handle_set_alarm(){
  myAlarm[0].alarm_h = HTTP.arg("alarm1_h").toInt();
  myAlarm[0].alarm_m = HTTP.arg("alarm1_m").toInt(); 
  myAlarm[0].alarm_stat = HTTP.arg("alarm1_stat").toInt();  
  myAlarm[1].alarm_h = HTTP.arg("alarm2_h").toInt();
  myAlarm[1].alarm_m = HTTP.arg("alarm2_m").toInt(); 
  myAlarm[1].alarm_stat = HTTP.arg("alarm2_stat").toInt();     
  saveConfig();
  //Serial.println("alarm1_h: " + alarm[0].alarm_h + ", alarm1_m: " + alarm[0].alarm_m + ", alarm1_stat: " + alarm[0].alarm_stat);
  //Serial.println("alarm2_h: " + alarm[1].alarm_h + ", alarm2_m: " + alarm[1].alarm_m + ", alarm2_stat: " + alarm[1].alarm_stat);
  HTTP.send(200, "text/plain", "OK"); 
}  

void handle_Restart() {
  String restart = HTTP.arg("device");       
  if (restart == "ok") {                         
    HTTP.send(200, "text/plain", "Reset OK");
    ESP.restart();                               
  }
  else {                                       
    HTTP.send(200, "text/plain", "No Reset"); 
  }
}

void handle_resetConfig() {
  String restart = HTTP.arg("device");
  if(restart == "ok") {
    //SPIFFS.format();
    SPIFFS.remove("/myconfig.json");
    Serial.println("ESP erase Config file");
    delay(3000);
    HTTP.send(200, "text/plain", "OK");
    delay(3000);
    ESP.restart();
  }
}
