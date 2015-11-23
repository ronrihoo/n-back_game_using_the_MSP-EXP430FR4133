///////////////////////////////////////////////////////////////////////////////////////////
// LCD_Launchpad_Addon.h
//
// Brief: adding functionality to the segmented LCD on the MSP-EXP430FR4133.
// 
// Author: Ronald Rihoo
//
///////////////////////////////////////////////////////////////////////////////////////////

#ifndef LCD_LAUNCHPAD_ADDON_H_
#define LCD_LAUNCHPAD_ADDON_H_

// SCROLLERS
void scroll_left(char x[], int initial_pause, int scroll_speed);
void scroll_right(char x[], int initial_pause, int scroll_speed);
void scroll_left_wlength(char x[], int length, int initial_pause, int scroll_speed);
void scroll_right_wlength(char x[], int length, int initial_pause, int scroll_speed);
void scroll_left_bounded(char x[], int initial_pause, int scroll_speed);
void scroll_right_bounded(char x[], int initial_pause, int scroll_speed);

// PRINT FUNCTIONS
void printd(char the_string[], int delay_time);       // print, delay
void printdc(char the_string[], int delay_time);      // print, delay, clear

// MENU FEATURES
void menu_display_three_items(char item1[], char item2[], char item3[], int item_scroll_speed);
int menu_selection(int items);

// CHARACTER COUNTERS
int lengthof(char set[]);
int limlengthof(char set[], int limit);

#endif
