#include "snake.h"
#include <pthread.h>
#include <iostream>
#include <vector>
#include <utility>
#include "snake_map.h"
#include "macros.h"

using namespace std;

void *input_thread_work(void *arg)
{
    struct Snake *snake = (struct Snake *)arg;
    while (true)
    {
        if(!snake->flag) continue;
        Direction direction = get_input();
        snake->update_next_direction(direction);
    }
}

Snake::Snake(void)
{
    flag = false;
    direction.curDirection = "Rast";
    next_direction = direction;
    food_eaten = false;
    is_dead = false;
    length = INITIAL_SNAKE_LENGTH;
    clear_snake_world();
    initialize_snake();
    sem_init(&snake_sema, 0, 1);
    pthread_create(&input_thread, NULL, input_thread_work, this);
}

void Snake::update_direction(Direction direction)
{
    sem_wait(&this->snake_sema);
    if(direction.curDirection == "Chap"){
        if (this->direction.curDirection != "Rast"){
            this->direction = direction;
        }
        sem_post(&this->snake_sema);
        return;
    }
    if(direction.curDirection == "Rast"){
        if (this->direction.curDirection != "Chap"){
            this->direction = direction;
        }
        sem_post(&this->snake_sema);
        return;
    }
    if(direction.curDirection == "Bala"){
        if (this->direction.curDirection != "Paiin"){
            this->direction = direction;
        }
        sem_post(&this->snake_sema);
        return;
    }
    if(direction.curDirection == "Paiin"){
        if (this->direction.curDirection != "Bala"){
            this->direction = direction;
        }
        sem_post(&this->snake_sema);
        return;
    }
    sem_post(&this->snake_sema);
}

void Snake::update_next_direction(Direction direction)
{
    this->next_direction = direction;
}

Direction Snake::get_direction(void)
{
    Direction result;
    result.curDirection = "Rast";
    sem_wait(&this->snake_sema);
    result = this->direction;
    sem_post(&this->snake_sema);
    return result;
}

void Snake::validate_direction(void)
{
    if (next_direction.curDirection != "Error")
    {
        update_direction(next_direction);
    }
}

void Snake::update_movement(void)
{
    pair<int, int> movement_part;
    Direction direction = get_direction();
    if(direction.curDirection == "Chap"){
        movement_part = make_pair(snake_head.first, snake_head.second - 1);
    }
    else if(direction.curDirection == "Bala"){
        movement_part = make_pair(snake_head.first - 1, snake_head.second);
    }
    else if(direction.curDirection == "Rast"){
        movement_part = make_pair(snake_head.first, snake_head.second + 1);
    }
    else if(direction.curDirection == "Paiin"){
        movement_part = make_pair(snake_head.first + 1, snake_head.second);
    }
    snake_head = movement_part;
    snake_parts.push_back(movement_part);
    food_eaten = snake_head.first == snake_food.first && snake_head.second == snake_food.second;
    if (food_eaten)
    {
        length++;
    }
    else
    {
        pair<int, int> tail = snake_parts.front();
        snake_world_array[tail.first][tail.second]--;
        snake_parts.erase(snake_parts.begin());
    }
    int head_value = ++snake_world_array[snake_head.first][snake_head.second];
    if (head_value > 1)
    {
        is_dead = true;
    }
}

void Snake::set_snake_food(pair<int, int> snake_food)
{
    this->snake_food = snake_food;
}

void Snake::clear_snake_world(void)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            snake_world_array[i][j] = 0;
        }
    }
}

void Snake::initialize_snake(void)
{
    for (int i = 0; i < INITIAL_SNAKE_LENGTH; i++)
    {
        pair<int, int> snake_part = make_pair(MAP_HEIGHT / 2, MAP_WIDTH / 2 - (INITIAL_SNAKE_LENGTH / 2) + i);
        snake_parts.push_back(snake_part);
        snake_world_array[snake_part.first][snake_part.second] = 1;
    }
    snake_head = snake_parts[snake_parts.size() - 1];
}
