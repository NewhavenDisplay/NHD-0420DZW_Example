/*
/Program for writing to NHD-0420DZW series display. 
/This code is written for the Arduino Uno (Microchip ATmega328P) using Serial Interface. 
/
/Newhaven Display invests time and resources providing this open source code,
/Please support Newhaven Display by purchasing products from Newhaven Display! 

* Copyright (c) 2020 Alee Shah - Newhaven Display International, Inc. 
*
* This code is provided as an example only and without any warranty by Newhaven Display. 
* Newhaven Display accepts no responsibility for any issues resulting from its use.
* The developer on the final application incorporating any parts of this 
*  sample code is responsible for ensuring its safe and correct operation
*   and for any consequences resulting from its use. 
* See the GNU General Public License for more details.
* 
* 
*/

/****************************************************
*      PINOUT: Arduino Uno -> Character OLED        *
****************************************************/

#define CS    11
#define SDI   12
#define SCL   13

/****************************************************
*                 Text Strings                      *
****************************************************/

char const text1[] = ("  Newhaven Display  ");
char const text2[] = ("   International    ");
char const text3[] = ("   CHARACTER TEST   ");
char const text4[] = ("  Serial Interface  ");
char const text5[] = ("ABCDEFGHIJKLMOPQRSTU");
char const text6[] = ("VWXYZabcdefghijklmno");
char const text7[] = ("pqrstuvwxyz123456789");
char const text8[] = (" <(' ')> || <(' ')> ");

/****************************************************
*               Function Commands                   *
****************************************************/

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Command Function:  
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  10-bit Instruction Transmission
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void command(char i)
{  
  unsigned int m;
  digitalWrite(CS, LOW);   // CS = 0;
  digitalWrite(SDI, LOW);  // RS = 0;
  digitalWrite(SCL, LOW);
  digitalWrite(SCL, HIGH); // Clock RS Pin in
  digitalWrite(SCL, LOW);
  delay(1);
  digitalWrite(SDI, LOW);  // RW = 0;
  digitalWrite(SCL, LOW);
  digitalWrite(SCL, HIGH); // Clock RW Pin in
  digitalWrite(SCL, LOW);
  for(m=0;m<8;m++){        // Clock in DB0 - DB7
    if((i&0x80)==0x80)
    digitalWrite(SDI, HIGH);
    else
    digitalWrite(SDI, LOW);
    while(0);
    i=(i<<1);
    digitalWrite(SCL, LOW);
    while(0);
    digitalWrite(SCL, HIGH);
    while(0);
    digitalWrite(SCL, LOW);
    }
  digitalWrite(CS, HIGH);  // CS = 1;
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Start_Data_Transmission Function: 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Set CS pin LOW to begin transmission; Set RS & RW bits 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void start_data_transmission()
{  
  digitalWrite(CS, LOW);   // CS = 0;
  delay(1);
  digitalWrite(SDI, HIGH); // RS = 1;
  digitalWrite(SCL, LOW);
  digitalWrite(SCL, HIGH); // Clock RS Pin in
  digitalWrite(SCL, LOW);
  delay(1);
  digitalWrite(SDI, LOW);  // RW = 0;
  digitalWrite(SCL, LOW);
  digitalWrite(SCL, HIGH); // Clock RW Pin in
  digitalWrite(SCL, LOW);
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Data Function: 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Send 8-bit Transmission; Can be continuous transmission
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void data(char i)
{    
  unsigned int m;
  for(m=0;m<8;m++){        // Clock in DB0 - DB7
    if((i&0x80)==0x80)
    digitalWrite(SDI, HIGH);
    else
    digitalWrite(SDI, LOW);
    while(0);
    i=(i<<1);
    digitalWrite(SCL, LOW);
    while(0);
    digitalWrite(SCL, HIGH);
    while(0);
    digitalWrite(SCL, LOW);
    }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  End_Data_Transmission Function: 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Set CS pin HIGH to end transmission.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void end_data_transmission()
{
  digitalWrite(CS, HIGH);  // CS = 1;
  delay(1);
}

/****************************************************
*                  Display Functions                *
****************************************************/

void clear_screen(){         // clear display 
 command(0x01);
}

void ret_home(){             // Return to home position
 command(0x02); 
}


void disp1(){                 // DISPLAY TEXT
  clear_screen();
  ret_home();                 // First Line
  start_data_transmission();
  for( int i=0;i<20;i++){
    data(text1[i]);
  }
  end_data_transmission();
/******************************************/    
  command(0xc0);              // Second Line
  start_data_transmission();
  for (int i=0;i<20;i++){
    data(text2[i]);
  }
  end_data_transmission();
/******************************************/     
  command(0x94);              // Third Line
  start_data_transmission();
  for( int i=0;i<20;i++){
    data(text3[i]);
  }
  end_data_transmission();  
/******************************************/   
  command(0xD4);              // Fourth Line
  start_data_transmission();
  for (int i=0;i<20;i++){
    data(text4[i]);  
  }
  end_data_transmission();  
}


void disp2(){                 // DISPLAY TEXT
  clear_screen();
  ret_home();                 // First Line
  start_data_transmission();
  for( int i=0;i<20;i++){
    data(text5[i]);
  }
  end_data_transmission();
/******************************************/    
  command(0xc0);              // Second Line
  start_data_transmission();
  for (int i=0;i<20;i++){
    data(text6[i]);
  }
  end_data_transmission();
/******************************************/     
  command(0x94);              // Third Line
  start_data_transmission();
  for( int i=0;i<20;i++){
    data(text7[i]);
  }
  end_data_transmission();   
/******************************************/      
  command(0xD4);              // Fourth Line
  start_data_transmission();
  for (int i=0;i<20;i++){
    data(text8[i]);  
  }
  end_data_transmission();  
}

/****************************************************
*              Initialization Routine               *
****************************************************/

void init1(){
  delay(300);

  command(0x28);             //Function set
  delay(2);
  command(0x08);             //Display OFF
  delay(2);
  command(0x01);             //Clear Display
  delay(2);
  command(0x06);             //Entry Mode set
  delay(2);
  command(0x02);             //Return Home
  delay(2);
  command(0x0C);             //Display ON
  delay(2);
}

/*****************************************************
*           Setup Function, to run once              *
*****************************************************/

void setup() {
  DDRB = 0xFF; // Enable pins on PORT B as outputs
  init1();
  delay(100);
}

/*****************************************************
*           Loop Function, to run repeatedly         *
*****************************************************/

void loop() {
  disp1();
  delay(2500);
  disp2();
  delay(2500);
}
