#define green_led 12
#define red_led   14
#define data_pin  13
void setup(){
  pinMode(green_led,OUTPUT);
  pinMode(red_led,OUTPUT);
  pinMode(data_pin,INPUT);
  Serial.begin(9600);
}
void loop(){
  int data=digitalRead(data_pin);
  Serial.println(data);
  digitalWrite(green_led,HIGH);
  digitalWrite(red_led,LOW);
  if(data==1){
  digitalWrite(green_led,LOW);
  digitalWrite(red_led,HIGH);
  }
  else{
  digitalWrite(green_led,HIGH);
  digitalWrite(red_led,LOW);
  }
}
