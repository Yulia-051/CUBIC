#ifndef EBO_CLASS_H
#define EBO_CLASS_H
#include "../../external/glad/glad.h"

typedef struct EBO {
    GLuint ID;
} EBO;

void EBO_Constructor(EBO* ebo, GLuint* indices, GLsizeiptr size);

void EBO_Bind(EBO* ebo);

void EBO_Unbind();

void EBO_Delete(EBO* ebo);

#endif



