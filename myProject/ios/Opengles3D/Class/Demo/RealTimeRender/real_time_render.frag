precision highp float;

uniform sampler2D image;

varying vec2 v_texCoord;


void main()
{
//    vec4 color = texture2D(image, v_texCoord);
//    gl_FragColor = vec4(color.b, color.g, color.r, 1.0);
//    
    gl_FragColor = texture2D(image, v_texCoord);
}



