#ifndef ROTATE_H
#define ROTATE_H

#define SIZE 5
#define SIZE_EDGE 25
#define STEPS 8000

#include "save_history.h"

void edgeUnClock(char edge[SIZE][SIZE]){
    char temp[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = edge[i][j];
        }
    }
    for (int j = 0, k = 4; j < SIZE; j++, k--) {
        for (int i = 0; i < SIZE; i++) {
            edge[j][i] = temp[i][k];
        }
    }
}
void edgeClock(char edge[SIZE][SIZE]){
    char temp[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = edge[i][j];
        }
    }
    for (int j = 0, k = 4; j < SIZE; j++, k--) {
        for (int i = 0; i < SIZE; i++) {
            edge[i][k] = temp[j][i];
        }
    }
    
}

void view_cube_from_history(int action, struct history* history, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){

    char* save_data_ptr = get_data_from_history(history, action);

    if (save_data_ptr != NULL){
        memcpy(l,save_data_ptr,25);

        memcpy(f,save_data_ptr + SIZE_EDGE*1,25);

        memcpy(r,save_data_ptr + SIZE_EDGE*2,25);

        memcpy(b,save_data_ptr + SIZE_EDGE*3,25);

        memcpy(u,save_data_ptr + SIZE_EDGE*4,25);

        memcpy(d,save_data_ptr + SIZE_EDGE*5,25);
    }


}
void U(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 0;
    
    for (int j = 0; j < SIZE; j++) {
        temp = b[k][j];
        b[k][j] = r[k][j];
        r[k][j] = f[k][j];
        f[k][j] = l[k][j];
        l[k][j] = temp;
    }
   
    edgeUnClock(u);
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void U2(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    for (int j = 0; j < SIZE; j++) {
        temp = b[1][j];
        b[1][j] = r[1][j];
        r[1][j] = f[1][j];
        f[1][j] = l[1][j];
        l[1][j] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}

void E(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 2;
    for (int j = 0; j < SIZE; j++) {
        temp = b[k][j];
        b[k][j] = r[k][j];
        r[k][j] = f[k][j];
        f[k][j] = l[k][j];
        l[k][j] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void D2(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 3;
    for (int j = 0; j < SIZE; j++) {
        temp = b[k][j];
        b[k][j] = r[k][j];
        r[k][j] = f[k][j];
        f[k][j] = l[k][j];
        l[k][j] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void D(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 4;
    //не доделано (сверху не поворачивает )
    for (int j = 0; j < SIZE; j++) {
        temp = b[k][j];
        b[k][j] = r[k][j];
        r[k][j] = f[k][j];
        f[k][j] = l[k][j];
        l[k][j] = temp;
    }
    edgeClock(d);
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void L_(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    
    char temp;
    edgeUnClock(l);
    for(int i = 0,k = 0; i<SIZE;i++){
        temp=u[i][k];
        u[i][k]=f[i][k];
        f[i][k]=d[i][k];
        d[i][k]=b[4-i][4-k];
        b[4-i][4-k]=temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}

void L2_(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 1;
    for (int i = 0; i < SIZE; i++) {
        temp = u[i][k];
        u[i][k] = f[i][k];
        f[i][k] = d[i][k];
        d[i][k] = b[4-i][4-k];
        b[4-i][4-k] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void M(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 2;
    for (int i = 0; i < SIZE; i++) {
        temp = u[i][k];
        u[i][k] = f[i][k];
        f[i][k] = d[i][k];
        d[i][k] = b[4-i][4-k];
        b[4-i][4-k] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void R2(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 3;
    for (int i = 0; i < SIZE; i++) {
        temp = u[i][k];
        u[i][k] = f[i][k];
        f[i][k] = d[i][k];
        d[i][k] = b[4-i][4-k];
        b[4-i][4-k] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}


void R(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    
    char temp;
    edgeClock(r);
    for(int i = 0,k = 4; i<SIZE;i++){
        temp = u[i][k];
        u[i][k]=f[i][k];
        f[i][k]=d[i][k];
        d[i][k]=b[4-i][4-k];
        b[4-i][4-k] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}



void F(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    edgeClock(f);
    int k = 4;
    char temp;
    for (int j = 0; j < SIZE; j++) {

        temp  = u[k][j];
        u[k][j] = l[4-j][k];
        l[4-j][k] = d[4-k][4-j];
        d[4-k][4-j] = r[j][4-k];
        r[j][4-k] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void F_(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    edgeUnClock(f);
    int k = 4;
    char temp;
    for (int j = 0; j < SIZE; j++) {

        temp  = u[k][j];
        u[k][j] = r[j][4-k];
        r[j][4-k] = d[4-k][4-j];
        d[4-k][4-j] = l[4-j][k];
        l[4-j][k] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}

void B(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    edgeClock(b);
    int k = 0;
    char temp;
    for (int j = 0; j < SIZE; j++) {

        temp  = u[k][j];
        u[k][j] = r[j][4-k];
        r[j][4-k] = d[4-k][4-j];
        d[4-k][4-j] = l[4-j][k];
        l[4-j][k] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void B_(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    edgeUnClock(b);
    int k = 0;
    char temp;
    for (int j = 0; j < SIZE; j++) {

        temp  = u[k][j];
        u[k][j] = l[4-j][k];
        l[4-j][k] = d[4-k][4-j];
        d[4-k][4-j] = r[j][4-k];
        r[j][4-k] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
/////////////////////////////
void U_(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp[SIZE][SIZE];
    int k = 0;
    //не доделано (сверху не поворачивает )
    for (int j = 0; j < SIZE; j++) {

        temp[k][j]  = f[k][j];
        f[k][j] = r[k][j];
        r[k][j] = b[k][j];
        b[k][j] = l[k][j];
        l[k][j] = temp[k][j];
    }
    edgeClock(u);
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void U2_(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    for (int j = 0; j < SIZE; j++) {
        temp = b[1][j];
        b[1][j] = l[1][j];
        l[1][j] = f[1][j];
        f[1][j] = r[1][j];
        r[1][j] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void E_(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 2;
    for (int j = 0; j < SIZE; j++) {
        temp = l[k][j];
        l[k][j] = f[k][j];
        f[k][j] = r[k][j];
        r[k][j] = b[k][j];
        b[k][j] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void D2_(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 3;
    for (int j = 0; j < SIZE; j++) {
        temp = b[k][j];
        b[k][j] = l[k][j];
        l[k][j] = f[k][j];
        f[k][j] = r[k][j];
        r[k][j] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void D_(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 4;
    //не доделано (сверху не поворачивает )
    for (int j = 0; j < SIZE; j++) {
        temp = b[k][j];
        b[k][j] = l[k][j];
        l[k][j] = f[k][j];
        f[k][j] = r[k][j];
        r[k][j] = temp;
    }
    edgeUnClock(d);
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}

/////////////////
void L(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    
    char temp;
    edgeClock(l);
    for(int i = 0,k = 0; i<SIZE;i++){
        temp=u[i][k];
        u[i][k]=b[4-i][4-k];
        b[4-i][4-k]=d[i][k];
        d[i][k]=f[i][k];
        f[i][k]=temp;

    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}

void L2(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 1;
    for (int i = 0; i < SIZE; i++) {
        temp = u[i][k];
        u[i][k] = b[4-i][4-k];
        b[4-i][4-k] = d[i][k];
        d[i][k] = f[i][k];
        f[i][k] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void M_(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 2;
    for (int i = 0; i < SIZE; i++) {
        temp = u[i][k];
        u[i][k] = b[4-i][4-k];
        b[4-i][4-k] = d[i][k];
        d[i][k] = f[i][k];
        f[i][k] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void R2_(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    char temp;
    int k = 3;
    for (int i = 0; i < SIZE; i++) {
        temp = u[i][k];
        u[i][k] = b[4-i][4-k];
        b[4-i][4-k] = d[i][k];
        d[i][k] = f[i][k];
        f[i][k] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}
void R_(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]) {
    
    char temp;
    edgeUnClock(r);
    for(int i = 0,k = 4; i<SIZE;i++){
        temp = u[i][k];
        u[i][k] = b[4-i][4-k];
        b[4-i][4-k] = d[i][k];
        d[i][k] = f[i][k];
        f[i][k] = temp;
    }
    save_data_to_history(history,l,f, r, b,u,d, count_moves);
}

#endif