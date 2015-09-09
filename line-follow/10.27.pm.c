// connect motor controller pins to Arduino digital pins

// motor left
int enL = 5;
int motor_A= 22;
int motor_B = 23;

// motor right
int enR = 6;
int motor_C = 24;
int motor_D = 25;

//led array
int s[]={1,2,3,4,5};//Analog pin A1 to A5 
int cut = 50;

//pwm
int pwmHigh_L=115;//given pwm to straight line
int pwmHigh_R=110;//given pwm to straight line

///tilt sensor which can ditect an angle
int tilt=52;


void setup()
{
  // set all the motor control pins to outputs
  pinMode(enR, OUTPUT);
  pinMode(enL, OUTPUT);
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT);
  pinMode(motor_C, OUTPUT);
  pinMode(motor_D, OUTPUT);
  
  //tilt sensor
  pinMode(tilt,INPUT);
  
  
  //sensor array
  for(int i=0;i<5;i++){
    pinMode(s[i],INPUT);
  }
  Serial.begin(9600);
}

void sensorRead(){
//sensor print in serial monotor
  for(int i=0;i<5;i++){
    s[i]=i+1;
    Serial.print(analogRead(s[i]));
    Serial.print(" ");
}
Serial.println();
}

void forward()
{
  
  
  // turn on motor A (left)
  digitalWrite(motor_A, HIGH);
  digitalWrite(motor_B, LOW);
  // set speed to 100 out of possible range 0~255
  
  // turn on motor B (right)
  digitalWrite(motor_C, HIGH);
  digitalWrite(motor_D, LOW);
  // set speed to 100 out of possible range 0~255
  analogWrite(enR, pwmHigh_R);
    analogWrite(enL, pwmHigh_L);
  
  
  

}

void breake()
{
  
  
  // turn on motor A (left)
  digitalWrite(motor_A, LOW);
  digitalWrite(motor_B, HIGH);
  // set speed to 100 out of possible range 0~255
  analogWrite(enR, pwmHigh_R/10);
  // turn on motor B (right)
  digitalWrite(motor_C, LOW);
  digitalWrite(motor_D, HIGH);
  // set speed to 100 out of possible range 0~255
  analogWrite(enL, pwmHigh_L/10);

}


void turnLeft(){
  
  breake();
  delay(30);
  
  while(true){
  if (analogRead(s[0])>cut && analogRead(s[1])<cut){
      
    breake();
    delay(20);
    Serial.println("turnLeft---->mainLoop");
    return;
  }
   
  
      //Stop left motor
      digitalWrite(motor_A, LOW);
      digitalWrite(motor_B, HIGH);
      // set speed to 200 out of possible range 0~255
      
      //Run left motor
      digitalWrite(motor_C, HIGH);
      digitalWrite(motor_D, LOW);
      // set speed to 200 out of possible range 0~255
      analogWrite(enL, pwmHigh_R/2);
      analogWrite(enR, pwmHigh_R/2);
      
  
  }
  
}

void turnRight(){
  
  breake();
  delay(30);
  
  while(true){
  if (analogRead(s[4])>cut && analogRead(s[3])<cut){
      
    breake();
    delay(20);
    Serial.println("turnLeft---->mainLoop");
    return;
  }
   
  
      //Run left motor
      digitalWrite(motor_A, HIGH);
      digitalWrite(motor_B, LOW);
      // set speed to 200 out of possible range 0~255
      
      //stop Right motor
      digitalWrite(motor_C, LOW);
      digitalWrite(motor_D, HIGH);
      // set speed to 200 out of possible range 0~255
      analogWrite(enL, pwmHigh_L/2);
      analogWrite(enR, pwmHigh_L/2);
      
  
  }
  
}

void left(){ //tern left to correct the error simple line following
  //Stop left motor
  digitalWrite(motor_A, HIGH);
  digitalWrite(motor_B, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enL, 2*pwmHigh_L/3);
  //Run right motor
  digitalWrite(motor_C, HIGH);
  digitalWrite(motor_D, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enR, pwmHigh_R);
  //forward();
  
}

void right(){ //tern right to correct the error simple line following
  //run left motor
  digitalWrite(motor_A, HIGH);
  digitalWrite(motor_B, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enL,pwmHigh_L);
  //stop right motor
  digitalWrite(motor_C, HIGH);
  digitalWrite(motor_D, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enR, 2*pwmHigh_R/3);
  //forward();
}

void stop1(){
  //Stop right motor
  digitalWrite(motor_A, LOW);
  digitalWrite(motor_B, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enR, 0);
  //Run left motor
  digitalWrite(motor_C, LOW);
  digitalWrite(motor_D, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enL, 0);
}


void loop(){
  
if (digitalRead(tilt)==0){  ///change pwm when ditect an angle
    pwmHigh_R=110/4;
    pwmHigh_L=115/4;
    Serial.println(digitalRead(tilt));
    
  }
  else{/// reset pwm after angle
    pwmHigh_R=110/4;
    pwmHigh_L=115/4;
    Serial.println(digitalRead(tilt));
  }
 if(analogRead(s[0])<cut && analogRead(s[1])<cut && analogRead(s[3])<cut && analogRead(s[4])<cut){ 
    stop1();
    delay(100000);
    Serial.println("all black");
 }
 else if(analogRead(s[0])>cut && analogRead(s[1])<cut && analogRead(s[3])>cut && analogRead(s[4])>cut){ 
    left();
    Serial.println("left");
 }
 else if(analogRead(s[0])>cut && analogRead(s[1])>cut && analogRead(s[3])<cut && analogRead(s[4])>cut){ 
    right();
    Serial.println("right");
 }
  else if(analogRead(s[0])<cut && analogRead(s[1])<cut && analogRead(s[4])>cut){ 
    turnLeft();
    Serial.println("turnLeft");
 }
 else if(analogRead(s[0])>cut && analogRead(s[3])<cut && analogRead(s[4])<cut){ 
    turnRight();
    Serial.println("turnRight");
 }
 else{
    forward(); 
 }
    
}
