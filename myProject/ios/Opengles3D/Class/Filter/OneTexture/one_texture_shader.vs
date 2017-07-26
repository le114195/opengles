attribute vec4 a_position;
attribute vec2 inputTextureCoordinate;
varying vec2 vTextureCoord;
void main()
{
    gl_Position = a_position;
    vTextureCoord = inputTextureCoordinate;
}
