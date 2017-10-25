
int inByte;

#define   ADRS_PIN_1  13
#define   ADRS_PIN_2  12
#define   ADRS_PIN_3  14
#define   ADRS_PIN_4  27
#define   ZX_PIN      34

int address = 0;
//portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void updateAddress() {
  int tempaddress = 0;
  tempaddress += (digitalRead(ADRS_PIN_1) == LOW) ? 1 : 0;
  tempaddress += (digitalRead(ADRS_PIN_2) == LOW) ? 2 : 0;
  tempaddress += (digitalRead(ADRS_PIN_3) == LOW) ? 4 : 0;
  tempaddress += (digitalRead(ADRS_PIN_4) == LOW) ? 8 : 0;
  address = tempaddress;
}
  
void setup() {
  pinMode(ADRS_PIN_1,INPUT);
  pinMode(ADRS_PIN_2,INPUT);
  pinMode(ADRS_PIN_3,INPUT);
  pinMode(ADRS_PIN_4,INPUT);
  updateAddress();

  pinMode(ZX_PIN,INPUT);
  attachInterrupt(digitalPinToInterrupt(ZX_PIN), zero_crossHandler, FALLING);
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Address: " + address);
}

void loop() {
  
  

}

void zero_crossHandler() {
  //portENTER_CRITICAL_ISR(&mux);
  //interruptCounter++;
  //portEXIT_CRITICAL_ISR(&mux);
}
