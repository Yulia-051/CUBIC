#ifndef SAVE_HISTORY_C
#define SAVE_HISTORY_C

#include "save_history.h"

//Выделяет память под структуру history и возвращает указатель на неё
struct history* init_history()
{
    struct history* hist = (struct history*)malloc(sizeof(struct history));
    if (hist == NULL){
        printf("Mem Alloc For struct history!\n");
        return NULL;
    }

    hist->current = NULL;
    hist->head = NULL;
    hist->tail = NULL;
    
    return hist;
}

//Добавляет данные в историю
int save_data_to_history(struct history* history, 
                     char left_size[SIZE][SIZE], 
                     char front_size[SIZE][SIZE],
                     char right_size[SIZE][SIZE],
                     char back_side[SIZE][SIZE],
                     char up_side[SIZE][SIZE],
                     char down_size[SIZE][SIZE], int* count_moves)
{
    //Выделяем память для хранения всего сохранения
    char* save_cube_data = (char*)malloc(sizeof(char) * CUBE_DATA_SIZE);
    if (save_cube_data == NULL){
        printf("Mem alloc for save_cube ERROR! (func: save_to_history)\n");
        return DATA_SAVE_FAILED;
    }

    //Записываем данные из всех массивов в save_cuve_data
    memcpy(save_cube_data, left_size, sizeof(char) * SIZE_EDGE);
    memcpy(save_cube_data + SIZE_EDGE * 1, front_size, sizeof(char) * SIZE_EDGE);
    memcpy(save_cube_data + SIZE_EDGE * 2, right_size, sizeof(char) * SIZE_EDGE);
    memcpy(save_cube_data + SIZE_EDGE * 3, back_side, sizeof(char) * SIZE_EDGE);
    memcpy(save_cube_data + SIZE_EDGE * 4, up_side, sizeof(char) * SIZE_EDGE);
    memcpy(save_cube_data + SIZE_EDGE * 5, down_size, sizeof(char) * SIZE_EDGE);

    //Создаём ноду для вставки сохранения в список
    struct history_node* hist_node = make_history_node();
    if (hist_node == NULL) return DATA_SAVE_FAILED;

    hist_node->data = save_cube_data;

    //Вставляем ноду сохранения в конец истории
    insert_save_in_history(history, hist_node);

    (*count_moves)++;

    return DATA_SAVE_SUCCESS;
}

//Возвращает указатель на данные из истории по указанному событию
char* get_data_from_history(struct history* hist, int action)
{
    if (action == GET_HEAD){
        hist->current = hist->head;
        return hist->current->data;
    }
    else if (action == GET_TAIL){
        hist->current = hist->tail;
        return hist->current->data;
    }
    else if (action == GET_NEXT){
        if (hist->current == hist->tail) return NULL;
        else {
            hist->current = hist->current->next;
            return hist->current->data;
        }
    }
    else if (action == GET_PREV){
        if (hist->current == hist->head) return NULL;
        else {
            hist->current = hist->current->prev;
            return hist->current->data;
        }
    }

    return NULL;
}


//Выделяет память под struct history_node и возвращает указатель на неё
static struct history_node* make_history_node()
{
    struct history_node* hist_node = (struct history_node*)malloc(sizeof(struct history_node));
    if (hist_node == NULL){
        printf("Mem alloc for hist_node ERROR! (func: make_history_node)\n");
        return NULL;
    }

    hist_node->data = NULL;
    hist_node->next = NULL;
    hist_node->prev = NULL;

    return hist_node;
}


//Вставляет struct history_node в конец списка сохранений
static void insert_save_in_history(struct history* hist, struct history_node* hist_node)
{
    if (hist->head == NULL){
        hist->head = hist_node;
        hist->tail = hist_node;
    }
    else {
        hist_node->prev = hist->tail;
        hist->tail->next = hist_node;
        hist->tail = hist_node;
    }

    hist->current = hist_node;
}

#endif