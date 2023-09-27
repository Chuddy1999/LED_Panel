#include <Arduino.h>
#include <vector>
using namespace std;

extern String test_string;
vector<vector<bool>> get_character(char character);
vector<byte> disassemble(String flowtext, function< void() > rbw, function< void() > mqtt_upd);
