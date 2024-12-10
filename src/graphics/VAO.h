#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "../../external/glad/glad.h"
#include "VBO.h"

typedef struct VAO {
    GLuint ID;
} VAO;

void VAO_Constructor(VAO* vao);

void VAO_LinkAttrib(VAO* vao, VBO* VBO, GLuint layout,GLuint numComponents,GLenum type, GLsizeiptr stride,void* offset);

void VAO_Bind(VAO* vao);

void VAO_Unbind();

void VAO_Delete(VAO* vao);

#endif