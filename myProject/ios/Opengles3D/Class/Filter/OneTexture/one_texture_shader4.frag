precision mediump float;

uniform sampler2D inputImageTexture;
varying vec2 textureCoord;

uniform vec3 colorMap;

void main()
{
    vec4 color = texture2D(inputImageTexture, textureCoord);
    gl_FragColor = color * vec4(colorMap, 1.0);
}

