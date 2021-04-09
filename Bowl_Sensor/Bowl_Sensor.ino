#include <Arduino.h>
#include <HX711.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"

HX711 water;                          // Initiate HX711 library
WiFiClient wifiClient;                // Initiate WiFi library
PubSubClient client(wifiClient);      // Initiate PubSubClient library

void setup() {
  Serial.begin(74880);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting...");

  while (WiFi.status() != WL_CONNECTED) {       // Wait till Wifi connected
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());                     // Print IP address

  client.setServer(MQTT_SERVER, 1883);                // Set MQTT server and port number
  client.setCallback(callback);                       // Set callback address, this is used for remote tare
  water.begin(WATER_DOUT_PIN, WATER_SCK_PIN);         // Start water scale on specified pins
  water.wait_ready();                                 // Ensure water scale is ready, this is a blocking function
  water.set_scale();                                  
  Serial.println("Water Set");
  water.wait_ready();
  water.tare();                                       // Tare scale on startup
  water.wait_ready();
  Serial.println("Water Zeroed");
  food.begin(FOOD_DOUT_PIN, FOOD_SCK_PIN);            // Start food scale on specified pins
  food.wait_ready();                                  // Ensure food scale is ready, this is a blocking function
  food.set_scale();                                  
  Serial.println("Food Set");
  food.wait_ready();
  food.tare();                                       // Tare scale on startup
  food.wait_ready();
  Serial.println("Food Zeroed");
}

void loop() {
  float reading; // Float for reading
  float raw; // Float for raw value which can be useful
  water.wait_ready(); // Wait till water scale is ready, this is blocking if your hardware is not connected properly.
  water.set_scale(calibration_factor);  // Sets the calibration factor.

  // Ensure we are still connected to MQTT Topics
  if (!client.connected()) {
    reconnect();
  }
  
  Serial.print("Reading: ");            // Prints weight readings in .2 decimal kg units.
  water.wait_ready();
  reading = water.get_units(10);        //Read water scale in g/Kg
  raw = water.read_average(5);          //Read raw value from scale too
  Serial.print(reading, 2);
  Serial.println(" kg");
  Serial.print("Raw: ");
  Serial.println(raw);
  Serial.print("Calibration factor: "); // Prints calibration factor.
  Serial.println(calibration_factor);

  if (reading < 0) {
    reading = 0.00;     //Sets reading to 0 if it is a negative value, sometimes loadcells will drift into slightly negative values
  }

  String value_str = String(reading);
  String value_raw_str = String(raw);
  client.publish(WATER_STATE_TOPIC, (char *)value_str.c_str());               // Publish weight to the WATER_STATE topic
  client.publish(WATER_STATE_RAW_TOPIC, (char *)value_raw_str.c_str());       // Publish raw value to the WATER_STATE_RAW topic

  client.loop();          // MQTT task loop
  water.power_down();    // Puts the scale to sleep mode for 3 seconds. I had issues getting readings if I did not do this
  delay(3000);
  water.power_up();
}

void reconnect() {
  while (!client.connected()) {       // Loop until connected to MQTT server
    Serial.print("Attempting MQTT connection...");
    if (client.connect(HOSTNAME, mqtt_username, mqtt_password)) {       //Connect to MQTT server
      Serial.println("connected"); 
      client.publish(AVAILABILITY_TOPIC, "online");         // Once connected, publish online to the availability topic
      client.subscribe(TARE_TOPIC);       //Subscribe to tare topic for remote tare
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);  // Will attempt connection again in 5 seconds
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, TARE_TOPIC) == 0) {
    Serial.println("starting tare...");
    water.wait_ready();
    water.set_scale();
    water.tare();       //Reset water scale to zero
    Serial.println("Water reset to zero");
  }
}
