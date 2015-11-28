///////////////////////////////////////////////////////////////////////////////////////////
// LCD_Launchpad_Addon.cpp
//
// Brief: adding functionality to the segmented LCD on the MSP-EXP430FR4133.
// 
// Author: Ronald Rihoo
//
///////////////////////////////////////////////////////////////////////////////////////////

#include "LCD_Launchpad.h"
#include "LCD_Launchpad_Addon.h"

LCD_LAUNCHPAD LCD_XYZ;        // using a weird name so that one of the common ones won't be used here

// SCROLLERS ////

// Scroll Left
void scroll_left(char x[], int initial_pause, int scroll_speed, int post_delay, boolean post_clear)
{
  int i = 0;
  int j = 0;
  int k = 0;
  
  int length = lengthof(x) + 1;
  
  for (i = 0; i < length; i++)
  {
    k = (length - 1) - i;
    
    if (k >= 6)
    {
      for (j = 0; j < 6; j++)
      {
        LCD_XYZ.showChar(x[i+j], j);
      }
    }
    else
    {
      for (j = 0; j < 6; j++)
      {
        if (j < k)
        {
          LCD_XYZ.showChar(x[i+j], j);
        }
        else
        {
          LCD_XYZ.showChar(' ', j);
        }
      }
    }
    

    // Wait so that the first word can be seen fully prior to scrolling
    if (i == 0)
    {
      delay(initial_pause);
    }    

    // Allow user to escape the message
    if (!(digitalRead(PUSH2)))
    {
      i = length;
    }
    else
    {
      // Regular scrolling speed
      delay(scroll_speed);
    }
  }
  
  delay(post_delay);
  
  if(post_clear == true)
  {
    LCD_XYZ.clear();
  }
}

// Scroll Right
void scroll_right(char x[], int initial_pause, int scroll_speed, int post_delay, boolean post_clear)
{
  int i = 0;
  int j = 0;
  int k = 0;
  
  int length = lengthof(x);
  
  for (i = 0; i < length + 1; i++)
  {
    k = (length - 1) - i;
    
    if (k >= 6)
    {
      for (j = 0; j < 6; j++)
      {
        LCD_XYZ.showChar(x[k-j], 5-j);
      }
    }
    else
    {
      for (j = 0; j < 6; j++)
      {
        if (j <= k)
        {
          LCD_XYZ.showChar(x[k-j], 5-j);
        }
        else
        {
          LCD_XYZ.showChar(' ', 5-j);
        }
      }
    }
    

    // Wait so that the first word can be seen fully prior to scrolling
    if (i == 0)
    {
      delay(initial_pause);
    }    

    // Allow user to escape the message
    if (!(digitalRead(PUSH2)))
    {
      i = length;
    }
    else
    {
      // Regular scrolling speed
      delay(scroll_speed);
    }
  }
  
  delay(post_delay);
  
  if(post_clear == true)
  {
    LCD_XYZ.clear();
  }
}

// Scroll Left - with string length defined
void scroll_left_wlength(char x[], int length, int initial_pause, int scroll_speed, int post_delay, boolean post_clear)
{
  int i = 0;
  int j = 0;
  int k = 0;
  
  for (i = 0; i < length; i++)
  {
    k = (length - 1) - i;
    
    if (k >= 6)
    {
      for (j = 0; j < 6; j++)
      {
        LCD_XYZ.showChar(x[i+j], j);
      }
    }
    else
    {
      for (j = 0; j < 6; j++)
      {
        if (j < k)
        {
          LCD_XYZ.showChar(x[i+j], j);
        }
        else
        {
          LCD_XYZ.showChar(' ', j);
        }
      }
    }
    

    // Wait so that the first word can be seen fully prior to scrolling
    if (i == 0)
    {
      delay(initial_pause);
    }    

    // Allow user to escape the message
    if (!(digitalRead(PUSH2)))
    {
      i = length;
    }
    else
    {
      // Regular scrolling speed
      delay(scroll_speed);
    }
  }
  
  delay(post_delay);
  
  if(post_clear == true)
  {
    LCD_XYZ.clear();
  }
}


// Scroll Right - with string length defined
void scroll_right_wlength(char x[], int length, int initial_pause, int scroll_speed, int post_delay, boolean post_clear)
{
  int i = 0;
  int j = 0;
  int k = 0;
  
  for (i = 0; i < length + 1; i++)
  {
    k = (length - 1) - i;
    
    if (k >= 6)
    {
      for (j = 0; j < 6; j++)
      {
        LCD_XYZ.showChar(x[k-j], 5-j);
      }
    }
    else
    {
      for (j = 0; j < 6; j++)
      {
        if (j <= k)
        {
          LCD_XYZ.showChar(x[k-j], 5-j);
        }
        else
        {
          LCD_XYZ.showChar(' ', 5-j);
        }
      }
    }
    

    // Wait so that the first word can be seen fully prior to scrolling
    if (i == 0)
    {
      delay(initial_pause);
    }    

    // Allow user to escape the message
    if (!(digitalRead(PUSH2)))
    {
      i = length;
    }
    else
    {
      // Regular scrolling speed
      delay(scroll_speed);
    }
  }
  
  delay(post_delay);
  
  if(post_clear == true)
  {
    LCD_XYZ.clear();
  }
}

// Scroll Left - bounded by string length
void scroll_left_bounded(char x[], int initial_pause, int scroll_speed, int post_delay, boolean post_clear)
{
  int i = 0;
  int j = 0;
  int k = 0;
  
  int length = lengthof(x) + 1;
  
  for (i = 0; i < length; i++)
  {
    k = (length - 1) - i;
    
    if (k >= 6)
    {
      for (j = 0; j < 6; j++)
      {
        LCD_XYZ.showChar(x[i+j], j);
      }
    }

    // Wait so that the first word can be seen fully prior to scrolling
    if (i == 0)
    {
      delay(initial_pause);
    }    

    // Allow user to escape the message
    if (!(digitalRead(PUSH2)))
    {
      i = length;
    }
    else
    {
      // Regular scrolling speed
      delay(scroll_speed);
    }
  }
  
  delay(post_delay);
  
  if(post_clear == true)
  {
    LCD_XYZ.clear();
  }
}

// Scroll Right - bounded by string length
void scroll_right_bounded(char x[], int initial_pause, int scroll_speed, int post_delay, boolean post_clear)
{
  int i = 0;
  int j = 0;
  int k = 0;
  
  int length = lengthof(x);
  
  for (i = 0; i < length + 1; i++)
  {
    k = (length - 1) - i;
    
    if (k >= 5)
    {
      for (j = 0; j < 6; j++)
      {
        LCD_XYZ.showChar(x[k-j], 5-j);
      }
    }
    

    // Wait so that the first word can be seen fully prior to scrolling
    if (i == 0)
    {
      delay(initial_pause);
    }    

    // Allow user to escape the message
    if (!(digitalRead(PUSH2)))
    {
      i = length;
    }
    else
    {
      // Regular scrolling speed
      delay(scroll_speed);
    }
  }
  
  delay(post_delay);
  
  if(post_clear == true)
  {
    LCD_XYZ.clear();
  }
}

// PRINT FUNCTIONS ////

// Print and delay
void LCD_printd(char the_string[], int delay_time)
{
  LCD_XYZ.print(the_string);
  delay(delay_time);
}

// Print, delay, and clear
void LCD_printdc(char the_string[], int delay_time)
{
  LCD_XYZ.print(the_string);
  delay(delay_time);
  LCD_XYZ.clear();
}

// delay, and clear
void LCD_delay_clear(int delay_time)
{
  delay(delay_time);
  LCD_XYZ.clear();
}

// MENU FEATURES ////

// Menu Display - three item list
void menu_display_three_items(char item1[], char item2[], char item3[], int item_scroll_speed)
{ 
  int length1 = lengthof(item1) + 1;
  int length2 = lengthof(item2) + 1;
  int length3 = lengthof(item3) + 1;
  
  LCD_XYZ.clear();
  
  if(length1 > 7)
  {
    scroll_left_wlength(item1, length1, 1000, item_scroll_speed, 0, true);
  }
  else
  {
    LCD_printdc(item1, 2000);
  }
  
  if(length2 > 7)
  {
    scroll_left_wlength(item2, length2, 1000, item_scroll_speed, 0, true);
  }
  else
  {
    LCD_printdc(item2, 2000);
  }
  
  if(length3 > 7)
  {
    scroll_left_wlength(item3, length3, 1000, item_scroll_speed, 0, true);
  }
  else
  {
    LCD_printdc(item3, 2000);
  }
}

// Menu Selection - numbered list
int menu_selection(int items)
{
  int selection = 0;
  int choice = 1;
  
  // Mode Selection ////
  while(selection < 1)
  {
    LCD_XYZ.displayText("Sel ", 1);                    // "Sel" for select
    LCD_XYZ.showSymbol(LCD_SEG_COLON4, 1);             // colon in segment 4 (meaning 5th segment)
    
    choice = choice + !(digitalRead(PUSH2));       // initially: choice = 1 + !(1) = 1 + 0 = 1
    
    // in selection phase: reset to 1 after passing 3
    if (choice > items)                                
    {
      choice = 1;
    }
    
    // show selected number in segment 5 (meaning right-most segment)
    LCD_XYZ.showChar(choice, 5);
    
    // when the left push button is pressed down, selection is entered
    if (digitalRead(PUSH1) == 0)
    {
      selection = choice;
    }
    
    // timer is too fast for pushing the button, so delay before next input is read
    delay(200);
  }
      
  LCD_XYZ.clear();
  return selection;
}

// CHARACTER COUNTERS ////

// Limit: 1000 characters
int lengthof(char set[])
{
  for (int i = 0; i < 1000; i++)
  {
    if (set[i] == '\0')
    {
     return i;
    }
  }
}

// Set the loop limit
int limlengthof(char set[], int limit)
{
  for (int i = 0; i < limit; i++)
  {
    if (set[i] == '\0')
    {
      return i;
    }
  }
}
