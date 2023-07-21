#include "input.h"
#include <termios.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

struct termios t;

void input_initialize(){
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

Direction get_input(){
    Direction result;
    result.curDirection = "Rast";
    char user_input = getchar();
    switch (user_input){
    case 'a':
        result.curDirection = "Chap";
        break;
    case 'w':
        result.curDirection = "Bala";
        break;
    case 'd':
        result.curDirection = "Rast";
        break;
    case 's':
        result.curDirection = "Paiin";
        break;
    case '\n':
        result.curDirection = "Enter";
        break;
    default:
        result.curDirection = "Error";
        cout << "Incorrect button clicked(" << user_input << ")" << endl;
        break;
    }
    return result;
}
