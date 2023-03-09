#include <Arduino.h>
#include <vector>
using namespace std;

// Setup for different grids on 7x15 board
extern byte grid[7][15];

extern byte border[30];

vector<vector<byte>>grid_for_content(int pos);
vector<vector<byte>>grid_for_flow_content(int pos);

// distance for clock
extern byte pos_L;
extern byte pos_LM;
extern byte pos_RM;
extern byte pos_R;

// defined grids for displaying time
extern vector<vector<byte>>gridL;
extern vector<vector<byte>>gridLM;
extern vector<vector<byte>>gridRM;
extern vector<vector<byte>>gridR;

// draw symbols into grid
vector<byte> drawer(vector<vector<bool>> symbol, vector<vector<byte>>grid_to_draw);

// Alphabet
extern vector<vector<bool>> A;
extern vector<vector<bool>> B;
extern vector<vector<bool>> C;
extern vector<vector<bool>> D;
extern vector<vector<bool>> E;
extern vector<vector<bool>> F;
extern vector<vector<bool>> G;
extern vector<vector<bool>> H;
extern vector<vector<bool>> I;
extern vector<vector<bool>> J;
extern vector<vector<bool>> K;
extern vector<vector<bool>> L;
extern vector<vector<bool>> M;
extern vector<vector<bool>> N;
extern vector<vector<bool>> O;
extern vector<vector<bool>> P;
extern vector<vector<bool>> Q;
extern vector<vector<bool>> R;
extern vector<vector<bool>> S;
extern vector<vector<bool>> T;
extern vector<vector<bool>> U;
extern vector<vector<bool>> V;
extern vector<vector<bool>> W;
extern vector<vector<bool>> X;
extern vector<vector<bool>> Y;
extern vector<vector<bool>> Z;

extern vector<vector<bool>> space;


extern vector<vector<bool>> null;
extern vector<vector<bool>> one;
extern vector<vector<bool>> two;
extern vector<vector<bool>> three;
extern vector<vector<bool>> four;
extern vector<vector<bool>> five;
extern vector<vector<bool>> six;
extern vector<vector<bool>> seven;
extern vector<vector<bool>> eight;
extern vector<vector<bool>> nine;