#include "VBO.h"
#include <stddef.h>


void VBO_Constructor(VBO* vbo, float* vertices, GLsizeiptr size) {
	glGenBuffers(1, &(vbo->ID));
	glBindBuffer(GL_ARRAY_BUFFER, vbo->ID);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
}

void VBO_Bind(VBO* vbo) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo->ID);
}

void VBO_Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO_Delete(VBO* vbo) {
	glDeleteBuffers(1, &(vbo->ID));
}
