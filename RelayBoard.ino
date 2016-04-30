#define BUTTON1 4
#define RELAY1 53
#define RELAY2 51
#define RELAY3 49
#define RELAY4 47
#define RELAY5 45
#define RELAY6 43
#define RELAY7 41
#define RELAY8 39
#define btnState = 0;

void setup() {
  pinMode(BUTTON1, INPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);
  pinMode(RELAY6, OUTPUT);
  pinMode(RELAY7, OUTPUT);
  pinMode(RELAY8, OUTPUT);

  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);
  digitalWrite(RELAY5, HIGH);
  digitalWrite(RELAY6, HIGH);
  digitalWrite(RELAY7, HIGH);
  digitalWrite(RELAY8, HIGH);
  
  trigger(RELAY1);
  trigger(RELAY2);
  trigger(RELAY3);
  trigger(RELAY4);
  trigger(RELAY5);
  trigger(RELAY6);
  trigger(RELAY7);
  trigger(RELAY8);
}

void loop() {
//  btnState = digitalRead(BUTTON1);
//  digitalWrite(RELAY1, btnState == HIGH ? LOW : HIGH);
  
  delay(5000);
}

void trigger(int relay) {
  digitalWrite(relay, LOW);
  delay(50);
  digitalWrite(relay, HIGH);
  delay(1000);
}
