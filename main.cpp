#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unistd.h>
#include <utility>
#include "macros.h"
#include "snake.h"
#include "snake_map.h"
#include "menu.h"

using namespace std;

Snake snake;
Menu menu;
SnakeMap snake_map(&snake);

void initialize(){
    input_initialize();
}

bool game_over(){
    bool result = false;
    pair<int, int> snake_head = snake.snake_head;
    if(snake_head.first < 1 || snake_head.first >= MAP_HEIGHT - 1 || snake_head.second < 1 || snake_head.second >= MAP_WIDTH - 1){
        result = true;
    }
    if(snake.is_dead){
        result = true;
    }
    return result;
}

void start_game(){
    while (true){
        snake.update_movement();
        if(game_over()){
            cout << "GAME IS OVER" << endl;
            break;
        }
        snake_map.redraw();

        usleep(PAUSE_LENGTH);

        snake.validate_direction();
    }
}

void start_menu(){
    menu.initialize_menu();
    while(true){
        for(int i = 0; i < 30; i++){
            cout << endl;
        }
        for(int i = 0; i < 20; i++) cout << '*';
        for(int i = 0; i < 10; i++) cout << endl;
        for(int i = 0; i < 3; i++){
            for(int i = 0; i < 8; i++) cout << ' ';
            if(menu.position == i){
                cout << "\x1b[31m";
            }
            cout << menu.Options[i];
            if(menu.position == i){
                cout << "\x1b[0m";
            }
            cout << endl;
            cout << endl;
            cout << endl;
        }
        menu.update_direction();
        string choice = menu.choice;
        if(choice == "Enter"){
            if(menu.position == 0){
                menu.flag = false;
                snake.flag = true;
                start_game();
                return;
            }
            else if(menu.position == 2){
                return;
            }
        }
        for(int i = 0; i < 20; i++) cout << '*';
        cout << endl;
        usleep(PAUSE_LENGTH * 2);
    }
}

int main(){
    initialize();
    start_menu();
    return 0;
}
