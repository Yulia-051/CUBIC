#ifndef SAVE_HISTORY_H
#define SAVE_HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//Действия, которые можно сделать с историей
#define GET_TAIL 0
#define GET_HEAD 1
#define GET_NEXT 2
#define GET_PREV 3

//Размер массива, который необходим для хранения данных одного куба
#define CUBE_DATA_SIZE 150
#define SIZE 5
#define SIZE_EDGE 25

//Удачное и неудачное добавление сохранения в историю
#define DATA_SAVE_SUCCESS 1
#define DATA_SAVE_FAILED -1


struct history_node
{
    char* data;
    struct history_node* next;
    struct history_node* prev;
};


typedef struct history
{
    struct history_node* head;
    struct history_node* tail;
    struct history_node* current;
}history;


//Выделяет память под структуру history и возвращает указатель на неё
struct history* init_history();

//Добавляет данные в историю
int save_data_to_history(struct history* hist, 
                     char left_size[SIZE][SIZE], 
                     char front_size[SIZE][SIZE],
                     char right_size[SIZE][SIZE],
                     char back_side[SIZE][SIZE],
                     char up_side[SIZE][SIZE],
                     char down_size[SIZE][SIZE], int* count_moves);


//Возвращает указатель на данные из истории по указанному событию
char * get_data_from_history(struct history* hist, int action);

//Выделяет память под struct history_node и возвращает указатель на неё
static struct history_node* make_history_node();

//Вставляет struct history_node в конец списка сохранений
static void insert_save_in_history(struct history* hist,struct history_node* hist_node);

//Очищает историю
void clear_history(struct history* history);
#endif