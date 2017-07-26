attribute vec4 a_position;
attribute vec4 a_Coordinate;

uniform float texelWidth;
uniform float texelHeight;

varying vec2 vTextureCoord;
varying vec2 leftTextureCoordinate;
varying vec2 rightTextureCoordinate;

varying vec2 topTextureCoordinate;
varying vec2 topLeftTextureCoordinate;
varying vec2 topRightTextureCoordinate;

varying vec2 bottomTextureCoordinate;
varying vec2 bottomLeftTextureCoordinate;
varying vec2 bottomRightTextureCoordinate;

void main()
{
    gl_Position = a_position;
    
    vec2 widthStep = vec2(texelWidth, 0.0);
    vec2 heightStep = vec2(0.0, texelHeight);
    vec2 widthHeightStep = vec2(texelWidth, texelHeight);
    vec2 widthNegativeHeightStep = vec2(texelWidth, -texelHeight);
    
    vTextureCoord = a_Coordinate.xy;
    leftTextureCoordinate = a_Coordinate.xy - widthStep;
    rightTextureCoordinate = a_Coordinate.xy + widthStep;
    
    topTextureCoordinate = a_Coordinate.xy - heightStep;
    topLeftTextureCoordinate = a_Coordinate.xy - widthHeightStep;
    topRightTextureCoordinate = a_Coordinate.xy + widthNegativeHeightStep;
    
    bottomTextureCoordinate = a_Coordinate.xy + heightStep;
    bottomLeftTextureCoordinate = a_Coordinate.xy - widthNegativeHeightStep;
    bottomRightTextureCoordinate = a_Coordinate.xy + widthHeightStep;
}
