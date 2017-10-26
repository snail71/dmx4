
int inByte;

#define   ADRS_PIN_1  13
#define   ADRS_PIN_2  12
#define   ADRS_PIN_3  14
#define   ADRS_PIN_4  27
#define   ZX_PIN      34
#define   OUT1        26
#define   OUT2        25
#define   OUT3        33
#define   OUT4        32

int address = 0;
volatile int zxcount = 0;
hw_timer_t * timer = NULL;

void IRAM_ATTR onTimer() {
  
}

//portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void updateAddress() {
  int tempaddress = 0;
  tempaddress += (digitalRead(ADRS_PIN_1) == LOW) ? 1 : 0;
  tempaddress += (digitalRead(ADRS_PIN_2) == LOW) ? 2 : 0;// this pin has strange issues when switch not closed - resets
  tempaddress += (digitalRead(ADRS_PIN_3) == LOW) ? 4 : 0;
  tempaddress += (digitalRead(ADRS_PIN_4) == LOW) ? 8 : 0;
  address = tempaddress;
}
  
void setup() {
  pinMode(ADRS_PIN_1,INPUT);
  pinMode(ADRS_PIN_2,INPUT);
  pinMode(ADRS_PIN_3,INPUT);
  pinMode(ADRS_PIN_4,INPUT);
  pinMode(OUT1,OUTPUT);
  pinMode(OUT2,OUTPUT);
  pinMode(OUT3,OUTPUT);
  pinMode(OUT4,OUTPUT);
  digitalWrite(OUT1,LOW);
  digitalWrite(OUT2,LOW);
  digitalWrite(OUT3,LOW);
  digitalWrite(OUT4,LOW);
  updateAddress();

  pinMode(ZX_PIN,INPUT);
  attachInterrupt(digitalPinToInterrupt(ZX_PIN), zero_crossHandler, FALLING);

  timer = timerBegin(0,80,true);
  timerAttachInterrupt(timer,&onTimer,true);
  // We set the event to fire every 38uS which gives us 256 steps of each half cycle 
  // There are 120 half cycles per second
  timerAlarmWrite(timer,38,true);
  timerAlarmEnable(timer);
  
  
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("");
  Serial.println("10D 4 CHANNEL DMX");
  Serial.print("Address: ");
  Serial.println(address,DEC);


  
}

void loop() {
  
    if(zxcount > 60) {
      zxcount = 0;
      Serial.println("60 xings");
    }

}

void zero_crossHandler() {
  //portENTER_CRITICAL_ISR(&mux);
  zxcount ++;
  //portEXIT_CRITICAL_ISR(&mux);
}
