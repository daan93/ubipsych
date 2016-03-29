int index = 0;
boolean locked = true;
int[] clickCode = {LEFT,LEFT,RIGHT,RIGHT,LEFT,LEFT,RIGHT,RIGHT};
int[] locks = {0,0,0,0,0,0,0,0};

import processing.serial.*; //import the Serial library
 Serial myPort;  //the Serial port object
 String val;
// since we're doing serial handshaking, 
// we need to check if we've heard from the microcontroller
boolean firstContact = false;

void setup() {
  size(600,200);
  //  initialize your serial port and set the baud rate to 9600
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n'); 
}


void draw() {
  for (int i = 0; i < 8; i ++) {
    if (locks[i] == 0) {
      fill(255,0,0);
      locked = true;
    }
    else {
      fill(0,255,0);
      locked = false;
    }
    int x = i * 60 + 25;
    rect(x,25,50,50);
  }
}

void mouseClicked() {
  if (index < 8) {
    if (mouseButton == clickCode[index]) {
      locks[index] = 1;
      index++;
    }
  }
}

void serialEvent( Serial myPort) {
//put the incoming data into a String - 
//the '\n' is our end delimiter indicating the end of a complete packet
val = myPort.readStringUntil('\n');
//make sure our data isn't empty before continuing
if (val != null) {
  //trim whitespace and formatting characters (like carriage return)
  val = trim(val);
  println(val);

  //look for our 'A' string to start the handshake
  //if it's there, clear the buffer, and send a request for data
  if (firstContact == false) {
    if (val.equals("A")) {
      myPort.clear();
      firstContact = true;
      myPort.write("A");
      println("contact");
    }
  }
  else { //if we've already established contact, keep getting and parsing data
    println("recieving "+val);

    if (locked == false) 
    {                           //if locked is false
      myPort.write('1');        //send a 1
      println("sending 1");
    }
    if (locked == true) 
    {                           //if locked is true
      myPort.write('0');        //send a 0
      println("sending 0");
    }

    // when you've parsed the data you have, ask for more:
    myPort.write("A");
    }
  }
}