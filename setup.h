/***************************************************
 *  Name:        setup
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Setup for the Arduino.           
 *
 ***************************************************/

  /* Boot-time OTA */

WebServer server(80);

  /* Server Index Page */

    const char* serverIndex =
    "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
    "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
    "<input type='file' name='update'>"
    "<input type='submit' value='Update'>"
    "</form>"
    "<div id='prg'>progress: 0%</div>"
    "<script>"
    "$('form').submit(function(e){"
    "e.preventDefault();"
    "var form = $('#upload_form')[0];"
    "var data = new FormData(form);"
    " $.ajax({"
    "url: '/update',"
    "type: 'POST',"
    "data: data,"
    "contentType: false,"
    "processData:false,"
    "xhr: function() {"
    "var xhr = new window.XMLHttpRequest();"
    "xhr.upload.addEventListener('progress', function(evt) {"
    "if (evt.lengthComputable) {"
    "var per = evt.loaded / evt.total;"
    "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
    "}"
    "}, false);"
    "return xhr;"
    "},"
    "success:function(d, s) {"
    "console.log('success!')"
    "},"
    "error: function (a, b, c) {"
    "}"
    "});"
    "});"
    "</script>";


int BATT_PULSE = 12;
 //  const int ledPin = 13; // useful on-board LED
  /* Setup outputs */
 

TaskHandle_t Task0;

void codeForTask0(void * parameter)
{
  for(;;){
    // code to pulse battery load on Core 0
   
    Serial.print("\n[info] Pulse Core 0 High");
    digitalWrite(BATT_PULSE, HIGH);
    delay(1400);
    Serial.print("\n[info] Pulse Core 0 Low");
    digitalWrite(BATT_PULSE, LOW);
    delay(5000);
       
  }
}

void setupCores(){
  xTaskCreatePinnedToCore(
    codeForTask0,
    "Task_0",
    1000,
    NULL,
    1,
    &Task0,
    0);
    
  delay(500);
  pinMode (BATT_PULSE, OUTPUT);
}




void setup() {

  setupCores();

Wire.begin();  //batt test
  /* Initialise serial */
    
    Serial.begin(115200);
  
  /* Setup inputs */

   ///////////////////////////////////////// rtc_clk_cpu_freq_set(RTC_CPU_FREQ_80M); // 80mhz cpu clock
    Serial.print("\n[init] Booting..\n[init] Configuring WDT");
    esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
    esp_task_wdt_add(NULL); //add current thread to WDT watch
  


  /* Boot-time connection to WiFi */
 
    esp_wifi_init; // wifi psave
    btStop(); // disable bluetooth 
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR); // psave light  
    Serial.print("\n[info] First time connect attempt to SSID: ") + String(Serial.print(WIFI_SSID));
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.print("\n[fail] Connection Failed!...");  
    esp_task_wdt_init(9, true);
    Serial.print("\n[fail] No WiFi, setting watchdog of 10 secs. Reset."); 
    delay(10000);
    }
    char buf[16]; sprintf(buf, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3] );
    Serial.print("\n[ ok ] WiFi connected. IP address: " + (String)buf + ", RSSI: " + (String)WiFi.RSSI()+"db");

  /* return index page which is stored in serverIndex */

    server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
    });
 
  /* handling uploading firmware file */
  
    server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
    }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
    Serial.printf("Update: %s\n", upload.filename.c_str());
    if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
    Update.printError(Serial);
    }
    } else if (upload.status == UPLOAD_FILE_WRITE) {

  /* flashing firmware */
    
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
    }
    } else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) { //true to set the size to the current progress
    Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
    } else {
    Update.printError(Serial);
    }
    }
    });
  
    server.begin();
    Serial.print("\nTelegram Command Bot, Version: "+(String)majorVersion+"."+(String)minorVersion)+"\n"; 
    }
    
    int ii = 0; // WDT

    
