void Time_init() {
#if USE_RTC == true
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }  
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  } 
#endif 
  timeSynch();
}

#if USE_RTC == true  
void timeSynch() {
  time_t gotTime;
  if (useRTC) {
    gotTime = getRtcTime();
    setTime(gotTime);        
  }
  else {
    if (WiFi.status() == WL_CONNECTED) { 
      gotTime = getNtpTime();
      if (gotTime > 0) { //if got time from NTP set RTC
        setTime(gotTime);
        time_t tn = now();
        rtc.adjust(DateTime(year(tn), month(tn), day(tn), hour(tn), minute(tn), second(tn)));  
      }
      else {
        statusUpdateNtpTime = 0;        
      }
    }
    else {
      gotTime = getRtcTime();
      setTime(gotTime); 
      statusUpdateNtpTime = 0; 
    }
  }
  Serial.println("ITime Ready RTS!");
}
#else 
void timeSynch() {
  time_t gotTime;
  if (WiFi.status() == WL_CONNECTED) { 
      gotTime = getNtpTime();
      if (gotTime<=0) {
        statusUpdateNtpTime = 0;        
      } 
      else {
        setTime(gotTime);
        Serial.println("timeSynch() Ready NTP!");
      }
  }
  else statusUpdateNtpTime = 0;
}
#endif

String GetTime(bool s) { //s - show seconds
  if ((timeStatus() != timeNotSet) && (timeStatus() != timeNeedsSync)) {
    time_t tn = now();
    String Time;
    if (s) {
      Time = String(hour(tn))+":"+ (minute(tn) < 10 ? "0"+String(minute(tn)) : String(minute(tn))) +":"+ String(second(tn));  
    }
    else {
      Time = String(hour(tn))+":"+ (minute(tn) < 10 ? "0"+String(minute(tn)) : String(minute(tn)));
    }
    //Serial.println("GetTime() "+Time);
    return Time; 
  }
  else {
    timeSynch();
    return "";
  }
}

void getTimeDisp(char *psz, bool f) { // Code for reading clock time for displey only
  time_t tn = now();
  sprintf(psz, "%02d%c%02d", hour(tn), (f ? ':' : ' '), minute(tn));
}


String GetDate() {
 time_t tn = now();
 //String Date = String(day(tn))+"."+(month(tn)<10 ? "0" + String(month(tn)) :  String(month(tn))) +"."+String(year(tn));//""; // Строка для результатов времени 
 //String Date = String(day(tn))+" "+monthStr(month(tn)) +" "+String(year(tn)) + ", " + dayStr(weekday(tn));//""; // Строка для результатов времени  
 String Date = String(day(tn))+" "+month_table[lang][month(tn)-1] +" "+String(year(tn)) + ", " + day_table[lang][weekday(tn)-1];
 //String Date = String(day(tn))+ "." + (month(tn)<10 ? "0" + String(month(tn)) :  String(month(tn))) + "." + String(year(tn)) + ", " + day_table[lang][weekday(tn)-1];
 //Serial.println(Date);
 Date.toLowerCase();
 return Date; 
}

bool compTimeInt(float tFrom, float tTo, float tNow) { //Comparing time for proper processing from 18.00 to 8.00
  if (tFrom < tTo)  {
    if ((tFrom <= tNow) && (tTo >= tNow)) return true; else return false;
  }
  else if (tFrom > tTo) {
    if (tNow <= 23.59 && tFrom <= tNow)  return true;
    else if (tNow >= 0 && tTo >= tNow)  return true;
    else return false;  
  }
  else {
    return false;
  }
}

void workAlarms() {
  static bool checkStatus = 1; //don't set digitalWrite(BUZ_PIN, LOW) all time
  static unsigned long lastTimeAlarm;
  static bool onAlarm; 
  uint8_t bitOn = 0; 
  time_t tn = now();  
  if (digitalRead(ALARM_PIN)) {
    //Serial.println("Button H click.");
    stopAlarm = true;
    timeStopAlarm = millis();
  }  
  if (stopAlarm && (millis()-timeStopAlarm > 1000*60)) { //через 1 min надо отключить кнопку остановки будильника
    stopAlarm = false;  
  }
  if (checkStatus && (stopAlarm || !((hour(tn)==myAlarm[0].alarm_h && minute(tn)==myAlarm[0].alarm_m) || (hour(tn)==myAlarm[1].alarm_h && minute(tn)==myAlarm[1].alarm_m)))) {
    digitalWrite(BUZ_PIN, LOW); 
    checkStatus = 0; 
  } 
  bitOn = (day_byte[weekday(tn)-1]) & myAlarm[0].alarm_stat;
  //Serial.print("bitOn "); Serial.println(bitOn);
  if ((bitOn > 0) && hour(tn)==myAlarm[0].alarm_h && minute(tn)==myAlarm[0].alarm_m && !stopAlarm) {
    if (millis()-lastTimeAlarm > 500) {
      digitalWrite(BUZ_PIN, onAlarm);
      lastTimeAlarm = millis();
      onAlarm = !onAlarm;
    }
    checkStatus = 1;
  }
  bitOn = (day_byte[weekday(tn)-1]) & myAlarm[1].alarm_stat;      
  if ((bitOn > 0) && hour(tn)==myAlarm[1].alarm_h && minute(tn)==myAlarm[1].alarm_m && !stopAlarm) {
    if (millis()-lastTimeAlarm > 1000) {
      digitalWrite(BUZ_PIN, onAlarm);
      lastTimeAlarm = millis();
      onAlarm = !onAlarm;
    }
  }
  checkStatus = 1; 
  //Serial.print("stopAlarm "); Serial.println(stopAlarm);Serial.print("checkStatus "); Serial.println(checkStatus);             
}
