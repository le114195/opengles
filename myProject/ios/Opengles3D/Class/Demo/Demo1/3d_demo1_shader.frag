precision mediump float;
varying vec2 v_texCoord;
uniform sampler2D s_baseMap;
void main()
{
    gl_FragColor = texture2D(s_baseMap, v_texCoord);
}
