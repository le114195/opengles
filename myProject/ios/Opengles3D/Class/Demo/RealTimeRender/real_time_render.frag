precision highp float;

uniform sampler2D image;

varying vec2 v_texCoord;


void main()
{
    gl_FragColor = texture2D(image, v_texCoord);
}



