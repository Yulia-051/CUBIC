sudo apt-get --assume-yes install ./external/pack/gcc.deb ./external/pack/glfw.deb ./external/pack/glfw-dev.deb;
gcc cube.c ./external/glad/glad.c ./src/graphics/VBO.c ./src/graphics/VAO.c ./src/graphics/EBO.c ./src/graphics/shaderClass.c -o ./cubik -lglfw -lm;
echo Проект собран

gcc cube.c ./external/glad/glad.c ./src/graphics/VBO.c ./src/graphics/VAO.c ./src/graphics/EBO.c ./src/graphics/shaderClass.c -o arr -lGL -lglfw -lm; ./arr