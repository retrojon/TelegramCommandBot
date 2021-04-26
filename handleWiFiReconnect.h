void handleWiFiReconnect() {

    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    // if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {

    Serial.print("\n[fail] Reconnecting to WiFi"); //serial debug
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(2500);
    char buf[16]; sprintf(buf, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3] );
    Serial.print("\n[ ok ] WiFi connected. IP address: " + (String)buf + ", RRSI: " + (String)WiFi.RSSI()); } }
