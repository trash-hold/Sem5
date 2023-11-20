#define GATE_PIN 9 
#define HALL_IN 3

#define GEARSHIFT_CONST 3.646       // 1 / (14.58*4) 
#define TOP_SPEED 15
#define KP 1

int sample_number = 0;
int delta_t[4];

float speed_meas = 0;
float speed_ref = 100;

unsigned long last_sample = 0;


void setup() {
    Serial.begin(9600);

    pinMode(HALL_IN, INPUT_PULLUP);
    pinMode(GATE_PIN, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(HALL_IN), sample, CHANGE);

}

void loop() {
    int sum = 0;

    for (int i = 0; i < 4; i++)
        sum += delta_t[i];

    speed_meas = (sum == 0 || millis() - last_sample > 2000) ? 0 : 1 / (GEARSHIFT_CONST * sum);

    //int pwm_value = map(KP * (speed_ref - speed_meas), 0, TOP_SPEED, 0, 255)
    //analogWrite(GATE_PIN, pwm_value);
    //Have to measure top_speed

    if (Serial.available())
    {
        int temp = read_data();
        speed_ref = temp != -1 ? temp : speed_ref;
    }

}

void sample()
{
    delta_t[sample_number] = millis() - last_sample;
    last_sample = millis();

    sample_number = (sample_number + 1) % 4;
}



signed int read_data()
{
    //Wanted data format is "z X", where X is an integer >= 0
    //If given value or code letter is incorrect the function returns -1 - which should be interpreted as error message
    int read_byte = Serial.read();

    switch (read_byte)
    {
        case 'Z':
        case 'z':
            Serial.println("New speed: ");
            speed = Serial.parseInt();
            Serial.println(speed);

            return speed >= 0 ? speed : -1;
            break;
        default:
            return -1
    }
}
