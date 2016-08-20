/* Cumpanasu Florin
 *  Some nice moves of a 2 axis head
 *  Just connect the vertical axe servo and horizontal axe servo
 *  Build for 180 degree servos
 *  On Funduino(Asduino) 
 *  Amtel atmega328p Xplained mini
 *  AVRISP Mkll programmer
 * GitHub: https://github.com/profimedica 
 * StackOverflow: http://stackoverflow.com/users/1001199/profimedica
 * VisualStudio: https://profimedica.visualstudio.com/
 * LinkdIn: https://www.linkedin.com/in/florincumpanasu
 * Painting: https://www.facebook.com/paintalbum
*/

#include <Servo.h>

Servo myservoVertical;
Servo myservoOrizontal;

int pos = 0;

void setup() {
  myservoVertical.attach(3);  // attaches the servo on pin 3 to the servo object
  myservoOrizontal.attach(5);  // attaches the servo on pin 3 to the servo object
  pinMode(PIN_LED_13, OUTPUT);
  delay(5000);
}

void loop() {
  int program = random(0, 20);
  int groundLevel = 50;
  delay(random(0, 50));
  if(program > 16)
  {
    bool isInitialized = false;
    int randomUp = random(80, 100);
    for (pos = groundLevel; pos <= randomUp; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservoVertical.write(pos);              // tell servo to go to position in variable 'pos'
      if(pos%5 == 0)
      digitalWrite(PIN_LED_13, HIGH);   // turn the LED on (HIGH is the voltage level)
      if(!isInitialized)
      {
        for(int i=0; i < 5; i++)
        {
          digitalWrite(PIN_LED_13, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(20);
          digitalWrite(PIN_LED_13, LOW);    // turn the LED off by making the voltage LOW
          delay(10);
        }
        isInitialized = true;
      }
      delay(100);                       // waits 15ms for the servo to reach the position
      digitalWrite(PIN_LED_13, LOW);    // turn the LED off by making the voltage LOW
    }
    for (pos = randomUp; pos >= groundLevel; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservoVertical.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  if(program == 15)
  {
    delay(random(100, 1000));
  }
  if(program == 1)
  {
    int randomLeft = random(50, 80);
    int randomRight = random(50, 80);
    for (pos = randomLeft; pos <= randomRight; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservoOrizontal.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = randomRight; pos >= randomLeft; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservoOrizontal.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  if(program == 5)
  {
    int randomLeft = random(100, 120);
    int randomRight = random(100, 120);
    for (pos = randomLeft; pos <= randomRight; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservoOrizontal.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = randomRight; pos >= randomLeft; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservoOrizontal.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  if(program > 1 && program < 5)
  {
    int randomLeft = 105;
    int randomRight = 100;
    for (pos = randomLeft; pos <= randomRight; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservoOrizontal.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = randomRight; pos >= randomLeft; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservoOrizontal.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  if(program == 0)
  {
    int randomLeft = 105;
    int randomRight = 120;
    for (pos = randomLeft; pos <= randomRight; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservoOrizontal.write(pos);              // tell servo to go to position in variable 'pos'
      delay(30);                       // waits 15ms for the servo to reach the position
    }
    for (pos = randomRight; pos >= randomLeft; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservoOrizontal.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15ms for the servo to reach the position
    }
  }
  if(program > 5 && program <10)
  {
    int randomUp = random(groundLevel, 90);
    for (pos = groundLevel; pos <= randomUp; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservoVertical.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = randomUp; pos >= groundLevel; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservoVertical.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  else
  {
    int randomLeft = random(50, 80);
    int randomRight = random(50, 80);
    for (pos = randomLeft; pos <= randomRight; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservoOrizontal.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = randomRight; pos >= randomLeft; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservoOrizontal.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}
