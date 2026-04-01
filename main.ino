#include <WiFi.h>
#include <HTTPClient.h>
#include <TFT_eSPI.h>  // Libreria per display ESP32-DIV

// =======================
// WiFi Credentials
// =======================
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// =======================
// Telegram Bot Settings
// =======================
String botToken = "YOUR_BOT_TOKEN";
String chatID  = "YOUR_CHAT_ID";

// =======================
// Pin Configuration
// =======================
const int pirPin = 13;      // PIR sensor output
const int buzzerPin = 12;   // Optional buzzer

// =======================
// Display Setup
// =======================
TFT_eSPI tft = TFT_eSPI();  // Create display object
TFT_eSprite sprite = TFT_eSprite(&tft);

// =======================
// System Variables
// =======================
bool motionDetected = false;
unsigned long lastTriggerTime = 0;
const unsigned long cooldown = 10000; // 10 seconds

// =======================
// Function: Send Telegram Message
// =======================
void sendTelegramMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + botToken +
                 "/sendMessage?chat_id=" + chatID +
                 "&text=" + message;
    http.begin(url);
    http.GET();
    http.end();
  }
}

// =======================
// Display Update Functions
// =======================
void showSafe() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(3);
  tft.setCursor(20, tft.height()/2 - 20);
  tft.println("SAFE");
}

void showAlert() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.setTextSize(3);
  tft.setCursor(20, tft.height()/2 - 20);
  tft.println("ALERT");
}

// =======================
// Setup
// =======================
void setup() {
  Serial.begin(115200);

  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Initialize display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi: " + String(WiFi.localIP()));

  // Show initial SAFE state
  showSafe();

  // Notify system is online
  sendTelegramMessage("System armed and ready.");
}

// =======================
// Loop
// =======================
void loop() {
  int pirSignal = digitalRead(pirPin);

  // Motion detected
  if (pirSignal == HIGH && !motionDetected && (millis() - lastTriggerTime > cooldown)) {
    motionDetected = true;
    lastTriggerTime = millis();

    Serial.println("Motion detected (signal from PIR)");

    // Activate buzzer
    digitalWrite(buzzerPin, HIGH);

    // Update display
    showAlert();

    // Send notification
    sendTelegramMessage("Alert: Motion detected!");
  }

  // Motion ended
  if (pirSignal == LOW && motionDetected) {
    motionDetected = false;

    Serial.println("No motion (signal cleared)");

    digitalWrite(buzzerPin, LOW);

    // Update display
    showSafe();
  }

  delay(200);
}
