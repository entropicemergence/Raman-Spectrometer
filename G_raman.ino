//uint16_t buf[4][256];
uint16_t buf[29553];
uint16_t bufb[3695];
int scale=50;
int scale1=3700;
int scale2=3700;
String inString = "";
int a=0;
int b=0;
int c=0;
int d=0;
int e=0;
int f=0;
int g=0;
int h=0;

//float temp;

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
//  Serial.begin(9600);
  SerialUSB.begin(0);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT); 
  int t=analogRead(0);
  scale=50;
  scale1=3700;
  scale2=3700;

  ADC->ADC_MR |= 0x80; // these lines set free running mode on adc 7 (pin A0)
  ADC->ADC_CR=2;
  ADC->ADC_CHER=0x80;

  REG_PIOC_OWER = 0x0000000e; //  pin 35, pin 34, pin 33
  REG_PIOC_OWDR = 0xfffffff1;

  sensors.begin();

}

void loop() {
    if (SerialUSB.available() > 0) {
      while (SerialUSB.available() > 0) {
        int inChar = SerialUSB.read();
        if (isDigit(inChar)) {
          // convert the incoming byte to a char and add it to the string:
          inString += (char)inChar;
        }
    
      }
    
      scale=inString.toInt();
      inString = "";
      if (scale > 4500){
        scale1=scale-5000;
        scale1=scale1*140*5;
        }
      else if (scale < 4500){
        scale2=scale*140*5;
      }
    }

  ADC->ADC_MR |= 0x80; // these lines set free running mode on adc 7 (pin A0)
  ADC->ADC_CR=2;
  ADC->ADC_CHER=0x80;


//  int q0=0;
//  int a0;
//pin 35, pin 34, pin 33
  for(int a=0;a<10;a++){
      cl();
    }
  
//  int t=micros();
  cl2(scale1);
  for(int a=0;a<4;a++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }

  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x0000000a; //1010

  for(int i=0;i<5;i++){

    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x0000000a; //1010
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000008; //1000
    }
  }


  for(int i=0;i<5;i++){

    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x00000002; //0010
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000000; //0000
    }
  }


  for(int a=0;a<4;a++){
      REG_PIOC_ODSR = 0x00000002; //0010
    }


//  int tt=13;
  int tt=9;
  for(int i=0;i<3694;i++){
    int q=i*8;
    for(int k=0;k<tt;k++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }
    buf[q]=ADC->ADC_CDR[7];
    for(int j=0;j<tt;j++){
      REG_PIOC_ODSR = 0x00000004; //0100
    }  
    buf[q+1]=ADC->ADC_CDR[7];
    
    for(int k=0;k<tt;k++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }
    buf[q+2]=ADC->ADC_CDR[7];
    for(int j=0;j<tt;j++){
      REG_PIOC_ODSR = 0x00000004; //0100
    }
    buf[q+3]=ADC->ADC_CDR[7];
    for(int k=0;k<tt;k++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }
    buf[q+4]=ADC->ADC_CDR[7];
    for(int j=0;j<tt;j++){
      REG_PIOC_ODSR = 0x00000004; //0100
    }
    buf[q+5]=ADC->ADC_CDR[7];
//    buf[i]=ADC->ADC_CDR[6];     
    for(int k=0;k<tt;k++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }
    buf[q+6]=ADC->ADC_CDR[7];
    for(int j=0;j<tt;j++){
      REG_PIOC_ODSR = 0x00000004; //0100
    }
    buf[q+7]=ADC->ADC_CDR[7];
//    buf[i]=a
//    buf[i]=(b+a)/2;
//  buf[i]=b;
  }
//    bufb[i]=buf[j];
  delay(3);
  for(int i=0;i<3694;i++){
    int j=i*8;
  bufb[i]=buf[j]+buf[j+1]+buf[j+5];
  }
  ADC->ADC_CHDR=0x80;  // disabling previous pin
  ADC->ADC_MR |= 0x40; // these lines set free running mode on adc 7 (pin A0)
  ADC->ADC_CR=2;
  ADC->ADC_CHER=0x40;
//  for(int i=3694;i<7388;i++){
//    buf[i]=999;
//  }
//  sensors.requestTemperatures();
//  sensors.getTempCByIndex(0)
//  bufb[3693]=
  bufb[3694] = 12500;
//  t=micros()-t;
//  Serial.print(t);Serial.print(" micros "); //Serial.println(q0);
  SerialUSB.write((uint8_t *)bufb,7390);
  sensors.requestTemperatures();
  SerialUSB.println(sensors.getTempCByIndex(0)); 

  ADC->ADC_CHDR=0x40;
  delay(3);
}






void cl()
{
  for(int a=0;a<4;a++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }

  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x0000000a; //1010

  for(int i=0;i<5;i++){

    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x0000000a; //1010
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000008; //1000
    }
  }


  for(int i=0;i<5;i++){

    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x00000002; //0010
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000000; //0000
    }
  }


  for(int a=0;a<4;a++){
      REG_PIOC_ODSR = 0x00000002; //0010
    }

  for(int i=0;i<3694;i++){

    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000004; //0100
    }
    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000004; //0100
    }
    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000004; //0100
    }
    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000004; //0100
    }


  }
}


void cl2(int scale)
{
  for(int a=0;a<4;a++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }

  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x00000002; //0010
  REG_PIOC_ODSR = 0x0000000a; //1010

  for(int i=0;i<5;i++){

    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x0000000a; //1010
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000008; //1000
    }
  }


  for(int i=0;i<5;i++){

    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x00000002; //0010
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000000; //0000
    }
  }

  for(int a=0;a<4;a++){
      REG_PIOC_ODSR = 0x00000002; //0010
    }

  for(int i=0;i<scale;i++){

    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000004; //0100
    }
    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000004; //0100
    }
    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000004; //0100
    }
    for(int k=0;k<6;k++){
      REG_PIOC_ODSR = 0x00000006; //0110
    }
    for(int j=0;j<6;j++){
      REG_PIOC_ODSR = 0x00000004; //0100
    }
  }
}

//5421 micros  reading if loop using 6x
//5421 micros 
//5421 micros about 1.465 us per data
//5421 micros

//29642 micros reading if loop using 16x
//29642 micros 
//29642 micros about 8.011 us per data
//29642 micros
