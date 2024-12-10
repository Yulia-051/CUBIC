#include "shaderClass.h"


char* get_file_contents(const char* filename)
{
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    char* contents = (char*)malloc(length + 1);
    if (contents == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
    fread(contents, 1, length, fp);
    contents[length] = '\0';

    fclose(fp);
    return contents;
}

void Shader_init(Shader* shader, const char* vertexFile, const char* fragmentFile)
{
    const char* vertexCode = (const char*)get_file_contents(vertexFile);
    const char* fragmentCode = (const char*)get_file_contents(fragmentFile);
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
    glCompileShader(fragmentShader);

    shader->ID = glCreateProgram();
    glAttachShader(shader->ID, vertexShader);
    glAttachShader(shader->ID, fragmentShader);
    glLinkProgram(shader->ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void Shader_Active(Shader* shader)
{
    glUseProgram(shader->ID);
}

void Shader_Delete(Shader* shader)
{
    glDeleteProgram(shader->ID);
}
