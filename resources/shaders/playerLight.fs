#version 100

precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;
uniform sampler2D texture0;

uniform sampler2D lightTexture;
uniform vec4 lightTextureRegion;


void main() {
    vec4 lightColor = texture2D(lightTexture, lightTextureRegion.xy + lightTextureRegion.zw * fragTexCoord.xy);
    vec4 sample = texture2D(texture0, fragTexCoord);
    vec4 darkened = (1. - lightColor.a) * sample + lightColor.a * vec4(lightColor.rgb * sample.rgb, 1.0);
    vec4 lightened = 0.2 * lightColor + sample;
    float darkStrength = 1.0 - dot(vec3(1.), lightColor.rgb) / 3.;

    vec4 oColor = darkened * darkStrength + lightened * (1. - darkStrength);
    oColor.a = sample.a;

    gl_FragColor = oColor;
}
