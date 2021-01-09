#{{ HEADER }}

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexture;
in vec2 vTextureOffset;
flat in int vFace;
flat in int vAlpha;
flat in int vAnimated;

uniform sampler2D uTexture;
uniform vec3 uLightPosition;
uniform vec3 uLightColor;
uniform float uLightDirIntensity;
uniform float uLightAmbIntensity;
uniform int uVerticalOffset;

out vec4 fFragColor;


/**
 * Compute the color of the fragment according to uTexture.
 *
 * @return The computed color.
 */
vec4 computeTextureColor() {
    vec2 textureCoordinates = vec2((vTexture.x + vTextureOffset.x) / 8.f, 0);

    if (vAnimated != 0) {
        textureCoordinates.y = (vTexture.y + float(uVerticalOffset)) / 64.f;
    } else {
        textureCoordinates.y = (vTexture.y + (vTextureOffset.y * 6.f) + float(vFace)) / 32.f;
    }

    return texture(uTexture, textureCoordinates);
}

/**
 * Compute the diffuse lighting of the fragment.
 *
 * @return The computed diffuse lighting.
 */
vec3 computeDiffuseLighting() {
    vec3 lightDirection = normalize(uLightPosition - vPosition);
    vec3 diffuse = vec3(max(dot(vNormal, lightDirection), 0.0f));
    return diffuse * uLightDirIntensity;
}


void main() {
    vec4 textureColor = computeTextureColor();
    if (textureColor.w == 0.f) {
        discard;
    }

    vec3 diffuse = computeDiffuseLighting();
    vec3 ambient = vec3(uLightAmbIntensity);
    vec3 light =  (diffuse + ambient) * uLightColor;

    fFragColor = vec4(
        min(1.f, light.x),
        min(1.f, light.y),
        min(1.f, light.z),
        1
    ) * textureColor;
}
