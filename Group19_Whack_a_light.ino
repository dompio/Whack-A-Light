/**
 * This is the code for the Whack a light Arduino game created as part of the AC22006 Physical Computing module.
 * It uses the custom library for Adafruit MPR121 Capacitive touch sensor and parts of the example code from the custom library (sketch called "MPR121 test").
 * All copied code is marked by an asterisk in the comments. (  // * )
 * 
 * @authors Group 19 (Sarah Hill, Dominika Piosik, Lorena Weepers, Jamie Burton, Reece Elder)
 * @version 26/02/2018
 */

/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>  // *
#include "Adafruit_MPR121.h"  // *

Adafruit_MPR121 cap = Adafruit_MPR121();  // *

// Keeps track of the last pin touched
uint16_t currtouched = 0;  // *

// Declarations of input pins for buttons
const int button1Pin = 4;
const int button2Pin = 13;

// Declarations of variables representing the state of buttons
int button1State = 0;
int button2State = 0;

// Declarations of input pins for LEDs
int LED1 = 12;
int LED2 = 11;
int LED3 = 10;
int LED4 = 9;
int LED5 = 8;
int LED6 = 7;
int LED7 = 6;
int LED8 = 5;
int greenLED = 2;
int redLED = 3;

// Declaration of variable to store the current score
int score = 0;

void setup()
{
  // Set the mode of button pins to input
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  // Set the mode of LED pins to output
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Set the data rate to 9600 bps for communication between the Arduino and a computer
  Serial.begin(9600);

  // Needed to keep the Arduino from starting too fast
  while (!Serial)  // *
  {
    delay(10);  // *
  }
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A))  // *
  {
    Serial.println("MPR121 not found, check wiring?");  // *
    while (1);  // *
  }

  Serial.println("*********************************");
  Serial.println(" ");
  Serial.println("   Welcome to Whack a light!");
  Serial.println(" ");
  Serial.println("*********************************");
  Serial.println(" ");
  Serial.println("START A NEW GAME");
  Serial.println("Choose game mode:");
  Serial.println("Press 1 to choose EASY");
  Serial.println("Press 2 to choose HARD");
}

void loop() 
{
  playGame();
}

/**
 * Calls other functions and controls the flow of a game
 */
void playGame()
{
  int counter = 0;                            // variable to count the number of moves in the current game
  
  button1State = digitalRead(button1Pin);     // read the input from button number 1
  button2State = digitalRead(button2Pin);     // read the input from button number 2
  
    if(button1State == HIGH)                  // if button 1 was pressed
    {
      Serial.println(" ");
      Serial.println("Mode EASY selected");
      delay(3000);                            // waits for 3 seconds to start a game 
        
      while(counter < 25)                     // while there were no more than 25 moves made
      {
        whichRandomLED(4000, 6000);           // calls the whichRandom LED(lower, upper) function and passes minimum and maximum time values as parameters
        counter ++;                           // increments counter after a move was made
      }
      endGame();                              // after 25 moves in a game displays end message
    }
    else if(button2State == HIGH)             // if button 2 was pressed
    {
      Serial.println(" ");
      Serial.println("Mode HARD selected");
      delay(3000);                            // waits for 3 seconds to start a game 
       
      while(counter < 25)                     // while there were no more than 25 moves made
      {
        whichRandomLED(1000, 2000);           // calls the whichRandomLED(lower, upper) function and passes minimum and maximum time values as parameters
        counter ++;                           // increments counter after a move was made
      }
      endGame();                              // after 25 moves in a game displays end message
    }

}

/**
 * Choose an LED to light up and call appropriate functions to read user input within a specified amount of time and calculate the score
 * 
 * @param lower Lower bound of the interval to set the delayTime
 * @param upper Upper bound of the interval to set the delayTime
 */
void whichRandomLED(int lower, int upper) 
{
  
  int delayTime = getDelayTime(lower, upper);    // delayTime is the amount of time that the LED is lighted up for
  boolean hit = false;                           // indicates if the right pad was hit
  
  int pinNumber = random(1, 9);                  // the reference number of randomly selected pin (from 1 to 8) corresponding to the LED to light up
    
  switch(pinNumber)
  {
    case 1:
      digitalWrite(LED1, HIGH);               // turns on LED1 
      hit = checkPin(pinNumber, delayTime);   // calls the function that reads input from the capacitive sensor
      calculateScore(hit);                    // calls the function that calculates current score and gives feedback to user
      digitalWrite(LED1, LOW);                // turns off LED1
      break;
    case 2:
      digitalWrite(LED2, HIGH);               // turn on LED2
      hit = checkPin(pinNumber, delayTime);   // calls the function that reads input from the capacitive sensor 
      calculateScore(hit);                    // calls the function that calculates current score and gives feedback to user
      digitalWrite(LED2, LOW);                // turn off LED2
      break;
    case 3:
      digitalWrite(LED3, HIGH);               // turn on LED3
      hit = checkPin(pinNumber, delayTime);   // calls the function that reads input from the capacitive sensor 
      calculateScore(hit);                    // calls the function that calculates current score and gives feedback to user
      digitalWrite(LED3, LOW);                // turn off LED3
      break;
    case 4:
      digitalWrite(LED4, HIGH);               // turn on LED4
      hit = checkPin(pinNumber, delayTime);   // calls the function that reads input from the capacitive sensor 
      calculateScore(hit);                    // calls the function that calculates current score and gives feedback to user
      digitalWrite(LED4, LOW);                // turn off LED4  
      break;
    case 5:
      digitalWrite(LED5, HIGH);               // turn on LED5 
      hit = checkPin(pinNumber, delayTime);   // calls the function that reads input from the capacitive sensor 
      calculateScore(hit);                    // calls the function that calculates current score and gives feedback to user
      digitalWrite(LED5, LOW);                // turn off LED5
      break;
    case 6:
      digitalWrite(LED6, HIGH);               // turn on LED6
      hit = checkPin(pinNumber, delayTime);   // calls the function that reads input from the capacitive sensor 
      calculateScore(hit);                    // calls the function that calculates current score and gives feedback to user
      digitalWrite(LED6, LOW);                // turn off LED6
      break;
    case 7:
      digitalWrite(LED7, HIGH);               // turn on LED7 
      hit = checkPin(pinNumber, delayTime);   // calls the function that reads input from the capacitive sensor 
      calculateScore(hit);                    // calls the function that calculates current score and gives feedback to user
      digitalWrite(LED7, LOW);                // turn off LED7
      break;
    case 8:
      digitalWrite(LED8, HIGH);               // turn on LED8 
      hit = checkPin(pinNumber, delayTime);   // calls the function that reads input from the capacitive sensor 
      calculateScore(hit);                    // calls the function that calculates current score and gives feedback to user
      digitalWrite(LED8, LOW);                // turn off LED8
      break;
  }
}

/**
 * Returns a random delay time form a specified interval
 * 
 * @param lower Lower bound of the interval
 * @param upper Upper bound of the interval
 * @return random integer from the specified interval
 */
int getDelayTime(int lower, int upper)
{
  
  return random(lower, upper);
  
}

/**
 * Checks if the currently touched pad corresponds to the LED that lights up
 * 
 * @param index The number of touch sensor pin corresponding to the LED that lights up
 * @param delayTime The amount of time to wait for user input
 * @return boolean value indicating if the currently touched pad corresponds to the LED that lights up
 */
boolean checkPin(int index,int delayTime)
{
  int timePassed;     // the amount of time that passed since the start of reading the user input
  
  while(timePassed < delayTime)     // while the time since the start of reading the input is less than the time of waiting for user input
  {
    
    // Get the currently touched pad
    currtouched = cap.touched();  // *
    
    if ((currtouched & _BV(index)))      // * if the index of currently touched pad corresponds to the index of LED that lights up
    {
      return true;
    }
    
    timePassed++;    // increment timePassed
  }
  
  return false;
}

/**
 * Calculates current score, signalises if the user successfully hit the right pad or not through lighting up green or red LED, respectively
 * Displays the current score message
 * 
 * @param hit Boolean value indicating if the right pad was hit or not
 */
void calculateScore(boolean hit)
{
  if(hit == 1)
  {
    score++;
    digitalWrite(greenLED, HIGH);
    delay(getDelayTime(200,400));
    digitalWrite(greenLED, LOW);
  }
  else if(hit == 0)
  {
    digitalWrite(redLED, HIGH);
    delay(getDelayTime(200,400));
    digitalWrite(redLED, LOW);
  }
  Serial.println(" ");
  Serial.print("YOUR CURRENT SCORE IS: ");
  Serial.println(score);
  Serial.println(" ");
}

/**
 * Displays end message with final score and the message to begin a new game
 */
void endGame()
{
  // Calls the function to signalise the end of a game on the LED grid
  flash();
  
  Serial.println("*********************************");
  Serial.println(" ");
  Serial.print("YOUR FINAL SCORE IS: ");
  Serial.println(score);
  Serial.println(" ");
  Serial.println("*********************************");
  Serial.println(" ");
  Serial.println("START A NEW GAME");
  Serial.println("Choose game mode:");
  Serial.println("Enter 1 to choose easy");
  Serial.println("Enter 2 to choose hard");
  score = 0;    // reset score after a game finished
}

/**
 * Signalise the end of a game by flashing all lights 3 times
 */
void flash()
{
  for(int i = 0; i < 3; i++)
  {
    delay(300);
    digitalWrite(redLED, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);
    digitalWrite(LED6, HIGH);
    digitalWrite(LED7, HIGH); 
    digitalWrite(LED8, HIGH);   
    delay(400);
    digitalWrite(redLED, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, LOW);
    digitalWrite(LED8, LOW);  
  }
}

