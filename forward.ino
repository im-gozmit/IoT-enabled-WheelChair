float Kp=0,Ki=0,Kd=0;
float error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;
int sensor[5]={0, 0, 0, 0, 0};
int initial_motor_speed=100;

void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);

void setup()
{
 pinMode(9,OUTPUT); //PWM Pin 1
 pinMode(10,OUTPUT); //PWM Pin 2
 pinMode(6,OUTPUT); //Left Motor Pin 1
 pinMode(9,OUTPUT); //Left Motor Pin 2
 pinMode(10,OUTPUT); //Right Motor Pin 1
 pinMode(11,OUTPUT);  //Right Motor Pin 2
 Serial.begin(9600); //Enable Serial Communications
}

void loop()
{
    read_sensor_values();
    calculate_pid();
    motor_control();
}

void read_sensor_values()
{
  sensor[0]=digitalRead(2);
  sensor[1]=digitalRead(3);
  sensor[2]=digitalRead(4);
  sensor[3]=digitalRead(5);
  sensor[4]=digitalRead(7);
  Serial.print(sensor[0]);
  Serial.print("   ");
  Serial.print(sensor[1]);
  Serial.print("   ");
Serial.print(sensor[2]);
  Serial.print("   ");
Serial.print(sensor[3]);
  Serial.print("   ");
Serial.print(sensor[4]);
  Serial.print("\n");

  if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==1))
  error=4;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==1)&&(sensor[4]==1))
  error=3;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==1)&&(sensor[4]==0))
  error=2;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[4]==1)&&(sensor[4]==0))
  error=1;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[4]==0)&&(sensor[4]==0))
  error=0;
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[4]==0)&&(sensor[4]==0))
  error=-1;
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==0))
  error=-2;
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==0))
  error=-3;
  else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==0))
  error=-4;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==0))
    if(error==-4) error=-5;
    else error=5;

}

void calculate_pid()
{
    P = error;
    I = I + previous_I;
    D = error-previous_error;
    
    PID_value = (Kp*P) + (Ki*I) + (Kd*D);
    
    previous_I=I;
    previous_error=error;
}

void motor_control()
{
    // Calculating the effective motor speed:
    int left_motor_speed = initial_motor_speed-PID_value;
    int right_motor_speed = initial_motor_speed+PID_value;
    
    // The motor speed should not exceed the max PWM value
    constrain(left_motor_speed,0,255);
    constrain(right_motor_speed,0,255);
  
  analogWrite(6,initial_motor_speed-PID_value);   //Left Motor Speed
    analogWrite(10,initial_motor_speed+PID_value);  //Right Motor Speed
    //following lines of code are to make the bot move forward
    /*The pin numbers and high, low values might be different
    depending on your connections */
    analogWrite(9,0);
    analogWrite(11,0);
 //   digitalWrite(A2,LOW);
   // digitalWrite(A3,HIGH);
}
