// This version is mainly used when using iOS app for control
//    - currently, this is the only way of controlling the car
// 
// Differences from Ardulego_Arduino_Due:
//  - no serial communictation with Arduino Uno
//  - 
#include <Servo.h>

char c=' ';
bool started;

int delay_count;
int led_num;
int led_counter;

bool leds_enabled;
bool motors_enabled;
bool leftblink_on;
bool rightblink_on;
bool doors_open;
bool left_dr_open;
bool right_dr_open;

bool drive_forward;
bool drive_backward;

double distance_front;
long duration_front;
double distance_back;
long duration_back;

// Taillights -------------------------------------------
int LED_bro = 32; // back right outer
int LED_bri = 33; // back right inner
int LED_bli = 34; // back left inner
int LED_blo = 35; // back left outer

// Underglow --------------------------------------------
int LED_ufl = 36; // underglow front left
int LED_ufr = 37; // underglow front right
int LED_ubr = 38; // underglow back right
int LED_ubl = 39; // underglow back left

// Headlights -------------------------------------------
int LED_hro = 40; // headlight right outer
int LED_hri = 41; // headlight right inner
int LED_hli = 42; // headlight left inner
int LED_hlo = 43; // headlight left outer

// Motors -----------------------------------------------
int motor_enable = 7; // allows current to flow to the motors
int motor_ctrl_1 = 6; // controls first gate
int motor_ctrl_2 = 5; // controls second gate

// Ultrasonic sensors -----------------------------------
const int trigger_back = 12;
const int echo_back = 11;
const int trigger_front = 10;
const int echo_front = 9;
bool alternator; // true -> front, false -> back

// Servo setup code -------------------------------------
Servo left_base; // left horizontally rotating servo
Servo left_lift; // left vertically rotating servo
Servo right_base; // right horizontally rotating servo
Servo right_lift; // right vertically rotating servo

int lb_pin = 48; // pin for left_base servo
int ll_pin = 49; // pin for left_lift servo
int rb_pin = 50; // pin for right_base servo
int rl_pin = 51; // pin for right_lift servo

int pos_lb; // position of left_base servo
int pos_ll; // position of left_lift servo 
int pos_rb; // position of right_base servo
int pos_rl; // position of right_list servo

// Setup function ---------------------------------------
void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);

  // headlight initialization
  pinMode(LED_hro, OUTPUT);
  pinMode(LED_hri, OUTPUT);
  pinMode(LED_hli, OUTPUT);
  pinMode(LED_hlo, OUTPUT);
  digitalWrite(LED_hro, LOW);
  digitalWrite(LED_hri, LOW);
  digitalWrite(LED_hli, LOW);
  digitalWrite(LED_hlo, LOW);

  // taillight initialization
  pinMode(LED_bro, OUTPUT);
  pinMode(LED_bri, OUTPUT);
  pinMode(LED_bli, OUTPUT);
  pinMode(LED_blo, OUTPUT);
  digitalWrite(LED_bro, LOW);
  digitalWrite(LED_bri, LOW);
  digitalWrite(LED_bli, LOW);
  digitalWrite(LED_blo, LOW);

  // underglow initialization
  pinMode(LED_ufl, OUTPUT);
  pinMode(LED_ufr, OUTPUT);
  pinMode(LED_ubr, OUTPUT);
  pinMode(LED_ubl, OUTPUT);
  digitalWrite(LED_ufl, LOW);
  digitalWrite(LED_ufr, LOW);
  digitalWrite(LED_ubr, LOW);
  digitalWrite(LED_ubl, LOW);

  // motor initialization
  pinMode(motor_enable, OUTPUT);
  digitalWrite(motor_enable, LOW);
  pinMode(motor_ctrl_1, OUTPUT);
  pinMode(motor_ctrl_2, OUTPUT);
  digitalWrite(motor_ctrl_1, LOW);
  digitalWrite(motor_ctrl_2, LOW);

  // ultrasonic sensor initialization
  pinMode(trigger_front, OUTPUT);
  pinMode(echo_front, INPUT);
  pinMode(trigger_back, OUTPUT);
  pinMode(echo_back, INPUT);

  // servo initialization
  left_base.attach(lb_pin);
  left_lift.attach(ll_pin);
  right_base.attach(rb_pin);
  right_lift.attach(rl_pin);
  pos_lb = 0; // default position of each servo (may need to adjust)
  pos_ll = 0;
  pos_rb = 0;
  pos_rl = 0;

  // variable initialization
  leds_enabled = false;
  motors_enabled = false;
  doors_open = false;
  left_dr_open = false;
  right_dr_open = false;
  
  leftblink_on = false;
  rightblink_on = false;
  
  drive_forward = false;
  drive_backward = false;

  delay_count = 500;
  led_counter = 0;

  distance_front = 100;
  distance_back = 100;
  started = false;

  Serial.println("Started: no");
  Serial.println("LEDs: disabled");
  Serial.println("Motors: disabled");
}

// Main loop --------------------------------------------
void loop() {
  // converse with phone
  if (Serial3.available()){ // if something has be sent to serial
      Serial.println("Connected");
        c = Serial3.read(); // accept input
        Serial.write(c);

        if(c == '0'){ // turn on LED
          if(started){
            turn_off();
            started = false;
            Serial.println("Started: no");
          }
          else{
            lights_start();
            started = true;
            Serial.println("Started: yes");
          }
        }
        else if(c == '1'){ // drive forward
          forward();
        }
        else if(c == '2'){ // drive backward
          backward();
        }
        else if(c == '3'){ // left signal
          leftSignal();
        }
        else if(c == '4'){ // right signal
          rightSignal();
        }
        else if(c == '5'){ // open/close doors
//          if(!doors_open){
//            open_doors();
//            doors_open = true;
//          }
//          else{
//            close_doors();
//            doors_open = false;
//          }
        }
        else if(c == '6'){ // open left door
//          if(!left_dr_open){
//            left_door_open();
//            left_dr_open = true;
//          }
//          else{
//            left_door_close();
//            left_dr_open = false;
//          }
        }
        else if(c == '7'){ // open right door
//          if(!right_dr_open){
//            right_door_open();
//            right_dr_open = true;
//          }
//          else{
//            right_door_close();
//            right_dr_open = false;
//          }
        }
    }

//    if(alternator){ // using front
//      distance_front = ultrasonic_distance_front();
//      alternator = false;
//    }
//    else{
//      distance_back = ultrasonic_distance_back();
//      alternator = true;
//    }
//    if((distance_front < 20) && (distance_back < 20)){
////      Serial.print("Distance front: ");
////      Serial.println(distance_front);
////      Serial.print("Distance back: ");
////      Serial.println(distance_back);
//      flash_both();
//    }
//    else if(distance_front < 20){
////      Serial.print("Distance front: ");
////      Serial.println(distance_front);
//      flash_front();
//    }
//    else if(distance_back < 20){
////      Serial.print("Distance back: ");
////      Serial.println(distance_back);
//      flash_back();
//    }
}

// General functions ------------------------------------
void turn_on(){
  digitalWrite(LED_hro, HIGH);
  digitalWrite(LED_hri, HIGH);
  digitalWrite(LED_hli, HIGH);
  digitalWrite(LED_hlo, HIGH);
  
  digitalWrite(LED_bro, HIGH);
  digitalWrite(LED_bri, HIGH);
  digitalWrite(LED_bli, HIGH);
  digitalWrite(LED_blo, HIGH);

  digitalWrite(LED_ufl, HIGH);
  digitalWrite(LED_ufr, HIGH);
  digitalWrite(LED_ubr, HIGH);
  digitalWrite(LED_ubl, HIGH);
}

void turn_off(){
  digitalWrite(LED_hro, LOW);
  digitalWrite(LED_hri, LOW);
  digitalWrite(LED_hli, LOW);
  digitalWrite(LED_hlo, LOW);
  
  digitalWrite(LED_bro, LOW);
  digitalWrite(LED_bri, LOW);
  digitalWrite(LED_bli, LOW);
  digitalWrite(LED_blo, LOW);

  digitalWrite(LED_ufl, LOW);
  digitalWrite(LED_ufr, LOW);
  digitalWrite(LED_ubr, LOW);
  digitalWrite(LED_ubl, LOW);
}

// used to make code easier to read/more concise
double ultrasonic_distance_front(){
  digitalWrite(trigger_front, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigger_front, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_front, LOW);
  
  duration_front = pulseIn(echo_front, HIGH);
  distance_front = duration_front * 0.034 / 2; // in cm
//  Serial.print("Distance front: ");
//  Serial.println(distance_front);
  return distance_front;
}

double ultrasonic_distance_back(){
  digitalWrite(trigger_back, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigger_back, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_back, LOW);

  duration_back = pulseIn(echo_back, HIGH);
  distance_back = duration_back * 0.034 / 2; // in cm
//  Serial.print("Distance back: ");
//  Serial.println(distance_back);
  return distance_back;
}

// Light functions --------------------------------------
void lights_start(){
  digitalWrite(LED_bri, HIGH); // start with inner LED
  digitalWrite(LED_bli, HIGH);
  digitalWrite(LED_hri, HIGH);
  digitalWrite(LED_hli, HIGH);
  delay(133);
  digitalWrite(LED_bri, LOW);
  digitalWrite(LED_bli, LOW);
  digitalWrite(LED_hri, LOW);
  digitalWrite(LED_hli, LOW);
  
  digitalWrite(LED_bro, HIGH);
  digitalWrite(LED_blo, HIGH);
  digitalWrite(LED_hro, HIGH);
  digitalWrite(LED_hlo, HIGH);
  delay(133);
  digitalWrite(LED_bro, LOW);
  digitalWrite(LED_blo, LOW);
  digitalWrite(LED_hro, LOW);
  digitalWrite(LED_hlo, LOW);

  delay(201);
  
  digitalWrite(LED_bri, HIGH);
  digitalWrite(LED_bli, HIGH);
  digitalWrite(LED_hri, HIGH);
  digitalWrite(LED_hli, HIGH);
  delay(133);
  digitalWrite(LED_bri, LOW);
  digitalWrite(LED_bli, LOW);
  digitalWrite(LED_hri, LOW);
  digitalWrite(LED_hli, LOW);
  
  digitalWrite(LED_bro, HIGH);
  digitalWrite(LED_blo, HIGH);
  digitalWrite(LED_hro, HIGH);
  digitalWrite(LED_hlo, HIGH);
  
  digitalWrite(LED_bri, HIGH);
  digitalWrite(LED_bli, HIGH);
  digitalWrite(LED_hri, HIGH);
  digitalWrite(LED_hli, HIGH);

//  delay(200);
  digitalWrite(LED_ufr, HIGH);
//  delay(200);
  digitalWrite(LED_ufl, HIGH);
//  delay(200);
  digitalWrite(LED_ubl, HIGH);
//  delay(200);
  digitalWrite(LED_ubr, HIGH);
}

void leftSignal(){
  digitalWrite(LED_bli, LOW);
  digitalWrite(LED_blo, LOW);
  digitalWrite(LED_hli, LOW);
  digitalWrite(LED_hlo, LOW);
  delay(200);
  for(int i = 0; i < 5; i++){
    digitalWrite(LED_bli, HIGH);
    digitalWrite(LED_hli, HIGH);
    delay(200);
    digitalWrite(LED_blo, HIGH);
    digitalWrite(LED_hlo, HIGH);
    delay(200);

    digitalWrite(LED_bli, LOW);
    digitalWrite(LED_hli, LOW);
    digitalWrite(LED_blo, LOW);
    digitalWrite(LED_hlo, LOW);
    delay(200);
  }
  if(started){
    digitalWrite(LED_bli, HIGH);
    digitalWrite(LED_blo, HIGH);
    digitalWrite(LED_hli, HIGH);
    digitalWrite(LED_hlo, HIGH);
  }
}

void rightSignal(){
  digitalWrite(LED_bri, LOW);
  digitalWrite(LED_bro, LOW);
  digitalWrite(LED_hri, LOW);
  digitalWrite(LED_hro, LOW);
  delay(200);
  for(int i = 0; i < 5; i++){
    digitalWrite(LED_bri, HIGH);
    digitalWrite(LED_hri, HIGH);
    delay(200);
    digitalWrite(LED_bro, HIGH);
    digitalWrite(LED_hro, HIGH);
    delay(200);

    digitalWrite(LED_bri, LOW);
    digitalWrite(LED_bro, LOW);
    digitalWrite(LED_hri, LOW);
    digitalWrite(LED_hro, LOW);
    delay(200);
  }
  if(started){
    digitalWrite(LED_bri, HIGH);
    digitalWrite(LED_bro, HIGH);
    digitalWrite(LED_hri, HIGH);
    digitalWrite(LED_hro, HIGH);
  }
}

// LED flash functions for proximity sensor obstacle detection
// blink once per instance of close contact
void flash_front(){
  bool on = digitalRead(LED_hri);
  digitalWrite(LED_hro, LOW);
  digitalWrite(LED_hri, LOW);
  digitalWrite(LED_hli, LOW);
  digitalWrite(LED_hlo, LOW);
  delay(150);
  digitalWrite(LED_hro, HIGH);
  digitalWrite(LED_hri, HIGH);
  digitalWrite(LED_hli, HIGH);
  digitalWrite(LED_hlo, HIGH);
  delay(150);
  digitalWrite(LED_hro, LOW);
  digitalWrite(LED_hri, LOW);
  digitalWrite(LED_hli, LOW);
  digitalWrite(LED_hlo, LOW);
  delay(150);
  digitalWrite(LED_hro, HIGH);
  digitalWrite(LED_hri, HIGH);
  digitalWrite(LED_hli, HIGH);
  digitalWrite(LED_hlo, HIGH);
  
  if(!on){ // turns LEDs back to LOW if they were turn off before
    delay(150);
    digitalWrite(LED_hro, LOW);
    digitalWrite(LED_hri, LOW);
    digitalWrite(LED_hli, LOW);
    digitalWrite(LED_hlo, LOW);
  }
}

void flash_back(){
  bool on = digitalRead(LED_bri);
  digitalWrite(LED_bro, LOW);
  digitalWrite(LED_bri, LOW);
  digitalWrite(LED_bli, LOW);
  digitalWrite(LED_blo, LOW);
  delay(150);
  digitalWrite(LED_bro, HIGH);
  digitalWrite(LED_bri, HIGH);
  digitalWrite(LED_bli, HIGH);
  digitalWrite(LED_blo, HIGH);
  delay(150);
  digitalWrite(LED_bro, LOW);
  digitalWrite(LED_bri, LOW);
  digitalWrite(LED_bli, LOW);
  digitalWrite(LED_blo, LOW);
  delay(150);
  digitalWrite(LED_bro, HIGH);
  digitalWrite(LED_bri, HIGH);
  digitalWrite(LED_bli, HIGH);
  digitalWrite(LED_blo, HIGH);
  
  if(!on){
    delay(150);
    digitalWrite(LED_bro, LOW);
    digitalWrite(LED_bri, LOW);
    digitalWrite(LED_bli, LOW);
    digitalWrite(LED_blo, LOW);
  }
}

void flash_both(){
  bool on_front = digitalRead(LED_hri);
  bool on_back = digitalRead(LED_bri);
  digitalWrite(LED_hro, LOW);
  digitalWrite(LED_hri, LOW);
  digitalWrite(LED_hli, LOW);
  digitalWrite(LED_hlo, LOW);
  digitalWrite(LED_bro, LOW);
  digitalWrite(LED_bri, LOW);
  digitalWrite(LED_bli, LOW);
  digitalWrite(LED_blo, LOW);
  delay(150);
  digitalWrite(LED_hro, HIGH);
  digitalWrite(LED_hri, HIGH);
  digitalWrite(LED_hli, HIGH);
  digitalWrite(LED_hlo, HIGH);
  digitalWrite(LED_bro, HIGH);
  digitalWrite(LED_bri, HIGH);
  digitalWrite(LED_bli, HIGH);
  digitalWrite(LED_blo, HIGH);
  delay(150);
  digitalWrite(LED_hro, LOW);
  digitalWrite(LED_hri, LOW);
  digitalWrite(LED_hli, LOW);
  digitalWrite(LED_hlo, LOW);
  digitalWrite(LED_bro, LOW);
  digitalWrite(LED_bri, LOW);
  digitalWrite(LED_bli, LOW);
  digitalWrite(LED_blo, LOW);
  delay(150);
  digitalWrite(LED_hro, HIGH);
  digitalWrite(LED_hri, HIGH);
  digitalWrite(LED_hli, HIGH);
  digitalWrite(LED_hlo, HIGH);
  digitalWrite(LED_bro, HIGH);
  digitalWrite(LED_bri, HIGH);
  digitalWrite(LED_bli, HIGH);
  digitalWrite(LED_blo, HIGH);
  
  if(!on_front){
    delay(150);
    digitalWrite(LED_hro, LOW);
    digitalWrite(LED_hri, LOW);
    digitalWrite(LED_hli, LOW);
    digitalWrite(LED_hlo, LOW);
  }
  if(!on_back){
    delay(150);
    digitalWrite(LED_bro, LOW);
    digitalWrite(LED_bri, LOW);
    digitalWrite(LED_bli, LOW);
    digitalWrite(LED_blo, LOW);
  }
}

// Door functions ---------------------------------------
void open_doors(){
  // simultaneously rotate base servos as the lift servos lift doors
  for(int i = 0; i < 4; i++){
    left_base.write(pos_lb + 10);
    right_base.write(pos_rb + 10);
    left_lift.write(pos_ll + 13);
    right_lift.write(pos_rl + 13);
    pos_lb += 10;
    pos_rb += 10;
    pos_ll += 13;
    pos_rl += 13;
    delay(50);
  }
}

void close_doors(){
  // simultaneously rotate base servos as the lift servos lift doors
  for(int i = 0; i < 4; i++){
    left_base.write(pos_lb - 10);
    right_base.write(pos_rb - 10);
    left_lift.write(pos_ll - 13);
    right_lift.write(pos_rl - 13);
    pos_lb -= 10;
    pos_rb -= 10;
    pos_ll -= 13;
    pos_rl -= 13;
    delay(50);
  }
}

void left_door_open(){
  for(int i = 0; i < 4; i++){
    left_base.write(pos_lb + 10);
    left_lift.write(pos_ll + 13);
    pos_lb += 10;
    pos_ll += 13;
    delay(50);
  }
}
void left_door_close(){
  for(int i = 0; i < 4; i++){
    left_base.write(pos_lb - 10);
    left_lift.write(pos_ll - 13);
    pos_lb -= 10;
    pos_ll -= 13;
    delay(50);
  }
}

void right_door_open(){
  for(int i = 0; i < 4; i++){
    right_base.write(pos_rb + 10);
    right_lift.write(pos_rl + 13);
    pos_rb += 10;
    pos_rl += 13;
    delay(50);
  }
}
void right_door_close(){
  for(int i = 0; i < 4; i++){
    right_base.write(pos_rb - 10);
    right_lift.write(pos_rl - 13);
    pos_rb -= 10;
    pos_rl -= 13;
    delay(50);
  }
}

// Motor functions --------------------------------------
void forward(){
  bool driving = false;
  
  do{
    // check distance
    distance_front = ultrasonic_distance_front();
    Serial.println("Checked forward distance");
    // if far enough away from an obstacle and the car isn't driving
    if((!driving) && (distance_front > 15)){
      // sent power to motors
      Serial.println("Starting motor...");
      digitalWrite(motor_ctrl_1, HIGH); // adjust for correct direction
      digitalWrite(motor_ctrl_2, LOW);
//     analogWrite(motor_enable, 255); // full speed
      digitalWrite(motor_enable, HIGH);
      driving = true;
    }
    // flash lights if too close to an obstacle
    if(distance_front < 15){
      flash_front();
    }
    Serial.println("Keep driving");
  }while(distance_front > 25);

  // cut power from motors
//  analogWrite(motor_enable, 0);
  digitalWrite(motor_enable, LOW);
  digitalWrite(motor_ctrl_1, LOW);
  digitalWrite(motor_ctrl_2, LOW);
}

void backward(){
  // sent power to motors
  bool driving = false;
  
  do{
      distance_back = ultrasonic_distance_back();

      if((!driving) && (distance_back > 15)){
        // sent power to motors
        digitalWrite(motor_ctrl_1, LOW); // adjust for correct direction
        digitalWrite(motor_ctrl_2, HIGH);
//        analogWrite(motor_enable, 255); // full speed
        digitalWrite(motor_enable, HIGH);
        driving = true;
      }
      // flash lights if too close to an obstacle
      if(distance_back < 15){
        flash_back();
      }
  }while(distance_back > 25);
  
  // cut power from motors
//  analogWrite(motor_enable, 0);
  digitalWrite(motor_enable, LOW);
  digitalWrite(motor_ctrl_1, LOW);
  digitalWrite(motor_ctrl_2, LOW);
}
