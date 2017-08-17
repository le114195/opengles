precision mediump float;
varying vec2 v_texCoord;
uniform sampler2D s_baseMap;

uniform float alpha_t;

void main()
{
    vec4 color = texture2D(s_baseMap, v_texCoord);
    gl_FragColor = vec4(color.r, color.g, color.b, color.a * alpha_t);
}
