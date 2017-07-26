attribute vec4 a_position;
attribute vec2 a_texCoord;
varying vec2 t_Coord;


void main()
{
    gl_Position = a_position;
    t_Coord = a_texCoord;
}
