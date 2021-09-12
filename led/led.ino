char data_masuk;
int led = 3;
void setup() {

pinMode(led, OUTPUT);
Serial.begin(9600);
}

void loop() {

data_masuk=Serial.read();
if(data_masuk=='on')
   {
    digitalWrite(led,HIGH);
    Serial.print("lampu nyala");
   }
else if(data_masuk=='of')
   {
    digitalWrite(led,LOW);
    Serial.print("lampu mati");
   }
}
