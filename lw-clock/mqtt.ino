void init_mqtt() {
  mqttClient.setServer(mqtt_server.c_str(), mqtt_port);
  mqttClient.setCallback(callback);  
}

void callback(char* topic, byte* payload, unsigned int length) { 
  Serial.print("Message arrived ");
  payload[length] = '\0';
  String strTopic = String(topic);
  String strPayload = String((char*)payload);
  Serial.print(strTopic);  Serial.print(" => "); Serial.println(strPayload);
  if(strTopic == mqtt_sub_crline) {
    Serial.println(strPayload);
    crLine = strPayload;
  }      
}

boolean reconnect() {
  Serial.print("Attempting MQTT connection...");
  // Attempt to connect
  if (mqttClient.connect(mqtt_name.c_str(), mqtt_user.c_str(), mqtt_pass.c_str())) {
    Serial.println("connected");
    // Once connected, publish an announcement...
    mqttClient.publish("ClockTopic", "Hello world");//*************************************************************
    // ... and resubscribe
    mqttClient.subscribe(mqtt_sub_crline.c_str()); // Subcribe to topic "creeping line"
  }
  else {
    Serial.print("failed, rc=");
    Serial.print(mqttClient.state());
    Serial.println(" try again in 5 seconds");
  }
  return mqttClient.connected();
}

#if (USE_BME280 == true || USE_DHT == true) 
  void sendMQTT() {
#if USE_DHT == true
    String tempDHT; 
    String humDHT; 
    float h = dht.readHumidity(); 
    float t = dht.readTemperature(); 
    if (isnan(t) || isnan(h))  {
      Serial.println("Failed to read from DHT");
      tempDHT = "tErr"; 
      humDHT = "hErr"; 
    }
    else {
      float hic = dht.computeHeatIndex(t, h, false);
      tempDHT = String(hic, 1); 
      humDHT = String(h, 1); 
      Serial.print("Temperature: "); Serial.print(tempDHT); Serial.print("°C"); Serial.print(". Humidity: "); Serial.print(humDHT); Serial.println("%");     
    }
    tempDHT.toCharArray(mqttData, (tempDHT.length()+1));
    mqttClient.publish(mqtt_pub_temp.c_str(), mqttData, true); //  
    humDHT.toCharArray(mqttData, (humDHT.length()+1));
    mqttClient.publish(mqtt_pub_hum.c_str(), mqttData, true); // 
#endif //DHT
#if USE_BME280 == true
    String tempBME = String(bme280.readTempC()); 
    String humBME = String(bme280.readHumidity());
    String pressBME = String(bme280.readPressure());
    Serial.print("Temperature: "); Serial.print(tempBME); Serial.print("°C"); Serial.print(". Humidity: "); Serial.print(humBME); Serial.print("%");
    Serial.print(". Pressure: ");Serial.print(pressBME); Serial.println("hPa");
    tempBME.toCharArray(mqttData, (tempBME.length()+1));
    mqttClient.publish(mqtt_pub_temp.c_str(), mqttData, true); //  
    humBME.toCharArray(mqttData, (humBME.length()+1));
    mqttClient.publish(mqtt_pub_hum.c_str(), mqttData, true);    
    pressBME.toCharArray(mqttData, (pressBME.length()+1));
    mqttClient.publish(mqtt_pub_press.c_str(), mqttData, true);        
#endif //BME280   
  }
#endif
