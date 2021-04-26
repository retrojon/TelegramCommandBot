void handleNewMessages(int numNewMessages)  { // Check for recent messages

    IRsend irsend; 
    
    Serial.print("\nNew message ") + (String(numNewMessages));
    for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    Serial.print(text);

    String from_name = bot.messages[i].from_name;
    
    if (from_name == "")
   
    from_name = "Guest";

  /* Reboot ESP32 option */
   
    if (text == "/ESPreset") {
      
    esp_task_wdt_init(10, true);
    Serial.print(", Sent: ESP reboot in 10s\n[info] Set watchdog timer to 10s, now rebooting...");
    bot.sendMessage(chat_id, "ESP reboot in 10s ", ""); }

  /* OTA */
  
    if (text == "/OTA") {
      
//    digitalWrite(ledPin, LOW);
    OTAon = true;
    Serial.print(", Sent: OTA Active");
    Serial.print("\n[warn] OTA active on HTTP port 80");
    bot.sendMessage(chat_id, "OTA Active", ""); }  


  /* Get WiFi IP option */

    if (text == "/GetWifiIP") {

    char buf[16]; sprintf(buf, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3] );
    Serial.print("\nWiFi IP address: " + (String)buf);
    bot.sendMessage(chat_id, "Wifi IP: " + String(buf), ""); }

  /* Get WiFi IP option */

    if (text == "/Batt") {

       Serial.print("\nBattery %: ");

}
    
    

  /* Get WiFi Signal Strength dB option */
  
    if (text == "/GetWifiRSSI") {
      
    Serial.print(", Sent: "+(String)WiFi.RSSI()+"dB rssi.");
    bot.sendMessage(chat_id, "Wifi RSSI: " + String(WiFi.RSSI()), ""); }

  /* Toggle IR Led on P4 option */
    
    if (text == "/IRtoggle") {
  
    const char yamahaVolDown[] PROGMEM // Humax IR Code [Power button]
    = "0000 006C 0022 0002 015B 00AD " /* Pronto header + start bit */
      "0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 " /* Lower address byte */
      "0016 0016 0016 0016 0016 0016 0016 0016 0016 0041 0016 0016 0016 0016 0016 0016 " /* Upper address byte (inverted at 8 bit mode) */
      "0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 " /* command byte */
      "0016 0041 0016 0041 0016 0041 0016 0041 0016 0041 0016 0041 0016 0041 0016 0041 0016 0726 " /* inverted command byte + stop bit */
      "015B 0057 0016 0E6C"; /* NEC repeat pattern*/
      irsend.sendPronto(yamahaVolDown, NUMBER_OF_REPEATS);       
      Serial.print(", Sent: IRLed is toggled. Sending IR signal at pin " + String(IR_SEND_PIN));
      
      bot.sendMessage(chat_id, "IR Led toggled", ""); }

  /* Fetch time from ntp server {unix epoch} option */
  
    if (text == "/GetTime") {
   
    configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
    time_t now = time(nullptr);
    while (now < 24 * 3600) {
    delay(100);
    now = time(nullptr); }
    String myString = String(now);
    time (& now); // read the current time
    localtime_r (& now, & tm); // update the structure tm with the current time
    String epochconverted = String(tm.tm_mday) + ("\/") + (tm.tm_mon + 1) + ("\/") + (tm.tm_year + 1900) + ("-") + (tm.tm_hour) + ("\:") + (tm.tm_min) + ("\:") + (tm.tm_sec);
    Serial.print(", Sent: ");
    Serial.print(String(epochconverted));
    bot.sendMessage(chat_id, String(epochconverted), ""); }

  /* Ping option */
   
    if (text == "/Ping") {
    Ping.ping(ip);
    Serial.print(", Sent: " + String(Ping.averageTime())+"ms");
    bot.sendMessage(chat_id, String(Ping.averageTime())+"ms", ""); }

  /* CPU option */
   
    if (text == "/KeepAlive") {
    Serial.print(", Sent: Stayin' Alive "); 
    bot.sendMessage(chat_id, "Stayin' Alive ", "");
    secondTimer.reset();    
    Serial.print("\n[info] will stay online for longer");
    flagy1 = true; // kill 1st-timer
    flagy2 = false; // hopefully now ignore timer1 loop 
    }

  /* spare option */
   
    if (text == "/spare") {
    }

  /* Homepage options */

    if (text == "/start") {

    String welcome = "Hello " + from_name + ",\n";
    welcome += "\n";
    welcome += "Telegram Command Bot, Version: ";
    welcome += (String)majorVersion + "." + (String)minorVersion + "\n";
    welcome += "\n";
    welcome += "List of available commands:\n\n";
    welcome += "/IRtoggle - Toggle the Humax IR power\n";
    welcome += "\n";
    welcome += "/GetTime - Fetch from a NTP server\n";
    welcome += "\n";
    welcome += "/Ping - Ping Humax\n";
    welcome += "\n";
    welcome += "/GetWifiRSSI - Check WIFI Signal\n";
    welcome += "\n";
    welcome += "/GetWifiIP - WIFI local IP\n";
    welcome += "\n";
    welcome += "/ESPreset - Reboot within 10 secs\n";
    welcome += "\n";
    welcome += "/OTA - HTTP OTA\n";
    welcome += "\n";
    welcome += "/KeepAlive - Don't fall asleep for 60 mins\n";
    bot.sendMessage(chat_id, welcome, "Markdown"); 
    Serial.print(", Sent: {Welcome screen}"); } } }
