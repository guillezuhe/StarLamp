AsyncWebServer server(80);

void setupServer() {


  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.on("/setStarType", [](AsyncWebServerRequest *request) {
    if (request->hasArg("type")) {
      int type = request->arg("type").toInt();
      stateManager.setStarType(type);
      //request->send(200, "text/plain", "Star type set to " + String(type));
      request->redirect("/");
    } else {
      request->send(400, "text/plain", "Missing 'type' parameter");
    }
  });

  server.on("/setBrightness", [](AsyncWebServerRequest *request) {
    if (request->hasArg("value")) {
      int value = request->arg("value").toInt();
      // Transform from absolute magnitude to brightness percentage
      value = - 10 / 3 * value + 200 / 3; // Linear mapping from [-10, +20] to [100, 0]
      stateManager.setBrightness(value);
      FastLED.setBrightness(value);
      //request->send(200, "text/plain", "Brightness set to " + String(value));
      request->redirect("/");
    } else {
      request->send(400, "text/plain", "Missing 'value' parameter");
    }
  });

  server.on("/setNoiseStr", [](AsyncWebServerRequest *request) {
    if (request->hasArg("value")) {
      float value = request->arg("value").toFloat();
      // Transform from Rossby number to noise strength
      // First linearize from [0.1, 10] to [-1, 1]
      value = log10(value);
      // Then map to [0, 75] and convert to int
      value = -75 / 2 * value + 75 / 2;
      stateManager.setNoiseStr((int)value);
      //request->send(200, "text/plain", "Noise strength set to " + String(value));
      request->redirect("/");
    } else {
      request->send(400, "text/plain", "Missing 'value' parameter");
    }
  });
  server.begin();
}