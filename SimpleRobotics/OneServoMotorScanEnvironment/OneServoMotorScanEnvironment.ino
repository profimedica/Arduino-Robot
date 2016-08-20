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

//Servo myservoVertical;
Servo myservoHorizontal;

int pos = 90;

void setup() {
  //myservoVertical.attach(3);  // attaches the servo on pin 3 to the servo object
  myservoHorizontal.attach(5);  // attaches the servo on pin 5 to the servo object
}

void ScanFromLeftToRight(Servo servo, int speed)
{
  for(int i = pos; i < 180; i+=speed)
  {
    speed = pos/50*3;
    servo.write(i);
    delay(20);
  }
  servo.write(pos);
}

void ScanFromRightToLeft(Servo servo, int speed)
{
  for(int i = pos; i > 0; i-=speed)
  {
    speed = pos/50*3;
    servo.write(i);
    delay(20);
  }
  servo.write(pos);
}

void loop() {
  int focusTime = 3600;
  int randomSpeed = random(1, 10);
  int randomPreference = random(1, 100);

  if(randomPreference%2 == 1)
  {
    ScanFromLeftToRight(myservoHorizontal, randomSpeed);
    //delay(focusTime);
    ScanFromRightToLeft(myservoHorizontal, randomSpeed);
  }
  else
  {
    ScanFromRightToLeft(myservoHorizontal, randomSpeed);
    //delay(focusTime);
    ScanFromLeftToRight(myservoHorizontal, randomSpeed);
  }
  delay(focusTime);
}
