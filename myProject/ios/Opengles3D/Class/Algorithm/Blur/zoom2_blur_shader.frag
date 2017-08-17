precision mediump float;

varying highp vec2 textureCoordinate;

uniform sampler2D inputImageTexture;

uniform highp vec2 blurCenter;
uniform highp float blurSize;

void main()
{
    
    float bSize = sqrt(textureCoordinate.x * textureCoordinate.x + textureCoordinate.y * textureCoordinate.y) * 0.1 + 1.0;
    highp vec2 samplingOffset = (textureCoordinate - vec2(0.5, 0.5)) * bSize + vec2(0.5, 0.5);
    
    

    
    vec4 colorMap = texture2D(inputImageTexture, samplingOffset);
    
    gl_FragColor = vec4(colorMap.b, colorMap.g, colorMap.r, colorMap.a);
    
}
