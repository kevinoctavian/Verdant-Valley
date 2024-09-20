#version 450 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Texture1;
uniform vec4 Colors;

void main() {
    FragColor = texture(Texture1, TexCoord);
}
