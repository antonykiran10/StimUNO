// For applying solenoid stimulus and use the signal from the
// vibration sensor to light an LED.
// Detected 2.5msec delay from the time sensor signal comes on to the
// time that the LED turns ON
//
//char foo;            // required to clean up some other problems
int  DETECT = A0; //Piezo sensor analog input
int  LED1 = 7;    //IR LED or TTL to camera can be connected. Turns on when piezo crosses threshold.
int  LED2 = 8;    //ON when the solenoid is triggered.
int  SOLENOID = 4; //Solenoid connected here and controlls it via relay
//int  STRT=1;
int  N = 3;   //Number of piezo signals to be averaged
long MN = 0;  //Accumulator for baseline piezo value
long MNV = 0; //Accumulator for piezo detection
int tmp;      //Temprorary variable to read in piezo value.

void setup() {
  //  Serial.begin(9600);
  pinMode(DETECT, INPUT);   //Piezo input
  pinMode(LED1, OUTPUT);  //IR LED or TTL to camera (will glow on receiving input from piezo)
  pinMode(LED2, OUTPUT);  //Solenoid indicator
  //  pinMode(STRT,OUTPUT);
  pinMode(SOLENOID, OUTPUT);  //
  digitalWrite(LED1, LOW);  //Off  the vibration detection(piezo)
  digitalWrite(LED2, LOW);  //Off  the vibration detection (solenoid)
  digitalWrite(SOLENOID, LOW);  //Off  the solenoid current
  delay(750);  //Delay 6 seconds
  MN = 0; //Mean initialized to zero
  for (int n = 0; n < 10; n++) //For finding mean
  {
    MN = MN + analogRead(DETECT); //Accumulating for mean
  }
  MN = MN / 10; //Averaging  find mean baseline
}

//8msc per count. So for 50000 counts it will be 40sec.
void loop() {
  digitalWrite(SOLENOID, HIGH); //ON the solenoid
  digitalWrite(LED2, HIGH);  //On LED for experimenter
  MNV = 0; //Assigning the mean baseline
  while (MNV < 50  )   //Detection of deviation of threshold=40 above the mean baseline
  {
    MNV = 0; //Initializing the accumulator
    for (int n = 0; n < N; n++) //Averaging N readings
    {
      tmp = MN - analogRead(DETECT);
      MNV = MNV + abs(tmp); //Accumulating the sensor reading
      //           Serial.println(MNV);
    }
    MNV = MNV / N; //Averaging the sensor reading
    //          Serial.println(abs(MNV-MN));
    //          Serial.println(MNV);
    //          Serial.println(0);
    delay(1);  //For stability
  }
  digitalWrite(LED1, HIGH);  //On IR LED   / TTL

  delay(50);  //For stability
  digitalWrite(SOLENOID, LOW); //Off the solenoid
  digitalWrite(LED2, LOW);  //Off LED for experimenter
  digitalWrite(LED1, LOW);  //Off IR LED
  //        delay(1000);  //Delay 1 second
  delay(10000);  //Delay 10 seconds
}
