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
static int lastDistance = 0;
static int distance = 0;
static int hit = 0;

char* Modes[] = {
  "Forward", "Forward Left", "Forward Right", 
  "Backward", "Backward Right", "Backward Right"};

bool DEBUG = false;
int focusTime = 500;
int step = 10;//random(1, 10);
int stabilization = 100;//random(1, 10);
int directionTolerance = 10;
  
// ========== HARDWARE INITIALIZATION AREA ========== //

// You can ignore the colors. 
// They are just to remember where to plug my wires.
// Your wires will have other colors

// Define Servo Motors
Servo myservoVertical;
Servo myservoHorizontal;

// Define ultrasound conections
// green Grnd
// maron 5+
const int trigPin = 4; // Mov
const int echoPin = 2; // Blue

// Dual Bridge Motor Driver
int ENA=11; // YELLOW Left wheel speed
int IN1=10; // ORANGE connected to Arduino's port 2
int IN2=9;  // RED    power motor L
int IN3=8;  // Maron  Start/Stop motor R
int IN4=7;  // BLACK  power motor R
int ENB=6;  // WHITE  Right wheel speed

// ============== GLOBAL VARIABLES AREA ============== //

int directionCorection = 0;
// Returning position
int pos = 90;
// Miliseconds needed for stabilization before every measurement
int stabilizationTime = 40;
// Recorded distances at each degree
int DistanceAt[180];
int mode = 0;
char outputLine[261];
 
void setup() {
pinMode(12,INPUT); // Shock sensor
pinMode(13,OUTPUT); // Shock sensor
 
// ============ PREPARE DRIVER BRIDGE =============== //
 pinMode(ENA,OUTPUT);//output
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 digitalWrite(ENA,LOW);
 digitalWrite(ENB,LOW);//stop driving
 digitalWrite(IN1,LOW); 
 digitalWrite(IN2,HIGH);//setting motorA's directon
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);//setting motorB's directon

// ============ CUSTOM CONFIGURATION AREA ============ //

  // Connect servo motors
  //myservoVertical.attach(3);  // attaches the servo on pin 3 to the servo object
  myservoHorizontal.attach(5);  // attaches the servo on pin 5 to the servo object
  // Connect ultrasound
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // Connect serial only in debug mode
  //if(DEBUG)
  {
    Serial.begin(9600);
  }
}

int MeasureDistance()
{
  Serial.print(lastDistance);
  Serial.print(" ");
  Serial.print(Modes[mode]);
  Serial.print(" ");
  Serial.println(directionTolerance);
  delay(stabilization);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); 
  distance = pulseIn(echoPin, HIGH)*0.034/2; 
  hit = digitalRead(12)-1;
  if(hit)
  {
    Serial.println("* @ $ % ^");
    Back();
  }
  UpdateTolerance(distance);
  return distance;
}

void ScanFromLeftToRight(Servo servo, int step)
{
  for(int i = pos; i < 165; i+=step)
  {
    servo.write(i);    
    DistanceAt[i] = MeasureDistance();
  }
  servo.write(pos);
}

void ScanFromRightToLeft(Servo servo, int step)
{
  for(int i = pos; i > 15; i-=step)
  {
    servo.write(i);
    DistanceAt[i] = MeasureDistance();
  }
  servo.write(pos);
}

void RegularScan(Servo servo)
{
  servo.write(110);
  DistanceAt[0] = MeasureDistance();
  servo.write(70);
  DistanceAt[2] = MeasureDistance();
  servo.write(pos);
  DistanceAt[1] = MeasureDistance();
}

void FullScan()
{
  int randomPreference = random(1, 100);

  if(randomPreference%2 == 1)
  {
    ScanFromLeftToRight(myservoHorizontal, step);
    //delay(focusTime);
    ScanFromRightToLeft(myservoHorizontal, step);
  }
  else
  {
    ScanFromRightToLeft(myservoHorizontal, step);
    //delay(focusTime);
    ScanFromLeftToRight(myservoHorizontal, step);
  }
}

void loop() {
  int distance = MeasureDistance();
  //analogRead(13)
  
  //Serial.println(digitalRead(12));
  if(distance < 40)
  {
    Serial.println("Prepare to hit!");
    digitalWrite(ENB,LOW);//stop driving
    digitalWrite(ENA,LOW);//stop driving
    RegularScan(myservoHorizontal);
    ComputeCorection();
  }
  else
  {
    Serial.println("GO!");
    mode = 0;
    int speed = distance > 175 ? 255 : 80 + distance;
    analogWrite(ENB,speed);//stop driving
    analogWrite(ENA,speed);//stop driving
  }
  if(DEBUG)
  {
     DisplayDistances();
     delay(500);
  }
}

void UpdateTolerance(int distance)
{
  if(distance - lastDistance > -2 && distance - lastDistance < 2)
  {
    directionTolerance--;
    lastDistance = distance;
    if(directionTolerance <= 0)
    {
      Back();
    }
  }
  else
  {
    directionTolerance = random(3,4);
    lastDistance = distance;
  }
}

void Back()
{
  if(distance >= 20 && directionTolerance >= 0)
  {
    Serial.print(".......");
    return;
  }
  Serial.print("back => ");
  //Serial.print(" ");
  //Serial.print(distance);
  digitalWrite(13, HIGH);
    while((distance < 20) || (directionTolerance < 1) || hit)
    {
      int randomPreference = random(1, 100);
      int randomDirection = random(1, 100);
      Serial.print(randomPreference%2);
      Serial.print(":");
      Serial.print(randomDirection%2);
      mode = 3+randomPreference%2+randomDirection%2;
      digitalWrite(IN2,randomDirection%2==0?0:1); 
      digitalWrite(IN1,randomDirection%2==0?1:0);//setting motorA's directon
      digitalWrite(IN4,randomDirection%2==0?0:1);
      digitalWrite(IN3,randomDirection%2==0?1:0);//setting motorB's directon
      analogWrite(ENB,(randomPreference%2 == 1)?0:255);//stop driving
      analogWrite(ENA,(randomPreference%2 == 1)?255:0);//stop driving
      Serial.print(randomDirection==1? "LEFT LEFT": "Right Right");
      Serial.println(randomPreference==1? "FFD":"BWD");
      delay(random(50, 500));
      MeasureDistance();
    }
    Serial.println("----------");
    digitalWrite(IN1,LOW); 
    digitalWrite(IN2,HIGH);//setting motorA's directon
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);//setting motorB's directon
    analogWrite(ENB, LOW);//stop driving
    analogWrite(ENA, LOW);//stop driving
    digitalWrite(13, LOW);
}

int ComputeCorection()
{
  Serial.println("!!!!!!!!!!");
  if(DistanceAt[1] < 20)
  {
    //Step(); 
    if(DistanceAt[0] > DistanceAt[2])
    {
      digitalWrite(ENB,LOW);//stop driving
      analogWrite(ENA,250);//start driving motorA
      mode = 1;
      while(MeasureDistance() < 20)
      {
        Serial.println(">>>>>>");
        delay(30);
      }
      digitalWrite(ENA,LOW);//stop driving
    }
    else
    {
      digitalWrite(ENA,LOW);//stop driving
      analogWrite(ENB,250);//start driving motorA
      mode = 2;
      while(MeasureDistance() < 20)
      {
        Serial.println("<<<<<<");
        delay(30);
      }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             }
      digitalWrite(ENB,LOW);//stop driving
  }
  analogWrite(ENA,LOW);//start driving motorA
  analogWrite(ENB,LOW);//start driving motorA
      
}

void DisplayDistances()
{
    int seriesSize = 3;
    int samples = seriesSize;
    for(int i = 0; i < samples; i++)
    {
      outputLine[i*12+0] = '[';
      outputLine[i*12+1] = (48 + (i*seriesSize/samples)%1000/100);
      outputLine[i*12+2] = (48 + (i*seriesSize/samples)%100/10);
      outputLine[i*12+3] = (48 + (i*seriesSize/samples)%10);
      outputLine[i*12+4] = ':';
      outputLine[i*12+5] = (48 + DistanceAt[i*seriesSize/samples]%10000/1000);
      outputLine[i*12+6] = (48 + DistanceAt[i*seriesSize/samples]%1000/100);
      outputLine[i*12+7] = (48 + DistanceAt[i*seriesSize/samples]%100/10);
      outputLine[i*12+8] = (48 + DistanceAt[i*seriesSize/samples]%10);
      outputLine[i*12+9] = ']';
      outputLine[i*12+10] = ',';
      outputLine[i*12+11] = ' ';
     }
     outputLine[samples*12] = '\n';
     Serial.println(outputLine);
}

void Step()
{
  for(int i = 0; i < 10; i++)
 {
   digitalWrite(IN1,HIGH);//setting motorA's directon
   digitalWrite(IN2,LOW);//setting motorA's directon
  
   digitalWrite(IN3,HIGH);//setting motorA's directon
   digitalWrite(IN4,LOW);//setting motorA's directon
 for(int i = 2; i < 100; i+=i/2)
 {
     analogWrite(ENB,i);//start driving motorA
     analogWrite(ENA,i);//start driving motorA
     //delay(20);
 }
   delay(400);
   
   digitalWrite(IN1,LOW);//setting motorA's directon
   digitalWrite(IN2,HIGH);//setting motorA's directon
   
   digitalWrite(IN3,LOW);//setting motorA's directon
   digitalWrite(IN4,HIGH);//setting motorA's directon
 for(int i = 2; i < 100; i+=i/2)
 {
     analogWrite(ENB,i);//start driving motorA
     analogWrite(ENA,i);//start driving motorA
     //delay(20);
 }
   delay(300);
 }
}

