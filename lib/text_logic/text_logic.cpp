#include <Arduino.h>
#include <vector>
#include <iostream>
#include <define_LED_grid.h>
using namespace std;

void tester(vector<vector<bool>> test_vector)
{
    for (int i = 0; i < test_vector.size(); i++)
    {
        for (int j = 0; j < test_vector[i].size(); j++)
        {
            Serial.print(test_vector[i][j]);
        }
        Serial.println();
    }
}

vector<vector<bool>> get_character(char character)
{
    bool(*temp_character)[3];
    vector<vector<bool>> ret_character(5, vector<bool>(3));
    switch (character)
    {
    case ' ':
        temp_character = space;
        break;

    case 'A':
        temp_character = A;
        break;

    case 'B':
        temp_character = B;
        break;

    case 'C':
        temp_character = C;
        break;

    case 'D':
        temp_character = D;
        break;

    case 'E':
        temp_character = E;
        break;

    case 'F':
        temp_character = F;
        break;

    case 'G':
        temp_character = G;
        break;

    case 'H':
        temp_character = H;
        break;

    case 'I':
        temp_character = I;
        break;

    case 'J':
        temp_character = J;
        break;

    case 'K':
        temp_character = K;
        break;

    case 'L':
        temp_character = L;
        break;

    case 'M':
        temp_character = M;
        break;

    case 'N':
        temp_character = N;
        break;

    case 'O':
        temp_character = O;
        break;

    case 'P':
        temp_character = P;
        break;

    case 'Q':
        temp_character = Q;
        break;

    case 'R':
        temp_character = R;
        break;

    case 'S':
        temp_character = S;
        break;

    case 'T':
        temp_character = T;
        break;

    case 'U':
        temp_character = U;
        break;

    case 'V':
        temp_character = V;
        break;

    case 'W':
        temp_character = W;
        break;

    case 'X':
        temp_character = X;
        break;

    case 'Y':
        temp_character = Y;
        break;

    case 'Z':
        temp_character = Z;
        break;

    case '0':
        temp_character = null;
        break;

    case '1':
        temp_character = one;
        break;

    case '2':
        temp_character = two;
        break;

    case '3':
        temp_character = three;
        break;

    case '4':
        temp_character = four;
        break;

    case '5':
        temp_character = five;
        break;

    case '6':
        temp_character = six;
        break;

    case '7':
        temp_character = seven;
        break;

    case '8':
        temp_character = eight;
        break;

    case '9':
        temp_character = nine;
        break;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ret_character[i][j] = *(*(temp_character + i) + j);
        }
    }

    // Serial.println("character:");
    // for (int i=0; i<5; i++){

    //     for (int l=0; l<3; l++){
    //         Serial.print(ret_character[i][l]);
    //         Serial.print(" ");
    //     }
    //     Serial.println();
    // }

    return ret_character;
}

void disassemble()
{

    String test_string = "SEND NUDES";

    byte str_size = test_string.length();
    vector<int> negative_iterator(str_size);

    for (int i=0; i<str_size; i++){
        negative_iterator[i] = -(4*i)-1;
    }


    vector<vector<bool>> text_symbol(5, vector<bool>(3));
    vector<vector<byte>> text_grid(5, vector<byte>(3));

    for (int i=0; negative_iterator[str_size]<16; i++){
        byte iterator = 0;
        for (char const &character : test_string){
            text_symbol = get_character(character);
            text_grid = grid_for_content(negative_iterator[iterator]);
            iterator++;
        }
        for (int l=0; l<negative_iterator.size();l++){
            negative_iterator[l]++;
        }
    }

    // calculate correct position











    // vector<vector<bool>> text_vector = {{0}, {0}, {0}, {0}, {0}};
    // vector<vector<bool>> character_vector(5, vector<bool>(3));
    // for (char const &iterator : test_string)
    // {
    //     character_vector = get_character(iterator);

    //     for (int i = 0; i < 5; i++)
    //     {
    //         text_vector.push_back(character_vector[i]);
    //     }
    // }


    // for (int i = 0; i < text_vector.size(); i++)
    // {
    //     for (int j = 0; j < text_vector[i].size(); j++)
    //     {
    //         Serial.print(text_vector[i][j]);
    //     }
    //     Serial.println();
    //     delay(2000);
    // }
}