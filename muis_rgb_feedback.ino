
char data; // Data received from the serial port
int signal=A0;
int value=0;
int redPin=10;
int greenPin=11;
int bluePin=12;
int rood = 0;
int counter = 0;
 
bool ledState = false; // state variable for the LED

void setup()
{
  Serial.begin(9600);          // opens serial port, sets data rate to 9600 bps
  establishContact();          // send a byte to establish contact until receiver responds 
  pinMode(signal,INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  digitalWrite(redPin, ledState);
  digitalWrite(greenPin, ledState);
  digitalWrite(bluePin, ledState);
}
void loop()
{

  if (Serial.available() > 0) { // If data is available to read,
    data = Serial.read(); // read it and store it in data
    Serial.println(data);

    if(data == '1') //if we get a 1
    {
      Serial.println("Mouse unlocked");
      delay(500);
      value=analogRead(signal);
      Serial.println(value);
      delay(500);
    
      //Conditions for different colors
      if (value>1020)
      {
        Serial.println("Green");
        setColor(0, 255, 0);  // green
        counter = 0; // reset counter
      }
      else if (value<= 1020)
      {
        counter += 1000; // update counter
        Serial.print("Counter: ");
        Serial.println(counter);
        if (counter < 10000) {
          setColor(0,0,255);  // blue
          Serial.println("Blue");
        }
        else {
          setColor(255,0,0); // red
          Serial.println("Red");
        }
      }
    }
    if(data == '0') //if we get a 0
    {
      Serial.println("mouse locked");
      counter = 0; // reset counter
        
      delay(100);
    }
   
  }
}
  

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("A");   // send a capital A
  delay(300);
  }
}



