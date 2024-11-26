#include <stdio.h>
#include <string.h>
#include <math.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define N 25
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y,aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.8f,0.3f,0.02f,1.0f);\n"
"}\n\0";


int ifWindowNull(GLFWwindow* window);
GLFWwindow* openWindow(GLFWwindow* window);

int main(){
    int white[N]={0};
    int red[N]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    int blue[N]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
    int orange[N]={3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
    int green[N]={4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};
    int yellow[N]={5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
    
    glfwInit();
    
    GLfloat vertices[] ={
        -0.5f,-0.5f*1.73/3,0.0f, 
        0.5f,-0.5f*1.73/3,0.0f, 
        0.0f,0.5f*1.73*2/3,0.0f,
        -0.5f/2,0.5f*1.73/6,0.0f,
        0.5f/2,0.5f*1.73/6,0.0f,
        0.0f,-0.5f*1.73/3,0.0f 
    };
    GLuint indices[]={
        0,3,5,
        3,2,4,
        5,4,1
    };

    GLFWwindow* window = NULL;
    window = openWindow(window);

    if(ifWindowNull(window)==1){return -1;}

    glfwMakeContextCurrent(window); //object
    gladLoadGL();

    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader); //Delete the now useless vertex and fragment shaders objects
    glDeleteShader(fragmentShader);

    printf("%u\n",shaderProgram);

    GLuint VAO, VBO,EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    while(!glfwWindowShouldClose(window)){
        
        glClearColor(0.07f,0.13f,0.17f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteProgram(shaderProgram);
    

    //printf("yel = %d\n",green[24]);
    glfwDestroyWindow(window);
    glfwTerminate();
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

//clear; gcc cube.c glad/glad.c VBO.c VAO.c EBO.c shaderClass.c -o arr -lGL -lglfw; ./arr