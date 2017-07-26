attribute vec4 a_position;
attribute vec4 a_texCoord;
varying vec2 textureCoordinate;

uniform mat4 u_mvpMatrix;

void main()
{
    gl_Position = a_position;
    
    vec4 xx = u_mvpMatrix * a_texCoord;
    textureCoordinate = vec2(xx.r, xx.g);
}
