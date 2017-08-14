precision mediump float;

uniform sampler2D inputImageTexture;
varying vec2 textureCoord;

const highp float quantizationLevels = 7.0;

void main()
{
    vec4 color = texture2D(inputImageTexture, textureCoord);
    
    float red = color.r;
    float green = color.g;
    float blur = color.b;
    
    float total = (red + green + blur) / 3.0;
    
    int t = int(total * quantizationLevels) + 1;
    total = float(t);
    total = total / quantizationLevels * 3.0;
    
    float rate = total / (red + green + blur);
    
    red = red * rate;
    green = green * rate;
    blur = blur * rate;

//    int r = int(red * quantizationLevels) + 1;
//    red = float(r);
//    red = red / quantizationLevels;
//    
//    int g = int(green * quantizationLevels) + 1;
//    green = float(g);
//    green = green / quantizationLevels;
//    
//    int b = int(blur * quantizationLevels) + 1;
//    blur = float(b);
//    blur = blur / quantizationLevels;
    
    
    gl_FragColor = vec4(red, green, blur, 1.0);
}
