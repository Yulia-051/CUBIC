#include "VAO.h"


void VAO_Constructor(VAO* vao) {
	glGenVertexArrays(1, &(vao->ID));
}

void VAO_LinkAttrib(VAO* vao, VBO* VBO, GLuint layout,GLuint numComponents,GLenum type, GLsizeiptr stride,void* offset) {
	//VBO_Bind(VBO);
	glVertexAttribPointer(layout, numComponents,type, GL_FALSE, stride,offset);
	glEnableVertexAttribArray(layout);
	//VBO_Unbind(VBO);
}

void VAO_Bind(VAO* vao) {
	glBindVertexArray(vao->ID);
}

void VAO_Unbind() {
	glBindVertexArray(0);
}

void VAO_Delete(VAO* vao) {
	glDeleteVertexArrays(1, &(vao->ID));
}
