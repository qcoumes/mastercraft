#{{ HEADER }}

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in int aData;

uniform mat4 uMV;
uniform mat4 uMVP;
uniform mat4 uNormal;
uniform vec3 uChunkPosition;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexture;
out vec2 vTextureOffset;
flat out int vFace;
flat out int vAlpha;
flat out int vAnimated;


// Use to extract the bits 0b00000000.0000xxxx of aData, representing the X offset of the texture of the cube (&).
const int TEXTURE_X = 15;

// Use to extract the bits 0b00000000.xxxx0000 of aData, representing the Y offset of the texture of the cube (& >> 4).
const int TEXTURE_Y = 240;

// Use to extract the bits 0b00000xxx.00000000 of aData, representing the face of the cube (& >> 8).
const int FACE = 1792;

// Use to extract the bits 0b0000x000.00000000 of aData, telling if the cube has an alpha channel (&).
const int ALPHA = 1 << 11;

// Use to extract the bits 0b000x0000.00000000 of aData, telling if the cube has an animated texture (&).
const int ANIMATED = 1 << 12;

// Use to extract the bits 0b00Xx0000.00000000 of aData, telling the texture use an overlay according to the top of the cube (&).
const int TOP_OVERLAY = 1 << 13;


void main(){
    vec4 vertexPosition = vec4(aPosition + uChunkPosition, 1);

    vPosition = vec3(uMV * vertexPosition);
    vNormal = vec3(uNormal * vec4(aNormal, 0));
    vTexture = aTexture;
    vTextureOffset = vec2(aData & TEXTURE_X, (aData & TEXTURE_Y) >> 4 );
    vFace = (aData & FACE) >> 8;
    vAlpha = aData & ALPHA;
    vAnimated = aData & ANIMATED;

    gl_Position = uMVP * vertexPosition;
}

