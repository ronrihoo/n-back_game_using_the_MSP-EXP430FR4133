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
void scroll_left(char x[], int initial_pause, int scroll_speed, int post_delay, boolean post_clear);
void scroll_right(char x[], int initial_pause, int scroll_speed, int post_delay, boolean post_clear);
void scroll_left_wlength(char x[], int length, int initial_pause, int scroll_speed, int post_delay, boolean post_clear);
void scroll_right_wlength(char x[], int length, int initial_pause, int scroll_speed, int post_delay, boolean post_clear);
void scroll_left_bounded(char x[], int initial_pause, int scroll_speed, int post_delay, boolean post_clear);
void scroll_right_bounded(char x[], int initial_pause, int scroll_speed, int post_delay, boolean post_clear);

// PRINT FUNCTIONS
void LCD_printd(char the_string[], int delay_time);       // print, delay
void LCD_printdc(char the_string[], int delay_time);      // print, delay, clear
void LCD_delay_clear(int delay_time);                     // delay, clear

// MENU FEATURES
void menu_display_three_items(char item1[], char item2[], char item3[], int item_scroll_speed);
int menu_selection(int items);

// CHARACTER COUNTERS
int lengthof(char set[]);
int limlengthof(char set[], int limit);

#endif
