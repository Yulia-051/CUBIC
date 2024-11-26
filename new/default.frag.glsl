#version 330 core
out vec4 FragColor;


in vec2 texture_position;
uniform sampler2D texture_0;

in vec3 render_color;
uniform int render_variant;


void main(){
   if(render_variant == 0){
      FragColor = vec4(render_color, 1.0);
   }
   
   else if(render_variant == 1){
      //FragColor = vec4(1.0,0.5,0.5,1.0);
      FragColor = texture(texture_0, texture_position);
   }
}