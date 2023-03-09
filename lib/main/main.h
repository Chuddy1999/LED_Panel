#include <define_LED_grid.h>
#include <Arduino.h>
#include <FastLED.h>
#include <iostream>
#include <string.h>
#include <array>
#include <vector>

#include <define_LED_grid.h>
#include <text_logic.h>

using namespace std;

extern int Hour;
extern int minu;
extern int sec;
extern int val_L;
extern int val_LM;
extern int val_RM;
extern int val_R;


extern vector<byte>text_print_symbol;


// Date
bool isLastSundayOver(int weekday, int day);

int getTimeOffset();

// Functions
void instantOn(vector<byte>symbol);

/* __________ code to display time __________ */


void setTime(int time_piece, vector<vector<byte>>grid_position);

void getTime();

void rainbow();

/* __________ code to display text __________ */





void handleWSData(String cutData);

String processor(const String &var);