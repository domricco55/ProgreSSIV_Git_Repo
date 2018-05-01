
void setup() {
  Serial.begin(9600);
  while ( !Serial ) ;
  Serial.print("Hello World!");

}

void loop() {
  // put your main code here, to run repeatedly:
   Serial.println("Hello user. I am your debugging assistant. You may call me TeensyTron5000.");
   delay( 500 );
}

