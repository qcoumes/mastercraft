#{{ HEADER }}

in vec3 vTexture;

uniform samplerCube uCubemap;
uniform vec3 uSkyColor;

out vec4 fFragColor;


void main() {
    fFragColor = vec4(vec3(1.f) - (texture(uCubemap, vTexture).xyz * (vec3(1.f) - uSkyColor)), 1);
}
