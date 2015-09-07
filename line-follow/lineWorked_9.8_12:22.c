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
int pwmHigh_L=205;
int pwmHigh_R=200;

void setup()
{
  // set all the motor control pins to outputs
  pinMode(enR, OUTPUT);
  pinMode(enL, OUTPUT);
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT);
  pinMode(motor_C, OUTPUT);
  pinMode(motor_D, OUTPUT);
  
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
  analogWrite(enR, pwmHigh_R);
  // turn on motor B (right)
  digitalWrite(motor_C, HIGH);
  digitalWrite(motor_D, LOW);
  // set speed to 100 out of possible range 0~255
  analogWrite(enL, pwmHigh_L);

}

void turnLeft(){
  
  
  while(true){
  if (analogRead(s[0])>cut && analogRead(s[1])<cut){
      
    
    Serial.println("turnLeft---->mainLoop");
    return;
  }
   
  
      //Stop left motor
      digitalWrite(motor_A, LOW);
      digitalWrite(motor_B, LOW);
      // set speed to 200 out of possible range 0~255
      
      //Run left motor
      digitalWrite(motor_C, HIGH);
      digitalWrite(motor_D, LOW);
      // set speed to 200 out of possible range 0~255
      analogWrite(enL, 0);
      analogWrite(enR, 70);
      
  
  }
  
}

void turnRight(){
  
  
  while(true){
  if (analogRead(s[4])>cut && analogRead(s[3])<cut){
      
    
    Serial.println("turnLeft---->mainLoop");
    return;
  }
   
  
      //Run left motor
      digitalWrite(motor_A, HIGH);
      digitalWrite(motor_B, LOW);
      // set speed to 200 out of possible range 0~255
      
      //stop Right motor
      digitalWrite(motor_C, LOW);
      digitalWrite(motor_D, LOW);
      // set speed to 200 out of possible range 0~255
      analogWrite(enL, 70);
      analogWrite(enR, 0);
      
  
  }
  
}

void left(){ //tern left to correct the error simple line following
  //Stop left motor
  digitalWrite(motor_A, LOW);
  digitalWrite(motor_B, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enL, 9*pwmHigh_L/10);
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
  digitalWrite(motor_C, LOW);
  digitalWrite(motor_D, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enR, 9*pwmHigh_R/10  );
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

//to stop a motor it is enough to set enable to 0 or set both pins to same stage (low or high)

 //1. analogWrite(enR, 0);

//2.digitalWrite(motor_A, LOW);
  //digitalWrite(motor_B, LOW);

//3.digitalWrite(motor_A, HIGH);
  //digitalWrite(motor_B, HIGH);


void loop()
{
 if(analogRead(s[0])<cut && analogRead(s[1])<cut && analogRead(s[2])<cut && analogRead(s[3])<cut && analogRead(s[4])<cut){ 
    stop1();
    delay(100000);
    Serial.println("all black");
 }
 else if(analogRead(s[0])>cut && analogRead(s[1])<cut && analogRead(s[2])<cut  && analogRead(s[3])>cut && analogRead(s[4])>cut){ 
    left();
    Serial.println("left");
 }
 else if(analogRead(s[0])>cut && analogRead(s[1])>cut && analogRead(s[2])<cut  && analogRead(s[3])<cut && analogRead(s[4])>cut){ 
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
