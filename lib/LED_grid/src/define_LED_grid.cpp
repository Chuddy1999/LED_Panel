#include <Arduino.h>
#include <vector>
#include <define_LED_grid.h>
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

// Grid for Flowtext, 105 will get erased in later logic
byte grid_for_flow[7][21] = {
    {105, 105, 105, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 105, 105, 105},
    {105, 105, 105, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 105, 105, 105},
    {105, 105, 105, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 105, 105, 105},
    {105, 105, 105, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 105, 105, 105},
    {105, 105, 105, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 105, 105, 105},
    {105, 105, 105, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 105, 105, 105},
    {105, 105, 105, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 105, 105}};

byte border[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104};

// Alphabet
vector<vector<bool>> A = {
    {false,true,false},
    {true,false,true},
    {true,true,true},
    {true,false,true},
    {true,false,true}
};
vector<vector<bool>> B = {
    {true,true,false},
    {true,false,true},
    {true,true,false},
    {true,false,true},
    {true,true,false}
};
vector<vector<bool>> C = {
    {false,true,true},
    {true,false,false},
    {true,false,false},
    {true,false,false},
    {false,true,true}
};
vector<vector<bool>>D = {
    {true,true,false},
    {true,false,true},
    {true,false,true},
    {true,false,true},
    {true,true,false}
};
vector<vector<bool>>E = {
    {true,true,true},
    {true,false,false},
    {true,true,true},
    {true,false,false},
    {true,true,true}
};
vector<vector<bool>>F = {
    {true,true,true},
    {true,false,false},
    {true,true,false},
    {true,false,false},
    {true,false,false}
};
vector<vector<bool>>G = {
    {true,true,true},
    {true,false,false},
    {true,false,true},
    {true,false,true},
    {true,true,true}
};
vector<vector<bool>>H = {
    {true,false,true},
    {true,false,true},
    {true,true,true},
    {true,false,true},
    {true,false,true}
};
vector<vector<bool>>I = {
    {true,true,true},
    {false,true,false},
    {false,true,false},
    {false,true,false},
    {true,true,true}
};
vector<vector<bool>>J = {
    {true,true,true},
    {false,false,true},
    {true,false,true},
    {true,false,true},
    {false,true,true}
};
vector<vector<bool>>K = {
    {true,false,true},
    {true,true,false},
    {true,false,false},
    {true,true,false},
    {true,false,true}
};
vector<vector<bool>>L = {
    {true,false,false},
    {true,false,false},
    {true,false,false},
    {true,false,false},
    {true,true,true}
};
vector<vector<bool>>M = {
    {true,false,true},
    {true,true,true},
    {true,false,true},
    {true,false,true},
    {true,false,true}
};
vector<vector<bool>>N = {
    {true,true,true},
    {true,false,true},
    {true,false,true},
    {true,false,true},
    {true,false,true}
};
vector<vector<bool>>O = {
    {false,true,false},
    {true,false,true},
    {true,false,true},
    {true,false,true},
    {false,true,false}
};
vector<vector<bool>>P = {
    {true,true,true},
    {true,false,true},
    {true,true,true},
    {true,false,false},
    {true,false,false}
};
vector<vector<bool>>Q = {
    {true,true,true},
    {true,false,true},
    {true,true,true},
    {false,false,true},
    {false,false,true}
};
vector<vector<bool>>R = {
    {true,true,true},
    {true,false,true},
    {true,true,true},
    {true,true,false},
    {true,false,true}
};
vector<vector<bool>>S = {
    {true,true,true},
    {true,false,false},
    {true,true,true},
    {false,false,true},
    {true,true,true}
};
vector<vector<bool>>T = {
    {true,true,true},
    {false,true,false},
    {false,true,false},
    {false,true,false},
    {false,true,false}
};
vector<vector<bool>>U = {
    {true,false,true},
    {true,false,true},
    {true,false,true},
    {true,false,true},
    {true,true,true}
};
vector<vector<bool>>V = {
    {false,false,false},
    {true,false,true},
    {true,false,true},
    {true,false,true},
    {false,true,false}
};
vector<vector<bool>>W = {
    {true,false,true},
    {true,false,true},
    {true,false,true},
    {true,true,true},
    {true,false,true}
};
vector<vector<bool>>X = {
    {false,false,false},
    {false,false,false},
    {true,false,true},
    {false,true,false},
    {true,false,true}
};
vector<vector<bool>>Y = {
    {true,false,true},
    {true,false,true},
    {true,true,true},
    {false,true,false},
    {false,true,false}
};
vector<vector<bool>>Z = {
    {true,true,true},
    {false,false,true},
    {false,true,false},
    {true,false,false},
    {true,true,true}
};

vector<vector<bool>>space = {
    {false,false,false},
    {false,false,false},
    {false,false,false},
    {false,false,false},
    {false,false,false}
};



vector<vector<bool>>null = {
    {true,true,true},
    {true,false,true},
    {true,false,true},
    {true,false,true},
    {true,true,true}
};
vector<vector<bool>>one = {
    {false,false,true},
    {false,true,true},
    {false,false,true},
    {false,false,true},
    {false,false,true}
};
vector<vector<bool>>two = {
    {true,true,true},
    {false,false,true},
    {true,true,true},
    {true,false,false},
    {true,true,true}
};
vector<vector<bool>>three = {
    {true,true,true},
    {false,false,true},
    {true,true,true},
    {false,false,true},
    {true,true,true}
};
vector<vector<bool>>four = {
    {true,false,true},
    {true,false,true},
    {true,true,true},
    {false,false,true},
    {false,false,true}
};
vector<vector<bool>>five = {
    {true,true,true},
    {true,false,false},
    {true,true,true},
    {false,false,true},
    {true,true,true}
};
vector<vector<bool>>six = {
    {true,true,true},
    {true,false,false},
    {true,true,true},
    {true,false,true},
    {true,true,true}
};
vector<vector<bool>>seven = {
    {true,true,true},
    {false,false,true},
    {false,true,false},
    {false,true,false},
    {false,true,false}
};
vector<vector<bool>>eight = {
    {true,true,true},
    {true,false,true},
    {true,true,true},
    {true,false,true},
    {true,true,true}
};
vector<vector<bool>>nine = {
    {true,true,true},
    {true,false,true},
    {true,true,true},
    {false,false,true},
    {true,true,true}
};


vector<vector<bool>>exclamation = {
    {false,true,false},
    {false,true,false},
    {false,true,false},
    {false,false,false},
    {false,true,false}
};

vector<vector<bool>>question = {
    {true,true,false},
    {false,false,true},
    {false,true,false},
    {false,false,false},
    {false,true,false}
};

vector<vector<bool>>bracketL = {
    {false,false,true},
    {false,true,false},
    {false,true,false},
    {false,true,false},
    {false,false,true}
};

vector<vector<bool>>bracketR = {
    {true,false,false},
    {false,true,false},
    {false,true,false},
    {false,true,false},
    {true,false,false}
};

vector<vector<bool>>colon = {
    {false,false,false},
    {false,true,false},
    {false,false,false},
    {false,true,false},
    {false,false,false}
};

vector<vector<bool>>addition = {
    {false,false,false},
    {false,true,false},
    {true,true,true},
    {false,true,false},
    {false,false,false}
};

vector<vector<bool>>subtraction = {
    {false,false,false},
    {false,false,false},
    {true,true,true},
    {false,false,false},
    {false,false,false}
};

vector<vector<bool>>underscore = {
    {false,false,false},
    {false,false,false},
    {false,false,false},
    {false,false,false},
    {true,true,true}
};

vector<vector<bool>>multi = {
    {false,false,false},
    {false,false,false},
    {false,true,false},
    {false,false,false},
    {false,false,false}
};

vector<vector<bool>>dot = {
    {false,false,false},
    {false,false,false},
    {false,false,false},
    {false,false,false},
    {false,true,false}
};



// distance for clock
byte pos_L=0;
byte pos_LM=4;
byte pos_RM=8;
byte pos_R=12;


vector<vector<byte>>grid_for_content(int pos){
    vector<vector<byte>> grid_array(5, vector<byte>(3));

    for (int h = 0; h < 5; h++){

        for (int w = 0; w < 3; w++){
            grid_array[h][w] = grid[h+1][w+pos];
        }
    }
    return grid_array;
}


vector<vector<byte>>grid_for_flow_content(int pos){
    vector<vector<byte>> grid_array(5, vector<byte>(3));

    for (int h = 0; h < 5; h++){

        for (int w = 0; w < 3; w++){
            grid_array[h][w] = grid_for_flow[h+1][w+pos];
        }
    }
    return grid_array;
}


// defined grids for displaying time
vector<vector<byte>> gridL = grid_for_content(pos_L);
vector<vector<byte>> gridLM = grid_for_content(pos_LM);
vector<vector<byte>> gridRM = grid_for_content(pos_RM);
vector<vector<byte>> gridR = grid_for_content(pos_R);

// draw symbols into grid
vector<byte> drawer(vector<vector<bool>>symbol, vector<vector<byte>>grid_to_draw){
    vector<byte> symbol_on_grid_vector;
    grid_to_draw.resize(5, vector<byte>(3));
    symbol.resize(5, vector<bool>(3));
    
    for (int i=0; i<5; i++){
        for (int l=0; l<3; l++){
            if (symbol[i][l] == true && grid_to_draw[i][l] != 105){
                symbol_on_grid_vector.push_back(grid_to_draw[i][l]);
            }
        }
    }

    return symbol_on_grid_vector;       // returns all bytes of grid, that shall light up
}