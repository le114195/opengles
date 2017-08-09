precision mediump float;

uniform sampler2D inputImageTexture;
varying vec2 textureCoord;

void main()
{
    vec4 color = texture2D(inputImageTexture, textureCoord);
    
    float red = color.r;
    float green = color.g;
    float blur = color.b;
    
    float total = (red + green + blur) / 3.0;
    
    int t = int(total * 5.0) + 1;
    total = float(t);
    total = total / 5.0 * 3.0;
    
    float rate = total / (red + green + blur);
    
    red = red * rate;
    green = green * rate;
    blur = blur * rate;
    
    gl_FragColor = vec4(red, green, blur, 1.0);
}
