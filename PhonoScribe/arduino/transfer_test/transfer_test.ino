// output pin for zeros
const int zero = 9;
// output pin for ones
const int one = 10;

int val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(zero, OUTPUT);
  pinMode(one, OUTPUT);
  digitalWrite(zero, LOW);
  digitalWrite(one, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  // read the incoming byte:
  val = Serial.read();
  if (val != -1) {
    if (val) {
      digitalWrite(one, HIGH);
      delay(500);
    } else {
      digitalWrite(zero, HIGH);
      delay(500);
    }
  }
  digitalWrite(zero, LOW);
  digitalWrite(one, LOW);
}
