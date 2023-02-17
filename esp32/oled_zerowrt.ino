#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

WiFiClient client;  // or WiFiClientSecure for HTTPS
HTTPClient http;

// create what ever variables you need
double volts;
double bvolts;

// these are a required variables for the graphing functions
bool Redraw1 = true;
bool Redraw2 = true;
bool Redraw3 = true;
bool Redraw4 = true;
double ox , oy ;
double ox1 , oy1 ;

// create the display object
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Label
const char* label = "ZeroWrt";

// WIFI Config
const char* ssid = "ZeroWrt";
const char* password = "zerodev123";
const char* hostname = "ESP-1";

// URL Config
const char* serverUrl = "http://192.168.2.1:8080/api";

unsigned char wifi1_icon4[] =
{
  0b00000000, 0b00000000, //                 
  0b00000111, 0b11100000, //      ######     
  0b00011111, 0b11111000, //    ##########   
  0b00111111, 0b11111100, //   ############  
  0b01110000, 0b00001110, //  ###        ### 
  0b01100111, 0b11100110, //  ##  ######  ## 
  0b00001111, 0b11110000, //     ########    
  0b00011000, 0b00011000, //    ##      ##   
  0b00000011, 0b11000000, //       ####      
  0b00000111, 0b11100000, //      ######     
  0b00000100, 0b00100000, //      #    #     
  0b00000001, 0b10000000, //        ##       
  0b00000001, 0b10000000, //        ##       
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
};

 unsigned char wifi1_icon3[] =
{
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //    
  0b00000000, 0b00000000, //    
  0b00000000, 0b00000000, //    
  0b00000000, 0b00000000, //  
  0b00000111, 0b11100000, //      ######  
  0b00001111, 0b11110000, //     ########    
  0b00011000, 0b00011000, //    ##      ##   
  0b00000011, 0b11000000, //       ####      
  0b00000111, 0b11100000, //      ######     
  0b00000100, 0b00100000, //      #    #     
  0b00000001, 0b10000000, //        ##       
  0b00000001, 0b10000000, //        ##       
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
};


 unsigned char wifi1_icon2[] =
{
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //          
  0b00000000, 0b00000000, //        
  0b00000000, 0b00000000, //      
  0b00000011, 0b11000000, //       ####      
  0b00000111, 0b11100000, //      ######     
  0b00000100, 0b00100000, //      #    #     
  0b00000001, 0b10000000, //        ##       
  0b00000001, 0b10000000, //        ##       
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
};

 unsigned char wifi1_icon1[] =
{
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //          
  0b00000000, 0b00000000, //        
  0b00000000, 0b00000000, //      
  0b00000000, 0b00000000, //             
  0b00000000, 0b00000000, //           
  0b00000000, 0b00000000, //          
  0b00000001, 0b10000000, //        ##       
  0b00000001, 0b10000000, //        ##       
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
};

 unsigned char wifi1_icon0[] =
{
  0b00000000, 0b00000000, //                 
  0b00000000, 0b00000000, //                 
  0b00111000, 0b00001110, //   ###       ### 
  0b00111100, 0b00011110, //   ####     #### 
  0b00111110, 0b00111110, //   #####   ##### 
  0b00011111, 0b01111100, //    ##### #####  
  0b00001111, 0b11111000, //     #########   
  0b00000111, 0b11110000, //      #######    
  0b00000011, 0b11100000, //       #####     
  0b00000111, 0b11110000, //      #######    
  0b00001111, 0b11111000, //     #########   
  0b00011111, 0b01111100, //    ##### #####  
  0b00111110, 0b00111110, //   #####   ##### 
  0b00111100, 0b00011110, //   ####     #### 
  0b00111000, 0b00001110, //   ###       ### 
  0b00000000, 0b00000000, //                 
};

//Offline Mode
int timeNow = 0;
int timeOut = 20;
boolean offlineMode = false;

void setup() {

  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
    
  initWiFi();
}

// Setup WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(hostname);
  WiFi.begin(ssid, password);
  display.clearDisplay();
  showBanner(label);

  display.setTextSize(1);             
  display.setTextColor(WHITE);        
  display.setCursor(0,20);             
  display.println("Connecting to WiFi ..");
  display.display();
  offlineMode = false;
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    timeNow += 1;
    if (timeNow == timeOut) {
      break;
    }
    delay(1000);
  }
  if (WiFi.status() != WL_CONNECTED){
    offlineMode == true;
  }else {
    offlineMode == false;
  }
}

void loop(void) {
  display.clearDisplay();
  showBanner(label);
  showBarWifi();

  String response = httpGETRequest(serverUrl);
  JSONVar responseObject = JSON.parse(response);

  // validate JSON
  if (JSON.typeof(responseObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }

  if (responseObject.hasOwnProperty("data")) {
    String upload = String(((double)responseObject["data"]["traffic_upload"])/1024);
    String download = String(((double)responseObject["data"]["traffic_download"])/1024);
    String cpu = String((int)responseObject["data"]["cpu"]);
    String ram = String((int)responseObject["data"]["ram"]);
    int uptime = (int)responseObject["data"]["uptime"];

    showTraffic(upload, download);
    showCPURAM(cpu, ram);
    showUptime(uptime);
  }

  display.display();
  delay(1000);
}

// SHOW BANNER
void showBanner(String label){
  display.fillRect(0, 0,  127 , 14, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(2, 4);
  display.println(label);
}

// SHOW TRAFFIC
void showTraffic(String up, String down){
  display.setCursor(55,33);             
  display.println("U: " + up+ "Mb/s");

  display.setCursor(55,43);             
  display.println("D: " + down + "Mb/s");
}

// SHOW CPU & RAM
void showCPURAM(String cpu, String ram){
  display.setCursor(0,33);             
  display.println("CPU: " + cpu+ "%");

  display.setCursor(0,43);             
  display.println("RAM: " + ram + "%");
}

// SHOW Uptime
void showUptime(int totalSec){
  display.setCursor(0,53);             
  display.println("Uptime: " + secToTime(totalSec));
}

// Show Bar Wifi
void showBarWifi() {
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  if (WiFi.status() == WL_CONNECTED){
      if (WiFi.RSSI() >= -50){
      display.drawBitmap(0, 15, wifi1_icon4, 16, 16, 1);
      }else if ((WiFi.RSSI() < -50) &&  (WiFi.RSSI() > -70)){
        display.drawBitmap(0, 15, wifi1_icon3, 16, 16, 1);
      }else if ((WiFi.RSSI() < -70) &&  (WiFi.RSSI() > -80)){
        display.drawBitmap(0, 15, wifi1_icon2, 16, 16, 1);
      }else {
        display.drawBitmap(0, 15, wifi1_icon1, 16, 16, 1);
      }
      display.setCursor(18,18 );             
      display.println(WiFi.localIP());
    }else{
      offlineMode = true;
      display.setCursor(4,20);             
      display.println("Offline Mode");
    }
}

// Utils HTTP GET REQUEST
String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  http.begin(client, serverName);
  
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();

  return payload;
}

// Utils Sec to Time String
String secToTime(int totalSecond) {
  int hour = totalSecond / 3600;
  int minute = (totalSecond % 3600) / 60;
  int second = totalSecond % 60;

  return (String)hour + ":" + (String)minute + ":" + (String)second;
}
