// C++ code
//
void setup()
{
  for(int i=0; i<8; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop()
{
  //0
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  
  //1
  digitalWrite(0, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  
  //2
  digitalWrite(2, LOW);
  digitalWrite(0, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  
  //3
  digitalWrite(4, LOW);
  digitalWrite(2, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  
  //4
  digitalWrite(0, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(3, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  
  //5
  digitalWrite(1, LOW);
  digitalWrite(0, HIGH);
  digitalWrite(3, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  
  //6
  digitalWrite(4, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  
  //7
  for(int i=3; i<7; i++){
  	digitalWrite(i, LOW);
  }
  
  digitalWrite(1, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  
  //8
  for(int i=3; i<7; i++){
    digitalWrite(i, HIGH);
  }
  delay(1000); // Wait for 1000 millisecond(s)
  
  //9
  digitalWrite(4, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  
  setup();
}