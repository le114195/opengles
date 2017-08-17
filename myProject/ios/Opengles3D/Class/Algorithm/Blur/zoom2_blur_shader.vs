attribute vec4 a_position;
attribute vec2 a_texCoord;
varying vec2 textureCoordinate;
void main()
{
    gl_Position = a_position;
    textureCoordinate = a_texCoord;
}
