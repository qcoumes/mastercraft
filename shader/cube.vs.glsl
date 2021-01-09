#{{ HEADER }}

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

uniform mat4 uMV;
uniform mat4 uMVP;
uniform mat4 uNormal;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexture;



void main(){
    vec4 vertexPosition = vec4(aPosition, 1.f);

    vPosition = vec3(uMV * vertexPosition);
    vNormal = vec3(uNormal * vec4(aNormal, 0.f));
    vTexture = aTexture;

    gl_Position = uMVP * vertexPosition;
}

