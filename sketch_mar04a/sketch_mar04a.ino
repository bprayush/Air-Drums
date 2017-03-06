void setup()
{
  Serial.begin(9600);
  pinMode(3, INPUT);  
  pinMode(5, INPUT);
  pinMode(6, INPUT);
}

int threshold = 20;
int pin1;
int pin2;
int pin3;

void loop()
{
  char ch = Serial.read();

  pin1 = getData(3);
  pin2 = getData(5);
  pin3 = getData(6);  

  if(pin1 > 99)
    pin1 = 99;
  if(pin2 > 99)
    pin2 = 99;
  if(pin3 > 99)
    pin3 = 99;


  if(pin1 <= threshold)
  {
      Serial.print('a');
      if(pin1 < 10)
        Serial.print(0);
      Serial.print(pin1);
 // Serial.println("-------------------pin 3------------------");
  }
  if(pin2 <= threshold)
  {
    Serial.print('b');
    if(pin2 < 10)
        Serial.print(0);
    Serial.print(pin2);
  }
  //Serial.println("-------------------pin 5------------------");
  if(pin3 <= threshold)
  {
    Serial.print('c');
    if(pin3 < 10)
        Serial.print(0);
    Serial.print(pin3);
  }

  delay(250);
  //Serial.println("-------------------pin 6------------------");

  
}

int getData(int pingPin)
{
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  /*
  if(cm >=10 && cm <=99)
    Serial.print(0);
  else if(cm < 10)
  {
    Serial.print(0);
    Serial.print(0);
  }
  Serial.print(cm);
  */
  return cm;
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
