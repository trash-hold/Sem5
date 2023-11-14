#define ECHO_PIN 2
#define BUTTON_IN 3
#define TRIG_PIN 7
#define D1_PIN 9
#define D2_PIN 10
#define D3_PIN 11

float count_us = 0;
float distance = 0;
float x = 0;

int mode = 0;
float measurments[12];

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //pinMode(ECHO_PIN, INPUT);
  //pinMode(TRIG_PIN, OUTPUT);
  pinMode(BUTTON_IN, INPUT);

  //*
  pinMode(D1_PIN, OUTPUT);
  pinMode(D2_PIN, OUTPUT);
  pinMode(D3_PIN, OUTPUT);//*/
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_IN), changeMode, RISING);
  Serial.println("Start");

}

void loop() {
  // put your main code here, to run repeatedly:
    //sonarMeasure();
    x = ((int) x + 10) % 500;
    distance = 500 -x ;
    //Serial.println(distance);
    switch(mode)
    {
        case 0: 
          break;
        case 1: 
          break;
        case 2: 
          int d1_val, d2_val, d3_val;
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
          int d1_val, d2_val, d3_val;

          if(distance > 200)
          {
              int d1_val, d2_val, d3_val;
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

      Serial.print(mode);
 }