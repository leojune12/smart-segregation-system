#include <HCSR04.h>
#include <Servo.h>

Servo myservo;

// hc(Trig, Echo)
HCSR04 hc(2, 3);

#define cotagious_servo_pin 4
#define inductive_proximity_sensor_pin 5
#define inductive_servo_pin 6
#define capacitive_proximity_sensor_pin 7
#define capacitive_servo_pin 8

int pos = 90;

void setup() {
  Serial.begin(9600);

  pinMode(capacitive_proximity_sensor_pin, INPUT);
  pinMode(inductive_proximity_sensor_pin, INPUT);

  myservo.attach(inductive_servo_pin);
  myservo.write(pos);
  myservo.detach();

  myservo.attach(capacitive_servo_pin);
  myservo.write(pos);
  myservo.detach();
}

void loop() {
  check_contagious_status();
  metal_sensor_status();
  plastic_sensor_status();
}

void metal_sensor_status() {
  bool sensor_status = digitalRead(inductive_proximity_sensor_pin);
  Serial.print("Inductive status: ");
  Serial.println(sensor_status);

  if (!sensor_status) {
    push_inductive_servo();
    delay(1000);
    pull_inductive_servo();
  }
}

void plastic_sensor_status() {
  bool sensor_status = digitalRead(capacitive_proximity_sensor_pin);
  Serial.print("Capacitive status: ");
  Serial.println(sensor_status);

  if (sensor_status) {
    push_capacitive_servo();
    delay(1000);
    pull_capacitive_servo();
  }
}

void check_contagious_status() {
  float distance = read_contagious_distance();
  Serial.println(distance);
  if (distance < 15) {
    push_contagious_servo();
    pull_contagious_servo();
  }
}

float read_contagious_distance() {
  return hc.dist(0);
  delay(60); 
}

void push_contagious_servo() {
  myservo.attach(cotagious_servo_pin);
  for (pos = 0; pos <= 100; pos += 1) {
    myservo.write(pos);
    delay(10);
  }
  myservo.detach();
}

void pull_contagious_servo() {
  myservo.attach(cotagious_servo_pin);
  for (pos = 100; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }
  myservo.detach();
}

void pull_capacitive_servo() {
  myservo.attach(capacitive_servo_pin);
  for (pos = 40; pos <= 90; pos += 1) {
    myservo.write(pos);
    delay(10);
  }
  myservo.detach();
}

void push_capacitive_servo() {
  myservo.attach(capacitive_servo_pin);
  for (pos = 90; pos >= 40; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }
  myservo.detach();
}

void pull_inductive_servo() {
  myservo.attach(inductive_servo_pin);
  for (pos = 40; pos <= 90; pos += 1) {
    myservo.write(pos);
    delay(10);
  }
  myservo.detach();
}

void push_inductive_servo() {
  myservo.attach(inductive_servo_pin);
  for (pos = 90; pos >= 40; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }
  myservo.detach();
}
