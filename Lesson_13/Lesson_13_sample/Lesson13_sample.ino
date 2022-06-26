int IR[] = {A0,A1,A2,A3,A4}

int get_IR(int id){
    int state = digitalRead(IR[id]);
    return state;
}

void setup(){
    Serial.begin(9600);
    pinMode(IR0,INPUT);
    pinMode(IR1,INPUT);
    pinMode(IR2,INPUT);
    pinMode(IR3,INPUT);
    pinMode(IR4,INPUT);
}

void loop(){
    int State0 = get_IR(0);
    int State1 = get_IR(1);
    int State2 = get_IR(2);
    int State3 = get_IR(3);
    int State4 = get_IR(4);
    Serial.print(State0);
    Serial.print(State1);
    Serial.print(State2);
    Serial.print(State3);
    Serial.print(State4);
    Serial.print("\n");
    delay(100);
}