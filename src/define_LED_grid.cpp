#include <Arduino.h>
#include <vector>
using namespace std;

// Setup for different grids on 7x15 board
byte grid[7][15] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
    {29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15},
    {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44},
    {59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45},
    {60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74},
    {89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75},
    {90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104}};

byte border[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104};


byte grid_for_content(byte pos){
    byte grid_array[5][3];

    for (int i=0+pos; i<3+pos; i++){
        
        for(int l=1; l<6; l++){
            grid_array[l-1][i-pos] = grid[l][i];
        }
    }
    return grid_array[5][3];
}

// distance for clock
byte L=0;
byte LM=4;
byte RM=8;
byte R=12;

// defined grids for displaying time
byte gridL[5][3] = {grid_for_content(L)};
byte gridLM[5][3] = {grid_for_content(LM)};
byte gridRM[5][3] = {grid_for_content(RM)};
byte gridR[5][3] = {grid_for_content(R)};

// draw symbols into grid
vector<byte> drawer(bool symbol[5][3], byte grid_to_draw[5][3]){
    vector<byte> symbol_on_grid_vector = {};
    
    for (int i=0; i<6; i++){
        for (int l=0; l<3; i++){
            if (symbol[i][l] == 1){
                symbol_on_grid_vector.push_back(grid_to_draw[i][l]);
            }
        }
    }
    return symbol_on_grid_vector;
}

// Alphabet
bool A[5][3] = {
    {0,1,0},
    {1,0,1},
    {1,1,1},
    {1,0,1},
    {1,0,1}
};
bool B[5][3] = {
    {1,1,0},
    {1,0,1},
    {1,1,0},
    {1,0,1},
    {1,1,0}
};
bool C[5][3] = {
    {0,1,1},
    {1,0,0},
    {1,0,0},
    {1,0,0},
    {0,1,1}
};
bool D[5][3] = {
    {1,1,0},
    {1,0,1},
    {1,0,1},
    {1,0,1},
    {1,1,0}
};
bool E[5][3] = {
    {1,1,1},
    {1,0,0},
    {1,1,1},
    {1,0,0},
    {1,1,1}
};
bool F[5][3] = {
    {1,1,1},
    {1,0,0},
    {1,1,0},
    {1,0,0},
    {1,0,0}
};




bool null[5][3] = {
    {1,1,1},
    {1,0,1},
    {1,0,1},
    {1,0,1},
    {1,1,1}
};
bool one[5][3] = {
    {0,0,1},
    {0,1,1},
    {0,0,1},
    {0,0,1},
    {0,0,1}
};
bool two[5][3] = {
    {1,1,1},
    {0,0,1},
    {1,1,1},
    {1,0,0},
    {1,1,1}
};
bool three[5][3] = {
    {1,1,1},
    {0,0,1},
    {1,1,1},
    {0,0,1},
    {1,1,1}
};
bool four[5][3] = {
    {1,0,1},
    {1,0,1},
    {1,1,1},
    {0,0,1},
    {0,0,1}
};
bool five[5][3] = {
    {1,1,1},
    {1,0,0},
    {1,1,1},
    {0,0,1},
    {1,1,1}
};
bool six[5][3] = {
    {1,1,1},
    {1,0,0},
    {1,1,1},
    {1,0,1},
    {1,1,1}
};
bool seven[5][3] = {
    {1,1,1},
    {0,0,1},
    {0,1,0},
    {0,1,0},
    {0,1,0}
};
bool eight[5][3] = {
    {1,1,1},
    {1,0,1},
    {1,1,1},
    {1,0,1},
    {1,1,1}
};
bool nine[5][3] = {
    {1,1,1},
    {1,0,1},
    {1,1,1},
    {0,0,1},
    {1,1,1}
};