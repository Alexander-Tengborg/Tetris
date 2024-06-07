uniform sampler2D texture;
uniform float time;

float rand(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

float rand2(vec2 c) {
    return fract(cos(c*time));
}

vec3 palette(float t) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 0.7, 0.4);
    vec3 d = vec3(0.00, 0.15, 0.20);

    return a + b*cos(6.28318*(c*t+d));
}

void main()
{
    vec2 res = vec2(900, 800);

    vec2 uv = (gl_FragCoord.xy * 2.0 - res) / res.y;
    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0);

    for(float i = 0.0; i < 4.0; i++) {
        uv = fract(uv * 1.5) - 0.5;
        float d = length(uv) * exp(-length(uv0));
        vec3 col = palette(length(uv0) + i*.4 + time*.4);

        d = sin(d*8. + time / 10.)/8.;
        d = abs(d);
        d = 0.01 / d;

        finalColor += col * d;
    }

    gl_FragColor = vec4(finalColor, 0.5);
}