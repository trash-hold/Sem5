#define GATE_PIN
#define HALL_IN

int sample_number = 0;
u_int start_time = 0;
u_int end_time = 0;
u_int rotation_time = 0;



void setup() {

    pinMode(HALL_IN, INPUT_PULLUP);
    pinMode(GATE_PIN, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(HALL_IN), sample, CHANGE);

}

void loop() {


}

void sample()
{
    
}