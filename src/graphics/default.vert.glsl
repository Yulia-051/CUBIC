#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 texture_position_input;

out vec3 render_color;
uniform float scale;
out vec2 texture_position;
void main()
{
    gl_Position = vec4(aPos.x - aPos.x*scale, aPos.y - aPos.y*scale,aPos.z - aPos.z*scale, 1.0);
    render_color = aColor;
    texture_position = texture_position_input;
}


/*
#version 330 core
layout (location = 0) in vec2 position_input;
layout (location = 1) in vec2 texture_position_input;



out vec2 texture_position;



void main(){
   gl_Position = vec4(position_input.x, position_input.y, 1.0, 1.0);
   texture_position = texture_position_input;
}*/