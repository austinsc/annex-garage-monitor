#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>
#include <ArduinoJson.h>

#define NUMBER_OF_DOORS 2
#define NUMBER_OF_LIGHTS 2

int doors[NUMBER_OF_DOORS] = {53, 49};
int lights[NUMBER_OF_LIGHTS] =  {51, 47};
int relays[8] = {53, 51, 49, 47, 45, 43, 41, 39};
BridgeServer server;
StaticJsonBuffer<200> jsonBuffer;

void setup() {
  for(int i = 0; i < 8; i++) {
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], HIGH);
  }
    
  // Initialize the bridge
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  BridgeClient client = server.accept();
  String command = client.readStringUntil('/');
  command.trim();
  
  client.println(F("Status:200"));
  client.println(F("content-type:application/json"));
  client.println();

  if(command == "motor") {
    int door = client.parseInt();    
    client.println("{");
    client.println("}");
    trigger(doors[door]);
  } else if(command == "lights") {    
    client.println("{");
    client.println("}");
    for(int i = 0; i < NUMBER_OF_LIGHTS; i++) {
      trigger(lights[i]);
    }
  } else if (command == "inputs") {
      client.println("{");
      client.print(F("\"sensor0\":"));
      client.print(HIGH);
      client.println(F(","));      
      client.print(F("\"sensor1\":"));
      client.print(LOW);
      client.println("}");
    }

  client.stop();
  delay(10);
}

void trigger(int relay) {
  digitalWrite(relay, LOW);
  delay(100);
  digitalWrite(relay, HIGH);
}

void toggle(int relay, bool value) {  
  digitalWrite(relay, value ? LOW : HIGH);
}

