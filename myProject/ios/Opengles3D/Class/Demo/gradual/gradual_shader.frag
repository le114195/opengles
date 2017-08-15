precision mediump float;

uniform sampler2D inputImageTexture;
varying vec2 textureCoord;
const float edgeWidth = 0.1;

void main()
{
    vec4 mapColor = texture2D(inputImageTexture, textureCoord);
    float alpha_t = min(textureCoord.x, (1.0 - textureCoord.x));
    alpha_t = min(alpha_t / edgeWidth, 1.0);
    gl_FragColor = vec4(mapColor.r, mapColor.g, mapColor.b, alpha_t);
}
