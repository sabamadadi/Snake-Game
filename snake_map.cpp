#include "snake_map.h"
#include <pthread.h>
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include "macros.h"

using namespace std;

SnakeMap::SnakeMap(Snake *snake){
    this->snake = snake;
    clear_map(this->map_array);
    srand(time(NULL));
    update_snake_food(true);
}

void SnakeMap::redraw(void){
    clear_map(this->map_array);
    for (int i = 0; i < MAP_END; i++){
        cout << endl;
    }
    update_score();
    vector<pair<int, int>> snake_parts = snake->snake_parts;
    for (int i = 0; i < snake_parts.size(); i++){
        pair<int, int> tmp = snake_parts[i];
        map_array[tmp.first][tmp.second] = SNAKE_CHAR;
    }
    update_snake_head(map_array, snake);
    update_snake_food(false);
    map_array[snake_food.first][snake_food.second] = SNAKE_FOOD_CHAR;
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            if(i == snake_food.first && j == snake_food.second){
                cout << "\x1b[31m";
            }
            cout << map_array[i][j] << " ";
            if(i == snake_food.first && j == snake_food.second){
                cout << "\x1b[0m";
            }
        }
        cout << endl;
    }
}

void SnakeMap::update_snake_food(bool force_update){
    if (snake->food_eaten || force_update){
        while (true){
            int random_i = rand() % MAP_WIDTH;
            int random_j = rand() % MAP_HEIGHT;
            if (map_array[random_i][random_j] == MAP_CHAR){
                snake_food = make_pair(random_i, random_j);
                snake->set_snake_food(snake_food);
                snake->food_eaten = false;
                break;
            }
        }
    }
}

void clear_map(char map_array[MAP_HEIGHT][MAP_WIDTH]){
    for(int i = 0; i < MAP_HEIGHT; i++){
        map_array[i][0] = WALL_CHAR;
        map_array[i][MAP_WIDTH - 1] = WALL_CHAR;   
    }
    for(int i = 0; i < MAP_WIDTH; i++){
        map_array[0][i] = WALL_CHAR;
        map_array[MAP_HEIGHT - 1][i] = WALL_CHAR;   
    }
    for (int i = 1; i + 1 < MAP_HEIGHT; i++){
        for (int j = 1; j + 1 < MAP_WIDTH; j++){
            map_array[i][j] = MAP_CHAR;
        }
    }
}

void update_snake_head(char map_array[MAP_HEIGHT][MAP_WIDTH], Snake *snake){
    char snake_head_char = SNAKE_CHAR;
    Direction direction = snake->get_direction();
    if(direction.curDirection == "Chap"){
        snake_head_char = SNAKE_HEAD_WEST;
    }
    else if(direction.curDirection == "Bala"){
        snake_head_char = SNAKE_HEAD_NORTH;
    }
    else if(direction.curDirection == "Rast"){
        snake_head_char = SNAKE_HEAD_EAST;
    }
    else if(direction.curDirection == "Paiin"){
        snake_head_char = SNAKE_HEAD_SOUTH;
    }
    pair<int, int> snake_head = snake->snake_head;
    map_array[snake_head.first][snake_head.second] = snake_head_char;
}

void SnakeMap::update_score(void){
    cout << "Score:" << snake->length << endl;
}