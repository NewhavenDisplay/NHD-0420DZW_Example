/*
/Program for writing to NHD-0420DZW series display. 
/This code is written for the Arduino Uno (Microchip ATmega328P) using 4-Bit / 8-Bit 6800 Parallel Interface. 
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
// The 8 bit data bus is connected to PORTD 0-7 of the Arduino Uno
// The 4 bit data bus is connected to PORTD 4-7 of the Arduino Uno

#define E_Pin 10
#define R_W   9
#define R_S   8

unsigned char mode = 4; // 4 = 4-Bit parallel  
                        // 8 = 8-Bit Parallel

/****************************************************
*                 Text Strings                      *
****************************************************/

char const text1[] = ("  Newhaven Display  ");
char const text2[] = ("   International    ");
char const text3[] = ("   CHARACTER TEST   ");

char const text4[] = ("   4-Bit Parallel   ");
char const text5[] = ("   8-Bit Parallel   ");

char const text6[] = ("ABCDEFGHIJKLMOPQRSTU");
char const text7[] = ("VWXYZabcdefghijklmno");
char const text8[] = ("pqrstuvwxyz123456789");
char const text9[] = (" <(' ')> || <(' ')> ");

/****************************************************
*               Function Commands                   *
****************************************************/

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  4-bit / 8-bit 6800 Parallel Interface 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void latch()                  // command to latch E  
{                           
  digitalWrite(E_Pin, HIGH);  
  delay(1);
  digitalWrite(E_Pin, LOW); 
  delay(2);
}

void command(char i)
{
  switch(mode)
  {
    case 4: PORTD = i;
            digitalWrite(R_S, LOW);    // Command
            digitalWrite(R_W, LOW);    // Write
            latch();                   // Latch upper 4 bits
            i = i<<4;                  // shift 4 bits
            PORTD = i;                 // Take lower 4 bits
            latch();                   // Latch lower 4 bits
            break;
            
    case 8: PORTD = i;
            digitalWrite(R_S, LOW);    // Data
            digitalWrite(R_W, LOW);    // Write
            latch();                   // Latch 8 bits
            break;           
  }
}

void data(char i)
{
  switch(mode)
  {
    case 4: PORTD = i;
            digitalWrite(R_S, HIGH);              // Data
            digitalWrite(R_W, LOW);               // Write
            latch();                              // Latch upper 4 bits
            i = i<<4;                             // shift 4 bits
            PORTD = i;                            // Take lower 4 bits
            latch();                              // Latch lower 4 bits
            break;
            
    case 8: PORTD = i;
            digitalWrite(R_S, HIGH);              // Data
            digitalWrite(R_W, LOW);               // Write
            latch();                              // Latch 8 bits
            break;           
  }
}

/****************************************************
*                  Display Functions                *
****************************************************/

void clear_screen(){                    // clear display 
 command(0x01);
}

void ret_home(){                        // Return to home position
 command(0x02); 
}


void disp1(){                 // DISPLAY TEXT
  clear_screen();
  ret_home();                 // First Line
  for( int i = 0; i< 20; i++){
    data(text1[i]);
  }
  command(0xc0);              // Second Line
  for (int i = 0; i<20; i++){
    data(text2[i]);
  }
  command(0x94);              // Third Line
  for( int i = 0; i< 20; i++){
    data(text3[i]);  
  }
  command(0xD4);              // Fourth Line
  for (int i = 0; i<20; i++){
    switch(mode){
      case 4:data(text4[i]);
             break;
      case 8:data(text5[i]);
             break;
    }
  }
}


void disp2(){                 // DISPLAY TEXT
  clear_screen();   
  ret_home();                 // First Line
  for( int i = 0; i< 20; i++){
    data(text6[i]);  
  }
  command(0xc0);              // Second Line
  for (int i = 0; i<20; i++){
    data(text7[i]); 
  }
  command(0x94);              // Third Line
  for( int i = 0; i< 20; i++){
    data(text8[i]);   
  }
  command(0xD4);              // Fourth Line
  for (int i = 0; i<20; i++){
    data(text9[i]);  
  }
}

/****************************************************
*              Initialization Routine               *
****************************************************/

void init1(){
  digitalWrite(E_Pin, LOW);
  delay(300);  

  switch(mode)
  {
  case 4:command(0x28);      //Enable 4-Bit Mode
         delay(5);
         break;
  case 8:command(0x38);      //Enable 8-Bit Mode
         delay(5);
         break;
  }
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
  DDRD = 0xFF; // Enable pins on PORT D as outputs
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
