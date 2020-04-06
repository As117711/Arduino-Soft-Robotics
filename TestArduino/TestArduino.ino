
int pinEngine1=7, pinEngine2=8, pinPWM1=6;
int led1=3, led2=4, led3=5;

void setup() {
    pinMode(pinEngine1, OUTPUT);
    pinMode(pinEngine2, OUTPUT);
    pinMode(pinPWM1, OUTPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(A0, INPUT);

    //FSR
    pinMode(12, OUTPUT);
    pinMode(A1, INPUT);
    digitalWrite(12, HIGH);

    //FSR 2
    pinMode(13, OUTPUT);
    pinMode(A2, INPUT);
    digitalWrite(13, HIGH);

    digitalWrite(pinEngine1, HIGH);
    digitalWrite(pinEngine2, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);

    Serial.begin(9600);
    // Excel
    Serial.println("CLEARDATA"); //clears up any data left from previous projects
    //Serial.println("LABEL,Acolumn,Bcolumn,..."); //always write LABEL, so excel knows the next things will be the names of the columns (instead of Acolumn you could write Time for instance)
    Serial.println("LABEL,Date,Time,FSR1,FSR2,millis");
    Serial.println("RESETTIMER"); //resets timer to 0

}

void enginePwm(int pinNumber, float value)
{
    float temp = value / 10;

    if (value > 65)
    {
        digitalWrite(pinEngine1, HIGH);
        digitalWrite(pinEngine2, LOW);

        digitalWrite(pinNumber, HIGH);
        delay(temp);
        digitalWrite(pinNumber, LOW);
        delay(10 - temp);
    }
    else if (value < 35)
    {
        digitalWrite(pinEngine2, HIGH);
        digitalWrite(pinEngine1, LOW);
        //if(temp<1) {temp=1;}
        digitalWrite(pinNumber, HIGH);
        delay(10 - temp);
        digitalWrite(pinNumber, LOW);
        delay(temp);
    }
    else
    {
        digitalWrite(pinEngine2, LOW);
        digitalWrite(pinEngine1, LOW);
    }

    String msg = " temp : ";
    msg = msg + temp;

    // Serial.println(msg);
}
void led(int value)
{
    if (value > 55)
    {
        digitalWrite(led3, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led1, LOW);

    }
    else if (value < 45)
    {
        digitalWrite(led3, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led1, HIGH);

    }
    else
    {
        digitalWrite(led3, LOW);
        digitalWrite(led2, HIGH);
        digitalWrite(led1, LOW);
    }
}


void loop() {
    Serial.print("DATA,TIME,TIMER,");
    float current = analogRead(A0);
    current = (current * 100) / 1024;

    float fsr = analogRead(A1);
    fsr = (fsr * 100) / 1024;
    float fsr2 = analogRead(A2);
    fsr2 = (fsr2 * 100) / 1024;

    String msg = "";
    msg = msg + fsr;
    msg = msg + ",";
    msg = msg + fsr2;
    msg = msg + ",";

    Serial.println(msg);
    led(fsr2);
    //enginePwm(6, fsr);
    //Serial.println(current);
    delay(100);
}