precision mediump float;

uniform sampler2D inputImageTexture;
varying vec2 textureCoord;

uniform vec3 colorMap;


void main()
{
    gl_FragColor = texture2D(inputImageTexture, textureCoord);
}
