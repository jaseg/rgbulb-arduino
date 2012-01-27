
char buf[6];
unsigned char bufPos = 0;
unsigned int colorBuffer[3];
int currentColor = 0;

void setup(){
  Serial.begin(9600);
  //init PWM
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  TCCR1A = (1<<COM3A1) | (1<<COM3B1) | (1<<COM3C1) | (1<<WGM31);
  TCCR1B = (1<<CS30) | (1<<WGM32) | (1<<WGM33);
  ICR1 = 0xFFFF;
}

void loop(){
  int c;
  if(Serial.available()){
    c = Serial.read();
    if(c == ',' || c == '\n' || c == 0){
      buf[bufPos] = 0;
      bufPos = 0;
      colorBuffer[currentColor] = atoi(buf);
      currentColor++;
      if(currentColor > 2){ //got all values
        Serial.println(colorBuffer[0]);
        Serial.println(colorBuffer[1]);
        Serial.println(colorBuffer[2]);
        OCR1A = colorBuffer[0];
        OCR1B = colorBuffer[1];
        OCR1
        C = colorBuffer[2];
      }
    }else{
      buf[bufPos] = c;
      if(bufPos < 5) //ignore trailing garbage
        bufPos++;
    }
    if(c == '\n' || c == 0){
      currentColor = 0;
    }
  }
}
