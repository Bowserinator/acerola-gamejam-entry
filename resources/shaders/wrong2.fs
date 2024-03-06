#version 100

precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;
uniform sampler2D texture0;
uniform vec2 resolution;
uniform float strength;

vec4 blur(int samples, float gap, vec2 dir) {
    vec4 color = vec4(0.);
    for (int i = 0; i < samples; i++) {
        color += texture2D(texture0, fragTexCoord + dir * float(i) * gap);
    }
    return color / float(samples);
}

void main() {
    vec2 center = vec2(0.5, 0.5);
    vec2 dir = (fragTexCoord - center) / resolution;

    vec4 tmp1 = texture2D(texture0, fragTexCoord) * (1. - strength) + strength * blur(5, 15., dir);
    vec4 tmp2 = texture2D(texture0, fragTexCoord) * (1. - strength) + strength * blur(5, 35., dir);
    vec4 tmp3 = texture2D(texture0, fragTexCoord) * (1. - strength) + strength * blur(5, 25., dir);

    vec3 gray = vec3(tmp1.r, 0., 0.);
    tmp1.rgb = vec3(tmp1.r, tmp2.g, tmp3.b) * (1. - strength) + gray * (strength);

    gl_FragColor = tmp1;
}
