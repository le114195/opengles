attribute vec4 a_position;
attribute vec4 inputTextureCoordinate;
attribute vec4 inputTextureCoordinate2;

varying vec2 textureCoordinate;
varying vec2 textureCoordinate2;

void main()
{
    gl_Position = a_position;
    textureCoordinate = inputTextureCoordinate.xy;
    textureCoordinate2 = inputTextureCoordinate2.xy;
}
