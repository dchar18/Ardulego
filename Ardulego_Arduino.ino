//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(8,9); // RX, TX 


char c=' ';
boolean NL = true;

//char input;
bool started;

int delay_count;
int led_num;
int led_counter;

bool leds_enabled;
bool motors_enabled;
bool leftblink_on;
bool rightblink_on;

bool drive_forward;
bool drive_backward;

double distance_front;
long duration_front;
double distance_back;
long duration_back;

// Taillights
int LED_bro = 32; // back right outer
int LED_bri = 33; // back right inner, NEED TO RE-SOLDER
int LED_bli = 34; // back left inner
int LED_blo = 35; // back left outer

// Underglow
int LED_ufl = 36; // underglow front left
int LED_ufr = 37; // underglow front right
int LED_ubr = 38; // underglow back right
int LED_ubl = 39; // underglow back left

// headlights
int LED_hro = 40; // headlight right outer
int LED_hri = 41; // headlight right inner
int LED_hli = 42; // headlight left inner
int LED_hlo = 43; // headlight left outer

// motors
int Motor_fl = 50; // motor front left
int Motor_fr = 51; // motor front right
int Motor_bl = 52; // motor back left (same side as Motor_fl)
int Motor_br = 53; // motor back right

// Ultrasonic sensors
const int trigger_back = 12;
const int echo_back = 11;
const int trigger_front = 10;
const int echo_front = 9;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
//  BTserial.begin(9600);

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

  // ultrasonic sensor initialization
  pinMode(trigger_front, OUTPUT);
  pinMode(echo_front, INPUT);
  pinMode(trigger_back, OUTPUT);
  pinMode(echo_back, INPUT);

  leds_enabled = false;
  motors_enabled = false;
  
  leftblink_on = false;
  rightblink_on = false;
  
  drive_forward = false;
  drive_backward = false;

  delay_count = 500;
  led_counter = 0;

  started = false;

  Serial.println("Started: no");
  Serial.println("LEDs: disabled");
  Serial.println("Front motor: disabled");
  Serial.println("Rear motor: disabled");
}

void loop() {
  // sensors
  // converse with phone
  if (Serial3.available()){
      Serial.println("Connected");
        c = Serial3.read();
        Serial.write(c);

        if(c == '0'){ // turn on LED
          if(started){
            turn_off();
            started = false;
          }
          else{
            lights_start();
            started = true;
          }
        }
        else if(c == '1'){ // turn on motors
          
        }
        else if(c == '2'){ // drive forward
          
        }
        else if(c == '3'){ // drive backward
          
        }
        else if(c == '4'){ // left signal
          leftSignal();
        }
        else if(c == '5'){ // right signal
          rightSignal();
        }
    }
  
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
  digitalWrite(LED_bli, HIGH);
  digitalWrite(LED_blo, HIGH);
  digitalWrite(LED_hli, HIGH);
  digitalWrite(LED_hlo, HIGH);
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
  digitalWrite(LED_bri, HIGH);
  digitalWrite(LED_bro, HIGH);
  digitalWrite(LED_hri, HIGH);
  digitalWrite(LED_hro, HIGH);
}
