
int x;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(1);
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(12, LOW);
  while (Serial.available()){
    x = Serial.readString().toInt();
    Serial.print(1);
    digitalWrite(12, HIGH);
    while (!Serial.available());
    x = Serial.readString().toInt();
    Serial.print(1);
  }
}
