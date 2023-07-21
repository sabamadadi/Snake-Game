#ifndef _menu_h
#define _menu_h

#include <semaphore.h>
#include "input.h"
#include <thread>
#include <utility>

using namespace std;

class Menu{
public:
    int position;
    string Options[3] = {"New game", "Load previous game", "Exit"};
    string choice;
    void update_next_direction(Direction direction);
    void update_direction();
    void initialize_menu();
    Direction next_direction;
    bool flag;
private:
    pthread_t input_thread;
    sem_t menu_sema;
};

#endif