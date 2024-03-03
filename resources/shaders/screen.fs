#version 100

precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;
uniform sampler2D texture0;
uniform vec2 resolution;

const float GRILLE_OPACITY = 0.1;
const float GAP = 4.0;

void main() {
    float t1 = texture2D(texture0, fragTexCoord).r;
    float t2 = texture2D(texture0, fragTexCoord + vec2(1.0) / resolution).g;
    float t3 = texture2D(texture0, fragTexCoord - vec2(1.0) / resolution).b;
    gl_FragColor = vec4(t1, t2, t3, 1.0);
}
