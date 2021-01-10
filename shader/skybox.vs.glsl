#{{ HEADER }}

layout (location = 0) in vec3 aPosition;

uniform mat4 uMVP;

out vec3 vTexture;


void main() {
    vTexture = aPosition;
    gl_Position = uMVP * vec4(aPosition, 1.0);
}
