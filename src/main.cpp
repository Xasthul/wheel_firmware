#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define NUM_SPEED_SAMPLES 5 // Number of samples to average for smoothing

const char *ssid = "DAYAHOM_Stuff";
const char *password = "11092022";

const int udp_port = 5685; // port to listen to

AsyncUDP udp;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool shouldDisplay = false;
float speedSamples[NUM_SPEED_SAMPLES]; // Array to store speed samples for smoothing
int sampleIndex = 0;                   // Index to store the current sample
int roundedSpeed = 0;                  // Rounded speed value

void connectWifi()
{
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}

void listenUDP(int port)
{
  if (udp.listen(port))
  {
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
    udp.onPacket([](AsyncUDPPacket packet)
                 {
      float speed;

      memcpy(&speed, packet.data() + 256, sizeof(float)); // Extract speed data from packet

      // Store the speed sample in the array
      speedSamples[sampleIndex] = speed;
      sampleIndex = (sampleIndex + 1) % NUM_SPEED_SAMPLES;

      // Calculate the average of the speed samples for smoothing
      float totalSpeed = 0;
      for (int i = 0; i < NUM_SPEED_SAMPLES; i++) {
        totalSpeed += speedSamples[i];
      }
      float smoothedSpeed = totalSpeed / NUM_SPEED_SAMPLES;

      // Round the smoothed speed to the nearest integer
      roundedSpeed = round(smoothedSpeed * 3.6);

      // Set the flag to indicate that display should be updated
      shouldDisplay = true; });
  }
}

void setup()
{
  Serial.begin(115200);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  connectWifi();
  listenUDP(udp_port);
}

void loop()
{
  if (shouldDisplay)
  {
    // Clear the display buffer
    display.clearDisplay();

    // Set text size, color and print the speed in the center of the display buffer
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor((SCREEN_WIDTH - (5 * 8 * 2)) / 2, (SCREEN_HEIGHT - 16) / 2); // Center text
    display.print(roundedSpeed);
    display.print(" km/h");

    // Display the content on the OLED
    display.display();
    shouldDisplay = false; // Reset the flag
  }
}