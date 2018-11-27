#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <PubSubClient.h>         //MQTT
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
 
////**********START CUSTOM PARAMS******************//
 
//Define parameters for the http firmware update
const char* host = "MqttSwitch"; // This is the name of the AP that will be created for setup.
const char* update_path = "/WebFirmwareUpgrade"; // leave as is
const char* update_username = "<yourPreferredUsername>"; // this is the user you want to use to login to the wemos to set it up
const char* update_password = "<yourPreferredPassword>"; // this is the password you want to use to set up the wemos.
 
//Define the pins
#define RELAY_PIN 5
#define CONFIG_TRIGGER_PIN 3
 
//Define MQTT Params. If you don't need to 
#define mqtt_server "<TheIPOfYourMQTTServer>" // this is the IP of the mqtt server the wemos will connect to
#define switch_topic "MqttSwitch/switch" // This is the name of the mqtt topic.  I recommend just changing the part before the forward slash.
#define mqtt_sub "MqttSwitch/#" // this is the topic your wemos will subscribe to.  Just change the first part to match what you have above.
const char* mqtt_user = "<yourMQTTServierUser>"; // this is the user you use to connect to MQTT
const char* mqtt_pass = "yourMQTTServerPassword"; // this is the password you use to connect to MQTT.
 
//************END CUSTOM PARAMS********************//
//This can be used to output the date the code was compiled
const char compile_date[] = __DATE__ " " __TIME__;
 
//Setup the web server for http OTA updates. 
ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
 
WiFiClient espClient;
 
//Initialize MQTT
PubSubClient client(espClient);
 
//Setup Variables
String switch1;
String strTopic;
String strPayload;
 
//Wifi Manager will try to connect to the saved AP. If that fails, it will start up as an AP
//which you can connect to and setup the wifi
WiFiManager wifiManager;
long lastMsg = 0;
 
void setup() {
  //Set Relay(output) pins
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  pinMode(CONFIG_TRIGGER_PIN, INPUT);
 
  Serial.begin(115200);
 
  //Set the wifi config portal to only show for 3 minutes, then continue.
  wifiManager.setConfigPortalTimeout(180);

  if (!wifiManager.autoConnect(host)) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
 
  //sets up the mqtt server, and sets callback() as the function that gets called
  //when a subscribed topic has data
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); //callback is the function that gets called for a topic sub
 
  //setup http firmware update page.
  MDNS.begin(host);
  httpUpdater.setup(&httpServer, update_path, update_username, update_password);
  httpServer.begin();
  MDNS.addService("http", "tcp", 80);
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local%s in your browser and login with username '%s' and your password\n", host, update_path, update_username);
}
 
void loop() {
  //If MQTT client can't connect to broker, then reconnect
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); //the mqtt function that processes MQTT messages
  httpServer.handleClient(); //handles requests for the firmware update page
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  //if the topic has a payload "ON", then turn on the relay
  payload[length] = '\0';
  strTopic = String((char*)topic);
  
  if (strTopic == switch_topic)
  {
    switch1 = String((char*)payload);
    
    if (switch1 == "ON")
    {
      //turn on the relay
      Serial.println("ON");
      digitalWrite(RELAY_PIN, HIGH);
    }
    else if (switch1 = "OFF")
    {
      Serial.println("OFF");
      digitalWrite(RELAY_PIN, LOW);
    }
    else
    {
      // otherwise default to off for safety.
      Serial.println("Unknown topic or switch state, turning off");
      digitalWrite(RELAY_PIN, LOW);
      client.publish(switch_topic, "OFF");
    }
  }
}
 
void reconnect() {
  //Reconnect to Wifi and to MQTT. If Wifi is already connected, then autoconnect doesn't do anything.
  wifiManager.setConfigPortalTimeout(180);

  if (!wifiManager.autoConnect(host)) {
    Serial.println("failed to connect, we should reset and see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  Serial.print("Attempting MQTT connection...");
  if (client.connect(host, mqtt_user, mqtt_pass)) {
    Serial.println("connected");
    client.subscribe(mqtt_sub);
  } else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
    // Wait 5 seconds before retrying
    delay(5000);
  }
}
