precision mediump float;
uniform sampler2D inputImageTexture;
varying highp vec2 textureCoordinate;
uniform float alpha_t;
void main()
{
    vec4 colorMap = texture2D(inputImageTexture, textureCoordinate);
    gl_FragColor = vec4(colorMap.r, colorMap.g, colorMap.b, alpha_t * colorMap.a);
}
