precision mediump float;
varying highp vec2 textureCoordinate;
varying highp vec2 textureCoordinate2;

uniform sampler2D inputImageTexture;
uniform sampler2D inputImageTexture2;

const float alpha_t = 0.3;

void main()
{
    vec4 bottom = texture2D(inputImageTexture, textureCoordinate);
    vec4 top = texture2D(inputImageTexture2, textureCoordinate2);
    
    float r = alpha_t * top.r + (1.0 - alpha_t) * bottom.r;
    float g = alpha_t * top.g + (1.0 - alpha_t) * bottom.g;
    float b = alpha_t * top.b + (1.0 - alpha_t) * bottom.b;
    
    gl_FragColor = vec4(r, g, b, 1.0);
    
    
}
