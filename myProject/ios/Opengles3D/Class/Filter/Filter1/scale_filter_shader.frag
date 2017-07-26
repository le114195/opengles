precision mediump float;
varying vec2 v_texCoord;
uniform sampler2D colorMap;
uniform float alpha;
uniform float scale;
void main()
{
    vec4 bottom = texture2D(colorMap, v_texCoord);
    vec2 top_texCoord = v_texCoord * (2.0 - scale);
    top_texCoord = vec2(top_texCoord.x + (scale - 1.0 ) * 0.5, top_texCoord.y + (scale - 1.0 ) * 0.5);
    vec4 topColor = texture2D(colorMap, top_texCoord);
    float r = topColor.r * alpha + (1.0 - alpha) * bottom.r;
    float g = topColor.g * alpha + (1.0 - alpha) * bottom.g;
    float b = topColor.b * alpha + (1.0 - alpha) * bottom.b;
    gl_FragColor = vec4(r, g, b, 1.0);
}
