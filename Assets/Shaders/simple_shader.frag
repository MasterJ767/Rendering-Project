#version 450
#extension GL_KHR_vulkan_glsl: enable

layout(location = 0) in vec3 fragPosWorld;
layout(location = 1) in vec3 fragColour;
layout(location = 2) in vec3 fragNormalWorld;
layout(location = 3) in vec2 fragUV;

layout(location = 0) out vec4 outColour;

struct PointLight {
    vec4 position;
    vec4 colour;
};

layout(set = 0, binding = 0) uniform GlobalUbo {
    mat4 projectionMatrix;
    mat4 viewMatrix;
    mat4 inverseViewMatrix;
    vec4 ambientLightColour;
    PointLight pointLights[10];
    int numLights;
} ubo;

layout(set = 1, binding = 1) uniform sampler2D diffuseMap;

layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
} push;

void main() {
    vec3 diffuseLight = ubo.ambientLightColour.xyz * ubo.ambientLightColour.w;
    vec3 specularLight = vec3(0.0);
    vec3 surfaceNormal = normalize(fragNormalWorld);

    vec3 cameraPosWorld = ubo.inverseViewMatrix[3].xyz;
    vec3 viewDirection = normalize(cameraPosWorld - fragPosWorld);

    for (int i = 0; i < ubo.numLights; ++i) {
        PointLight light = ubo.pointLights[i];
        vec3 directionToLight = light.position.xyz - fragPosWorld;
        float attenuation = 1.0 / dot(directionToLight, directionToLight);
        directionToLight = normalize(directionToLight);

        float cosAngIncidence = max(dot(surfaceNormal, directionToLight), 0);
        vec3 intensity = light.colour.xyz * light.colour.w * attenuation;

        diffuseLight += intensity * cosAngIncidence;

        vec3 halfAngle = normalize(directionToLight + viewDirection);
        float blinnTerm = dot(surfaceNormal, halfAngle);
        blinnTerm = clamp(blinnTerm, 0, 1);
        blinnTerm = pow(blinnTerm, 512.0);
        specularLight += intensity * blinnTerm;
    }

    vec3 colour = texture(diffuseMap, fragUV).xyz;

    outColour = vec4(diffuseLight * colour + specularLight * fragColour, 1.0);
}