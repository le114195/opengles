precision mediump float;
uniform sampler2D inputImageTexture;
varying highp vec2 textureCoordinate;

uniform float strength;

void main()
{
    vec4 colorMap = texture2D(inputImageTexture, textureCoordinate);
    colorMap = vec4(colorMap.b, colorMap.g, colorMap.r, colorMap.a);
    
    float alpha;
    
    float x = (textureCoordinate.x - 0.5) * 2.0;
    float y = (textureCoordinate.y - 0.5) * 2.0;

    alpha = sqrt(x * x + y * y + 0.1)/sqrt(2.2);
    
    alpha = sqrt(alpha);
    alpha = sqrt(alpha);
    alpha = sqrt(alpha) * strength;
    
    
    alpha = clamp(alpha, 0.0, 1.0);
    
    vec4 nightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    float r = alpha * nightColor.r + (1.0 - alpha) * colorMap.r;
    float g = alpha * nightColor.g + (1.0 - alpha) * colorMap.g;
    float b = alpha * nightColor.b + (1.0 - alpha) * colorMap.b;
    
    vec4 color = vec4(r, g, b, 1.0);
    
    gl_FragColor = vec4(color.rgb * pow(2.0, 0.1), 1.0);
}
