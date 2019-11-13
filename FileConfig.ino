// Load saved config from myconfig.json
bool loadConfig() {
  File configFile = SPIFFS.open("/myconfig.json", "r");  
  if (!configFile) {  // not found
    Serial.println(F("Failed to open config file"));
    saveConfig();   //  create file
    configFile.close();
    return false;
  }
  size_t size = configFile.size();   // myconfig.json must be less 2048 byte
  if (size > 2048) {  
    Serial.println(F("Config file size is too large"));
    configFile.close();
    return false;
  }
  jsonConfig = configFile.readString(); // load config 
  configFile.close();
   DynamicJsonDocument jsonDoc(5096); //4096
   DeserializationError error = deserializeJson(jsonDoc, jsonConfig);
   if (error) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(error.c_str());
      return false;
   }   
   JsonObject root = jsonDoc.as<JsonObject>();    
    ssidAP = root["ssidAPName"].as<String>(); // Так получаем строку
    passwordAP = root["ssidAPPassword"].as<String>();
    timezone = root["timezone"];               // Так получаем число
    isDayLightSaving = root["isDayLightSaving"];
    SSDP_Name = root["SSDPName"].as<String>();
    ssid = root["ssidName"].as<String>();
    password = root["ssidPassword"].as<String>();
    weathFrom = root["weathFrom"]; weathTo = root["weathTo"];
    fcastFrom = root["fcastFrom"]; fcastTo = root["fcastTo"];
    clockFrom = root["clockFrom"]; clockTo = root["clockTo"];
    dateFrom = root["dateFrom"]; dateTo = root["dateTo"];
    seaFrom = root["seaFrom"]; seaTo = root["seaTo"];        
    strText0 = root["ledText0"].as<String>();
    strText1 = root["ledText1"].as<String>();
    strText2 = root["ledText2"].as<String>();
    strText3 = root["ledText3"].as<String>();
    isTxtOn0 = root["isTxtOn0"];
    isTxtOn1 = root["isTxtOn1"];
    isTxtOn2 = root["isTxtOn2"];
    isTxtOn3 = root["isTxtOn3"];
    txtFrom0 = root["txtFrom0"];
    txtFrom1 = root["txtFrom1"];
    txtFrom2 = root["txtFrom2"];
    txtFrom3 = root["txtFrom3"];
    txtTo0 = root["txtTo0"];
    txtTo1 = root["txtTo1"];
    txtTo2 = root["txtTo2"];
    txtTo3 = root["txtTo3"];
    isCrLine0 = root["isCrLine0"];
    isCrLine1 = root["isCrLine1"];
    isCrLine2 = root["isCrLine2"];
    isCrLine3 = root["isCrLine3"];
    global_start = root["global_start"]; global_stop = root["global_stop"];
    fontUsed = root["fontUsed"];
    brightd = root["brightd"]; brightn = root["brightn"];
    dmodefrom = root["dmodefrom"]; dmodeto = root["dmodeto"];             
    speedTicker = root["speed_d"];
    isLedWeather = root["isLedWeather"];
    isLedForecast = root["isLedForecast"];
    isLedClock = root["isLedClock"];
    isLedDate = root["isLedDate"];
    isLedSea = root["isLedSea"];
    CITY_ID = root["city_code"].as<String>();
    W_URL = root["weatherHost"].as<String>();
    W_API = root["w_api"].as<String>();
    lang = root["lang"];
    sNtpServerName = root["ntp_server"].as<String>();
#if USE_RTC == true
    useRTC = root["useRTC"];
#endif   
    mqttOn = root["mqttOn"];
    mqtt_server = root["mqtt_server"].as<String>();
    mqtt_port = root["mqtt_port"].as<int>();
    mqtt_user = root["mqtt_user"].as<String>();
    mqtt_pass = root["mqtt_pass"].as<String>();
    mqtt_name = root["mqtt_name"].as<String>();
    mqtt_sub_crline = root["mqtt_sub_crline"].as<String>();
    mqtt_pub_temp = root["mqtt_pub_temp"].as<String>();
    mqtt_pub_hum = root["mqtt_pub_hum"].as<String>();
    mqtt_pub_press = root["mqtt_pub_press"].as<String>();
    //crLine = root["crLine"].as<String>();
    isLedTHP = root["isLedTHP"];
    thpFrom = root["thpFrom"]; thpTo = root["thpTo"];
    tspeakOn = root["tspeakOn"];
    tspeak_server = root["tspeak_server"].as<String>();
    tspeak_channal = root["tspeak_channal"].as<int>();
    tspeak_wapi = root["tspeak_wapi"].as<String>();  
    myAlarm[0].alarm_h = root["alarm1_h"].as<int>();
    myAlarm[0].alarm_m = root["alarm1_m"].as<int>();
    myAlarm[0].alarm_stat = root["alarm1_stat"].as<int>(); 
    myAlarm[1].alarm_h = root["alarm2_h"].as<int>();
    myAlarm[1].alarm_m = root["alarm2_m"].as<int>();
    myAlarm[1].alarm_stat = root["alarm2_stat"].as<int>();       
    return true;
}

// Write to myconfig.json
bool saveConfig() {
  DynamicJsonDocument jsonDoc(5096);//4096
  DeserializationError error = deserializeJson(jsonDoc, jsonConfig);
  if (error) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(error.c_str());
      return false;
  }     
  JsonObject json = jsonDoc.as<JsonObject>();  
  json["SSDPName"] = SSDP_Name;
  json["ssidAPName"] = ssidAP;
  json["ssidAPPassword"] = passwordAP;
  json["ssidName"] = ssid;
  json["ssidPassword"] = password;
  json["timezone"] = timezone;
  json["isDayLightSaving"] = isDayLightSaving;
  json["weathFrom"] = weathFrom; json["weathTo"] = weathTo;
  json["fcastFrom"] = fcastFrom; json["fcastTo"] = fcastTo;
  json["clockFrom"] = clockFrom; json["clockTo"] = clockTo;
  json["dateFrom"] = dateFrom; json["dateTo"] = dateTo; 
  json["seaFrom"] = seaFrom; json["seaTo"] = seaTo;     
  json["ledText0"] = strText0;
  json["ledText1"] = strText1;
  json["ledText2"] = strText2;
  json["ledText3"] = strText3;
  json["isTxtOn0"] = isTxtOn0;
  json["isTxtOn1"] = isTxtOn1;
  json["isTxtOn2"] = isTxtOn2;
  json["isTxtOn3"] = isTxtOn3;
  json["txtFrom0"] = txtFrom0;
  json["txtFrom1"] = txtFrom1;
  json["txtFrom2"] = txtFrom2;
  json["txtFrom3"] = txtFrom3;
  json["txtTo0"] = txtTo0;
  json["txtTo1"] = txtTo1;
  json["txtTo2"] = txtTo2;
  json["txtTo3"] = txtTo3;
  json["isCrLine0"] = isCrLine0; 
  json["isCrLine1"] = isCrLine1;  
  json["isCrLine2"] = isCrLine2;  
  json["isCrLine3"] = isCrLine3; 
  json["global_start"] = global_start; json["global_stop"] = global_stop; 
  json["fontUsed"] = fontUsed; 
  json["brightd"] = brightd; json["brightn"] = brightn;
  json["dmodefrom"] = dmodefrom; json["dmodeto"] = dmodeto;
  json["speed_d"] = speedTicker;
  json["isLedWeather"] = isLedWeather;
  json["isLedForecast"] = isLedForecast;
  json["isLedClock"] = isLedClock;
  json["isLedDate"] = isLedDate;
  json["isLedSea"] = isLedSea;
  json["weatherHost"] = W_URL;
  json["city_code"] = CITY_ID;
  json["w_api"] = W_API;
  json["lang"] = lang;
  json["ntp_server"] = sNtpServerName;
#if USE_RTC == true
  json["useRTC"] = useRTC;
#endif  
  json["mqttOn"] = mqttOn;
  json["mqtt_server"] = mqtt_server;
  json["mqtt_port"] = mqtt_port;
  json["mqtt_user"] = mqtt_user;
  json["mqtt_pass"] = mqtt_pass;
  json["mqtt_name"] = mqtt_name;
  json["mqtt_sub_crline"] = mqtt_sub_crline;
  json["mqtt_pub_temp"] = mqtt_pub_temp;
  json["mqtt_pub_hum"] = mqtt_pub_hum;
  json["mqtt_pub_press"] = mqtt_pub_press;
  json["isLedTHP"] = isLedTHP;
  json["thpFrom"] = thpFrom; json["thpTo"] = thpTo;
  json["tspeakOn"] = tspeakOn;
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
  serializeJson(json, jsonConfig);
  File configFile = SPIFFS.open("/myconfig.json", "w");
  if (!configFile) {
    Serial.println(F("Failed to open config file for writing"));
    configFile.close();
    return false;
  }
  serializeJson(json, configFile);
  configFile.close();
  return true;
}
