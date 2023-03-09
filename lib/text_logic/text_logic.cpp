#include <Arduino.h>
#include <vector>
#include <iostream>
#include <define_LED_grid.h>
#include <main.h>
using namespace std;

vector<vector<bool>> ret_character(5, vector<bool>(3));
byte str_size;
vector<int> negative_iterator;
vector<vector<bool>> text_symbol(5, vector<bool>(3));
vector<byte> print_symbol;
vector<vector<byte>> text_grid(5, vector<byte>(3));
byte itera;
int loop0;
int loop1;
int loop2;
int loop3;
char character;

vector<vector<bool>> get_character(char character)
{
    switch (character)
    {
    case ' ':
        ret_character = space;
        break;

    case 'A':
        ret_character = A;
        break;

    case 'B':
        ret_character = B;
        break;

    case 'C':
        ret_character = C;
        break;

    case 'D':
        ret_character = D;
        break;

    case 'E':
        ret_character = E;
        break;

    case 'F':
        ret_character = F;
        break;

    case 'G':
        ret_character = G;
        break;

    case 'H':
        ret_character = H;
        break;

    case 'I':
        ret_character = I;
        break;

    case 'J':
        ret_character = J;
        break;

    case 'K':
        ret_character = K;
        break;

    case 'L':
        ret_character = L;
        break;

    case 'M':
        ret_character = M;
        break;

    case 'N':
        ret_character = N;
        break;

    case 'O':
        ret_character = O;
        break;

    case 'P':
        ret_character = P;
        break;

    case 'Q':
        ret_character = Q;
        break;

    case 'R':
        ret_character = R;
        break;

    case 'S':
        ret_character = S;
        break;

    case 'T':
        ret_character = T;
        break;

    case 'U':
        ret_character = U;
        break;

    case 'V':
        ret_character = V;
        break;

    case 'W':
        ret_character = W;
        break;

    case 'X':
        ret_character = X;
        break;

    case 'Y':
        ret_character = Y;
        break;

    case 'Z':
        ret_character = Z;
        break;

    case 'Ä':
        ret_character = AE;
        break;

    case 'Ü':
        ret_character = UE;
        break;

    case 'Ö':
        ret_character = OE;
        break;

    case '0':
        ret_character = null;
        break;

    case '1':
        ret_character = one;
        break;

    case '2':
        ret_character = two;
        break;

    case '3':
        ret_character = three;
        break;

    case '4':
        ret_character = four;
        break;

    case '5':
        ret_character = five;
        break;

    case '6':
        ret_character = six;
        break;

    case '7':
        ret_character = seven;
        break;

    case '8':
        ret_character = eight;
        break;

    case '9':
        ret_character = nine;
        break;
    }
    return ret_character;
}

int translate_position(int position)
{
    // left side of the grid should be position 0, but in define_grid_cpp
    // left is position 0 and right is position 14.

    // calculate correct position:
    int translated_position;
    translated_position = 19 - position;
    return translated_position;
}

vector<byte> disassemble(String flowtext)
{
    str_size = flowtext.length();
    negative_iterator.resize(str_size);

    for (loop0 = 0; loop0 < str_size; loop0++)
    {
        negative_iterator[loop0] = -(4 * loop0) - 1;
    }
    for (loop1 = 0; negative_iterator.back() < 19; loop1++)
    {
            for (loop3 = 0; loop3 < str_size; loop3++ /* char const &character : flowtext */)
            {
                character = flowtext[loop3];
                text_symbol = get_character(character);

                if (negative_iterator[loop3] < 19 && negative_iterator[loop3] >= 0)
                {
                    text_grid = grid_for_flow_content(translate_position(negative_iterator[loop3]));
                    print_symbol = drawer(text_symbol, text_grid);
                    instantOn(print_symbol);
                    FastLED.show();
                }
            }
            FastLED.clear();
            delay(150);
        for (loop2 = 0; loop2 < (int)negative_iterator.size(); loop2++)
        {
            negative_iterator[loop2]++;
        }
    }
    return print_symbol;
}