attribute vec4 a_position;
attribute vec2 a_texCoord;
varying vec2 textureCoord;
void main()
{
    gl_Position = a_position;
    textureCoord = a_texCoord;
}


