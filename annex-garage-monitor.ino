///*
// * @author jennellew
// * 
// * ANNEX GARAGE MONITOR
// */
//
//#include <Bridge.h>
//#include <BridgeServer.h>
//#include <BridgeClient.h>
//#include <Process.h>
//#include <avr/pgmspace.h>
//
///* CHANGE NUMBER OF GARAGES HERE */
//#define GARAGES 2
//
//const static char TIMESTAMP_CMD[] = "date +%r;Y%m%d-%r";
//const static char DISK_USAGE[]="df -h | grep '/mnt/sda1' | awk '{print $3,$2,int($5)}'";
//const static char REBOOT[]="reboot";
//
//// Listen on default port 5555, the webserver on the Yun
//// will forward there all the HTTP requests for us.
//BridgeServer server;
//
///*  
// *  INPUT PINS FOR GARAGE DOOR SENSORS
// *  ADD OR REMOVE VARIABLES HERE
// *  Note: I keep these variables to save processing for constructing JSON with sensor readings. Feel free to edit for cleaner code.
// */
//static const byte sensor0 = 2;
//static const byte sensor1 = 3;
//
///*
// * INPUT PINS FOR GARAGE DOOR SENSOR, OUTPUT PINS FOR GARAGE DOOR MOTOR
// * ADD OR REMOVE PINS HERE 
// */
//static const byte sensorPins[GARAGES] = {2, 3};
//static const byte motorPins[GARAGES] = {53, 51};
//
//void setup() {
//  // Delay required for Linux side to boot up after remote rebooting from web portal 
//  delay(7500);
//  
//  Serial.begin(9600);
//  
//  // Bridge startup
//  for (int i = 0; i < GARAGES; i++) {
//    pinMode(sensorPins[i], INPUT_PULLUP);
//    pinMode(motorPins[i], OUTPUT);
//  }
//  Bridge.begin();
//
//  // Listen for incoming connection only from localhost
//  // (no one from the external network could connect)
//  server.listenOnLocalhost();
//  server.begin();
//}
//
//void loop() {
//  // Get clients coming from server
//  BridgeClient client = server.accept();
//
//  // Check for new client
//  if (client) {
//
//    // Check if client has sent a command to Arduino
//    String command = client.readStringUntil('/');
//    command.trim();
//    
//    // Activates garage motor and closes door
//    if (command == "motor") {
//
//      //int motor = client[strlen(client) - 1] - '0';
//      byte motor = client.parseInt();
//
////      Serial.println(motor);
////      Serial.print("sensor ");
////      Serial.println(digitalRead(sensorPins[motor]));
//
//      // Check if garage door is open - want to prevent accidental opening instead of closing
//      if (digitalRead(sensorPins[motor])) { 
//        digitalWrite(motorPins[motor], HIGH);
//        delay(300);
//        digitalWrite(motorPins[motor], LOW);
//      }
//
//      // Construct JSON header
//      client.println(F("Status:200"));
//      client.println(F("content-type:application/json"));
//      client.println();
//      client.println("{");
//
//      //close
//      client.println("}");
//    }
//
//    // Sends the results of garage door sensors to web portal
//    else if (command == "inputs") {
//
//      // Construct JSON header
//      client.println(F("Status:200"));
//      client.println(F("content-type:application/json"));
//      client.println();
//      client.println("{");
//      
//      /* loop (if required) */
//      client.print(F("\"sensor0\":"));
//      client.print(digitalRead(sensor0));
//      client.println(F(","));
//      
//      client.print(F("\"sensor1\":"));
//      client.print(digitalRead(sensor1));
//      
//      
//      //close
//      client.println("}");
//    }
//
//    // Sends the remaining disk space on SD card to web portal
//    else if (command == "storage") {
//      Process diskUsage;
//
//      // Query disk usage and return in the format of "[Disk Used] [Disk Total] [% Used]
//      diskUsage.runShellCommand(DISK_USAGE);
//      while (diskUsage.running());
//      String parsedUsage;
//      while (diskUsage.available()) {
//        char c = diskUsage.read();
//        parsedUsage.concat(c);
//      }
//      parsedUsage.trim();
//      
//      // Send back new screenshot name
//      client.println(F("Status:200"));
//      client.println(F("content-type:application/json"));
//      client.println();
//      client.println("{");
//      
//      /* loop (if required) */
//      client.print(F("\"usage\":\""));
//      client.print(parsedUsage);
//
//      //close
//      client.println("\"}");
//  
//      diskUsage.close();
//    }
//
//    // Fully reboots the Arduino Yun (both Linux + Arduino)
//    else if (command == "reboot") {
//      Process restart;
//      restart.runShellCommand(REBOOT);  
//    }
//
//    // Close connection and free resources.
//    client.stop();
//  }
//
//  delay(50); // Poll every 50ms
//}
//

