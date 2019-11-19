var langEN = {
	header:"LED Screen with weather informer",
    save:"Save",
	save1:"Save",
	save2:"Save",
	save3:"Save",
	save4:"Save",
	saveSet:"Set",
    setWiFi:"Setting wifi",
    setTime:"Setting time",
    setMqtt:"Configuring mqtt",
    setWeather:"Setting weather",
    setLed:"Setting display",
    help:"Help",
    reset:"Restart device",
    do:"to:",
    lang:"Language",
	//-- index
	P_wifi_title:"WIFI setup",
	P_wifi_informer:"Connecting to the internet network will allow you to synchronize the time and receive a weather forecast.",
	P_wifi_setWiFi:"Connecting to WiFi router",
    P_wifi_ssid:"Enter the name of the WiFi network",
	P_wifi_password:"Enter the WiFi network password",
	P_wifi_setAP:"Access Point Parameters (IP_192.168.4.1)",
    P_wifi_ssidAP:"Enter the name of the access point",
	P_wifi_passwordAP:"Enter the access point password",
	P_wifi_setSSDP:"Device name in LAN", //*****************
	P_wifi_ssdp:"Enter the name of SSDP",
    //-- time
    P_time_title:"Time setting",
	P_time_informer:"Now:",
	P_time_set:"Set time",
	P_time_setNTP:'The exact NTP time server',
    P_time_adressNTP:"Enter the NTP server address",
	P_time_usesync:"Set synchronization with NTP server",
	P_time_timeZone:"Choose a time zone",
	P_time_daylight:"Daylight Saving Time",
    P_time_save:"Belt out of PC and saving",
	P_time_sync:"Time synchronization",
    P_time_alarm:"Alarm clock",
    P_time_number:"Number",
    P_time_hour:"Hours",
    P_time_minute:"Minutes",
	P_time_sec:"Seconds",
    P_time_set2:"Settings",
	P_date_set:"Set date",
	P_time_day:"Day",
	P_time_month:"Month",	
	P_time_year:"Year",	
    //-- weather
    P_weather_title:"Setting the weather",
	P_weather_informer:"To obtain the weather forecast,",
    P_weather_linkAPI:"here we take the API key,",
    P_weather_linkID:"but here we find the cityID of our city.",
    P_weather_server:"Weather Server",
	P_weather_key:"API weather key",
    P_weather_ID:"ID of the City",
	P_weather_outForecast:"Display of weather forecast",
    P_weather_timeScrollStart:"Display a running line, with:",
    P_weather_timeScrollSpeed:"Treadmill speed",
	P_weather_update:"Update weather forecast",
    //-- setup
    P_setup_title:"Settings screen",
	P_setup_speed:"Speed of creeping line",
	P_setup_brightness:"Regular brightness",
    P_setup_dmfrom:"Day mode with:",
	P_setup_dmto:"to:",
	P_setup_brightday:"Brightness during the day:",
    P_setup_brightnight:"at night:",
	P_setup_vba:"Automatic brightness level",
    P_setup_clockNight:"Show only watches at night",
	P_setup_font:"Font",
    //-- led
    P_led_title:"Screen setting",
	P_led_set:"Show",
	P_led_weather:"Weather",
	P_led_forecast:"Weather forecast",
	P_led_clock:"Current time",
	P_led_date:"Current date",
	P_led_sea:"Sea temperature",
	P_led_infOn:"On",
	P_led_infFrom:"From",
	P_led_infTo:"To",		
	P_led_texts:"Text on the screen",
	P_led_textOn:"On",
	P_led_textFrom:"From",
	P_led_textTo:"to",
	P_led_textCrL:"Creeping line",
	P_led_text:"Text",
	P_led_textsOnOff:"Working hours",
	P_led_textstart:"From",
	P_led_textstop:"to",
	P_led_THP:"Temp., hum., press. onboard",	
    //-- help
    P_help_title:"If something went wrong ...",
	P_help_informer1:"ATTENTION!!! Some changes can be irreversible !!!",
    P_help_informer2:"If you have entered something wrong and can not change it, then return the device to factory settings. The configuration file will be deleted. Device rebooted!",
	P_help_conf:"Open the configuration file",
	P_help_html:"Download HTML files",
    //P_help_com:"Display information in the COM port",
	P_help_update:"Update: select and download the firmware (bin)",
    P_help_upload:"download",
    P_help_wait:"Wait...",
    restart:"Back to factory settings",
    //-- mqtt
    P_mqtt_title:"Configure MQTT",
	P_mqtt_informer:"Configure the MQTT server. You can use an external server, for example: ",
    P_mqtt_mqttOn:"Use MQTT server",
	P_mqtt_set:"Connection to MQTT server:",
    P_mqtt_server:"MQTT server address",
	P_mqtt_port:"MQTT Server Port",
    P_mqtt_user:"Server user login",
	P_mqtt_pass:"Server User Password",
    P_mqtt_setESP:"Configuring ESP",
	P_mqtt_name:"Device name (ESP)",
	P_mqtt_sub_inform:"Topic for inform message",
    P_mqtt_pub_temp:"Temperature publication",
    P_mqtt_pub_hum:"Humidity publication",
	P_mqtt_pub_press:"Pressure publication",
	P_get_sensor:"Update data from sensors",
		//----thingspeak
	P_tspeak_title:"Configure transmit data to external server",	
	P_tspeak_informer:"Configure the external server for transmit temperature, humidity, pressure, for example:",
	P_tspeak_mqttOn:"Use server",
	P_tspeak_server:"Server address",
	P_tspeak_channal:"Channal ID",
	P_tspeak_wapi:"API key for write"	
}