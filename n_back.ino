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
// Info:    "USE RIGHT BUTTON TO SELECT OR UNPAUSE"  (scrolls left)
//          "USE LEFT BUTTON TO ENTER OR PAUSE"      (scrolls left)
// 
// Prompt:  "SELECT N BACK NUMBER" (scrolls left)
// Menu:    " SEL: #"  (prints; where # can be: 1, 2, ..., 9)
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
int stimuli = 0;            // game stimuli level (use of distractions; e.g: LEDs)

// game
int level = 1;              // game level
int score_d1 = 0;           // game score; digit 1: L _ _ - - #
int score_d2 = 0;           // game score; digit 2: L _ _ - # -
int score_d3 = 0;           // game score; digit 3: L _ _ # - -
int set_size = 30;          // amount of letters in initial set
int g_backs = 3;            // guaranteed number of n-back repetitions
boolean pause = false;      // game pause option

char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";


void setup()
{ 
  // Initialize the on-board LCD
  LCD.init();
  
  // Turn the red LED off (it turns on after serial comm. begins)
  digitalWrite(LED1, LOW);
  
  // set the on-board push buttons 1 & 2 with input pullup
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  
  // initialize LEDs
  pinMode(LED1, OUTPUT);      
  pinMode(LED2, OUTPUT);

  // Splash ////
  LCD_printdc("n back", 3000);                                             // title, delay
  
  // Prompt -- Menu Instructions ////
  scroll_left_bounded("Use right button to select or unpause", 1000, 350, 0, true);
  scroll_left_bounded("Use left button to enter or pause", 1000, 350, 0, true);
  
  // Prompt -- N-Back # ////
  scroll_left("Select n back number", 1000, 350, 0, true);                 // string, initial pause, scroll rate, post pause, clear

  // Menu Selection -- N-Back #////
  n = menu_selection(9);                                                   // argument: 9 menu options

  // Prompt -- Difficulty Level ////
  scroll_left("Choose difficulty level", 1000, 350, 1000, true);           // string, initial pause, scroll rate, post pause, clear
  
  // Menu Display -- Difficulty Level ////
  menu_display_three_items("1 Hard", "2 Medium", "3 Easy", 300);           // item 1, ite..., scroll speed

  // Menu Selection -- Difficulty Level////
  difficulty_level = menu_selection(3)*1000;                               // argument: 3 menu items; scale by 1000 for game delay intervals
  
  // Transition ////
  LCD_printdc("Lvl 1", 2000);                                              // string, delay
}

void loop() 
{
  // Variables (that reset after each level)
  int counter;            // for looping through the letters
  int skip_op = 0;        // for skipping unnecessary loop when game button is pressed
  int delay_cycles = 0;   // for partitioning the "while loop" into tiny cycles to read game button
  int backs = 0;          // for counting how many times there will be a deliberate n-back in a set
  int level_score = 0;    // for counting how many n-backs have been scored in the current level (used for end-of-level messages)
  int temp = 0;           // for holding temporary index numbers when placing n-back repetitions in a set
  
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // n-back letter list generation //////                                                  // n-back letter list generation //////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // generate list of letters
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
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // level loop //////                                                                                        // level loop //////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  for (counter = 0; counter < set_size; counter++)
  {
    // indicate that letter has changed, in case of same letter resulting next
    LCD.showChar(' ', 0);
    delay(200);
    
    // display next character
    LCD.showChar(letter_set[counter], 0);
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // current score display //////                                                                // current score display //////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // L _ _ _ _ #  (comment indicates the output on the six segments of the LCD display)
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
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // user input management //////                                                                // user input management //////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // partition the while loop into tiny pieces to constantly
    // read for an input from the button
    while (delay_cycles < (difficulty_level/2))          // hard-coded approximation; needs code for real timing
    {
      // left button induces game pause; right button induces unpause
      if (digitalRead(PUSH1) == 0)
      {
        if (stimuli > 0)
        {
          digitalWrite(LED1, 1);                         // turn red LED on
        }
        
        LCD.showSymbol(LCD_SEG_CLOCK, 1);                // the clock segment on the LCD will indicate pause
        pause = true;
        delay(200);                                      // delay to ensure correct digital reading
        
        // pause until right button is pressed
        while (pause == true)
        {
          pause = (digitalRead(PUSH2));                  // waiting for right button to get pressed
        }
        
        if (stimuli > 0)
        {
          digitalWrite(LED1, 0);                         // turn red LED off
        }
        
        LCD.showSymbol(LCD_SEG_CLOCK, 0);                // turning off the clock segment
      }
      
      // when right (side) button is pressed down
      if(digitalRead(PUSH2) == 0)
      {
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // n-back check //////                                                                              // n-back check //////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // if the counter is past the nth letter in the list and the current letter is the same as n letters ago, 
        // then given the parent 'if condition,' the button is pressed at the correct time, so add one to the score, 
        // display it, skip the operation, and induce appropriate delay
        if ((counter > n) && (letter_set[counter] == letter_set[counter - n]))
        {
          // add one to score and level_score
          score_d1 = score_d1 + 1;
          level_score++;
          
          // when stimuli level is more than zero
          if (stimuli > 0)
          {
            digitalWrite(LED2, 1);                       // turn green LED on
          }

          ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          // score display management //////                                                    // score display management //////
          ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          
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
          ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          // end of: score display management //                                            // end of: score display management //
          ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          // back to: n-back check //                                                                  // back to: n-back check //
          ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////          
          
          // grab the remaining time in loop
          skip_op = (difficulty_level) - delay_cycles;   // difficulty_level = maximum loop time, so always > delay_cycles
          
          delay_cycles += skip_op;                       // necessary closure for the remainder of the while loop
          
          // let stimulus (green light) remain on for long enough to create a desirable UX
          delay(skip_op/2);
          
          // when stimuli level is more than zero
          if (stimuli > 0)
          {
            digitalWrite(LED2, 0);                       // turn green LED off
          }
          
          delay(skip_op/2);                              // delay just enough to not cause noticeable time variance
        }
        // end of: n-back check ////////////////////////////////////////////////////////////////////////// end of: n-back check //
      }
      
      delay_cycles++;
      delay(1);
    } 
    // end of: user input management (while loop) ////////////////////////////////// end of: user input management (while loop) //
    delay_cycles = 0;
  } 
  // end of: level loop //////////////////////////////////////////////////////////////////////////////////// end of: level loop //
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // level management and transition //////                                              // level management and transition //////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  
  LCD.clear();                                  // clear screen for transitioning phase
  level += 1;                                   // increment level
  
  // end-of-level message //////////////////////////////////////////////////////////////////////////////// end-of-level message //
  if (level_score >= backs)
  {
    scroll_left("Excellent", 1000, 300, 0, true);
  }
  else if (level_score < backs && level_score >= (backs - 2))
  {
    scroll_left("Good job", 1000, 300, 0, true);
  }
  
  // when level is between 1-9
  if (level > 0 && level < 10)
  {
    LCD.displayText("Lvl ");
    LCD.showChar(level, 4);
  }
  // when level is between 10-99, use a different way to print
  if (level > 9 && level < 100)
  {
    LCD.println("");                            // clear segments only
    LCD.print("Lvl ");                          // "LVL" to imply "level"
    LCD.println(level);                         // hard-coded out of laziness: specifically for a six-segment LCD
  }
  // when level goes to 100, reset the game (level 99 is currently the final level)
  if (level > 99)
  {
    level = 1;                                  // reset level to 1
    score_d1, score_d2, score_d3 = 0;           // reset all score digits
    LCD_printdc("Reset", 3000);                 // string, delay, clear
    LCD.displayText("Lvl ");                    // "L V L _ _ _ " -- use segments 0 (L), 1 (V), 2 (L), 3 (space)
    LCD.showChar(level, 4);                     // "L V L _ # _ " -- print level number in segment 4 (segment 5 unused)
  }
  LCD_delay_clear(3000);                        // from LCD_Launchpad_Addon
}
