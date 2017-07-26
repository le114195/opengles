precision mediump float;
uniform sampler2D u_sampler;
uniform int u_screen_width;
uniform int u_screen_height;
varying vec2 v_TexCoord;

float rgb2gray(vec3 color)
{
    return 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
}

float pixel_operator(float dx, float dy)
{
    vec4 rgba_color = texture( u_sampler, v_TexCoord + vec2(dx,dy) );
    return rgb2gray(rgba_color.rgb);
}

float sobel_filter()
{
//    float dx = 1.0 / float(u_screen_width); // e.g. 1920
//    float dy = 1.0 / float(u_screen_height); // e.g. 1080

    float dx = 1.0 / 1920.0; // e.g. 1920
    float dy = 1.0 / 1080.0; // e.g. 1080
    
    float s00 = pixel_operator(-dx, dy);
    float s10 = pixel_operator(-dx, 0.0);
    float s20 = pixel_operator(-dx, -dy);
    float s01 = pixel_operator(0.0, dy);
    float s21 = pixel_operator(0.0, -dy);
    float s02 = pixel_operator(dx, dy);
    float s12 = pixel_operator(dx, 0.0);
    float s22 = pixel_operator(dx, -dy);
    
    float sx = s00 + 2.0 * s10 + s20 - (s02 + 2.0 * s12 + s22);
    float sy = s00 + 2.0 * s01 + s02 - (s20 + 2.0 * s21 + s22);
    float dist = sx * sx + sy * sy;
    
    return dist;
}

void main
{
    float graylevel = sobel_filter();
    gl_FragColor = vec4(graylevel, graylevel, graylevel, 1.0);
}












