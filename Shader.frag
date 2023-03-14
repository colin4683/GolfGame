uniform vec2 pos;
uniform vec2 size;
uniform vec2 gradient_center;
uniform vec4 gradient_color1;
uniform vec4 gradient_color2;
void main(void){
    gl_FragColor = mix(
        gradient_color1,
        gradient_color2,
        distance(
            vec2(
                (gl_FragCoord.x - pos.x) / size.x,
                (gl_FragCoord.y - pos.y) / size.y),
            gradient_center));
}