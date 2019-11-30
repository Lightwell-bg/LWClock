var langRU = {
	header:"LED табло с информацией о погоде",
    save:"Сохранить", //Для нескольких кнопок на странице
	save1:"Сохранить",
	save2:"Сохранить",
	save3:"Сохранить",
	save4:"Сохранить",
	saveSet:"Установить",
    setWiFi:"Настройка wifi",
    setTime:"Настройка времени",
    setMqtt:"Настройка mqtt",
    setWeather:"Настройка погоды",
    setLed:"Настройка экрана",
    help:"Помощь",
    reset:"Перезагрузить устройство",
    do:"до:",
    lang:"Язык",
	//-- index
	P_wifi_title:"НАСТРОЙКА WIFI",
	P_wifi_informer:"Подключение к сети internet позволит синхронизировать время и получать прогноз погоды.",
	P_wifi_setWiFi:"Подключение к WiFi роутеру",
    P_wifi_ssid:"Введите имя WiFi сети",
	P_wifi_password:"Введите пароль WiFi сети",
	P_wifi_setAP:"Параметры точки доступа (IP_192.168.4.1)",
    P_wifi_ssidAP:"Введите имя точки доступа",
	P_wifi_passwordAP:"Введите пароль точки доступа",
	P_wifi_setSSDP:"Имя устройства в локальной сети", //**********************
	P_wifi_ssdp:"Введите имя SSDP",
    //-- time
    P_time_title:"Настройка времени",
	P_time_informer:"Время на устройстве: ",
	P_time_set:"Установка времени",
	P_time_setNTP:'Установка NTP сервера',
    P_time_adressNTP:"Введите адрес сервера",
	P_time_usesync:"Использовать синхронизацию с NTP сервером",
	P_time_timeZone:"Укажите часовой пояс",
	P_time_daylight:"Переход на летнее время",
    P_time_save:"Автоопределение часового пояса",
	P_time_sync:"Синхронизировать время",
    P_time_alarm:"Будильник",
    P_time_number:"Номер",
    P_time_hour:"Часы",
    P_time_minute:"Минуты",
	P_time_sec:"Секунды",
    P_time_set2:"Установка",
	P_date_set:"Установка даты",
	P_time_day:"День",
	P_time_month:"Месяц",
	P_time_year:"Год",
    //-- weather
    P_weather_title:"Настройка погоды",
	P_weather_informer:"Для получения прогноза погоды,",
    P_weather_linkAPI:"здесь берём API ключ,",
    P_weather_linkID:"а здесь находим cityID своего города.",
    P_weather_server:"Сервер погоды",
	P_weather_key:"Ключ погоды API",
    P_weather_ID:"ID Города",
	P_weather_outForecast:"Отображение прогноза погоды",
    P_weather_timeScrollStart:"Отображать бегущую строку с:",
    P_weather_timeScrollSpeed:"Скорость бегущей строки",
	P_weather_update:"Обновить прогноз погоды",
	P_sea_informer:"Для получения температуры морской воды,",
	P_sea_linkAPI:"здесь берем код (ID) города",
	P_sea_cityID:"Город",	
    //-- setup
    P_setup_title:"Настройки устройства",
	P_setup_speed:"Скорость бегущей строки",
	P_setup_brightness:"Обычная яркость",
    P_setup_dmfrom:"Дневной режим с:",
    P_setup_dmto:"до:",	
	P_setup_brightday:"Яркость днем:",
    P_setup_brightnight:"ночью:",
	P_setup_vba:"Автоматический уровень яркости",
    P_setup_clockNight:"Отображать ночью только часы",
    P_setup_dailySignal:"Ежечасный сигнал с:",
	P_setup_font:"Шрифт",
    //-- led
    P_led_title:"Настройки экрана",
	P_led_set:"Показывать",
	P_led_weather:"Погоду",
	P_led_forecast:"Прогноз погоды",
	P_led_clock:"Часы",
	P_led_date:"Дату",
	P_led_sea:"Температуру моря",
	P_led_infOn:"Вкл",
	P_led_infFrom:"От",
	P_led_infTo:"До",	
	P_led_texts:"Текст на экране",
	P_led_textOn:"Вкл",
	P_led_textFrom:"От",
	P_led_textTo:"До",
	P_led_textCrL:"Бег. строка",
	P_led_text:"Текст",
	P_led_textsOnOff:"Время работы табло",
	P_led_textstart:"от",
	P_led_textstop:"до",
	P_led_THP:"Темп., влаж., давл. на борту",
    //-- help
    P_help_title:"Если что-то пошло не так...",
	P_help_informer1:"ВНИМАНИЕ!!! Некоторые изменения могут быть необратимыми!!!",
    P_help_informer2:"Если вы что-то не верно ввели и не можете этого изменить, то верните устройство к заводским настройкам. Файл конфигурации будет удален. Устройство перезагружено",
	P_help_conf:"Открыть файл конфигурации",
	P_help_html:"Загрузка файлов HTML",
    //P_help_com:"Отображать информацию в СОМ порт",
	P_help_update:"Обновление: виберите и загрузите прошивку (bin)",
    P_help_upload:"загрузить",
    P_help_wait:"Подождите...",
    restart:"Вернуться к заводским установкам",
        //-- mqtt
    P_mqtt_title:"Настройка MQTT",
	P_mqtt_informer:"Выполните настройку MQTT сервера. Вы можете использовать внешний сервер, например: ",
    P_mqtt_mqttOn:"Использовать MQTT сервер",
	P_mqtt_set:"Подключение к MQTT серверу:",
    P_mqtt_server:"Адрес MQTT сервера",
	P_mqtt_port:"Порт MQTT сервера",
    P_mqtt_user:"Логин пользователя сервера",
	P_mqtt_pass:"Пароль пользователя сервера",
    P_mqtt_setESP:"Настройка ESP",
	P_mqtt_name:"Название устройства (ESP)",
	P_mqtt_sub_inform:"Топик информ сообщений",
    P_mqtt_pub_temp:"Топик публикации температуры",
    P_mqtt_pub_hum:"Топик публикации влажности",
	P_mqtt_pub_press:"Топик публикации давления",
	P_get_sensor:"Обновить показания датчиков",
		//----thingspeak
	P_tspeak_title:"Настройка передачи данных на сервер",	
	P_tspeak_informer:"Выполните настройку внешнего сервера для передачи и отображения температуры, влажности, давления. Например:",
	P_tspeak_mqttOn:"Использовать передачу данных на сервер",
	P_tspeak_server:"Адрес сервера",
	P_tspeak_channal:"Канал передачи данных",
	P_tspeak_wapi:"API ключ для записи"
}