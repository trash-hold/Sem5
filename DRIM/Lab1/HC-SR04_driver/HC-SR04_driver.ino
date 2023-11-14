//#include "pitches.h"      //For easier buzzer handling

//Sonar
#define ECHO_PIN 
#define TRIG_PIN 

//Buzzer
#define BUZZ_PIN 

//UI
#define BUTTON_IN 
#define D1_PIN 
#define D2_PIN 
#define D3_PIN 

float count_us = 0;
float distance = 0;
float x = 0;

int mode = 0;
float measurments[12];

void setup() {
  Serial.begin(9600);

  pinMode(ECHO_PIN, INPUT);
  pinMode(BUTTON_IN, INPUT);

  pinMode(TRIG_PIN, OUTPUT);

  pinMode(D1_PIN, OUTPUT);
  pinMode(D2_PIN, OUTPUT);
  pinMode(D3_PIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_IN), changeMode, RISING);
  Serial.println("Start");

}

void loop() {
  // put your main code here, to run repeatedly:
    sonarMeasure();
    /*
    //mock data
    x = ((int) x + 10) % 500;
    distance = 500 -x ;*/
    int d1_val, d2_val, d3_val;
    Serial.println(distance);

    switch(mode)
    {
        case 0: 
          if(distance < 500)
            tone(BUZZ_PIN, 440, map(distance, 500, 0, 1, 100));
          else
            noTone(BUZZ_PIN);
          break;
        case 1: 
          if(distance < 500)
            tone(BUZZ_PIN, map(distance, 500, 0, 440, 1046), 10);
          else
            noTone(BUZZ_PIN);
          break;
        case 2: 
          if(distance > 200)
          {
              if(distance <= 300)
              {
                d1_val = 255;
                d2_val = 255;
                d3_val = 255;
              }
              else if(distance <= 400)
              {
                  d1_val = 255;
                  d2_val = 255;
                  d3_val = 0;
              }
              else if(distance <= 500)
              {
                  d1_val = 255;
                  d2_val = 0;
                  d3_val = 0;
              }
              else
              {
                  d1_val = 0;
                  d2_val = 0;
                  d3_val = 0;
              }
              /*Serial.println("Analog write");
              Serial.println(d1_val);
              Serial.println(d2_val);
              Serial.println(d3_val);*/
          }
          else
          {   
              d1_val = 255;
              d2_val = 255;
              d3_val = 255;
          }

          analogWrite(D1_PIN, d1_val);
          analogWrite(D2_PIN, d2_val);
          analogWrite(D3_PIN, d3_val);
          break;

        case 3:
          if(distance > 200)
          {
              if(distance <= 300)
              {
                d1_val = 255;
                d2_val = 255;
                d3_val = 255 - map(distance, 200, 300, 0, 255);
              }
              else if(distance <= 400)
              {
                  d1_val = 255;
                  d2_val = 255 - map(distance, 300, 400, 0, 255);
                  d3_val = 0;
              }
              else if(distance <= 500)
              {
                 d1_val = 255 - map(distance, 400, 500, 0, 255);
                 d2_val = 0;
                 d3_val = 0;
              }
              else
              {
                  d1_val = 0;
                  d2_val = 0;
                  d3_val = 0;
              }
              /*Serial.println("Analog write");
              Serial.println(d1_val);
              Serial.println(d2_val);
              Serial.println(d3_val);*/
          }
          else
          {
              d1_val = 255;
              d2_val = 255;
              d3_val = 255;

          }
          analogWrite(D1_PIN, d1_val);
          analogWrite(D2_PIN, d2_val);
          analogWrite(D3_PIN, d3_val);
          break;
    }
    delay(100);

 }

 float count_avg()
 {
    float sum = measurments[0];
    for(int i=1; i<12; i++)
    {
        sum += measurments[i];
        measurments[i] = measurments[i-1];
    }

    return sum/12;
 }

void sonarMeasure()
{
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    count_us = pulseIn(ECHO_PIN, HIGH);
    measurments[0] = count_us*0.343/2;      //in mm

    distance = count_avg();
    Serial.println(distance);
}

 void changeMode()
 {
      mode = (mode + 1) % 4;
      analogWrite(D1_PIN, 0);
      analogWrite(D2_PIN, 0);
      analogWrite(D3_PIN, 0);
      //Serial.print(mode);
 }