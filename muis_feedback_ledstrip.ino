// pin assignments
int LDR = 0;

int timer = 0;
 
// initialize the serial port
// and declare inputs and outputs
void setup() {
  pinMode(LDR, INPUT);
  Serial.begin(9600);

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  // initialize digital pin 12 as an output.
  pinMode(12, OUTPUT);

  // initialize digital pin 11 as an output.
  pinMode(11, OUTPUT);
  
}
 
// read from the analog input connected to the LDR
// and print the value to the serial port.
// the delay is only to avoid sending so much data
// as to make it unreadable.
void loop() {
  int v = analogRead(LDR);
  Serial.print("Sterkte: ");
  Serial.println(v);
  delay(500);
  if (v >= 600) {
    // hand niet op de muis
    if (timer > 10000) {
      timer = 10000;
    }
    else if (timer < 1000) {
    }
    else {
      timer -= 1000;
    }
  } else {
    // hand wel op de muis
    timer += 500;
  }
  Serial.print("timer: ");
  Serial.println(timer);

  if (timer < 10000) { 
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else {
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  }

  if (timer < 7000) {
    digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else {
    digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
  }

  if (timer < 4000) {
    digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else {
    digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
  }
}
