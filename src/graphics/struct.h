
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

typedef struct {
    VAO vao;
    VBO vbo;
    EBO ebo;
    GLuint Texture;
    float coord[4];
    int active_bot;
}object;

