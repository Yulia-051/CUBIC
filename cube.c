#include <stdio.h>
#include <string.h>
#include <math.h>
#include "./external/glad/glad.h"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <time.h>

#include"./src/graphics/struct.h"
#include"./src/graphics/shaderClass.h"
#include"./src/graphics/VAO.h"
#include"./src/graphics/VBO.h"
#include"./src/graphics/EBO.h"
#include"rotate.h"
#include "save_history.h"

#define SIZE 5
#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 800
#define PRESSURE 0.5f
#define PRES_DIV 2
#define prop 0.66667
#define SIZE_EDGE 25

uint32_t mouse_status = 0;
int ifWindowNull(GLFWwindow* window);
int where_cursor(GLFWwindow* window);
int where_cur_bot(GLFWwindow* window,object* OBJ);
void mas_to_color(char mas[SIZE][SIZE], char edge);
void butt_collect(object* OBJ,char* image_name,float x1,float x2,float y1, float y2);
void change_cube(VAO* VAO1,VBO* VBO1, EBO* EBO1, char front[SIZE][SIZE], char up[SIZE][SIZE], char right[SIZE][SIZE]);
object* create_object(int isCube);
void delete_obj(object* OBJ);
void change_bot(object* button_r,object* button_u,object* button_d,object* button_l,object* button_reset,object* button_solve,object* button_back,object* button_forward,object* button_begin,object* button_end);
void reset(char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);

void solve(int*count_moves,struct history* history, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void solve_center_rib(int*count_moves, struct history* history, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void center_rib(int* count_moves, struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void search_and_rotate_center_rib(int*count_moves, struct history* history, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE],int* count,char search);
void cntNotOneColor(char edge[SIZE][SIZE],char search, int* count,int num);
int cheak_center(int num,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void solve_center_corn(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void center_corn(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void search_and_rotate_center_corn(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE],int* count,char search);

int search_rib_for_change(int*count_moves,struct history* history,int var, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void change_ribs(int*count_moves,struct history* history,int num_in_rib, int var,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void cntNotOneColor_rib(char f [SIZE][SIZE],char u[SIZE][SIZE],char search_f,char search_u,int* count);
int cheak_ribs(int* sequence_edges,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void solve_ribs(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void last_ribs(int*count_moves,struct history* history,int* sequence_edges, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void solve_white_rib(int*count_moves,struct history* history, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
int where_rib(char search_f, char search_u, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void solve_corners(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void solve_right_place_for_rib(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void swap_rib_right(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void yellow_ribs(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void change_last_four_ribs(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void four_edges_color(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void last_corners_part1(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void rotate_last_corn_for_part1(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);
void last_corners_part2(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);


void printRubiksCube(char left[SIZE][SIZE], char front[SIZE][SIZE], char right[SIZE][SIZE], char back[SIZE][SIZE], char up[SIZE][SIZE], char down[SIZE][SIZE]);
void printMatrix(char matrix[SIZE][SIZE]);
int operation(int* count_moves,struct history* history,int where,char orient,char l[SIZE][SIZE], char f[SIZE][SIZE], char r[SIZE][SIZE], char b[SIZE][SIZE], char u[SIZE][SIZE], char d[SIZE][SIZE]);
void one_square(int i,char color);
GLFWwindow* openWindow(GLFWwindow* window);

void turn_cube(int* count_moves, struct history* history, char orient, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]);

float w1 = 1.0f,w2 = 1.0f,w3 = 1.0f;
float r1 = 1.0f,r2 = 0.0f, r3 = 0.2f;
float g1 = 0.0f,g2 = 1.0f, g3 = 0.2f;

float o1 = 1.0f,o2 = 0.6f,o3 = 0.2f;
float b1 = 0.2f,b2 = 0.8f, b3 = 1.0f;
float yl1 = 1.0f,yl2 = 1.0f, yl3 = 0.2f;
enum buttons{
    but_turn_r=1,but_turn_u,but_turn_l,but_turn_d
};
enum matrix{
    front1_1,front1_2,front1_3,front1_4,front1_5,
    front2_1,front2_2,front2_3,front2_4,front2_5,
    front3_1,front3_2,front3_3,front3_4,front3_5,
    front4_1,front4_2,front4_3,front4_4,front4_5,
    front5_1,front5_2,front5_3,front5_4,front5_5,
    
    upper1_1,upper1_2,upper1_3,upper1_4,upper1_5,
    upper2_1,upper2_2,upper2_3,upper2_4,upper2_5,
    upper3_1,upper3_2,upper3_3,upper3_4,upper3_5,
    upper4_1,upper4_2,upper4_3,upper4_4,upper4_5,
    upper5_1,upper5_2,upper5_3,upper5_4,upper5_5,
    
    right1_1,right1_2,right1_3,right1_4,right1_5,
    right2_1,right2_2,right2_3,right2_4,right2_5,
    right3_1,right3_2,right3_3,right3_4,right3_5,
    right4_1,right4_2,right4_3,right4_4,right4_5,
    right5_1,right5_2,right5_3,right5_4,right5_5
};

float vertices[] ={
    //front GR
//1
     (-0.8f-0.042f)*prop,   0.2f+0.02f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.8f-0.042f)*prop,   0.4f+0.02f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-1.0f-0.042f)*prop,   0.5f+0.02f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-1.0f-0.042f)*prop,   0.3f+0.02f, 0.0f,   0.0f,1.0f,0.2f,// right d

     (-0.6f-0.032f)*prop,   0.1f+0.015f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.6f-0.032f)*prop,   0.3f+0.015f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-0.8f-0.032f)*prop,   0.4f+0.015f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-0.8f-0.032f)*prop,   0.2f+0.015f, 0.0f,   0.0f,1.0f,0.2f,// right d

     (-0.4f-0.021f)*prop,   0.0f+0.01f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.4f-0.021f)*prop,   0.2f+0.01f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-0.6f-0.021f)*prop,   0.3f+0.01f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-0.6f-0.021f)*prop,   0.1f+0.01f, 0.0f,   0.0f,1.0f,0.2f,// right d

    (-0.2f-0.01f)*prop,  -0.1f+0.005f, 0.0f,   0.0f,1.0f,0.2f,// left d
	(-0.2f-0.01f)*prop,   0.1f+0.005f, 0.0f,   0.0f,1.0f,0.2f,// left u
	(-0.4f-0.01f)*prop,   0.2f+0.005f, 0.0f,   0.0f,1.0f,0.2f,// right u
	(-0.4f-0.01f)*prop,   0.0f+0.005f, 0.0f,   0.0f,1.0f,0.2f,// right d

     0.0f*prop,  -0.2f, 0.0f,   0.0f,1.0f,0.2f,// right d
	 0.0f*prop,   0.0f, 0.0f,   0.0f,1.0f,0.2f,// right u
	-0.2*prop,   0.1f, 0.0f,   0.0f,1.0f,0.2f,// left u
    -0.2f*prop,  -0.1f, 0.0f,   0.0f,1.0f,0.2f,// left d
	//2  Gr

    (-0.8f-0.042f)*prop,   0.0f+0.01f, 0.0f,   0.0f,1.0f,0.2f,// left d
	(-0.8f-0.042f)*prop,   0.2f+0.01, 0.0f,    0.0f,1.0f,0.2f,// left u
	(-1.0f-0.042f)*prop,   0.3f+0.01f, 0.0f,   0.0f,1.0f,0.2f,// right u
	(-1.0f-0.042f)*prop,   0.1f+0.01f, 0.0f,   0.0f,1.0f,0.2f,// right d

    (-0.6f-0.032f)*prop,  -0.1f+0.005f, 0.0f,   0.0f,1.0f,0.2f,// left d
	(-0.6f-0.032f)*prop,   0.1f+0.005f, 0.0f,   0.0f,1.0f,0.2f,// left u
	(-0.8f-0.032f)*prop,   0.2f+0.005f, 0.0f,   0.0f,1.0f,0.2f,// right u
	(-0.8f-0.032f)*prop,   0.0f+0.005f, 0.0f,   0.0f,1.0f,0.2f,// right d

    (-0.4f-0.021f)*prop,  -0.2f-0.00f, 0.0f,   0.0f,1.0f,0.2f,// left d
	(-0.4f-0.021f)*prop,   0.0f-0.00f, 0.0f,   0.0f,1.0f,0.2f,// left u
	(-0.6f-0.021f)*prop,   0.1f-0.00f, 0.0f,   0.0f,1.0f,0.2f,// right u
	(-0.6f-0.021f)*prop,  -0.1f-0.00f, 0.0f,   0.0f,1.0f,0.2f,// right d

     (-0.2f-0.01f)*prop,  -0.3f-0.005f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.2f-0.01f)*prop,  -0.1f-0.005f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-0.4f-0.01f)*prop,   0.0f-0.005f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-0.4f-0.01f)*prop,  -0.2f-0.005f, 0.0f,   0.0f,1.0f,0.2f,// right d

    0.0f*prop,  -0.4f-0.01f, 0.0f,   0.0f,1.0f,0.2f,// right d
    0.0f*prop,  -0.2f-0.01f, 0.0f,   0.0f,1.0f,0.2f,// right u
	-0.2f*prop,  -0.1f-0.01f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 -0.2f*prop,  -0.3f-0.01f, 0.0f,   0.0f,1.0f,0.2f,// left d
     
//3  Gw
     (-0.8f-0.042f)*prop,  -0.2f-0.0f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.8f-0.042f)*prop,   0.0f-0.0f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-1.0f-0.042f)*prop,   0.1f-0.0f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-1.0f-0.042f)*prop,  -0.1f-0.0f, 0.0f,   0.0f,1.0f,0.2f,// right d

     (-0.6f-0.032f)*prop,  -0.3f-0.005f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.6f-0.032f)*prop,  -0.1f-0.005f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-0.8f-0.032f)*prop,   0.0f-0.005f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-0.8f-0.032f)*prop,  -0.2f-0.005f, 0.0f,   0.0f,1.0f,0.2f,// right d

     (-0.4f-0.021f)*prop,  -0.4f-0.01f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.4f-0.021f)*prop,  -0.2f-0.01f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-0.6f-0.021f)*prop,  -0.1f-0.01f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-0.6f-0.021f)*prop,  -0.3f-0.01f, 0.0f,   0.0f,1.0f,0.2f,// right d

     (-0.2f-0.01f)*prop,  -0.5f-0.015f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.2f-0.01f)*prop,  -0.3f-0.015f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-0.4f-0.01f)*prop,  -0.2f-0.015f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-0.4f-0.01f)*prop,  -0.4f-0.015f, 0.0f,   0.0f,1.0f,0.2f,// right d

     0.0f*prop,  -0.6f-0.02f, 0.0f,   0.0f,1.0f,0.2f,// right d
	 0.0f*prop,  -0.4f-0.02f, 0.0f,   0.0f,1.0f,0.2f,// right u
	-0.2f*prop,  -0.3f-0.02f, 0.0f,   0.0f,1.0f,0.2f,// left u
    -0.2f*prop,  -0.5f-0.02f, 0.0f,   0.0f,1.0f,0.2f,// left d

//4  Gl
     (-0.8f-0.042f)*prop,  -0.4f-0.01f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.8f-0.042f)*prop,  -0.2f-0.01f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-1.0f-0.042f)*prop,  -0.1f-0.01f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-1.0f-0.042f)*prop,  -0.3f-0.01f, 0.0f,   0.0f,1.0f,0.2f,// right d

     (-0.6f-0.032f)*prop,  -0.5f-0.015f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.6f-0.032f)*prop,  -0.3f-0.015f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-0.8f-0.032f)*prop,  -0.2f-0.015f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-0.8f-0.032f)*prop,  -0.4f-0.015f, 0.0f,   0.0f,1.0f,0.2f,// right d

     (-0.4f-0.021f)*prop,  -0.6f-0.02f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.4f-0.021f)*prop,  -0.4f-0.02f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-0.6f-0.021f)*prop,  -0.3f-0.02f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-0.6f-0.021f)*prop,  -0.5f-0.02f, 0.0f,   0.0f,1.0f,0.2f,// right d

     (-0.2f-0.01f)*prop,  -0.7f-0.025f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.2f-0.01f)*prop,  -0.5f-0.025f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-0.4f-0.01f)*prop,  -0.4f-0.025f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-0.4f-0.01f)*prop,  -0.6f-0.025f, 0.0f,   0.0f,1.0f,0.2f,// right d

     0.0f*prop,  -0.8f-0.03f, 0.0f,   0.0f,1.0f,0.2f,// right d
     0.0f*prop,  -0.6f-0.03f, 0.0f,   0.0f,1.0f,0.2f,// right u
	-0.2f*prop,  -0.5f-0.03f, 0.0f,   0.0f,1.0f,0.2f,// left u
    -0.2f*prop,  -0.7f-0.03f, 0.0f,   0.0f,1.0f,0.2f,// left d

//5-
     (-0.8f-0.042f)*prop,  -0.6f-0.02f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.8f-0.042f)*prop,  -0.4f-0.02f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-1.0f-0.042f)*prop,  -0.3f-0.02f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-1.0f-0.042f)*prop,  -0.5f-0.02f, 0.0f,   0.0f,1.0f,0.2f,// right d

     (-0.6f-0.032f)*prop,  -0.7f-0.025f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.6f-0.032f)*prop,  -0.5f-0.025f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-0.8f-0.032f)*prop,  -0.4f-0.025f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-0.8f-0.032f)*prop,  -0.6f-0.025f, 0.0f,   0.0f,1.0f,0.2f,// right d

     (-0.4f-0.021f)*prop,  -0.8f-0.03f, 0.0f,   0.0f,1.0f,0.2f,// left d
	 (-0.4f-0.021f)*prop,  -0.6f-0.03f, 0.0f,   0.0f,1.0f,0.2f,// left u
	 (-0.6f-0.021f)*prop,  -0.5f-0.03f, 0.0f,   0.0f,1.0f,0.2f,// right u
	 (-0.6f-0.021f)*prop,  -0.7f-0.03f, 0.0f,   0.0f,1.0f,0.2f,// right d

    (-0.2f-0.01f)*prop,  -0.9f-0.035f, 0.0f,   0.0f,1.0f,0.2f,// left d
	(-0.2f-0.01f)*prop,  -0.7f-0.035f, 0.0f,   0.0f,1.0f,0.2f,// left u
	(-0.4f-0.01f)*prop,  -0.6f-0.035f, 0.0f,   0.0f,1.0f,0.2f,// right u
	(-0.4f-0.01f)*prop,  -0.8f-0.035f, 0.0f,   0.0f,1.0f,0.2f,// right d

     0.0f*prop,  -1.0f-0.04f, 0.0f,   0.0f,1.0f,0.2f,// right d
     0.0f*prop,  -0.8f-0.04f, 0.0f,   0.0f,1.0f,0.2f,// right u
	-0.2f*prop,  -0.7f-0.04f, 0.0f,   0.0f,1.0f,0.2f,// left u
    -0.2f*prop,  -0.9f-0.04f, 0.0f,   0.0f,1.0f,0.2f,// left d 

//Upper
//1
     0.0f*prop,   0.8f+0.04f, 0.0f,   1.0f,1.0f,1.0f,// right d
    -0.2f*prop,   0.9f+0.04f, 0.0f,   1.0f,1.0f,1.0f,// left d
	 0.0f*prop,   1.0f+0.04f, 0.0f,   1.0f,1.0f,1.0f,// left u
	 0.2f*prop,   0.9f+0.04f, 0.0f,   1.0f,1.0f,1.0f,// right u

     (0.2f+0.01f)*prop,   0.7f+0.035f, 0.0f,   1.0f,1.0f,1.0f,// right d
     (0.0f+0.01f)*prop,   0.8f+0.035f, 0.0f,   1.0f,1.0f,1.0f,// left d
	 (0.2f+0.01f)*prop,   0.9f+0.035f, 0.0f,   1.0f,1.0f,1.0f,// left u
	 (0.4f+0.01f)*prop,   0.8f+0.035f, 0.0f,   1.0f,1.0f,1.0f,// right u

     (0.4f+0.02f)*prop,   0.6f+0.03f, 0.0f,   1.0f,1.0f,1.0f,// right d
     (0.2f+0.02f)*prop,   0.7f+0.03f, 0.0f,   1.0f,1.0f,1.0f,// left d
	 (0.4f+0.02f)*prop,   0.8f+0.03f, 0.0f,   1.0f,1.0f,1.0f,// left u
	 (0.6f+0.02f)*prop,   0.7f+0.03f, 0.0f,   1.0f,1.0f,1.0f,// right u

     (0.6f+0.03f)*prop,   0.5f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// right d
     (0.4f+0.03f)*prop,   0.6f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// left d
	 (0.6f+0.03f)*prop,   0.7f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// left u
	 (0.8f+0.03f)*prop,   0.6f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// right u

     (0.8f+0.04f)*prop,   0.4f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// right d
     (0.6f+0.04f)*prop,   0.5f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// left d
	 (0.8f+0.04f)*prop,   0.6f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// left u
	 (1.0f+0.04f)*prop,   0.5f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// right u

//2
    (-0.2f-0.01f)*prop,   0.7f+0.035f, 0.0f,   1.0f,1.0f,1.0f,// right d
    (-0.4f-0.01f)*prop,   0.8f+0.035f, 0.0f,   1.0f,1.0f,1.0f,// left d
	(-0.2f-0.01f)*prop,   0.9f+0.035f, 0.0f,   1.0f,1.0f,1.0f,// left u
	 (0.0f-0.01f)*prop,   0.8f+0.035f, 0.0f,   1.0f,1.0f,1.0f,// right u

    ( 0.0f)*prop,   0.6f+0.03f, 0.0f,   1.0f,1.0f,1.0f,// right d
    (-0.2f)*prop,   0.7f+0.03f, 0.0f,   1.0f,1.0f,1.0f,// left d
	 (0.0f)*prop,   0.8f+0.03f, 0.0f,   1.0f,1.0f,1.0f,// left u
	 (0.2f)*prop,   0.7f+0.03f, 0.0f,   1.0f,1.0f,1.0f,// right u

     (0.2f+0.01f)*prop,   0.5f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// right d
     (0.0f+0.01f)*prop,   0.6f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// left d
	 (0.2f+0.01f)*prop,   0.7f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// left u
	 (0.4f+0.01f)*prop,   0.6f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// right u

     (0.4f+0.02f)*prop,   0.4f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// right d
     (0.2f+0.02f)*prop,   0.5f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// left d
	 (0.4f+0.02f)*prop,   0.6f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// left u
	 (0.6f+0.02f)*prop,   0.5f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// right u

     (0.6f+0.03f)*prop,   0.3f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// right d
     (0.4f+0.03f)*prop,   0.4f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// left d
	 (0.6f+0.03f)*prop,   0.5f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// left u
	 (0.8f+0.03f)*prop,   0.4f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// right u

//3
    (-0.4f-0.02f)*prop,   0.6f+0.03f, 0.0f,   1.0f,1.0f,1.0f,// right d
    (-0.6f-0.02f)*prop,   0.7f+0.03f, 0.0f,   1.0f,1.0f,1.0f,// left d
	(-0.4f-0.02f)*prop,   0.8f+0.03f, 0.0f,   1.0f,1.0f,1.0f,// left u
	(-0.2f-0.02f)*prop,   0.7f+0.03f, 0.0f,   1.0f,1.0f,1.0f,// right u

    (-0.2f-0.01f)*prop,   0.5f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// right d
    (-0.4f-0.01f)*prop,   0.6f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// left d
	(-0.2f-0.01f)*prop,   0.7f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// left u
	(0.0f-0.01f)*prop,   0.6f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// right u

    ( 0.0f)*prop,   0.4f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// right d
    (-0.2f)*prop,   0.5f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// left d
	( 0.0f)*prop,   0.6f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// left u
	( 0.2f)*prop,   0.5f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// right u

    (0.2f+0.01f)*prop,   0.3f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// right d
    ( 0.0f+0.01f)*prop,   0.4f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// left d
	( 0.2f+0.01f)*prop,   0.5f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// left u
	( 0.4f+0.01f)*prop,   0.4f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// right u

    ( 0.4f+0.02f)*prop,   0.2f+0.01f, 0.0f,   1.0f,1.0f,1.0f,// right d
    ( 0.2f+0.02f)*prop,   0.3f+0.01f, 0.0f,   1.0f,1.0f,1.0f,// left d
	(0.4f+0.02f)*prop,   0.4f+0.01f, 0.0f,   1.0f,1.0f,1.0f,// left u
	( 0.6f+0.02f)*prop,   0.3f+0.01f, 0.0f,   1.0f,1.0f,1.0f,// right u

//4
    (-0.6f-0.03f)*prop,   0.5f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// right d
    (-0.8f-0.03f)*prop,   0.6f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// left d
	(-0.6f-0.03f)*prop,   0.7f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// left u
	(-0.4f-0.03f)*prop,   0.6f+0.025f, 0.0f,   1.0f,1.0f,1.0f,// right u

    (-0.4f-0.02f)*prop,   0.4f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// right d
    (-0.6f-0.02f)*prop,   0.5f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// left d
	(-0.4f-0.02f)*prop,   0.6f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// left u
	(-0.2f-0.02f)*prop,   0.5f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// right u

    (-0.2f-0.01f)*prop,   0.3f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// right d
    (-0.4f-0.01f)*prop,   0.4f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// left d
	(-0.2f-0.01f)*prop,   0.5f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// left u
	( 0.0f-0.01f)*prop,   0.4f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// right u

    ( 0.0f)*prop,   0.2f+0.01f, 0.0f,   1.0f,1.0f,1.0f,// right d
    (-0.2f)*prop,   0.3f+0.01f, 0.0f,   1.0f,1.0f,1.0f,// left d
	( 0.0f)*prop,   0.4f+0.01f, 0.0f,   1.0f,1.0f,1.0f,// left u
	( 0.2f)*prop,   0.3f+0.01f, 0.0f,   1.0f,1.0f,1.0f,// right u

     (0.2f+0.01f)*prop,   0.1f+0.005f, 0.0f,   1.0f,1.0f,1.0f,// right d
     (0.0f+0.01f)*prop,   0.2f+0.005f, 0.0f,   1.0f,1.0f,1.0f,// left d
	 (0.2f+0.01f)*prop,   0.3f+0.005f, 0.0f,   1.0f,1.0f,1.0f,// left u
	(0.4f+0.01f)*prop,   0.2f+0.005f, 0.0f,   1.0f,1.0f,1.0f,// right u

//5
    (-1.0f-0.04f)*prop,   0.5f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// left d
	(-0.8f-0.04f)*prop,   0.6f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// left u
	(-0.6f-0.04f)*prop,   0.5f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// right u
    (-0.8f-0.04f)*prop,   0.4f+0.02f, 0.0f,   1.0f,1.0f,1.0f,// right d

    (-0.8f-0.03f)*prop,   0.4f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// left d
	(-0.6f-0.03f)*prop,   0.5f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// left u
	(-0.4f-0.03f)*prop,   0.4f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// right u
    (-0.6f-0.03f)*prop,   0.3f+0.015f, 0.0f,   1.0f,1.0f,1.0f,// right d	 
    
    (-0.6f-0.02f)*prop,   0.3f+0.01f, 0.0f,   1.0f,1.0f,1.0f,// left d
	(-0.4f-0.02f)*prop,   0.4f+0.01f, 0.0f,   1.0f,1.0f,1.0f,// left u
	(-0.2f-0.02f)*prop,   0.3f+0.01f, 0.0f,   1.0f,1.0f,1.0f,// right u
    (-0.4f-0.02f)*prop,   0.2f+0.01f, 0.0f,   1.0f,1.0f,1.0f,// right d
     
    (-0.4f-0.01f)*prop,   0.2f+0.005f, 0.0f,   1.0f,1.0f,1.0f,// left d
	(-0.2f-0.01f)*prop,   0.3f+0.005f, 0.0f,   1.0f,1.0f,1.0f,// left u
	( 0.0f-0.01f)*prop,   0.2f+0.005f, 0.0f,   1.0f,1.0f,1.0f,// right u
    (-0.2f-0.01f)*prop,   0.1f+0.005f, 0.0f,   1.0f,1.0f,1.0f,// right d
     
    -0.2f*prop,   0.1f, 0.0f,   1.0f,1.0f,1.0f,// left d
	 0.0f*prop,   0.2f, 0.0f,   1.0f,1.0f,1.0f,// left u
	 0.2f*prop,   0.1f, 0.0f,   1.0f,1.0f,1.0f,// right u
     0.0f*prop,   0.0f, 0.0f,   1.0f,1.0f,1.0f,// right d
	 
//Right
  //1
     0.2f*prop,  -0.1f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 0.2f*prop,   0.1f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 0.0f*prop,   0.0f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 0.0f*prop,  -0.2f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.2f+0.01f)*prop,  -0.1f+0.005f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.2f+0.01f)*prop,   0.1f+0.005f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.4f+0.01f)*prop,   0.2f+0.005f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.4f+0.01f)*prop,   0.0f+0.005f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.4f+0.021f)*prop,   0.0f+0.01f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.4f+0.021f)*prop,   0.2f+0.01f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.6f+0.021f)*prop,   0.3f+0.01f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.6f+0.021f)*prop,   0.1f+0.01f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.6f+0.032f)*prop,   0.1f+0.015f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.6f+0.032f)*prop,   0.3f+0.015f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.8f+0.032f)*prop,   0.4f+0.015f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.8f+0.032f)*prop,   0.2f+0.015f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.8f+0.042f)*prop,   0.2f+0.02f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.8f+0.042f)*prop,   0.4f+0.02f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (1.0f+0.042f)*prop,   0.5f+0.02f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (1.0f+0.042f)*prop,   0.3f+0.02f, 0.0f,   1.0f,0.0f,0.2f,// right d

//2  Gr
     (0.2f)*prop,  -0.3f-0.01f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.2f)*prop,  -0.1f-0.01f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.0f)*prop,  -0.2f-0.01f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.0f)*prop,  -0.4f-0.01f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.2f+0.01f)*prop,  -0.3f-0.005f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.2f+0.01f)*prop,  -0.1f-0.005f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.4f+0.01f)*prop,   0.0f-0.005f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.4f+0.01f)*prop,  -0.2f-0.005f, 0.0f,   1.0f,0.0f,0.2f,// right d

    ( 0.4f+0.021f)*prop,  -0.2f-0.00f, 0.0f,   1.0f,0.0f,0.2f,// left d
	( 0.4f+0.021f)*prop,   0.0f-0.00f, 0.0f,   1.0f,0.0f,0.2f,// left u
	( 0.6f+0.021f)*prop,   0.1f-0.00f, 0.0f,   1.0f,0.0f,0.2f,// right u
	( 0.6f+0.021f)*prop,  -0.1f-0.00f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.6f+0.032f)*prop,  -0.1f+0.005f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.6f+0.032f)*prop,   0.1f+0.005f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.8f+0.032f)*prop,   0.2f+0.005f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.8f+0.032f)*prop,   0.0f+0.005f, 0.0f,   1.0f,0.0f,0.2f,// right d


     (0.8f+0.042f)*prop,   0.0f+0.01f, 0.0f,   1.0f,0.0f,0.2f,// left d
  	 (0.8f+0.042f)*prop,   0.2f+0.01, 0.0f,    1.0f,0.0f,0.2f,// left u
	 (1.0f+0.042f)*prop,   0.3f+0.01f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (1.0f+0.042f)*prop,   0.1f+0.01f, 0.0f,   1.0f,0.0f,0.2f,// right d

//3  Gw
	 0.0f*prop,  -0.4f-0.02f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 0.0f*prop,  -0.6f-0.02f, 0.0f,   1.0f,0.0f,0.2f,// right d
     0.2f*prop,  -0.5f-0.02f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 0.2f*prop,  -0.3f-0.02f, 0.0f,   1.0f,0.0f,0.2f,// left u

     (0.2f+0.01f)*prop,  -0.5f-0.015f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.2f+0.01f)*prop,  -0.3f-0.015f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.4f+0.01f)*prop,  -0.2f-0.015f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.4f+0.01f)*prop,  -0.4f-0.015f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.4f+0.021f)*prop,  -0.4f-0.01f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.4f+0.021f)*prop,  -0.2f-0.01f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.6f+0.021f)*prop,  -0.1f-0.01f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.6f+0.021f)*prop,  -0.3f-0.01f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.6f+0.032f)*prop,  -0.3f-0.005f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.6f+0.032f)*prop,  -0.1f-0.005f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.8f+0.032f)*prop,   0.0f-0.005f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.8f+0.032f)*prop,  -0.2f-0.005f, 0.0f,   1.0f,0.0f,0.2f,// right d

    ( 0.8f+0.042f)*prop,  -0.2f-0.0f, 0.0f,   1.0f,0.0f,0.2f,// left d
	( 0.8f+0.042f)*prop,   0.0f-0.0f, 0.0f,   1.0f,0.0f,0.2f,// left u
	( 1.0f+0.042f)*prop,   0.1f-0.0f, 0.0f,   1.0f,0.0f,0.2f,// right u
	( 1.0f+0.042f)*prop,  -0.1f-0.0f, 0.0f,   1.0f,0.0f,0.2f,// right d

//4  Gl
     (0.2f)*prop,  -0.7f-0.03f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.2f)*prop,  -0.5f-0.03f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.0f)*prop,  -0.6f-0.03f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.0f)*prop,  -0.8f-0.03f, 0.0f,   1.0f,0.0f,0.2f,// right d

    ( 0.2f+0.01f)*prop,  -0.7f-0.025f, 0.0f,   1.0f,0.0f,0.2f,// left d
	( 0.2f+0.01f)*prop,  -0.5f-0.025f, 0.0f,   1.0f,0.0f,0.2f,// left u
	( 0.4f+0.01f)*prop,  -0.4f-0.025f, 0.0f,   1.0f,0.0f,0.2f,// right u
	( 0.4f+0.01f)*prop,  -0.6f-0.025f, 0.0f,   1.0f,0.0f,0.2f,// right d

    (0.4f+0.021f)*prop,  -0.6f-0.02f, 0.0f,   1.0f,0.0f,0.2f,// left d
	(0.4f+0.021f)*prop,  -0.4f-0.02f, 0.0f,   1.0f,0.0f,0.2f,// left u
	( 0.6f+0.021f)*prop,  -0.3f-0.02f, 0.0f,   1.0f,0.0f,0.2f,// right u
	( 0.6f+0.021f)*prop,  -0.5f-0.02f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.6f+0.032f)*prop,  -0.5f-0.015f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.6f+0.032f)*prop,  -0.3f-0.015f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.8f+0.032f)*prop,  -0.2f-0.015f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.8f+0.032f)*prop,  -0.4f-0.015f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.8f+0.042f)*prop,  -0.4f-0.01f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.8f+0.042f)*prop,  -0.2f-0.01f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (1.0f+0.042f)*prop,  -0.1f-0.01f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (1.0f+0.042f)*prop,  -0.3f-0.01f, 0.0f,   1.0f,0.0f,0.2f,// right d

//5-
     0.2f*prop,  -0.9f-0.04f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 0.2f*prop,  -0.7f-0.04f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 0.0f*prop,  -0.8f-0.04f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 0.0f*prop,  -1.0f-0.04f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.2f+0.01f)*prop,  -0.9f-0.035f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.2f+0.01f)*prop,  -0.7f-0.035f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.4f+0.01f)*prop,  -0.6f-0.035f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.4f+0.01f)*prop,  -0.8f-0.035f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.4f+0.021f)*prop,  -0.8f-0.03f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.4f+0.021f)*prop,  -0.6f-0.03f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.6f+0.021f)*prop,  -0.5f-0.03f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.6f+0.021f)*prop,  -0.7f-0.03f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.6f+0.032f)*prop,  -0.7f-0.025f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.6f+0.032f)*prop,  -0.5f-0.025f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (0.8f+0.032f)*prop,  -0.4f-0.025f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (0.8f+0.032f)*prop,  -0.6f-0.025f, 0.0f,   1.0f,0.0f,0.2f,// right d

     (0.8f+0.042f)*prop,  -0.6f-0.02f, 0.0f,   1.0f,0.0f,0.2f,// left d
	 (0.8f+0.042f)*prop,  -0.4f-0.02f, 0.0f,   1.0f,0.0f,0.2f,// left u
	 (1.0f+0.042f)*prop,  -0.3f-0.02f, 0.0f,   1.0f,0.0f,0.2f,// right u
	 (1.0f+0.042f)*prop,  -0.5f-0.02f, 0.0f,   1.0f,0.0f,0.2f// right d
};

GLuint indeces[] = {
//gg
    0,2,1,0,3,2,
    4,6,5,4,7,6,
    8,10,9, 8,11,10,
    12,14,13,12,15,14,
    16,18,17,16,19,18,
//rr
    20,22,21,20,23,22,
    24,26,25,24,27,26,
    28,30,29,28,31,30,
    32,34,33,32,35,34,
    36,38,37,36,39,38,
//2
    40,42,41,40,43,42,
    44,46,45,44,47,46,
    48,50,49,48,51,50,
    52,54,53,52,55,54,
    56,58,57,56,59,58,
//3
    60,62,61,60,63,62,
    64,66,65,64,67,66,
    68,70,69,68,71,70,
    72,74,73,72,75,74,
    76,78,77,76,79,78,
//4
    80,82,81,80,83,82,
    84,86,85,84,87,86,
    88,90,89,88,91,90,
    92,94,93,92,95,94,
    96,98,97,96,99,98,
//5
    100,102,101,100,103,102,
    104,106,105,104,107,106,
    108,110,109,108,111,110,
    112,114,113,112,115,114,
    116,118,117,116,119,118,
//ww  ///1
    120,122,121,120,123,122,
    124,126,125,124,127,126,
    128,130,129,128,131,130,
    132,134,133,132,135,134,
    136,138,137,136,139,138,
//2
    140,142,141,140,143,142,
    144,146,145,144,147,146,
    148,150,149,148,151,150,
    152,154,153,152,155,154,
    156,158,157,156,159,158,
//3
    160,162,161,160,163,162,
    164,166,165,164,167,166,
    168,170,169,168,171,170,
    172,174,173,172,175,174,
    176,178,177,176,179,178,
// 4   
    180,182,181,180,183,182,
    184,186,185,184,187,186,
    188,190,189,188,191,190,
    192,194,193,192,195,194,
    196,198,197,196,199,198,
//5    
    200,202,201,200,203,202,
    204,206,205,204,207,206,
    208,210,209,208,211,210,
    212,214,213,212,215,214,
    216,218,217,216,219,218, 
//   
    220,222,221,220,223,222,
    224,226,225,224,227,226,
    228,230,229,228,231,230,
    232,234,233,232,235,234,
    236,238,237,236,239,238,
//   
    240,242,241,240,243,242,
    244,246,245,244,247,246,
    248,250,249,248,251,250,
    252,254,253,252,255,254,
    256,258,257,256,259,258,
//   
    260,262,261,260,263,262,
    264,266,265,264,267,266,
    268,270,269,268,271,270,
    272,274,273,272,275,274,
    276,278,277,276,279,278, 
//   
    280,282,281,280,283,282,
    284,286,285,284,287,286,
    288,290,289,288,291,290,
    292,294,293,292,295,294,
    296,298,297,296,299,298,
//   
    300,302,301,300,303,302,
    304,306,305,304,307,306,
    308,310,309,308,311,310,
    312,314,313,312,315,314,
    316,318,317,316,319,318 
};

int main(){
    char right[SIZE][SIZE] = {{'R', 'R', 'R', 'R', 'R'},
                            {'R', 'R', 'R', 'R', 'R'},
                            {'R', 'R', 'R', 'R', 'R'},
                            {'R', 'R', 'R', 'R', 'R'},
                            {'R', 'R', 'R', 'R', 'R'}};
 
    char left[SIZE][SIZE] = {{'O', 'O', 'O', 'O', 'O'},
                           {'O', 'O', 'O', 'O', 'O'},
                           {'O', 'O', 'O', 'O', 'O'},
                           {'O', 'O', 'O', 'O', 'O'},
                           {'O', 'O', 'O', 'O', 'O'}};
                          
    char front[SIZE][SIZE] = {{'G', 'G', 'G', 'G', 'G'},
                           {'G', 'G', 'G', 'G', 'G'},
                           {'G', 'G', 'G', 'G', 'G'},
                           {'G', 'G', 'G', 'G', 'G'},
                           {'G', 'G', 'G', 'G', 'G'}};
                          
    char back[SIZE][SIZE] = {{'B', 'B', 'B', 'B', 'B'},
                            {'B', 'B', 'B', 'B', 'B'},
                            {'B', 'B', 'B', 'B', 'B'},
                            {'B', 'B', 'B', 'B', 'B'},
                            {'B', 'B', 'B', 'B', 'B'}};
                           
    char up[SIZE][SIZE] = {{'W', 'W', 'W', 'W', 'W'},
                         {'W', 'W', 'W', 'W', 'W'},
                         {'W', 'W', 'W', 'W', 'W'},
                         {'W', 'W', 'W', 'W', 'W'},
                         {'W', 'W', 'W', 'W', 'W'}};
                        
    char down[SIZE][SIZE] = {{'Y', 'Y', 'Y', 'Y', 'Y'},
                           {'Y', 'Y', 'Y', 'Y', 'Y'},
                           {'Y', 'Y', 'Y', 'Y', 'Y'},
                           {'Y', 'Y', 'Y', 'Y', 'Y'},
                           {'Y', 'Y', 'Y', 'Y', 'Y'}};
    

    //Создаём новую историю сохранений
    struct history* history = init_history();

    int count_moves = 0;
    //save_data_to_history(history,left,front,right,back,up,down,&count_moves);
    
    glfwInit();
  
    GLFWwindow* window = NULL;
    window = openWindow(window);

    if(ifWindowNull(window)==1){return -1;}

    glfwMakeContextCurrent(window); //object
    gladLoadGL();
    int width=WINDOW_WIDTH, height=WINDOW_HEIGHT;
    
    glViewport(0, 0, width, height);
    
    
    Shader* shaderProgram=malloc(sizeof(Shader));
    Shader_init(shaderProgram, "./src/graphics/default.vert.glsl","./src/graphics/default.frag.glsl");

    shaderProgram->texture_slot0_uniform = glGetUniformLocation(shaderProgram->ID, TEXTURE_SLOT0_UNIFORM);
    glUniform1i(shaderProgram->texture_slot0_uniform, 0);
    glEnable(GL_BLEND);   // neeeeee ������������ 2
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /* ������� */
    object* CUBE = create_object(1);

    object* button_u = create_object(0);
    object* button_r = create_object(0);
    object* button_l = create_object(0);
    object* button_d = create_object(0);
    object* button_reset = create_object(0);
    object* button_solve = create_object(0);
    object* button_back = create_object(0);
    object* button_forward = create_object(0);
    object* button_begin = create_object(0);
    object* button_end = create_object(0);

    butt_collect(button_u,"up.png",-2.2,-1.8, 1.1, 1.5);
    butt_collect(button_r,"right.png",-1.8,-1.4, 0.7, 1.1);
    butt_collect(button_d,"down.png",-2.2,-1.8, 0.3, 0.7);
    butt_collect(button_l,"left.png",-2.6,-2.2, 0.7, 1.1);
    butt_collect(button_reset,"reset.png",-2.7,-1.2, -0.1, 0.2);
    butt_collect(button_solve,"solve.png",-2.7,-1.2, -0.5, -0.2);

    butt_collect(button_back,"back.png",1.4,1.8, 0.7, 1.1);
    butt_collect(button_forward,"forward.png",2.2,2.6, 0.7, 1.1);//
    butt_collect(button_begin,"begin.png",1.8,2.2, 1.1, 1.5);
    butt_collect(button_end,"end.png",1.8,2.2, 0.3, 0.7);
    
    int flag = 0;
    int pressed = 0;
    int where = 0;
    int pres_r = 0;
    int pres_u = 0;
    int pres_l = 0;
    int pres_d = 0;
    int active = 1;
    int active_bot_r = 0;
    int active_bot_u = 0;
    int active_bot_d = 0;
    int active_bot_l = 0;
    char orient;
    
    int status_cube = 0;
    GLuint uniID = glGetUniformLocation(shaderProgram->ID,"scale");
    GLuint uniRenderVarID = glGetUniformLocation(shaderProgram->ID,"render_variant");
    
    while(!glfwWindowShouldClose(window)){
        
        pressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if(!pressed && active == 1){active = 0;}
        pres_r = glfwGetKey(window,GLFW_KEY_RIGHT);
        pres_u = glfwGetKey(window,GLFW_KEY_UP);
        pres_l = glfwGetKey(window,GLFW_KEY_LEFT);
        pres_d = glfwGetKey(window,GLFW_KEY_DOWN);
 

        if(glfwGetKey(window,GLFW_KEY_TAB)){
            break;
        }
        if(!(pres_r || pres_u || pres_l || pres_d) && active == 0){
            
            if(where_cur_bot(window,button_r)){
                butt_collect(button_r,"right_light.png",-1.8,-1.4, 0.7, 1.1);
                button_r->active_bot = 1;

                if(pressed){
                    orient = 'r';active = 1;
                    turn_cube(&count_moves,history,orient, left, front, right, back,up,down);
                }
            }
            else if(where_cur_bot(window,button_u) ){
                butt_collect(button_u,"up_light.png",-2.2,-1.8, 1.1, 1.5);
                button_u->active_bot = 1;
                if(pressed){
                    orient = 'u';active = 1;
                    turn_cube(&count_moves,history,orient, left, front, right, back,up,down);
                }
            }
            else if(where_cur_bot(window,button_l)){
                butt_collect(button_l,"left_light.png",-2.6,-2.2, 0.7, 1.1);
                button_l->active_bot = 1;
                if(pressed){
                    orient = 'l';active = 1;
                    turn_cube(&count_moves,history,orient, left, front, right, back,up,down);
                }
            }
            else if(where_cur_bot(window,button_d)){
                butt_collect(button_d,"down_light.png",-2.2,-1.8, 0.3, 0.7);
                button_d->active_bot = 1;
                if(pressed){
                    orient = 'd';active = 1;
                    turn_cube(&count_moves,history,orient, left, front, right, back,up,down);
                }
            }
            else if(where_cur_bot(window,button_reset)){
                butt_collect(button_reset,"reset_light.png",-2.7,-1.2, -0.1, 0.2);
                button_reset->active_bot = 1;
                if(pressed){
                    active = 1;
                    clear_history(history);
                    reset(left, front, right, back,up,down);
                }
            }
            else if(where_cur_bot(window,button_solve)){
                butt_collect(button_solve,"solve_light.png",-2.7,-1.2, -0.5, -0.2);
                button_solve->active_bot = 1;
                if(pressed){
                    active = 1;
                    count_moves = 0;
                    clear_history(history);
                    save_data_to_history(history,left, front, right, back,up,down, &count_moves);
                    clock_t begin = clock();
                    solve(&count_moves,history,left, front, right, back,up,down);
                    clock_t end = clock();
                    
                    printf("The elapsed time is %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
                    printf("count_moves %d\n",count_moves);
                    status_cube=count_moves;
                }
            }
            else if(where_cur_bot(window,button_back)){
                butt_collect(button_back,"back_light.png",1.4,1.8, 0.7, 1.1);
                button_back->active_bot = 1;
                if(pressed){
                    active = 1;
                    //���������� ���������
                    
                    if(count_moves!=1){
                        if(status_cube==0){status_cube=count_moves;}
                        status_cube--; 
                        view_cube_from_history(GET_PREV,history,left,front,right,back,up,down);
                    }
                }
            }
            else if(where_cur_bot(window,button_forward)){
                butt_collect(button_forward,"forward_light.png",2.2,2.6, 0.7, 1.1);
                button_forward->active_bot = 1;
                if(pressed){
                    active = 1;
                    if(count_moves!=0){
                        if(status_cube==0){status_cube=count_moves;}
                        status_cube++;
                        if(status_cube > count_moves){
                            status_cube--;
                        }
                        view_cube_from_history(GET_NEXT,history,left,front,right,back,up,down);
                    
                    }
                    //��������� ��������� ������
                }
            }
            else if(where_cur_bot(window,button_begin)){
                butt_collect(button_begin,"begin_light.png",1.8,2.2, 1.1, 1.5);
                button_begin->active_bot = 1;
                if(pressed){
                    active = 1;
                    //������ ��������� ������
                    if(count_moves!=0){
                        status_cube=1;
                        view_cube_from_history(GET_HEAD,history,left,front,right,back,up,down);
                    }
                }
            }
            else if(where_cur_bot(window,button_end)){
                butt_collect(button_end,"end_light.png",1.8,2.2, 0.3, 0.7);
                button_end->active_bot = 1;
                if(pressed){
                    active = 1;
                    //��������� ��������� ������
                    if(count_moves!=0){
                        status_cube=count_moves;
                        view_cube_from_history(GET_TAIL,history,left,front,right,back,up,down);
                    }
                }
            }
            change_cube(&(CUBE->vao),&(CUBE->vbo),&(CUBE->ebo),front,up,right);
                              
        }
        else if(pressed && (pres_r || pres_u || pres_l || pres_d) && active == 0){
            where = where_cursor(window);
            //printf("%d ",where);
            active = 1;
            
            if(pres_r){orient = 'r';}
            else if(pres_u) {orient = 'u';}
            else if(pres_l) {orient = 'l';}
            else if(pres_d) {orient = 'd';}
            // printf("%c ",orient);

            if(operation(&count_moves,history,where,orient, left, front, right, back,up,down)){
                mas_to_color(front,'f');
                mas_to_color(up,'u');
                mas_to_color(right,'r');
            }
            // printf("%c %c %c %c %c\n",right[0][0],right[0][1],right[0][2],right[0][3],right[0][4]);
            change_cube(&(CUBE->vao),&(CUBE->vbo),&(CUBE->ebo),front,up,right);
        }
        else{pressed = 0;pres_r=0;pres_u=0;pres_l=0;pres_d=0;}
        flag++;
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Shader_Active(shaderProgram);
        glUniform1f(uniID,PRESSURE);
        
        glUniform1i(uniRenderVarID,0);
        VAO_Bind(&(CUBE->vao));
        
        glDrawElements(GL_TRIANGLES,480, GL_UNSIGNED_INT,0);  

        glUniform1i(uniRenderVarID,1);
        
        VAO_Bind(&(button_u->vao));
        glBindTexture(GL_TEXTURE_2D,button_u->Texture);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);
           
        VAO_Bind(&(button_r->vao));
        glBindTexture(GL_TEXTURE_2D,button_r->Texture);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);

        VAO_Bind(&(button_d->vao));
        glBindTexture(GL_TEXTURE_2D,button_d->Texture);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);
           
        VAO_Bind(&(button_l->vao));
        glBindTexture(GL_TEXTURE_2D,button_l->Texture);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);

        VAO_Bind(&(button_reset->vao));
        glBindTexture(GL_TEXTURE_2D,button_reset->Texture);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);

        VAO_Bind(&(button_solve->vao));
        glBindTexture(GL_TEXTURE_2D,button_solve->Texture);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);

        VAO_Bind(&(button_back->vao));
        glBindTexture(GL_TEXTURE_2D,button_back->Texture);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);

        VAO_Bind(&(button_forward->vao));
        glBindTexture(GL_TEXTURE_2D,button_forward->Texture);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);

        VAO_Bind(&(button_begin->vao));
        glBindTexture(GL_TEXTURE_2D,button_begin->Texture);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);

        VAO_Bind(&(button_end->vao));
        glBindTexture(GL_TEXTURE_2D,button_end->Texture);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);

        change_bot(button_r,button_u,button_d,button_l,button_reset,button_solve,button_back,button_forward,button_begin,button_end);
        
        VAO_Unbind();
        VBO_Unbind();
        EBO_Unbind();
        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glfwPollEvents();
    }

    //Очистка истории и освобождение памяти
    clear_history(history);
    free(history);

    delete_obj(CUBE);
    delete_obj(button_u);
    delete_obj(button_r);
    delete_obj(button_d);
    delete_obj(button_l);
    delete_obj(button_reset);
    delete_obj(button_solve);

    delete_obj(button_back);
    delete_obj(button_forward);
    delete_obj(button_begin);
    delete_obj(button_end);

    Shader_Delete(shaderProgram);
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}

void change_bot(object* button_r,object* button_u,object* button_d,object* button_l,object* button_reset,object* button_solve,object* button_back,object* button_forward,object* button_begin,object* button_end){
    if(button_r->active_bot){
        butt_collect(button_r,"right.png",-1.8,-1.4, 0.7, 1.1);
        button_r->active_bot = 0;
    }
    else if(button_u->active_bot){
        butt_collect(button_u,"up.png",-2.2,-1.8, 1.1, 1.5);
        button_u->active_bot = 0;
    }
    else if(button_d->active_bot){
        butt_collect(button_d,"down.png",-2.2,-1.8, 0.3, 0.7);
        button_d->active_bot = 0;
    }
    else if(button_l->active_bot){
        butt_collect(button_l,"left.png",-2.6,-2.2, 0.7, 1.1);
        button_l->active_bot = 0;
    }
    else if(button_reset->active_bot){
        butt_collect(button_reset,"reset.png",-2.7,-1.2, -0.1, 0.2);
        button_reset->active_bot = 0;
    }
    else if(button_solve->active_bot){
        butt_collect(button_solve,"solve.png",-2.7,-1.2, -0.5, -0.2);
        button_solve->active_bot = 0;
    }
    else if(button_back->active_bot){
        butt_collect(button_back,"back.png",1.4,1.8, 0.7, 1.1);
        button_back->active_bot = 0;
    }
    else if(button_forward->active_bot){
        butt_collect(button_forward,"forward.png",2.2,2.6, 0.7, 1.1);
        button_forward->active_bot = 0;
    }
    else if(button_begin->active_bot){
        butt_collect(button_begin,"begin.png",1.8,2.2, 1.1, 1.5);
        button_begin->active_bot = 0;
    }
    else if(button_end->active_bot){
        butt_collect(button_end,"end.png",1.8,2.2, 0.3, 0.7);
        button_end->active_bot = 0;
    }
}
void delete_obj(object* OBJ){
    VAO_Delete(&(OBJ->vao));
    VBO_Delete(&(OBJ->vbo));
    EBO_Delete(&(OBJ->ebo));
    free(OBJ);
}
object* create_object(int isCube){
    object* new_obj = (object*)malloc(sizeof(object));

    VAO_Constructor(&(new_obj->vao));
    VAO_Bind(&(new_obj->vao));

    VBO_Constructor(&(new_obj->vbo),vertices,sizeof(vertices));
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    EBO_Constructor(&(new_obj->ebo),indeces,sizeof(indeces));
    if(isCube){
        VAO_LinkAttrib(&(new_obj->vao),&(new_obj->vbo),0,3,GL_FLOAT,6*sizeof(float),(void*)0);
        VAO_LinkAttrib(&(new_obj->vao),&(new_obj->vbo),1,3,GL_FLOAT,6*sizeof(float),(void*)(3*sizeof(float)));
    }
    else{
        VAO_LinkAttrib(&(new_obj->vao),&(new_obj->vbo),0,3,GL_FLOAT,5*sizeof(float),(void*)0);
        VAO_LinkAttrib(&(new_obj->vao),&(new_obj->vbo),2,2,GL_FLOAT,5*sizeof(float),(void*)(3*sizeof(float)));
    }
    return new_obj;
}


void butt_collect(object* OBJ,char* image_name,float x1,float x2,float y1, float y2){
    int image_width, image_height, image_color_channels_num;
    unsigned char* image_data = stbi_load(image_name, &image_width, &image_height, &image_color_channels_num, 0); // neeeee
    
    glGenTextures(1, &(OBJ->Texture));
    glBindTexture(GL_TEXTURE_2D,OBJ->Texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // neeeee
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //x
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //y
    glTexImage2D(GL_TEXTURE_2D, 0, image_color_channels_num == 3 ? GL_RGB : GL_RGBA, image_width, image_height, 0, image_color_channels_num == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, image_data);  // neeee
    glGenerateMipmap(GL_TEXTURE_2D);   // neeeee
    stbi_image_free(image_data);
    glBindTexture(GL_TEXTURE_2D, 0);

    VAO_Bind(&(OBJ->vao));
    VBO_Bind(&(OBJ->vbo));
    EBO_Bind(&(OBJ->ebo));

    OBJ->coord[0]=x1;
    OBJ->coord[1]=x2;
    OBJ->coord[2]=y1;
    OBJ->coord[3]=y2;
    
    float vertices_bot[]={
        x2*prop,   y2, 0.0f,   1.0f,0.0f,// right u
        x2*prop,   y1, 0.0f,   1.0f,1.0f,// right d
        x1*prop,   y1, 0.0f,   0.0f,1.0f,// left d
        x1*prop,   y2, 0.0f,   0.0f,0.0f// left u
    };
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_bot), vertices_bot);
    VAO_Unbind();
    VBO_Unbind();
    EBO_Unbind();
}
void change_cube(VAO* VAO1,VBO* VBO1, EBO* EBO1, char front[SIZE][SIZE], char up[SIZE][SIZE], char right[SIZE][SIZE]){
    mas_to_color(front,'f');
    mas_to_color(up,'u');
    mas_to_color(right,'r');
    VAO_Bind(VAO1);
    VBO_Bind(VBO1);
    EBO_Bind(EBO1);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);  
    VAO_Unbind();
    VBO_Unbind();
    EBO_Unbind();
}
int operation(int* count_moves,struct history* history,int where,char orient, char l[SIZE][SIZE], char f[SIZE][SIZE], char r[SIZE][SIZE], char b[SIZE][SIZE], char u[SIZE][SIZE], char d[SIZE][SIZE]){
    
    if(orient == 'r'){
        switch(where){
            case front1_1:U(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_2:U(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_3:U(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_4:U(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_5:U(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_1:U2(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_2:U2(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_3:U2(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_4:U2(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_5:U2(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_1:E(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_2:E(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_3:E(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_4:E(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_5:E(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_1:D2(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_2:D2(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_3:D2(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_4:D2(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_5:D2(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_1:D(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_2:D(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_3:D(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_4:D(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_5:D(count_moves,history,l,f,r,b,u,d);return 1;
            default: return 0;
        }
    }
    
    else if(orient == 'u'){
        switch(where){
            case front1_1:L_(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_1:L_(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_1:L_(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_1:L_(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_1:L_(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_2:L2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_2:L2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_2:L2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_2:L2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_2:L2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_3:M(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_3:M(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_3:M(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_3:M(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_3:M(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_4:R2(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_4:R2(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_4:R2(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_4:R2(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_4:R2(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_5:R(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_5:R(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_5:R(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_5:R(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_5:R(count_moves,history,l,f,r,b,u,d);return 1;
            default: return 0;
        }
    }
    else if(orient == 'l'){
        switch(where){
            case front1_1:U_(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_2:U_(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_3:U_(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_4:U_(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_5:U_(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_1:U2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_2:U2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_3:U2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_4:U2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_5:U2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_1:E_(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_2:E_(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_3:E_(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_4:E_(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_5:E_(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_1:D2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_2:D2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_3:D2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_4:D2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_5:D2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_1:D_(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_2:D_(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_3:D_(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_4:D_(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_5:D_(count_moves,history,l,f,r,b,u,d);return 1;
            default: return 0;
        }
    }
    else if(orient == 'd'){
        switch(where){
            case front1_1:L(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_1:L(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_1:L(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_1:L(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_1:L(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_2:L2(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_2:L2(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_2:L2(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_2:L2(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_2:L2(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_3:M_(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_3:M_(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_3:M_(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_3:M_(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_3:M_(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_4:R2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_4:R2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_4:R2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_4:R2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_4:R2_(count_moves,history,l,f,r,b,u,d);return 1;
            case front1_5:R_(count_moves,history,l,f,r,b,u,d);return 1;
            case front2_5:R_(count_moves,history,l,f,r,b,u,d);return 1;
            case front3_5:R_(count_moves,history,l,f,r,b,u,d);return 1;
            case front4_5:R_(count_moves,history,l,f,r,b,u,d);return 1;
            case front5_5:R_(count_moves,history,l,f,r,b,u,d);return 1;
            default: return 0;
        }
    }
    
    return 0;
}
int where_cursor(GLFWwindow* window){
    GLdouble mouse_x,mouse_y;
    glfwGetCursorPos(window, &mouse_x,&mouse_y);

    mouse_y = -mouse_y + WINDOW_HEIGHT;
    mouse_x =  mouse_x / WINDOW_WIDTH*2-1;
    mouse_y =  mouse_y / WINDOW_HEIGHT*2-1;
    mouse_x = mouse_x * PRES_DIV;
    mouse_y = mouse_y * PRES_DIV;
   
    int shift = 0;
    
    for( int i = 0;i<SIZE;i++){
      
        for(int j = 0; j<SIZE; j++){
             /* � ��������� ����������� �� ����� */
            if(vertices[shift+(i*SIZE+j)*24 + 3*6]<=mouse_x && mouse_x <= vertices[shift+(i*SIZE+j)*24 + 1*6] && vertices[shift+(i*SIZE+j)*24 + 3*6 + 1]<= mouse_y && mouse_y <=vertices[shift+(i*SIZE+j)*24 + 1*6 + 1]){
                return i*SIZE+j;
            }
        }
        if(i==4 && shift != 1200){
            shift+=600;
            i=-1;
        }
    }

    return -1;
}
int where_cur_bot(GLFWwindow* window,object* OBJ){
    GLdouble mouse_x,mouse_y;
    glfwGetCursorPos(window, &mouse_x,&mouse_y);

    mouse_y = -mouse_y + WINDOW_HEIGHT;
    mouse_x =  mouse_x / WINDOW_WIDTH*2-1;
    mouse_y =  mouse_y / WINDOW_HEIGHT*2-1;
    mouse_x = mouse_x * PRES_DIV;
    mouse_y = mouse_y * PRES_DIV;

    if(OBJ->coord[0]*prop<=mouse_x && mouse_x <= OBJ->coord[1]*prop && OBJ->coord[2]<= mouse_y && mouse_y <=OBJ->coord[3]){
        return 1;
    }
    return 0;
}

int ifWindowNull(GLFWwindow* window){
    if(window == NULL){
        printf("ERRRORRRRRRRRRRRRRRR");
        glfwTerminate();
        return 1;
    }
    return 0;
}
GLFWwindow* openWindow(GLFWwindow* window){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    window=glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"CUBES",NULL,NULL);
    return window;
}
void one_square(int i,char color){

    float c1,c2,c3;
    if(color == 'R'){
        c1 = r1;c2 = r2; c3 = r3;
    }
    else if(color == 'G'){
        c1 = g1;c2 = g2; c3 = g3;
    }
    else if(color == 'W'){
        c1 = w1;c2 = w2; c3 = w3;
    }
    else if(color == 'O'){
        c1 = o1;c2 = o2; c3 = o3;
    }
    else if(color == 'B'){
        c1 = b1;c2 = b2; c3 = b3;
    }
    else if(color == 'Y'){
        c1 = yl1;c2 = yl2; c3 = yl3;
    }
     /* � ��������� ����������� �� ����� */
    for(int j = 0;j<4;j++){
        vertices[i + j*6 + 3]=c1;
        vertices[i + j*6 + 4]=c2;
        vertices[i + j*6 + 5]=c3;
    }
       
    
}
void mas_to_color(char mas[SIZE][SIZE],char edge){
    int i = 0; int shift = 0;
    if(edge == 'u'){
        shift = 600;
    }
    else if(edge == 'r'){
        shift = 1200;
    }
    for(;i<SIZE;i++){
        for(int j = 0; j<SIZE; j++){
            /* � ��������� ����������� �� ����� */
            /* ���������� ����� �������� */
            if(mas[i][j]=='R' && (vertices[shift + (i*SIZE+j)*24+3]!=r1 || vertices[shift + (i*SIZE+j)*24+4]!=r2 || vertices[shift + (i*SIZE+j)*24+5]!=r3)){
                one_square(shift + (i*SIZE+j)*24,'R');
            }
            else if(mas[i][j]=='G' && (vertices[shift + (i*SIZE+j)*24+3]!=g1 || vertices[shift + (i*SIZE+j)*24+4]!=g2 || vertices[shift + (i*SIZE+j)*24+5]!=g3)){
                one_square(shift + (i*SIZE+j)*24,'G');
            }
            else if(mas[i][j]=='W' && (vertices[shift + (i*SIZE+j)*24+3]!=w1 || vertices[shift + (i*SIZE+j)*24+4]!=w2 || vertices[shift + (i*SIZE+j)*24+5]!=w3)){
                one_square(shift + (i*SIZE+j)*24,'W');
            }
            else if(mas[i][j]=='O' && (vertices[shift + (i*SIZE+j)*24+3]!=o1 || vertices[shift + (i*SIZE+j)*24+4]!=o2 || vertices[shift + (i*SIZE+j)*24+5]!=o3)){
                one_square(shift + (i*SIZE+j)*24,'O');
            }
            else if(mas[i][j]=='B' && (vertices[shift + (i*SIZE+j)*24+3]!=b1 || vertices[shift + (i*SIZE+j)*24+4]!=b2 || vertices[shift + (i*SIZE+j)*24+5]!=b3)){
                one_square(shift + (i*SIZE+j)*24,'B');
            }
            else if(mas[i][j]=='Y' && (vertices[shift + (i*SIZE+j)*24+3]!=yl1 || vertices[shift + (i*SIZE+j)*24+4]!=yl2 || vertices[shift + (i*SIZE+j)*24+5]!=yl3)){
                one_square(shift + (i*SIZE+j)*24,'Y');
            }
        }
    }
}

///////////////////////////////////////////

void turn_cube(int* count_moves,struct history* history,char orient, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    char temp;
    if(orient == 'u'){
        for(int k = 0; k < SIZE; k++){
            /* � ��������� ����������� �� ����� 4-k */
            for (int i = 0; i < SIZE; i++) {
                temp = u[i][k];
                u[i][k] = f[i][k];
                f[i][k] = d[i][k];
                d[i][k] = b[4-i][4-k];
                b[4-i][4-k] = temp;
            }
        }
        edgeClock(r);
        edgeUnClock(l);
    }
    else if(orient == 'r'){
        for(int k = 0; k < SIZE; k++){
            for (int j = 0; j < SIZE; j++) {
                temp = r[k][j];
                r[k][j] = f[k][j];
                f[k][j] = l[k][j];
                l[k][j] = b[k][j];
                b[k][j] = temp;
            }
        }
        edgeClock(d);
        edgeUnClock(u);
    }
    else if(orient == 'l'){
        for(int k = 0; k < SIZE; k++){
            for (int j = 0; j < SIZE; j++) {
                temp = l[k][j];
                l[k][j] = f[k][j];
                f[k][j] = r[k][j];
                r[k][j] = b[k][j];
                b[k][j] = temp;
            }
        }
        edgeClock(u);
        edgeUnClock(d);
    }
    else if(orient == 'd'){
        for(int k = 0; k < SIZE; k++){
            /* � ��������� ����������� �� ����� 4-k */
            for (int i = 0; i < SIZE; i++) {
                temp = u[i][k];
                u[i][k] = b[4-i][4-k];
                b[4-i][4-k] = d[i][k];
                d[i][k] = f[i][k];
                f[i][k] = temp;
            }
        }
        edgeClock(l);
        edgeUnClock(r);
    }
    save_data_to_history(history,l,f,r,b,u,d, count_moves);
}
/////////////////////////////////////////////////////////
void solve_center_corn(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    int count = 0;
    char search;
    int cnt_edge = 0;
    int steps = 0;
    int doub;
    
    for(int j=0;j<6;j++){
        count = 0;
        steps = 0;
        search = f[2][2];
        cnt_edge = 0;
        
        cntNotOneColor(f,search,&count,2);
        while(count!=0){
            
                        
            search_and_rotate_center_corn(count_moves,history,l,f,r,b,u,d,&count,search);
            if(count!=0 && cnt_edge!=3 && steps!=4){
                cnt_edge++;
                turn_cube(count_moves,history,'r',l,f,r,b,u,d);
                turn_cube(count_moves,history,'d',l,f,r,b,u,d);
                turn_cube(count_moves,history,'l',l,f,r,b,u,d);
            }
            else if(count!=0 && cnt_edge==3 && steps!=4){
                turn_cube(count_moves,history,'d',l,f,r,b,u,d);
                int cnt = 0;
                steps = 0;
                do{
                    cntNotOneColor(f,f[2][2],&cnt,2);
                    if(cnt==0){
                        turn_cube(count_moves,history,'r',l,f,r,b,u,d);
                        steps++;
                    }
                    
                }
                while(cnt==0 && steps!=4 );//
                
                doub = count;
                search_and_rotate_center_corn(count_moves,history,l,f,r,b,u,d,&doub,search);
                turn_cube(count_moves,history,'u',l,f,r,b,u,d);
                
            }
            
            if( steps == 4){
                
                doub = count;
                search_and_rotate_center_corn(count_moves,history,l,f,r,b,u,d,&doub,search);
                turn_cube(count_moves,history,'d',l,f,r,b,u,d);
                search_and_rotate_center_corn(count_moves,history,l,f,r,b,u,d,&doub,search);
                break;
            }
        }
        if(cheak_center(2,l,f,r,b,u,d)){break;}
        turn_cube(count_moves,history,'d',l,f,r,b,u,d);
    }
    
}
void solve_center_rib(int*count_moves, struct history* history, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    int count = 0;
    char search = f[2][2];
    int cnt_edge = 0;
    int steps = 0;
    int doub;
    int cnt = 0;
    
    for(int j=0;j<6;j++){
        count = 0;
        steps = 0;
        search = f[2][2];
        cnt_edge = 0;
        
        cntNotOneColor(f,search,&count,1);
        
        while(count!=0){
            
            search_and_rotate_center_rib(count_moves,history,l,f,r,b,u,d,&count,search);
            if(count!=0 && cnt_edge!=3 && steps!=4){
                cnt_edge++;
                turn_cube(count_moves,history,'r',l,f,r,b,u,d);
                turn_cube(count_moves,history,'d',l,f,r,b,u,d);
                turn_cube(count_moves,history,'l',l,f,r,b,u,d);
            }
            else if(count!=0 && cnt_edge==3 && steps!=4){
                turn_cube(count_moves,history,'d',l,f,r,b,u,d);
                cnt = 0;
                steps = 0;
                do{
                    cntNotOneColor(f,f[2][2],&cnt,1);
                    if(cnt==0){
                        turn_cube(count_moves,history,'r',l,f,r,b,u,d);
                        steps++;
                    }
                    
                }
                while(cnt==0 && steps!=4 );//
                
                doub = count;
                search_and_rotate_center_rib(count_moves,history,l,f,r,b,u,d,&doub,search);
                turn_cube(count_moves,history,'u',l,f,r,b,u,d);
            }
            if(steps == 4){
                                
                doub = count;
                search_and_rotate_center_rib(count_moves,history,l,f,r,b,u,d,&doub,search);
                turn_cube(count_moves,history,'d',l,f,r,b,u,d);
                search_and_rotate_center_rib(count_moves,history,l,f,r,b,u,d,&doub,search);
                break;
            }
        }
        if(cheak_center(1,l,f,r,b,u,d)){break;}
        
        turn_cube(count_moves,history,'d',l,f,r,b,u,d);
    }
    
}
int cheak_center(int num, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    int count = 0;
    cntNotOneColor(l,l[2][2],&count,num);
    cntNotOneColor(f,l[2][2],&count,num);
    cntNotOneColor(r,l[2][2],&count,num);
    cntNotOneColor(b,l[2][2],&count,num);
    cntNotOneColor(u,l[2][2],&count,num);
    cntNotOneColor(d,l[2][2],&count,num);
    if(count>0){return 0;}
    return 1;
}
void cntNotOneColor(char edge[SIZE][SIZE],char search, int* count,int num){
    int* mas;
    int size = 0;
    int mas1[8]={1,2,2,1,2,3,3,2};
    int mas2[8]={1,1,1,3,3,1,3,3};

    if(num == 1){ mas=mas1;size = 8;}
    if(num == 2){ mas=mas2;size = 8;}

    for(int i = 0; i < size; i += 2){
        if( edge[mas[i]][mas[i+1]] != search ){
            (*count)++;
        }
    }
}
void search_and_rotate_center_corn(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE],int* count,char search){
    
    while( u[1][1] == search || u[1][3] == search || u[3][1] == search || u[3][3] == search ){

        if( u[1][1] == search ){
            while( f[1][3] == search ){F(count_moves,history,l,f,r,b,u,d);}
            U_(count_moves,history,l,f,r,b,u,d);
            U_(count_moves,history,l,f,r,b,u,d);
            center_corn(count_moves,history,l,f,r,b,u,d);
            (*count)--;
            
        }
        if( u[1][3] == search ){
            while(f[1][3]==search){F(count_moves,history,l,f,r,b,u,d);}
            U_(count_moves,history,l,f,r,b,u,d);
            center_corn(count_moves,history,l,f,r,b,u,d);
            (*count)--;

        }
        if( u[3][1] == search ){
            while(f[1][3]==search){F(count_moves,history,l,f,r,b,u,d);}
            U(count_moves,history,l,f,r,b,u,d);
            center_corn(count_moves,history,l,f,r,b,u,d);
            (*count)--;

        }
        if( u[3][3] == search ){
            while(f[1][3]==search){F(count_moves,history,l,f,r,b,u,d);}
            center_corn(count_moves,history,l,f,r,b,u,d);
            (*count)--;

        }
    }
    
}
void search_and_rotate_center_rib(int*count_moves, struct history* history, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE],int* count,char search){
    
     while( u[2][3] == search || u[1][2] == search || u[2][1] == search || u[3][2] == search ){

        if(u[2][3] == search){
            while(f[2][3]==search){F(count_moves,history,l,f,r,b,u,d);}
            center_rib(count_moves,history,l,f,r,b,u,d);
            (*count)--;
            
        }
        if(u[1][2] == search){
            while(f[2][3]==search){F(count_moves,history,l,f,r,b,u,d);}
            U_(count_moves,history,l,f,r,b,u,d);
        
            center_rib(count_moves,history,l,f,r,b,u,d);
            (*count)--;

        }
        if(u[2][1] == search){
            while(f[2][3]==search){F(count_moves,history,l,f,r,b,u,d);}
            U_(count_moves,history,l,f,r,b,u,d);
        
            U_(count_moves,history,l,f,r,b,u,d);
        
            center_rib(count_moves,history,l,f,r,b,u,d);
            (*count)--;

        }
        if(u[3][2] == search){
            while(f[2][3]==search){F(count_moves,history,l,f,r,b,u,d);}
            U(count_moves,history,l,f,r,b,u,d);
        
            center_rib(count_moves,history,l,f,r,b,u,d);
            (*count)--;

        }
    }
}

void solve(int*count_moves, struct history* history, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    /* ���������� � ������ 3�3 */
    solve_center_rib(count_moves,history,l,f,r,b,u,d);  // c����� ������������ ������
    solve_center_corn(count_moves,history,l,f,r,b,u,d); // ������ ������������ X
    solve_ribs(count_moves,history,l,f,r,b,u,d);// ��� �������� , ������ �����
    /* ������ 3�3 */
    solve_white_rib(count_moves,history,l,f,r,b,u,d); //��������� ������ ����� �����
    solve_corners(count_moves,history,l,f,r,b,u,d); // ��������� ������ ����� �����
    solve_right_place_for_rib(count_moves,history,l,f,r,b,u,d); // ���������� ������� �����
    yellow_ribs(count_moves,history,l,f,r,b,u,d); //��������� ����� ����� �� ������ �����
    four_edges_color(count_moves,history,l,f,r,b,u,d); // ������ ����� �������, 4 ������ ���� �������
    last_corners_part1(count_moves,history,l,f,r,b,u,d);
    last_corners_part2(count_moves,history,l,f,r,b,u,d);
}

/* ������ ���� */
void reset(char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    for(int i = 0; i< SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            r[i][j]='R';
            l[i][j]='O';
            f[i][j]='G';
            b[i][j]='B';
            u[i][j]='W';
            d[i][j]='Y';
        }
    }
}

void center_rib(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    R2_(count_moves,history,l,f,r,b,u,d);
    R_(count_moves,history,l,f,r,b,u,d);
    F_(count_moves,history,l,f,r,b,u,d);
    L2_(count_moves,history,l,f,r,b,u,d);
    L_(count_moves,history,l,f,r,b,u,d);

    R2(count_moves,history,l,f,r,b,u,d);
    R(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    R2(count_moves,history,l,f,r,b,u,d);
    R(count_moves,history,l,f,r,b,u,d);

    U(count_moves,history,l,f,r,b,u,d);
    L2(count_moves,history,l,f,r,b,u,d);
    L(count_moves,history,l,f,r,b,u,d);
    R2_(count_moves,history,l,f,r,b,u,d);
    R_(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    F(count_moves,history,l,f,r,b,u,d);
}

void center_corn(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    R2(count_moves,history,l,f,r,b,u,d);
    R(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    R2_(count_moves,history,l,f,r,b,u,d);
    R_(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    R2(count_moves,history,l,f,r,b,u,d);
    R(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    R2_(count_moves,history,l,f,r,b,u,d);
    R_(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
}
/////////////////// ribs
void printMatrix(char matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        printf("        ");
        for (int j = 0; j < SIZE; j++) {

            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}
void printRubiksCube(char left[SIZE][SIZE], char front[SIZE][SIZE], char right[SIZE][SIZE], char back[SIZE][SIZE], char up[SIZE][SIZE], char down[SIZE][SIZE]) {
    // ����� ������� �����
    printMatrix(up);

    // ����� �����, ��������, ������ � ������ ������
    for (int i = 0; i < SIZE; i++) {
        printf("%c%c%c%c%c   ", left[i][0], left[i][1], left[i][2], left[i][3], left[i][4]);
        printf("%c%c%c%c%c   ", front[i][0], front[i][1], front[i][2], front[i][3], front[i][4]);
        printf("%c%c%c%c%c   ", right[i][0], right[i][1], right[i][2], right[i][3], right[i][4]);
        printf("%c%c%c%c%c\n", back[i][0], back[i][1], back[i][2], back[i][3], back[i][4]);
    }

    // ����� ������ �����
    printMatrix(down);
    printf("\n");
}
void solve_ribs(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    int count;
    char search_f;
    char search_u;
    int cnt_edge;
    int steps;
    int doub;
    int num = 0;
    int count_cheak=1;
    int sequence_edges[12];
    while(1){
        count = 0;
        steps = 0;
        search_f = f[0][2];
        search_u = u[4][2];
        cnt_edge = 0;
        cntNotOneColor_rib(f,u,search_f,search_u,&count);
        count_cheak=count;
        
        while(count!=0){
            
            change_ribs(count_moves,history,0,1,l,f,r,b,u,d);
            
            
            if((f[4][1]==search_f && d[0][1]==search_u) || (f[4][3]==search_f && d[0][3]==search_u)){
                D(count_moves,history,l,f,r,b,u,d);
                U_(count_moves,history,l,f,r,b,u,d);
                R(count_moves,history,l,f,r,b,u,d);
                F(count_moves,history,l,f,r,b,u,d);
                U(count_moves,history,l,f,r,b,u,d);
            }
            if(f[4][1]==search_u && d[0][1]==search_f){
                num=1;
            }
            else if(f[4][3]==search_u && d[0][3]==search_f){
                num=3;
            }
            
            change_ribs(count_moves,history,num,2,l,f,r,b,u,d);
            
            count--;
            if(count!=0){
                turn_cube(count_moves,history,'d',l,f,r,b,u,d);
                turn_cube(count_moves,history,'l',l,f,r,b,u,d);
                
            }
            
        }
        int cheak = cheak_ribs(sequence_edges,l,f,r,b,u,d);
        
        
        /* ����� ���-�� ��������*/
        if(cheak == 0){break;}
        else if(cheak == 1){
            last_ribs(count_moves,history,sequence_edges,l,f,r,b,u,d);
            break;
        }
        else if(cheak == 2 && count_cheak==0){
            if(steps<3|| steps>4 && steps<7|| steps>8 && steps<11){
                turn_cube(count_moves,history,'u',l,f,r,b,u,d);
                steps++;
            }
            if(steps==4 || steps==7){
                turn_cube(count_moves,history,'l',l,f,r,b,u,d);
                steps++;
            }
        }
    }
}
void last_ribs(int*count_moves,struct history* history,int* sequence_edges, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    int k =0;
    int j =0;
    //char*edges[][5]={f,d, f,r, f,l, r,b, r,u, r,d, u,b, l,b, b,d, l,d, l,u, f,u};
    int save = 0;
   
  
    if(sequence_edges[k] != -1){//up
        j=sequence_edges[k];
        if(j==0){F(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);}
        else if(j==2){F_(count_moves,history,l,f,r,b,u,d);}
        else if(j==4){F(count_moves,history,l,f,r,b,u,d);} 
        else if(j==6){R_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);}
        else if(j==8){U_(count_moves,history,l,f,r,b,u,d);}
        else if(j==10){R(count_moves,history,l,f,r,b,u,d);R(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);}
        else if(j==12){U_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);}
        else if(j==14){L(count_moves,history,l,f,r,b,u,d);U(count_moves,history,l,f,r,b,u,d);}
        else if(j==16){B(count_moves,history,l,f,r,b,u,d);B(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);}
        else if(j==18){L_(count_moves,history,l,f,r,b,u,d);L_(count_moves,history,l,f,r,b,u,d);U(count_moves,history,l,f,r,b,u,d);}
        else if(j==20){U(count_moves,history,l,f,r,b,u,d);}
        else if(j==22){ //do nothing
        }
        k++;
    }
    
    save = j;
    cheak_ribs(sequence_edges,l,f,r,b,u,d);
    
    k=0;
    if(sequence_edges[k]==save){k++;}
    if(sequence_edges[k]!=-1){//down
        j=sequence_edges[k];
        if(j==0){//do nothing
        }
        else if(j==2){R_(count_moves,history,l,f,r,b,u,d); D_(count_moves,history,l,f,r,b,u,d);}
        else if(j==4){L(count_moves,history,l,f,r,b,u,d); D(count_moves,history,l,f,r,b,u,d);} 
        else if(j==6){R(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);}
        else if(j==8){R_(count_moves,history,l,f,r,b,u,d);R_(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);}
        else if(j==10){D_(count_moves,history,l,f,r,b,u,d);}
        else if(j==12){B_(count_moves,history,l,f,r,b,u,d);B_(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);}
        else if(j==14){L_(count_moves,history,l,f,r,b,u,d);D(count_moves,history,l,f,r,b,u,d);}
        else if(j==16){D(count_moves,history,l,f,r,b,u,d);D(count_moves,history,l,f,r,b,u,d);}
        else if(j==18){D(count_moves,history,l,f,r,b,u,d);}
        else if(j==20){L(count_moves,history,l,f,r,b,u,d);L(count_moves,history,l,f,r,b,u,d);D(count_moves,history,l,f,r,b,u,d);}
        else if(j==22){F(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);}
        k++;
    }
    //if...then...
    
    for(int k = 0;k<2;k++){
        if((u[4][1]==f[4][2] || u[4][1]==d[0][2]) && (u[4][1]==f[4][3] || u[4][1]==d[0][3]) && (f[0][1]==d[0][2] || f[0][1]==f[4][2])&& (f[0][1]==d[0][3] || f[0][1]==f[4][3])){
            //3
            // turn_cube(&count_moves,history'l',l,f,r,b,u,d);
            U_(count_moves,history,l,f,r,b,u,d);L_(count_moves,history,l,f,r,b,u,d);B(count_moves,history,l,f,r,b,u,d);
            turn_cube(count_moves,history,'u',l,f,r,b,u,d);
        }
        if((u[4][3]==f[4][2] || u[4][3]==d[0][2]) && (u[4][3]==f[4][1] || u[4][3]==d[0][1]) && (f[0][3]==d[0][2] || f[0][3]==f[4][2])&& (f[0][3]==d[0][1] || f[0][3]==f[4][1])){
            U_(count_moves,history,l,f,r,b,u,d);L_(count_moves,history,l,f,r,b,u,d);B(count_moves,history,l,f,r,b,u,d);
            turn_cube(count_moves,history,'u',l,f,r,b,u,d);
        }
        if(u[4][1]==d[0][1] && f[0][1]==f[4][1]&& f[0][1]==f[4][2]){
            //1
            R2(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);F_(count_moves,history,l,f,r,b,u,d);L(count_moves,history,l,f,r,b,u,d);U(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);R2_(count_moves,history,l,f,r,b,u,d);
        }
        if((u[4][3]==d[0][2] || u[4][3]==f[4][2])&& (u[4][3]==d[0][3] || u[4][3]==f[4][3]) && (f[0][3]==f[4][2] || f[0][3]==d[0][2])&& (f[0][3]==f[4][3] || f[0][3]==d[0][3])){
            //2
            L2_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);F_(count_moves,history,l,f,r,b,u,d);L(count_moves,history,l,f,r,b,u,d);U(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);L2(count_moves,history,l,f,r,b,u,d);
        }
        if(u[4][2]==f[4][1] && u[4][2]==f[4][3] && f[0][2]==f[4][1] && f[0][2]==f[4][3]){
            R2(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);F_(count_moves,history,l,f,r,b,u,d);L(count_moves,history,l,f,r,b,u,d);U(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);R2_(count_moves,history,l,f,r,b,u,d);
            L2_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);F_(count_moves,history,l,f,r,b,u,d);L(count_moves,history,l,f,r,b,u,d);U(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);L2(count_moves,history,l,f,r,b,u,d);
        }

        if(u[4][1]==f[0][2] && u[4][3]==f[0][2]&& f[0][1]==u[4][2] && f[0][3]==u[4][2] &&  f[4][1]==d[0][2] && f[4][3]==d[0][2]&& d[0][1]==f[4][2] && d[0][3]==f[4][2]){
            M(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);F_(count_moves,history,l,f,r,b,u,d);L(count_moves,history,l,f,r,b,u,d);U(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);M_(count_moves,history,l,f,r,b,u,d);
        }
        if(u[4][1]==u[4][3] && f[0][1]==f[0][3] && (f[4][2]==u[4][1] || d[0][2]==u[4][1])&&((f[4][2]==f[0][1] || d[0][2]==f[0][1]))){
            R2(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);F_(count_moves,history,l,f,r,b,u,d);L(count_moves,history,l,f,r,b,u,d);U(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);R2_(count_moves,history,l,f,r,b,u,d);
            L2_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);F_(count_moves,history,l,f,r,b,u,d);L(count_moves,history,l,f,r,b,u,d);U(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);L2(count_moves,history,l,f,r,b,u,d);
            turn_cube(count_moves,history,'u',l,f,r,b,u,d);
        }
        if(u[4][1]==f[0][2] && u[4][3]==f[0][2]&& f[0][1]==u[4][2] && f[0][3]==u[4][2]){
            //func hard
            R2_(count_moves,history,l,f,r,b,u,d);R2_(count_moves,history,l,f,r,b,u,d);B(count_moves,history,l,f,r,b,u,d);B(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);L2(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);
            R2_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);R2(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);R2(count_moves,history,l,f,r,b,u,d);
            F(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);L2_(count_moves,history,l,f,r,b,u,d);B(count_moves,history,l,f,r,b,u,d);B(count_moves,history,l,f,r,b,u,d);R2_(count_moves,history,l,f,r,b,u,d);R2_(count_moves,history,l,f,r,b,u,d);
        }
        
        F(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);
        if(u[0][1]==b[0][2] && u[0][3]==b[0][2]){turn_cube(count_moves,history,'d',l,f,r,b,u,d);}
    }
    
}
int cheak_ribs(int* sequence_edges, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    int count_rib = 0;
    int size = 4;

    int mas_f_u[]={0,1,0,3,0,2};
    int mas_u_f[]={4,1,4,3,4,2};

    int mas_f_r[]={1,4,3,4,2,4};
    int mas_r_f[]={1,0,3,0,2,0};

    int mas_f_l[]={1,0,3,0,2,0};
    int mas_l_f[]={1,4,3,4,2,4};

    int mas_f_d[]={4,1,4,3,4,2};
    int mas_d_f[]={0,1,0,3,0,2};

    int mas_r_b[]={1,4,3,4,2,4};
    int mas_b_r[]={1,0,3,0,2,0};

    int mas_r_u[]={0,1,0,3,0,2};
    int mas_u_r[]={1,4,3,4,2,4};

    int mas_r_d[]={4,1,4,3,4,2};
    int mas_d_r[]={1,4,3,4,2,4};

    int mas_u_b[]={0,1,0,3,0,2};
    int mas_b_u[]={0,3,0,1,0,2};

    int mas_l_b[]={1,0,3,0,2,0};
    int mas_b_l[]={1,4,3,4,2,4};

    int mas_b_d[]={4,1,4,3,4,2};
    int mas_d_b[]={4,3,4,1,4,2};

    int mas_l_d[]={4,1,4,3,4,2};
    int mas_d_l[]={1,0,3,0,2,0};

    int mas_l_u[]={0,1,0,3,0,2};
    int mas_u_l[]={1,0,3,0,2,0};

    int *mas1, *mas2;
   
    int* Bigmas[] = {mas_f_d,mas_d_f,mas_f_r,mas_r_f,mas_f_l,mas_l_f,mas_r_b,mas_b_r,mas_r_u,mas_u_r,
    mas_r_d,mas_d_r,mas_u_b,mas_b_u,mas_l_b,mas_b_l,mas_b_d,mas_d_b,mas_l_d,mas_d_l,
    mas_l_u,mas_u_l,mas_f_u,mas_u_f};

    char(*edge1)[5];
    char(*edge2)[5];
    void* edges[]={(void*)f,(void*)d,(void*)f,(void*)r,(void*)f,(void*)l,(void*)r,(void*)b,(void*)r,(void*)u,(void*)r,(void*)d,(void*)u,(void*)b,(void*)l,(void*)b,(void*)b,(void*)d,(void*)l,(void*)d,(void*)l,(void*)u,(void*)f,(void*)u};
    
    char search_1;
    char search_2;
    int cnt = 0;
    int j = 0;
    for(int m=0;m<12;m++){
        sequence_edges[m]=-1;
    }
    int k =0;
    for(;j<24;j+=2){
        mas1=Bigmas[j];
        mas2=Bigmas[j+1];
        edge1=(char(*)[5])(edges[j]);
        edge2=(char(*)[5])(edges[j+1]);
        search_1=edge1[mas1[4]][mas1[5]];
        search_2=edge2[mas2[4]][mas2[5]];
        cnt=0;
        for(int i=0;i<size;i+=2){
            if(edge1[mas1[i]][mas1[i+1]]!=search_1 || edge2[mas2[i]][mas2[i+1]]!=search_2){
                // if(edge1[mas1[i]][mas1[i+1]]!=search_2 || edge2[mas2[i]][mas2[i+1]]!=search_1 ){
                //     cnt++;
                //     break;
                // }
                cnt++;break;
            }
        }
        if(cnt>0){
            count_rib++;
            sequence_edges[k]=j;
            k++;
        }
    }
    if(count_rib>2){return 2;}
    if(count_rib == 0){return 0;}
    return 1;
}
void cntNotOneColor_rib(char f [SIZE][SIZE],char u[SIZE][SIZE],char search_f,char search_u,int* count){
    int size = 4;
    int mas_f[4]={0,1,0,3};
    int mas_u[4]={4,1,4,3};
    for(int i=0;i<size;i+=2){
        if(f[mas_f[i]][mas_f[i+1]]!=search_f || u[mas_u[i]][mas_u[i+1]]!=search_u){
            if(f[mas_f[i]][mas_f[i+1]]!=search_u || u[mas_u[i]][mas_u[i+1]]!=search_f ){
                (*count)++;
            }
        }
    }
}
//see qrt
//search_qrt
//if here then do...
//if not conect? then ...
//cheak right rib
//insert
//rotate if rib isnt full
//if 10_ribs full then

void change_ribs(int*count_moves,struct history* history,int num_in_rib, int var,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    //char*edges[][5]={f,d,f,r,f,l,r,b,r,u,r,d,u,b,l,b,b,d,l,d,l,u,f,u};
    int cnt = 0;
    int steps = 0;
    int j;
    
    j = search_rib_for_change(count_moves,history,var,l,f,r,b,u,d);
    if(var == 1){
        if(j==0){//do nothing
        }
        else if(j==2){R_(count_moves,history,l,f,r,b,u,d); D_(count_moves,history,l,f,r,b,u,d);}
        else if(j==4){L(count_moves,history,l,f,r,b,u,d); D(count_moves,history,l,f,r,b,u,d);} 
        else if(j==6){R(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);}
        else if(j==8){R_(count_moves,history,l,f,r,b,u,d);R_(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);}
        else if(j==10){D_(count_moves,history,l,f,r,b,u,d);}
        else if(j==12){B_(count_moves,history,l,f,r,b,u,d);B_(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);}
        else if(j==14){L_(count_moves,history,l,f,r,b,u,d);D(count_moves,history,l,f,r,b,u,d);}
        else if(j==16){D(count_moves,history,l,f,r,b,u,d);D(count_moves,history,l,f,r,b,u,d);}
        else if(j==18){D(count_moves,history,l,f,r,b,u,d);}
        else if(j==20){L(count_moves,history,l,f,r,b,u,d);L(count_moves,history,l,f,r,b,u,d);D(count_moves,history,l,f,r,b,u,d);}

    }
    if(var == 2){
        if(j==2){//do nothing
        }
        else if(j==4){ D(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);F_(count_moves,history,l,f,r,b,u,d);F_(count_moves,history,l,f,r,b,u,d);U(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);} 
        else if(j==6){R(count_moves,history,l,f,r,b,u,d);R(count_moves,history,l,f,r,b,u,d);}
        else if(j==8){R_(count_moves,history,l,f,r,b,u,d);}
        else if(j==10){R(count_moves,history,l,f,r,b,u,d);}
        else if(j==12){B_(count_moves,history,l,f,r,b,u,d);R(count_moves,history,l,f,r,b,u,d);R(count_moves,history,l,f,r,b,u,d);}
        else if(j==14){B_(count_moves,history,l,f,r,b,u,d);B_(count_moves,history,l,f,r,b,u,d);R(count_moves,history,l,f,r,b,u,d);R(count_moves,history,l,f,r,b,u,d);}
        else if(j==16){B(count_moves,history,l,f,r,b,u,d);R(count_moves,history,l,f,r,b,u,d);R(count_moves,history,l,f,r,b,u,d);}
        else if(j==18){D(count_moves,history,l,f,r,b,u,d);D(count_moves,history,l,f,r,b,u,d);R(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);}
        else if(j==20){U(count_moves,history,l,f,r,b,u,d);U(count_moves,history,l,f,r,b,u,d);R_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);}
        if(num_in_rib == 1){
            L2_(count_moves,history,l,f,r,b,u,d);
            U(count_moves,history,l,f,r,b,u,d);
            R(count_moves,history,l,f,r,b,u,d);
            U_(count_moves,history,l,f,r,b,u,d);
            L2(count_moves,history,l,f,r,b,u,d);
        }
        if(num_in_rib == 3){
            R2(count_moves,history,l,f,r,b,u,d);
            U(count_moves,history,l,f,r,b,u,d);
            R(count_moves,history,l,f,r,b,u,d);
            U_(count_moves,history,l,f,r,b,u,d);
            R2_(count_moves,history,l,f,r,b,u,d);
        }
    }
    
}
int search_rib_for_change(int*count_moves,struct history* history,int var, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    int size = 4;

    int mas_f_r[]={1,4,3,4,2,4};
    int mas_r_f[]={1,0,3,0,2,0};

    int mas_f_l[]={1,0,3,0,2,0};
    int mas_l_f[]={1,4,3,4,2,4};

    int mas_r_b[]={1,4,3,4,2,4};
    int mas_b_r[]={1,0,3,0,2,0};

    int mas_r_u[]={0,1,0,3,0,2};
    int mas_u_r[]={3,4,1,4,2,4};

    int mas_r_d[]={4,1,4,3,4,2};
    int mas_d_r[]={1,4,3,4,2,4};

    int mas_u_b[]={0,1,0,3,0,2};
    int mas_b_u[]={0,3,0,1,0,2};

    int mas_l_b[]={1,0,3,0,2,0};
    int mas_b_l[]={1,4,3,4,2,4};

    int mas_b_d[]={4,1,4,3,4,2};
    int mas_d_b[]={4,3,4,1,4,2};

    int mas_l_d[]={4,1,4,3,4,2};
    int mas_d_l[]={3,0,1,0,2,0};

    int mas_l_u[]={0,1,0,3,0,2};
    int mas_u_l[]={1,0,3,0,2,0};

    int mas_f_d[]={4,1,4,3,4,2};
    int mas_d_f[]={0,1,0,3,0,2};

    int *mas1, *mas2;

    int* Bigmas[] = {mas_f_d,mas_d_f,mas_f_r,mas_r_f,mas_f_l,mas_l_f,mas_r_b,mas_b_r,mas_r_u,mas_u_r,
    mas_r_d,mas_d_r,mas_u_b,mas_b_u,mas_l_b,mas_b_l,mas_b_d,mas_d_b,mas_l_d,mas_d_l,
    mas_l_u,mas_u_l};

    char(*edge1)[5];
    char(*edge2)[5];
    void* edges[]={(void*)f,(void*)d,(void*)f,(void*)r,(void*)f,(void*)l,(void*)r,(void*)b,(void*)r,(void*)u,(void*)r,(void*)d,(void*)u,(void*)b,(void*)l,(void*)b,(void*)b,(void*)d,(void*)l,(void*)d,(void*)l,(void*)u};
    
    char search_1;
    char search_2;
    int cnt = 0;
    int j = 0;

    if(var==1){
        char search_f=f[0][2];
        char search_u=u[4][2];
        for(;j<22;j+=2){
            mas1=Bigmas[j];
            mas2=Bigmas[j+1];
            edge1=(char(*)[5])(edges[j]);
            edge2=(char(*)[5])(edges[j+1]);
            
            cnt=0;
            for(int i=0;i<size;i+=2){
                if((edge1[mas1[i]][mas1[i+1]]==search_u && edge2[mas2[i]][mas2[i+1]]==search_f) || (edge1[mas1[i]][mas1[i+1]]==search_f && edge2[mas2[i]][mas2[i+1]]==search_u)){
                    cnt++;
                    break;
                }
            }
            if(cnt>0){
                break;
            }
        }
        
    }

    if(var==2){
        for(j=2;j<22;j+=2){
            mas1=Bigmas[j];
            mas2=Bigmas[j+1];
            edge1=(char(*)[5])(edges[j]);
            edge2=(char(*)[5])(edges[j+1]);
            search_1=edge1[mas1[4]][mas1[5]];
            search_2=edge2[mas2[4]][mas2[5]];
            cnt=0;
            for(int i=0;i<size;i+=2){
                if(edge1[mas1[i]][mas1[i+1]]!=search_1 || edge2[mas2[i]][mas2[i+1]]!=search_2){
                    // if(edge1[mas1[i]][mas1[i+1]]!=search_2 || edge2[mas2[i]][mas2[i+1]]!=search_1){
                    //     cnt++;
                    //     break;
                    // }
                    cnt++;
                    break;
                }
            }
            if(cnt>0){
                break;
            }
        }
        
    }
    return j;
    
}

void solve_white_rib(int*count_moves,struct history* history, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    int steps=0;
    while(u[2][2]!='W'&&steps<5){
        if(steps<3){
            turn_cube(count_moves,history,'d',l,f,r,b,u,d);
            steps++;
        }
        else if(steps==3){
            turn_cube(count_moves,history,'r',l,f,r,b,u,d);
            turn_cube(count_moves,history,'u',l,f,r,b,u,d);
            steps++;
        }
        else if(steps==4){
            turn_cube(count_moves,history,'u',l,f,r,b,u,d);
            turn_cube(count_moves,history,'u',l,f,r,b,u,d);
            steps++;
        }
    }
    
    if((u[0][2]!=u[2][2] || u[2][0]!=u[2][2] || u[2][4]!=u[2][2] || u[4][2]!=u[2][2]) || (l[0][2]!=l[2][2] || f[0][2]!=f[2][2] || r[0][2]!=r[2][2] || b[4][2]!=b[2][2])){
        for(int i = 0;i<4;i++){
            
            char search_f=f[2][2];
            char search_u=u[2][2];
            int j = 0;
            // printRubiksCube(l,f,r,b,u,d);
            int fl_cnt = 0;
            while(f[0][2]==search_f && u[4][2]==search_u && fl_cnt<4){
                turn_cube(count_moves,history,'l',l,f,r,b,u,d);search_f=f[2][2];search_u=u[2][2];
                fl_cnt++;
            }
            j = where_rib(search_f,search_u,l,f,r,b,u,d);
            
            if(j==0){F(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);}
            else if(j==2){F_(count_moves,history,l,f,r,b,u,d);}
            else if(j==4){F(count_moves,history,l,f,r,b,u,d);} 
            else if(j==6){R(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);R_(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);}
            else if(j==8){R_(count_moves,history,l,f,r,b,u,d);F_(count_moves,history,l,f,r,b,u,d);}
            else if(j==10){D_(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);}
            else if(j==12){B(count_moves,history,l,f,r,b,u,d);B(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);}
            else if(j==14){L_(count_moves,history,l,f,r,b,u,d);L_(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);L(count_moves,history,l,f,r,b,u,d);L(count_moves,history,l,f,r,b,u,d);}
            else if(j==16){D_(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);}
            else if(j==18){D(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);}
            else if(j==20){L(count_moves,history,l,f,r,b,u,d);F(count_moves,history,l,f,r,b,u,d);L_(count_moves,history,l,f,r,b,u,d);}
            else if(j==22){ //do nothing
            }
            if(f[0][2]!=search_f){
                F(count_moves,history,l,f,r,b,u,d);R_(count_moves,history,l,f,r,b,u,d);D_(count_moves,history,l,f,r,b,u,d);R(count_moves,history,l,f,r,b,u,d);F_(count_moves,history,l,f,r,b,u,d);F_(count_moves,history,l,f,r,b,u,d);
            }
            if(u[0][2]==u[2][2] && u[2][0]==u[2][2] && u[2][4]==u[2][2] && u[4][2]==u[2][2] && l[0][2]==l[2][2] && f[0][2]==f[2][2] && r[0][2]==r[2][2] && b[4][2]!=b[2][2]){break;}
            
            turn_cube(count_moves,history,'l',l,f,r,b,u,d);
            
        }
    }
    
    
}
int where_rib(char search_f, char search_u, char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    int size = 2;
    int mas_f_u[]={0,2};
    int mas_u_f[]={4,2};
    int mas_f_r[]={2,4};
    int mas_r_f[]={2,0};
    int mas_f_l[]={2,0};
    int mas_l_f[]={2,4};
    int mas_f_d[]={4,2};
    int mas_d_f[]={0,2};
    int mas_r_b[]={2,4};
    int mas_b_r[]={2,0};
    int mas_r_u[]={0,2};
    int mas_u_r[]={2,4};
    int mas_r_d[]={4,2};
    int mas_d_r[]={2,4};
    int mas_u_b[]={0,2};
    int mas_b_u[]={0,2};
    int mas_l_b[]={2,0};
    int mas_b_l[]={2,4};
    int mas_b_d[]={4,2};
    int mas_d_b[]={4,2};
    int mas_l_d[]={4,2};
    int mas_d_l[]={2,0};
    int mas_l_u[]={0,2};
    int mas_u_l[]={2,0};

    int *mas1, *mas2;
   
    int* Bigmas[] = {mas_f_d,mas_d_f,mas_f_r,mas_r_f,mas_f_l,mas_l_f,
    mas_r_b,mas_b_r,mas_r_u,mas_u_r,
    mas_r_d,mas_d_r,mas_u_b,mas_b_u,
    mas_l_b,mas_b_l,mas_b_d,mas_d_b,mas_l_d,mas_d_l,
    mas_l_u,mas_u_l,mas_f_u,mas_u_f};

    char(*edge1)[5];
    char(*edge2)[5];
    void* edges[]={(void*)f,(void*)d,(void*)f,(void*)r,(void*)f,(void*)l,(void*)r,(void*)b,(void*)r,(void*)u,(void*)r,(void*)d,(void*)u,(void*)b,(void*)l,(void*)b,(void*)b,(void*)d,(void*)l,(void*)d,(void*)l,(void*)u,(void*)f,(void*)u};
    
    int j = 0;
    int cnt=0;
    for(;j<24;j+=2){
        mas1=Bigmas[j];
        mas2=Bigmas[j+1];
        edge1=(char(*)[5])(edges[j]);
        edge2=(char(*)[5])(edges[j+1]);
        
        for(int i=0;i<size;i+=2){
            if(edge1[mas1[i]][mas1[i+1]]==search_f && edge2[mas2[i]][mas2[i+1]]==search_u || edge1[mas1[i]][mas1[i+1]]==search_u && edge2[mas2[i]][mas2[i+1]]==search_f){
                cnt= 1;
                break;
            }
        }
        if(cnt==1){break;}
    }
    return j;
}
void rotate_corn(int* count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    R(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    R_(count_moves,history,l,f,r,b,u,d);
    U(count_moves,history,l,f,r,b,u,d);
}
void solve_corners(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    
    turn_cube(count_moves,history,'u',l,f,r,b,u,d);
    turn_cube(count_moves,history,'u',l,f,r,b,u,d);
    char search_f;char search_d;char search_r;

    for(int i = 0;i<4;i++){
        search_f = f[2][2];
        search_r=r[2][2];
        search_d=d[2][2];
        if((f[4][4]==search_f || f[4][4]==search_r || f[4][4]==search_d)&&(d[0][4]==search_f || d[0][4]==search_d || d[0][4]==search_r)&&(r[4][0]==search_f || r[4][0]==search_d || r[4][0]==search_r)){
            while(d[0][4]!=search_d || f[4][4]!=search_f ||  r[4][0]!=search_r){rotate_corn(count_moves,history,l,f,r,b,u,d);}
            
        }
        else{
            if(f[4][4]==search_d || d[0][4]==search_d || r[4][0]==search_d){
                while(u[4][4]==search_d || f[0][4]==search_d || r[0][0]==search_d){
                    U_(count_moves,history,l,f,r,b,u,d);
                    //printf("yes place\n");
                }
                rotate_corn(count_moves,history,l,f,r,b,u,d);
                
            }
        }
        
        turn_cube(count_moves,history,'l',l,f,r,b,u,d);
    }
    
    for(int k=0;k<4;k++){
        search_f = f[2][2];
        search_r=r[2][2];
        search_d=d[2][2];
        if(f[4][4]!=search_f || d[0][4]!=search_d || r[4][0]!=search_r){
            //�� ������
            while(!((f[0][4]==search_f || f[0][4]==search_r || f[0][4]==search_d)&&(u[4][4]==search_f || u[4][4]==search_d || u[4][4]==search_r)&&(r[0][0]==search_f || r[0][0]==search_d || r[0][0]==search_r))){
                U_(count_moves,history,l,f,r,b,u,d);
                
            }
            while(d[0][4]!=search_d){rotate_corn(count_moves,history,l,f,r,b,u,d);}
        }
        turn_cube(count_moves,history,'l',l,f,r,b,u,d);
    }
    
}
//////////
void swap_rib_right(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    U_(count_moves,history,l,f,r,b,u,d);
    R(count_moves,history,l,f,r,b,u,d);
    U(count_moves,history,l,f,r,b,u,d);
    R_(count_moves,history,l,f,r,b,u,d);
    U(count_moves,history,l,f,r,b,u,d);
    F_(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    F(count_moves,history,l,f,r,b,u,d);
}
void swap_rib_left(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    U(count_moves,history,l,f,r,b,u,d);
    L_(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    L(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    F(count_moves,history,l,f,r,b,u,d);
    U(count_moves,history,l,f,r,b,u,d);
    F_(count_moves,history,l,f,r,b,u,d);
}
void solve_right_place_for_rib(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    for(int i = 0;i<4;i++){
        if(f[2][4]!=u[2][2] && r[2][0]!=u[2][2] && (f[2][4]!=f[2][2] || r[2][0]!=r[2][2])){
            while(f[0][2]!=u[2][2] && u[4][2]!=u[2][2]){U_(count_moves,history,l,f,r,b,u,d);}
            swap_rib_right(count_moves,history,l,f,r,b,u,d);
            
        }
        turn_cube(count_moves,history,'l',l,f,r,b,u,d);
        
    }
    
    char search_f;
    char search_r;
    for(int i = 0;i<4;i++){
        search_f = f[2][2];
        search_r = r[2][2];
        if(f[2][4]!=search_f || r[2][0]!=search_r){
            // while(!((f[0][2]==search_f && u[4][2]==search_r) || (f[0][2]==search_r && u[4][2]==search_f))){
            while((f[0][2]!=search_f || u[4][2]!=search_r) && (f[0][2]!=search_r || u[4][2]!=search_f)){
                
                U_(count_moves,history,l,f,r,b,u,d);
            }
            if(f[0][2]==search_f && u[4][2]==search_r){
                swap_rib_right(count_moves,history,l,f,r,b,u,d);
                turn_cube(count_moves,history,'l',l,f,r,b,u,d);
            }
            else if(f[0][2]==search_r && u[4][2]==search_f){
                turn_cube(count_moves,history,'l',l,f,r,b,u,d);
                U(count_moves,history,l,f,r,b,u,d);
                swap_rib_left(count_moves,history,l,f,r,b,u,d);
            }
            
        }
        else{turn_cube(count_moves,history,'l',l,f,r,b,u,d);}
        
    }
}
void yellow_ribs(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    // int mas_u[]={0,2, 2,0, 2,4, 4,2};
    int count=0;

    while(u[2][0]!=u[2][2]){U(count_moves,history,l,f,r,b,u,d);count++; if(count == 4){break;}}

    if(u[0][2]!=u[2][2] || u[2][0]!=u[2][2] || u[2][4]!=u[2][2] || u[4][2]!=u[2][2]){
        
        if(u[0][2]==u[2][2] && u[2][0]==u[2][2] && u[2][4]!=u[2][2] && u[4][2]!=u[2][2]){
            F(count_moves,history,l,f,r,b,u,d);
            rotate_corn(count_moves,history,l,f,r,b,u,d);
            rotate_corn(count_moves,history,l,f,r,b,u,d);
            F_(count_moves,history,l,f,r,b,u,d);
        }
        else if(u[4][2]==u[2][2] && u[2][0]==u[2][2] && u[0][2]!=u[2][2] && u[2][4]!=u[2][2]){
            U_(count_moves,history,l,f,r,b,u,d);
            F(count_moves,history,l,f,r,b,u,d);
            rotate_corn(count_moves,history,l,f,r,b,u,d);
            rotate_corn(count_moves,history,l,f,r,b,u,d);
            F_(count_moves,history,l,f,r,b,u,d);
        }
        else if(u[2][0]==u[2][2] && u[2][4]==u[2][2] && u[4][2]!=u[2][2] && u[0][2]!=u[2][2]){
            F(count_moves,history,l,f,r,b,u,d);
            rotate_corn(count_moves,history,l,f,r,b,u,d);
            F_(count_moves,history,l,f,r,b,u,d);
        }
        else if(u[2][0]!=u[2][2] && u[2][4]!=u[2][2] && u[4][2]!=u[2][2] && u[0][2]!=u[2][2]){
            F(count_moves,history,l,f,r,b,u,d);
            rotate_corn(count_moves,history,l,f,r,b,u,d);
            F_(count_moves,history,l,f,r,b,u,d);
            U_(count_moves,history,l,f,r,b,u,d);
            U_(count_moves,history,l,f,r,b,u,d);
            F(count_moves,history,l,f,r,b,u,d);
            rotate_corn(count_moves,history,l,f,r,b,u,d);
            rotate_corn(count_moves,history,l,f,r,b,u,d);
            F_(count_moves,history,l,f,r,b,u,d);
        }
    }
    
}
void four_edges_color(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    int count=0;
    int max_cnt=0;
    int max_i = 0;
    
    for(int i = 0;i<4;i++){
        count=0;
        if(l[0][2]==l[2][2]){
            count++;
        }
        if(f[0][2]==f[2][2]){
            count++;
        }
        if(r[0][2]==r[2][2]){
            count++;
        }
        if(b[0][2]==b[2][2]){
            count++;
        }

        if(count>max_cnt){
            max_cnt = count;
            max_i = i;
        }
        if(i<3){U_(count_moves,history,l,f,r,b,u,d);}
    }
    
    if(max_i == 0){U_(count_moves,history,l,f,r,b,u,d);}
    else if(max_i == 1){U_(count_moves,history,l,f,r,b,u,d);U_(count_moves,history,l,f,r,b,u,d);}
    else if(max_i == 2){U(count_moves,history,l,f,r,b,u,d);}
    int c = 0;
    
    if(max_cnt == 1){
        while(r[0][2]!=r[2][2] && c<4){turn_cube(count_moves, history,'l',l,f,r,b,u,d);c++;}
        change_last_four_ribs(count_moves,history,l,f,r,b,u,d);
        c=0;
    }
    else if (max_cnt == 2){
        while(r[0][2]!=r[2][2] && c<4){turn_cube(count_moves,history,'l',l,f,r,b,u,d);c++;}
        c = 0;

        if(l[0][2]==l[2][2] && r[0][2]==r[2][2]){
            change_last_four_ribs(count_moves,history,l,f,r,b,u,d);
            U_(count_moves,history,l,f,r,b,u,d);
            turn_cube(count_moves,history,'l',l,f,r,b,u,d);
            change_last_four_ribs(count_moves,history,l,f,r,b,u,d);
        }
        else if(l[0][2]!=l[2][2] && r[0][2]==r[2][2]){
            while(r[0][2]!=r[2][2] || b[0][2]!=b[2][2] && c<4){turn_cube(count_moves,history,'l',l,f,r,b,u,d);c++;}
            change_last_four_ribs(count_moves,history,l,f,r,b,u,d);
        }
        
    }

}
void change_last_four_ribs(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    R(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    R_(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    R(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    R_(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
}

void last_corners_part1(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    int up_left = 0;
    int up_right = 0;
    int down_left = 0;
    int down_right = 0;
    int cnt = 0;
    while(!up_left || !up_right || !down_left || !down_right){
        up_left = 0;
        up_right = 0;
        down_left = 0;
        down_right = 0;
        cnt = 0;

        if((u[0][0]==u[2][2] || u[0][0]==l[2][2] || u[0][0]==b[2][2]) && (l[0][0]==u[2][2] || l[0][0]==l[2][2] || l[0][0]==b[2][2]) && (b[4][4]==u[2][2] || b[4][4]==l[2][2] || b[4][4]==b[2][2])){
            up_left = 1;
        }
        if((u[0][4]==u[2][2] || u[0][4]==r[2][2] || u[0][4]==b[2][2]) && (r[0][4]==u[2][2] || r[0][4]==r[2][2] || r[0][4]==b[2][2]) && (b[0][0]==u[2][2] || b[0][0]==r[2][2] || b[0][0]==b[2][2])){
            up_right = 1;
        }
        if((u[4][0]==u[2][2] || u[4][0]==l[2][2] || u[4][0]==f[2][2]) && (l[0][4]==u[2][2] || l[0][4]==l[2][2] || l[0][4]==f[2][2]) && (f[0][0]==u[2][2] || f[0][0]==l[2][2] || f[0][0]==f[2][2])){
            down_left = 1;
        }
        if((u[4][4]==u[2][2] || u[4][4]==r[2][2] || u[4][4]==f[2][2]) && (r[0][0]==u[2][2] || r[0][0]==r[2][2] || r[0][0]==f[2][2]) && (f[0][4]==u[2][2] || f[0][4]==r[2][2] || f[0][4]==f[2][2])){
            down_right = 1;
        }
        if(up_left && up_right && down_left && down_right){break;}
        
        while((u[4][4]==u[2][2] || u[4][4]==r[2][2] || u[4][4]==f[2][2]) && (r[0][0]==u[2][2] || r[0][0]==r[2][2] || r[0][0]==f[2][2]) && (f[0][4]==u[2][2] || f[0][4]==r[2][2] || f[0][4]==f[2][2]) && cnt<4){
            turn_cube(count_moves, history,'l',l,f,r,b,u,d);
            cnt++;
        }
        cnt = 0;
        while(!((u[4][4]==u[2][2] || u[4][4]==r[2][2] || u[4][4]==f[2][2]) && (r[0][0]==u[2][2] || r[0][0]==r[2][2] || r[0][0]==f[2][2]) && (f[0][4]==u[2][2] || f[0][4]==r[2][2] || f[0][4]==f[2][2])) && cnt<4){
            rotate_last_corn_for_part1(count_moves,history,l,f,r,b,u,d);
            cnt++;
            turn_cube(count_moves,history,'l',l,f,r,b,u,d);
        }
    }
}
void rotate_last_corn_for_part1(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    R(count_moves,history,l,f,r,b,u,d);
    U(count_moves,history,l,f,r,b,u,d);
    L_(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
    R_(count_moves,history,l,f,r,b,u,d);
    U(count_moves,history,l,f,r,b,u,d);
    L(count_moves,history,l,f,r,b,u,d);
    U_(count_moves,history,l,f,r,b,u,d);
}
void last_corners_part2(int*count_moves,struct history* history,char l[SIZE][SIZE], char f[SIZE][SIZE],char r[SIZE][SIZE], char b[SIZE][SIZE],char u[SIZE][SIZE],char d[SIZE][SIZE]){
    int count = 4;
    if(u[0][0]==u[2][2]&& l[0][0]==l[2][2] &&  b[4][4]==b[2][2]){
        count--;
    }
    if(u[0][4]==u[2][2]  && r[0][4]==r[2][2]  &&   b[0][0]==b[2][2]){
        count--;
    }
    if(u[4][0]==u[2][2] && l[0][4]==l[2][2] &&  f[0][0]==f[2][2]){
        count--;
    }
    if(u[4][4]==u[2][2] && r[0][0]==r[2][2] && f[0][4]==f[2][2]){
        count--;
    }
    turn_cube(count_moves,history,'d',l,f,r,b,u,d);
    turn_cube(count_moves,history,'d',l,f,r,b,u,d);
    int cnt = 0;
    
    while(f[4][4]==f[2][2] &&  r[4][0]==r[2][2] &&  d[0][4]==d[2][2] && cnt<4){
        turn_cube(count_moves,history,'l',l,f,r,b,u,d);
        cnt++;
    }
    for(int j = 0;j<count;j++){
        cnt = 0;
        while(d[0][4]!=d[2][2]){rotate_corn(count_moves,history,l,f,r,b,u,d);}
        while(f[4][4]==f[4][2] &&  r[4][0]==r[4][2] &&  d[0][4]==d[0][2] && cnt<4){
            D_(count_moves,history,l,f,r,b,u,d);
            cnt++;
        }
    }
    for(int k = 0;k<4;k++){
        if(f[4][4]==f[2][2] &&  r[4][0]==r[2][2] &&  d[0][4]==d[2][2]){break;}
        D_(count_moves,history,l,f,r,b,u,d);
    }

}

//malloc ���������� void, 
// ������ ������ * ������