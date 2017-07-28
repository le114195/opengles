precision highp float;

uniform sampler2D mapColor;

varying vec2 v_texCoord;

void main()
{
    vec4 textureColor = texture2D(mapColor, v_texCoord);
    gl_FragColor = vec4(textureColor.r, 0.0, 0.0, 1.0);
}
