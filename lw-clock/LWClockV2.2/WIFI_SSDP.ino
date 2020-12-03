void SSDP_init(void) {
  HTTP.on("/description.xml", HTTP_GET, []() {
    SSDP.schema(HTTP.client());
  });
  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName(SSDP_Name);
  SSDP.setSerialNumber("001788102201");
  SSDP.setURL("/");
  SSDP.setModelName(nName);
  SSDP.setModelNumber(nVersion);
  SSDP.setModelURL("http://"+(WiFi.status() != WL_CONNECTED ? WiFi.softAPIP() : WiFi.localIP()));
  SSDP.setManufacturer("LIGHTWELL");
  SSDP.setManufacturerURL("https://led-lightwell.eu");
  SSDP.begin();
}
