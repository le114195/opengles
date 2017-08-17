precision mediump float;

uniform sampler2D inputImageTexture;
varying highp vec2 textureCoordinate;

void main()
{
    vec4 colorMap = texture2D(inputImageTexture, textureCoordinate);
    
    gl_FragColor = colorMap;
}
