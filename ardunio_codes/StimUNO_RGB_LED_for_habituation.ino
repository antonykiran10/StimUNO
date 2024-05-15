
int x;
#define red 9
#define green 10
#define blue 11
int t = 2000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(1);
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(12, LOW);
  analogWrite(red, 255);
  analogWrite(green, 255);
  analogWrite(blue, 255);
  while (Serial.available()){
    x = Serial.readString().toInt();
    Serial.print(1);
    digitalWrite(12, HIGH);
    analogWrite(green, 0);
    analogWrite(blue, 0);
    while (!Serial.available());
    x = Serial.readString().toInt();
    Serial.print(1);
  }
}
