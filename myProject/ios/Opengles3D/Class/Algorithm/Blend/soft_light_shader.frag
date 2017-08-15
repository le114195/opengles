precision highp float;
varying highp vec2 textureCoordinate;
varying highp vec2 textureCoordinate2;

uniform sampler2D inputImageTexture;
uniform sampler2D inputImageTexture2;

float rand(float x)
{
    return fract(sin(x) * 4358.5453123);
}

void main()
{
    vec4 base = texture2D(inputImageTexture, textureCoordinate);
    base = vec4(base.b, base.g, base.r, base.a);
    
    vec4 overlay = texture2D(inputImageTexture2, textureCoordinate2);
    
    float alphaDivisor = base.a + step(base.a, 0.0);
    gl_FragColor = base * (overlay.a * (base / alphaDivisor) + (2.0 * overlay * (1.0 - (base / alphaDivisor)))) + overlay * (1.0 - base.a) + base * (1.0 - overlay.a);
}

