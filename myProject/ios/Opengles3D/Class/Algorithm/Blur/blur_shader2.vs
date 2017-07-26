attribute vec4 a_position;
attribute vec4 inputTextureCoordinate;

uniform float texelWidthOffset;
uniform float texelHeightOffset;

varying vec2 blurCoordinates[15];

void main()
{
    gl_Position = a_position;
    
    vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);
    blurCoordinates[0] = inputTextureCoordinate.xy;
    blurCoordinates[1] = inputTextureCoordinate.xy + singleStepOffset * 1.497396;
    blurCoordinates[2] = inputTextureCoordinate.xy - singleStepOffset * 1.497396;
    blurCoordinates[3] = inputTextureCoordinate.xy + singleStepOffset * 3.493924;
    blurCoordinates[4] = inputTextureCoordinate.xy - singleStepOffset * 3.493924;
    blurCoordinates[5] = inputTextureCoordinate.xy + singleStepOffset * 5.490452;
    blurCoordinates[6] = inputTextureCoordinate.xy - singleStepOffset * 5.490452;
    blurCoordinates[7] = inputTextureCoordinate.xy + singleStepOffset * 7.486982;
    blurCoordinates[8] = inputTextureCoordinate.xy - singleStepOffset * 7.486982;
    blurCoordinates[9] = inputTextureCoordinate.xy + singleStepOffset * 9.483513;
    blurCoordinates[10] = inputTextureCoordinate.xy - singleStepOffset * 9.483513;
    blurCoordinates[11] = inputTextureCoordinate.xy + singleStepOffset * 11.480045;
    blurCoordinates[12] = inputTextureCoordinate.xy - singleStepOffset * 11.480045;
    blurCoordinates[13] = inputTextureCoordinate.xy + singleStepOffset * 13.476581;
    blurCoordinates[14] = inputTextureCoordinate.xy - singleStepOffset * 13.476581;
}
