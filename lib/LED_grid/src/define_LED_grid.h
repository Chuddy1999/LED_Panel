#include <Arduino.h>
#include <vector>
using namespace std;

// Setup for different grids on 7x15 board
extern byte grid[7][15];

extern byte border[30];

vector<vector<byte>>grid_for_content(byte pos);

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
vector<byte> drawer(bool symbol[5][3], vector<vector<byte>>grid_to_draw);

// Alphabet
extern bool A[5][3];
extern bool B[5][3];
extern bool C[5][3];
extern bool D[5][3];
extern bool E[5][3];
extern bool F[5][3];
extern bool G[5][3];
extern bool H[5][3];
extern bool I[5][3];
extern bool J[5][3];
extern bool K[5][3];
extern bool L[5][3];
extern bool M[5][3];
extern bool N[5][3];
extern bool O[5][3];
extern bool P[5][3];
extern bool Q[5][3];
extern bool R[5][3];
extern bool S[5][3];
extern bool T[5][3];
extern bool U[5][3];
extern bool V[5][3];
extern bool W[5][3];
extern bool X[5][3];
extern bool Y[5][3];
extern bool Z[5][3];

extern bool space[5][3];


extern bool null[5][3];
extern bool one[5][3];
extern bool two[5][3];
extern bool three[5][3];
extern bool four[5][3];
extern bool five[5][3];
extern bool six[5][3];
extern bool seven[5][3];
extern bool eight[5][3];
extern bool nine[5][3];