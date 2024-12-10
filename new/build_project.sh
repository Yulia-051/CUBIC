sudo apt-get --assume-yes install ./pack/gcc.deb ./pack/glfw.deb ./pack/glfw-dev.deb;
gcc cube.c glad/glad.c VBO.c VAO.c EBO.c shaderClass.c -o ./cubik -lglfw -lm;
echo Проект собран
