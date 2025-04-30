#define EN_A 6 
#define IN_1 4
#define IN_2 5
void forward(){
  digitalWrite(IN_2, HIGH);
  digitalWrite(IN_1, LOW);
}
void backward(){
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
}
void setMotor(int speed){
  speed > 0 ? forward() : backward();
  analogWrite(EN_A, abs(speed));
}
void setup() {
  // put your setup code here, to run once:
  pinMode(EN_A, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  Serial.begin(2000000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!Serial.available()) return;
  String command = Serial.readString();
  long speed = (command.toInt() * 0xFF) / 100;
  setMotor(speed);
  Serial.print("Set speed ");
  Serial.println(speed);
}
