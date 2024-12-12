

int Echo1 = A4; //left_sensor echo
int Trig1 = A5; //left_sensor trig
int Echo2 = A2; //central_sensor echo
int Trig2 = A3; //central_sensor trig
int Echo3 = A0; //right_sensor echo
int Trig3 = A1; //right_sensor trig

int in1 = 6;//pin 6 arduino
int in2 = 5;//pin 5 arduino
int in3 = 4;//pin 4 arduino
int in4 = 3;//pin 3 arduino
int ENA = 7;//pin 7 arduino
int ENB = 2;//pin 2 arduino
int PWM = 150;//ATUR KECEPATAN 10 SAMPAI 255
int Left_Distance = 0,Right_Distance = 0,Middle_Distance = 0 ;
void _Forward()
{

digitalWrite(in1,HIGH);//maju
digitalWrite(in2,LOW);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
analogWrite(ENA,PWM);
analogWrite(ENB,PWM);
Serial.println("cm");
}
void _Back()
{

digitalWrite(in1,LOW);//mundur
digitalWrite(in2,HIGH);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);
analogWrite(ENA,PWM);
analogWrite(ENB,PWM);
Serial.println("cm\t\t");
}
void _left()
{

digitalWrite(in1,LOW);//belok kiri
digitalWrite(in2,HIGH);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
analogWrite(ENA,PWM);
analogWrite(ENB,PWM);
Serial.println("cm\t\t");
}
void _right()
{

digitalWrite(in1,HIGH);//belok kanan
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);
analogWrite(ENA,PWM);
analogWrite(ENB,PWM);
Serial.println("cm\t\t");
}
void _Stop()
{
digitalWrite(in1,LOW);//stop
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW);
Serial.println("cm\t\t");
}
/*Ultrasonic distance measurement Sub function*/
int Left_Distance_test()
{
digitalWrite(Trig1, LOW);
delayMicroseconds(2);
digitalWrite(Trig1, HIGH);
delayMicroseconds(20);
digitalWrite(Trig1, LOW);
float Fdistance = pulseIn(Echo1, HIGH);
delay(10);

Fdistance= Fdistance/ 29 / 2;
return (int)Fdistance;
}
int Middle_Distance_test()
{
digitalWrite(Trig2, LOW);
delayMicroseconds(2);
digitalWrite(Trig2, HIGH);
delayMicroseconds(20);
digitalWrite(Trig2, LOW);
float Fdistance = pulseIn(Echo2, HIGH);
delay(10);
Fdistance= Fdistance/ 29 / 2;
return (int)Fdistance;
}
int Right_Distance_test()
{
digitalWrite(Trig3, LOW);
delayMicroseconds(2);
digitalWrite(Trig3, HIGH);
delayMicroseconds(20);
digitalWrite(Trig3, LOW);
float Fdistance = pulseIn(Echo3, HIGH);
delay(10);
Fdistance= Fdistance/ 29 / 2;
return (int)Fdistance;
}
void setup()
{
Serial.begin(9600);
pinMode(Echo1, INPUT);
pinMode(Trig1, OUTPUT);
pinMode(Echo2, INPUT);
pinMode(Trig2, OUTPUT);
pinMode(Echo3, INPUT);
pinMode(Trig3, OUTPUT);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
pinMode(ENA,OUTPUT);
pinMode(ENB,OUTPUT);

_Stop();
}
void loop()
{
Left_Distance = Left_Distance_test();
delay(10);
Middle_Distance = Middle_Distance_test();
delay(10);
Right_Distance = Right_Distance_test();
delay(10);
Serial.println("Left_Distance\tMiddle_Distance\tRight_Distance\tStatus\n");
Serial.print(Left_Distance);
Serial.print("cm\t\t");
Serial.print(Middle_Distance);
Serial.print("cm\t\t");
Serial.print(Right_Distance);
Serial.print("cm\t\t");
if(Middle_Distance<=80)
{
/* _Stop();
delay(1000);*/

if(Right_Distance>Left_Distance)
{
if((Right_Distance<=30)&&(Left_Distance<=30))
{_Stop();
delay(200);
_Back();
delay(2000);

}
else{
// _Back();
// delay(2000);
_right();
delay(500);}

}
else if(Right_Distance<Left_Distance)
{
if((Right_Distance<=30)&&(Left_Distance<=30))

{_Stop();
delay(200);
_Back();
delay(1000);
}
else{
// _Back();
// delay(3000);
_left();
delay(500);
}
}
}
else if(Right_Distance<=30)
{
_left();
delay(500);
}

else if(Left_Distance<=30)
{
_right();
delay(500);
}
else{
_Forward();
}
//delay(500);
}
