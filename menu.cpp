#include "menu.h"
#include <iostream>
#include <pthread.h>

void *menu_thread_work(void *arg)
{
    struct Menu *menu = (struct Menu *)arg;
    while (true)
    {
        if(!menu->flag) continue;
        Direction direction = get_input();
        menu->update_next_direction(direction);
    }
}

void Menu::initialize_menu(void){
    position = 0;
    flag = true;
    sem_init(&menu_sema, 0, 1);
    pthread_create(&input_thread, NULL, menu_thread_work, this);
}

void Menu::update_direction(){
    Direction direction = next_direction;
    sem_wait(&this->menu_sema);
    if(direction.curDirection == "Bala"){
        if (position != 0){
            position --;
        }

        next_direction.curDirection = "";
        sem_post(&this->menu_sema);
        return;
    }
    if(direction.curDirection == "Paiin"){
        if (position != 2){
            position ++;
        }
        next_direction.curDirection = "";
        sem_post(&this->menu_sema);
        return;
    }
    if(direction.curDirection == "Enter"){
        next_direction.curDirection = "";
        choice = "Enter";
        sem_post(&this->menu_sema);
        return;
    }
    sem_post(&this->menu_sema);
    return;
}

void Menu::update_next_direction(Direction direction){
    this->next_direction = direction;
}