#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // Detected I2C address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "FOOTBALL_EXT_2.4G";
const char* password = "cities3976";

void drawHappyFace(int x, int y) {
  display.fillCircle(x, y, 20, SSD1306_WHITE);  // Face circle
  display.fillCircle(x, y, 12, SSD1306_BLACK);  // Smile base
  display.fillCircle(x, y-3, 12, SSD1306_WHITE);  // Smile cover (leaves crescent)
  display.fillCircle(x-7, y-6, 2, SSD1306_BLACK);   // Left eye
  display.fillCircle(x+7, y-6, 2, SSD1306_BLACK);  // Right eye
}

void drawSadFace(int x, int y) {
  display.fillCircle(x, y, 20, SSD1306_WHITE);  // Face circle
  display.fillCircle(x, y+12, 10, SSD1306_BLACK); // Frown base
  display.fillCircle(x, y+15, 10, SSD1306_WHITE); // Frown cover (leaves crescent mouth pointing down)
  display.fillCircle(x-7, y-6, 2, SSD1306_BLACK);   // Left eye
  display.fillCircle(x+7, y-6, 2, SSD1306_BLACK);  // Right eye
}

bool pingGoogle() {
  WiFiClient client;
  Serial.println("Pinging (connecting to) google.com:80...");
  if (client.connect("google.com", 80)) {
    Serial.println("Ping successful!");
    client.stop();
    return true;
  }
  Serial.println("Ping failed.");
  return false;
}

void setup() {
  Serial.begin(115200);

  // Initialize I2C with SDA on D2 (GPIO 4) and SCL on D1 (GPIO 5)
  Wire.begin(4, 5); 

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0, 0);     
  display.println(F("Connecting to:"));
  display.println(ssid);
  display.println(F(""));
  display.print(F("Connecting"));
  drawSadFace(96, 32);
  display.display();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("Connecting to:"));
    display.println(ssid);
    display.println(F(""));
    display.print(F("Connecting"));
    for (int i = 0; i < (counter % 4); i++) {
      display.print(F("."));
    }
    display.println(F(""));
    drawSadFace(96, 32);
    display.display();
    counter++;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Show connected screen (with sad face first while checking connection to Google)
  display.clearDisplay();
  display.setCursor(0, 4);     
  display.println(F("Hi Glenn,"));
  display.println(F("how can i"));
  display.println(F("help you;"));
  display.println(F(""));
  display.print(F("IP: "));
  display.println(WiFi.localIP().toString());
  display.println(F("Checking ping..."));
  drawSadFace(96, 32);
  display.display();

  // Try to ping Google
  bool pingSuccess = pingGoogle();

  // Clear and update screen
  display.clearDisplay();
  display.setCursor(0, 8);     
  display.println(F("Hi Glenn,"));
  display.println(F("how can i"));
  display.println(F("help you;"));
  display.println(F(""));
  display.print(F("IP: "));
  display.println(WiFi.localIP().toString());

  if (pingSuccess) {
    // Show Happy face if Google was pinged successfully
    drawHappyFace(96, 32);
  } else {
    // Keep Sad face if ping failed
    drawSadFace(96, 32);
  }
  
  display.display();
  Serial.println(F("Display and WiFi initialized successfully."));
}

void loop() {
  // Nothing to do in the loop for a static text test
}
