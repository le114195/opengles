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
    vec4 base2 = texture2D(inputImageTexture, vec2(1.0 - textureCoordinate.x, 1.0 - textureCoordinate.y));
    vec4 base = texture2D(inputImageTexture, textureCoordinate);
    vec4 overlay;
    
    float random = base.r + base.g + base.b + base2.r + base2.b + base2.g;
    random = rand(random) + base.r + base2.r;
    random = rand(random) + base.g + base2.g;
    random = rand(random) + base.b + base2.b;
    float random_x = rand(random * 0.136);
    float random_y = rand(random * 2.508);
    
    overlay = texture2D(inputImageTexture2, vec2(random_x, random_y));

    float alphaDivisor = base.a + step(base.a, 0.0);
    
    gl_FragColor = base * (overlay.a * (base / alphaDivisor) + (2.0 * overlay * (1.0 - (base / alphaDivisor)))) + overlay * (1.0 - base.a) + base * (1.0 - overlay.a);
}

