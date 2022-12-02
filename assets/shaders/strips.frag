#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 color0;
uniform vec4 color1;
uniform float time;

const float PI = 3.14159;

float lerp(float a, float b, float t)
{
    return (1.0 - t) * a + t * b;
}

void main()
{
    // tentar adivinhar pq q tem aquele jitter
    // highp vec2 fragCoord = fragTexCoord;
    // vec4 col = texture2D(texture0, fragCoord);
    // gl_FragColor = col;

    vec2 fragCoord = fragTexCoord;

    // // resample texture coordinates to be in range [0,1] as if they need to repeat
    // int xCount = int(1.0/fragCoord.x); // might also be negative
    // int yCount = int(1.0/fragCoord.y); // might also be negative
    // // a negative coordinates will always have +1. For instance -1.5 will return xCount=-1 but the result must be -1.5 - (-1-1) = .5
    // xCount += fragCoord.x<.0?-1:0;
    // yCount += fragCoord.y<.0?-1:0;
    // fragCoord -= vec2(xCount, yCount);

    vec2 pos;

    // "Blends" the x and y axis together, simulating a rotation.
    // It's actually just a lerp, so there's distortion.
    // Compare o caso entre girar 45 graus e ter um fator t = 0.5 (ambos metade do caminho)
    pos.x = lerp(fragCoord.x, fragCoord.y, 0.5);
    pos.y = lerp(fragCoord.y, 1.0-fragCoord.x, 0.5);

    pos.x += sin(pos.y * 2.0 * PI * 2.0) * 0.05;
    pos.x *= 6.0;

    // gl_FragColor = vec4(vec3(step(0.5, fract(pos.x))), 1.0);
    gl_FragColor = vec4(step(0.5, fract(pos.xx)), 0.0, 1.0);
}
