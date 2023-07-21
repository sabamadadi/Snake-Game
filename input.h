#ifndef _input_h
#define _input_h

#include <iostream>

using namespace std;

struct Direction {
    string curDirection;
};

void input_initialize(void);
Direction get_input(void);

#endif