#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H
#define TEXTURE_SLOT0_UNIFORM "texture_0"
#include "glad/glad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char* get_file_contents(const char* filename);

typedef struct Shader{
    GLuint ID;
    GLuint texture_slot0_uniform;
}Shader;

void Shader_init(Shader* shader, const char* vertexFile, const char* fragmentFile);

void Shader_Active(Shader* shader);

void Shader_Delete(Shader* shader);

#endif