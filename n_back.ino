/////////////////////////////////////////////////////////////////////////
// "n-back" brain-game for MSP430-FR4133
//
// Brief: reads digital serial data from on-board push button 2 
//        as an input from the user. User is to push the button 
//        everytime the same letter appears that had appeared n
//        letters ago.
//
// Note: at this point, I do not consider this project to be complete.
//
// ___________________________________________________________________
//                                Flow
// Splash:  "N BACK" (prints)
// 
// Prompt:  "SELECT N BACK NUMBER" (scrolls left)
// Menu:    " SEL:#"   (prints; where # can be: 1, 2, ..., 9)
//
// Prompt:  "CHOOSE DIFFICULTY LEVEL" (scrolls left)
//          "1 HARD"   (prints)
//          "2 MEDIUM" (scrolls left)
//          "3 EASY"   (prints)
// Menu:    " SEL: #"  (prints; where # can be: 1, 2, 3)
//
// Pregame: "LVL #" (prints; where # is the level number)
//
// Game:    "L    #" (where L = letter from set and # = score < 10)
//          "L   ##" (where L = letter from set and # = score >  9)
//          "L  ###" (where L = letter from set and # = score > 99)
// ___________________________________________________________________
//
// Author: Ron Rihoo
//
/////////////////////////////////////////////////////////////////////////

// Libraries
#include "LCD_Launchpad.h"
#include "LCD_Launchpad_Addon.h"

// Hardware
LCD_LAUNCHPAD LCD;

// Variables and Constants ////

// menu
int difficulty_level = 0;   // game difficulty mode
int choice = 1;             // menu choice
int n = 0;                  // n-back number (2-back, 3-back, etc.)

// game
int level = 1;              // game level
int score_d1 = 0;           // game score; digit 1: L _ _ - - #
int score_d2 = 0;           // game score; digit 2: L _ _ - # -
int score_d3 = 0;           // game score; digit 3: L _ _ # - -
int set_size = 30;          // amount of letters in initial set
int g_backs = 3;            // guaranteed number of n-back repetitions

char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";


void setup()
{ 
  // Initialize the on-board LCD
  LCD.init();
  
  // Start serial communication at 9600 bits/second
  Serial.begin(9600); 
  
  // Turn the red LED off (it turns on after serial comm. begins)
  digitalWrite(LED1, LOW);
  
  // set the on-board push buttons 1 & 2 with input pullup
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);

  // Splash ////
  printdc("n back", 3000);                                       // title, delay
  
  // Prompt -- n-back # ////
  scroll_left("Select n back number", 1000, 400);                         // string, initial pause, scroll rate
  delay(1000);
  LCD.clear();

  // Menu Selection -- n-back #////
  n = menu_selection(9);                                             // argument: 9 menu options

  // Prompt -- Difficulty Level ////
  scroll_left("Choose difficulty level", 1000, 400);                 // string, initial pause, scroll rate
  delay(1000);
  LCD.clear();
  
  // Menu Display -- Difficulty Level ////
  menu_display_three_items("1 Hard", "2 Medium", "3 Easy", 300);     // item 1, ite..., scroll speed
  
  // Menu Selection -- Difficulty Level////
  difficulty_level = menu_selection(3)*1000;                         // argument: 3 menu items; scale by 1000 for game delay intervals
  
  // Transition ////
  printdc("Lvl 1", 2000);                                        // string, delay
}

void loop() 
{
  // Variables (that reset after each level)
  int counter;            // for looping through the letters
  int skip_op = 0;        // for skipping unnecessary loop when game button is pressed
  int delay_cycles = 0;   // for partitioning the "while loop" into tiny cycles to read game button
  int backs = 0;          // for counting how many times there will be a deliberate n-back in a set
  int temp = 0;           // for holding temporary index numbers when placing n-back repetitions in a set
  
  // Generating list of letters
  char letter_set[set_size];
  
  for (int i = 0; i < set_size; i++)
  {
    temp = random(25);
    letter_set[i] = alphabet[temp];
  } 
  
  // guarantee some, but randomize an addition of between 0 and 4.
  backs = g_backs + random(4);
  
  for (int j = 0; j < backs; j++)
  {
    temp = random(set_size - n);
      
    letter_set[temp + n] = letter_set[temp];
    Serial.println(letter_set);
  }
  
  Serial.println(letter_set);
  
  // Game loop
  for (counter = 0; counter < set_size; counter++)
  {
    // indicate that letter has changed, in case of same letter resulting next
    LCD.showChar(' ', 0);
    delay(200);
    
    // display next character
    LCD.showChar(letter_set[counter], 0);
    
    
    // display current score
    
    // L _ _ _ _ #
    LCD.showChar(score_d1, 5);
    
    // L _ _ _ # #
    if (score_d2 > 0 || score_d3 > 0)
    {
      LCD.showChar(score_d2, 4);
    }
    
    // L _ _ # # #
    if (score_d3 > 0)
    {
      LCD.showChar(score_d3, 3); 
    }
    
    // check whether n letters ago was the same as current letter, 
    // but only if the counter is past the nth letter in the list
    if ((counter > n) && (letter_set[counter] == letter_set[counter - n]))
    {
      // partition the while loop into tiny pieces to constantly
      // read for an input from the button
      while (delay_cycles < (difficulty_level/2))         // hard-coded approximation; needs code for real timing
      {
        // if the right button is pressed down, given our parent
        // if condition, the button is pressed at the correct time, 
        // so add one to the score, then skip the operation and induce delay
        if(digitalRead(PUSH2) == 0)
        {
          score_d1 = score_d1 + !(digitalRead(PUSH2));
          
          // Score display management ////
          
          // L _ _ - # 1
          if (score_d1 > 9)
          {
            score_d1 = 0;
            score_d2 += 1; 
            
            // L _ _ # 1 1
            if (score_d2 > 9)
            {
              score_d2 = 0;
              score_d3 += 1;
              
              LCD.showChar(score_d1, 5);
              LCD.showChar(score_d2, 4);
              LCD.showChar(score_d3, 3);
            }
            else
            {
              LCD.showChar(score_d1, 5);
              LCD.showChar(score_d2, 4);
            }
          }
          // L _ _ - - #
          else
          {
            LCD.showChar(score_d1, 5);
          }
          // //////////////////////// ////
          
          // grab the remaining time in loop
          skip_op = (difficulty_level) - delay_cycles;    // difficulty_level = maximum loop time, so always > delay_cycles
          
          delay_cycles += skip_op;                        // necessary closure for the remainder of the while loop
          
          delay(skip_op);                                 // delay just enough to not cause noticeable time variance
        }
        
        delay_cycles++;
        delay(1);
      }
      
      delay_cycles = 0;                                   // reset for next loop
    }
    else
    {
      delay(difficulty_level);                            // ensure stability (grandfathered from older version of the code); may need optimization
    }
    
  }
  
  // Level management and transitioning
  LCD.clear();
  level += 1;
  if (level > 0 && level < 10)
  {
    LCD.displayText("Lvl ");
    LCD.showChar(level, 4);
  }
  if (level > 9 && level < 100)
  {
    LCD.println("");
    LCD.print("Lvl ");
    LCD.println(level);
  }
  if (level > 99)
  {
    level = 1;
    score_d1, score_d2, score_d3 = 0;
    LCD.displayText("Reset");
    delay(3000);
    LCD.clear();
    LCD.displayText("Lvl ");
    LCD.showChar(level, 4);
  }
  delay(3000);
  LCD.clear();
}

