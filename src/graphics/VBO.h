#ifndef VBO_CLASS_H
#define VBO_CLASS_H
#include "../../external/glad/glad.h"

typedef struct VBO {
    GLuint ID;
} VBO;

void VBO_Constructor(VBO* vbo, float* vertices, GLsizeiptr size);

void VBO_Bind(VBO* vbo);

void VBO_Unbind();

void VBO_Delete(VBO* vbo);

#endif
