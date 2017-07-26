precision mediump float;

varying vec2 textureCoordinate;
varying vec2 leftTextureCoordinate;
varying vec2 rightTextureCoordinate;

varying vec2 topTextureCoordinate;
varying vec2 topLeftTextureCoordinate;
varying vec2 topRightTextureCoordinate;

varying vec2 bottomTextureCoordinate;
varying vec2 bottomLeftTextureCoordinate;
varying vec2 bottomRightTextureCoordinate;

uniform sampler2D inputImageTexture;

uniform vec2  offset;


vec4 edgeOffsetColor(vec2 offs)
{
    float edgeStrength = 1.0;
    
    float bottomLeftIntensity = texture2D(inputImageTexture, vec2(bottomLeftTextureCoordinate.x + offs.x, bottomLeftTextureCoordinate.y + offs.y)).r;
    float topRightIntensity = texture2D(inputImageTexture, vec2(topRightTextureCoordinate.x + offs.x, topRightTextureCoordinate.y + offs.y)).r;
    float topLeftIntensity = texture2D(inputImageTexture, vec2(topLeftTextureCoordinate.x + offs.x, topLeftTextureCoordinate.y + offs.y)).r;
    float bottomRightIntensity = texture2D(inputImageTexture, vec2(bottomRightTextureCoordinate.x + offs.x, bottomRightTextureCoordinate.y + offs.y)).r;
    float leftIntensity = texture2D(inputImageTexture, vec2(leftTextureCoordinate.x + offs.x, leftTextureCoordinate.y + offs.y)).r;
    float rightIntensity = texture2D(inputImageTexture, vec2(rightTextureCoordinate.x + offs.x, rightTextureCoordinate.y + offs.y)).r;
    float bottomIntensity = texture2D(inputImageTexture, vec2(bottomTextureCoordinate.x + offs.x, bottomTextureCoordinate.y + offs.y)).r;
    float topIntensity = texture2D(inputImageTexture, vec2(topTextureCoordinate.x + offs.x, topTextureCoordinate.y + offs.y)).r;
    
    float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;
    float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;
    
    float mag = length(vec2(h, v)) * edgeStrength;
    
    vec4 offsetColor = vec4(vec3(mag), 1.0);
    
    return offsetColor;
}

void main()
{
    vec4 redColor = edgeOffsetColor(offset);
    vec4 blueColor = edgeOffsetColor(vec2(offset.x * 0.5, offset.y * 0.5));
    
    redColor = vec4(redColor.r, 0.0, 0.0, 1.0);
    blueColor = vec4(0.0, 0.0, blueColor.b, 1.0);
    
    gl_FragColor = texture2D(inputImageTexture, textureCoordinate) + redColor + blueColor;
}






