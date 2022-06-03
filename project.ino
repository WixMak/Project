#include <HC_SR04.h> // ultrasonic sensor library
#include <BH1750.h> // ambient light sensor library

double cm = 0.0; //for distance 

int trigPin = D3; //define ultrasonic sensor trigger pin
int echoPin = D2; //define ultrasonic sensor echo pin
HC_SR04 rangefinder = HC_SR04(trigPin, echoPin); //define ultrasonic sensor rangefinder

BH1750 sensor(0x23, Wire); //define ambient light sensor address

int red_led = D6; //define red led pin
int blue_led = D7; //define blue led pin

int buzzer = D4; //define buzzer pin

void setup() {
    
    sensor.begin(); //start ambient light sensor
    sensor.set_sensor_mode(BH1750::forced_mode_high_res2); //set ambient light sensor mode
    
    pinMode(red_led, OUTPUT); //set red led pin mode
    pinMode(blue_led, OUTPUT); //set blue led pin mode
    
    Spark.variable("cm", &cm, DOUBLE); //declared and read the variable
    Spark.function("lightup", read_light); //declared the event name and call the function once received the request
    Spark.function("distance_check", get_distance); //declared the event name and call the function once received the request
    
    pinMode(buzzer, OUTPUT); //set buzzer pin mode
    
    Serial.begin(); //connect serial 
      

}

void light_trigger() {
        digitalWrite(red_led, HIGH); // turn on red led
        digitalWrite(blue_led, HIGH); // turn on blue led
        delay(100); // wait 0.1 second
        digitalWrite(red_led, LOW); // turn off red led
        digitalWrite(blue_led, LOW); // turn off blue led
        delay(100); // wiat 0.1 second
}

int read_light(String c) {
    sensor.make_forced_measurement(); // do the measurement
    Serial.print("lv:"); // print 'lv:' on serial monitor
    Serial.println(sensor.get_light_level()); // print light level on serial monitor
    Serial.println(" "); // print empty line on serial monitor
    float lv = sensor.get_light_level(); // return light level
    
    if(lv < 250){ // check light level is lower than 250 or not
       light_trigger(); // blink LEDs
     }
    return 1;
}

int get_distance(String c) {
    cm = rangefinder.getDistanceCM(); // get the distance (cm)
    Serial.print("dist:"); // print 'dist:' on serial monitor
    Serial.println(cm); // print distance on serial monitor
    buzzer_trigger(cm); //activate buzzer
    return 1; // return dustance (cm)
}

void buzzer_trigger(float dist) {
    if (dist <= 20){ // check distance lesser than 20cm
        tone(buzzer, 3000, 9000); // turn on buzzer
    }
    else if (dist <= 40 && dist > 20){ // check distance lesser than 40cm and greater than 20cm
        tone(buzzer, 3000, 9000); // turn on buzzer
        delay(300); // wait 0.3 sencond
        digitalWrite(buzzer,LOW); // turn off buzzer
        delay(300); // wait 0.3 sencond
    }
    else if (dist <= 60 && dist > 40){ // check distance lesser than 60cm and greater than 40cm
        tone(buzzer, 3000, 9000); // turn on buzzer
        delay(500); // wait 0.5 sencond
        digitalWrite(buzzer,LOW);// turn off buzzer
        delay(500); // wait 0.5 sencond
    }
     else if (dist <= 80 && dist > 60){ // check distance lesser than 80cm and greater than 60cm
        tone(buzzer, 3000, 9000); // turn on buzzer
        delay(1000); // wait 1 sencond
        digitalWrite(buzzer,LOW); // turn off buzzer
        delay(1000); // wait 1 sencond
    }
    else digitalWrite(buzzer,LOW); // turn off buzzer if distnace greater than 80cm
  
}







