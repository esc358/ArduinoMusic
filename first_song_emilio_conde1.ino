// Name: Emilio S Conde Ludena

/* 
Song obtained from here: https://create.arduino.cc/projecthub/jrance/super-mario-theme-song-w-piezo-buzzer-and-arduino-1cc2e4
*/


/*************************************************
* Public Constants
*************************************************/
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978



//global variables

int buzzerPin = 5 ; //The buzzerPin is connected to pin 5 of the Arduino.
int button1Pin = 2; //The SW1 button is connect to pin 2 of the Arduino.
int RedPin = 9; //The red RGB LED is connected pin 9 of the Arduino.
int GreenPin = 10; //The green RGB LED is connected pin 10 of the Arduino.
int BluePin = 11; //The blue RGB LED is connected pin 11 of the Arduino.
int flag;

// The melody array of Mario obtained from the quote above
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};

//durations by tempo
int durations[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};


//The Setup function runs once.

void setup() { 
  Serial.begin(9600); //Send data to Serial Monitor.
  pinMode(RedPin, OUTPUT); //Setup red RGB LED pin as an output pin.
  pinMode(GreenPin, OUTPUT); //Setup green RGB LED pin as an output pin.
  pinMode(BluePin, OUTPUT); //Setup blue RGB LED pin as an output pin.
  pinMode(buzzerPin, OUTPUT); //Setup red LED pin as an output pin
  pinMode(button1Pin, INPUT); //Setup button1 pin as an input pin.
}

//The loop function runs forever.
void loop()
{
  button(); //function to operate system
}

//function for the button
void button() 
{
  if (digitalRead(button1Pin) == HIGH)  //Check to see if button1 is pressed.
  {
    if(flag==0) // pressed one time is on
    {
      flag=1;
      delay(300);
      Serial.println("On");
      song();
    }else if(flag==1) //pressed secon time is off
    {
      flag=2;
      delay(300);
      Serial.println("OFF");
    }else if(flag==2) // pressed third time return to on
    {
      flag=0;
      delay(300);
    }
  }   
}

// function for the song
void song()
{
  //a foor loop to intantiate the array of the melody
    for (int thisNote = 0; thisNote < 77; thisNote++)
    {
      
      Serial.println(thisNote); //print notes
      // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
      int duration = 1000/ durations[thisNote];
      //generates wave of frequency to the pin by melody by durations
      tone(buzzerPin, melody[thisNote], duration);
      // pause between notes
      int pause = duration * 1.3;
      //delay between notes
      delay(pause);
      if(thisNote < 77) // if condition to play the led colors
      {
        colors();//refer to funcion below
        Serial.print("Color");
      }
      button();//check if button is pressed
      if(flag==2 || thisNote ==76) //condition to break out of the for loop
      {
        colorsOff();//function to turn colors off
        break; 
      }
     }
}

// function to control leds with random colors
void colors()
{
  analogWrite(RedPin,random(0,254));
  delay(20);
  analogWrite(GreenPin,random(0,254));
  delay(20);
  analogWrite(BluePin,random(0,254));
  delay(20);
}

//function to control leds to turn them off
void colorsOff()
{ 
  analogWrite(RedPin,0);
  delay(20);
  analogWrite(GreenPin,0);
  delay(20);
  analogWrite(BluePin,0);
  delay(20);
}