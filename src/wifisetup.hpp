// Network credentials
const char* ssid = "Starlight-BMC";
const char* password = "lamparita.7";

IPAddress ip(192, 168, 7, 7);
IPAddress gateway(192, 168, 7, 7);
IPAddress subnet(255, 255, 255, 0);


void setupWiFi() {
  WiFi.mode(WIFI_AP);
  while(!WiFi.softAP(ssid, password)) {
    Serial.println("Creating AP...");
    delay(1000);
  }
  // Configure static IP
  WiFi.softAPConfig(ip, gateway, subnet);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

}