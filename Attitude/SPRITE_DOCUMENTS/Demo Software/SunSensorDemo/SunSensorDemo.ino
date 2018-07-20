int val=0;
int back_sunsensor=13;
int front_sunsensor=8;
int newval=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

void loop() {
  val = analogRead(back_sunsensor);
//  val = analogRead(front_sunsensor);
  newval = (val/4);
  if (newval>255){
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
