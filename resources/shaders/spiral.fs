#version 100

// Based on https://www.shadertoy.com/view/MslyWB
precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;
uniform sampler2D texture0;

uniform vec2 resolution;
uniform float time;

const float pi = 3.141592;

float power(float r, float theta, float exponent, float timem) {
    return fract(1.5 * theta / pi + 12.0 * pow(r, exponent) + timem / 4. * time);
}

void main() {
    vec2 uv = (fragTexCoord - 0.5) * resolution / resolution.yy;
	float r = length(uv);
    float theta = atan(uv.y, uv.x);
    float offset = (
        power(r, theta, 0.5, 1.0) * 0.3 +
        power(r, theta, 0.7, 1.1) * 0.3 +
        power(r, theta, 0.9, 1.2) * 0.3 +
        power(r, theta, 1.5, 1.3) * 0.1
    ) < 0.5 ? 0. : 1.;

    vec4 sample1 = (1. - offset) * texture2D(texture0, fragTexCoord) + offset * texture2D(texture0, fragTexCoord + vec2(0.1));
    vec4 sample2 = (1. - offset) * texture2D(texture0, fragTexCoord) + offset * texture2D(texture0, fragTexCoord + vec2(0.11));
    vec4 sample3 = (1. - offset) * texture2D(texture0, fragTexCoord) + offset * texture2D(texture0, fragTexCoord + vec2(0.12));
    gl_FragColor = vec4(sample1.r, sample2.g, sample3.b, 1.0);
}
