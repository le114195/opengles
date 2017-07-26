precision mediump float;

uniform sampler2D inputImageTexture;
varying vec2 t_Coord;

uniform float texelWidthOffset;
uniform float texelHeightOffset;

uniform float weight[23];

vec4 totalColor(int r)
{
    int total = 8 * r + 1;
    
    vec4 sum = vec4(0.0, 0.0, 0.0, 1.0);

    vec2 topLeft, topCenter, topRight, left, right, bottomLeft, bottomCenter, bottomRight;

    for (int i = 1; i <= r; i++) {
        
        float fstep = float(i) * 5.5;
        
        topLeft = vec2(t_Coord.x - texelWidthOffset * float(fstep), t_Coord.y + texelHeightOffset * float(fstep));
        topCenter = vec2(t_Coord.x, t_Coord.y + texelHeightOffset * float(fstep));
        topRight = vec2(t_Coord.x + texelWidthOffset * float(fstep), t_Coord.y + texelHeightOffset * float(fstep));
        
        left = vec2(t_Coord.x - texelWidthOffset * float(fstep), t_Coord.y);
        right = vec2(t_Coord.x + texelWidthOffset * float(fstep), t_Coord.y);
        
        bottomLeft = vec2(t_Coord.x - texelWidthOffset * float(fstep), t_Coord.y - texelHeightOffset * float(fstep));
        bottomCenter = vec2(t_Coord.x, t_Coord.y - texelHeightOffset * float(fstep));
        bottomRight = vec2(t_Coord.x + texelWidthOffset * float(fstep), t_Coord.y - texelHeightOffset * float(fstep));
        
        sum += texture2D(inputImageTexture, topLeft) * weight[i];
        sum += texture2D(inputImageTexture, topCenter) * weight[i];
        sum += texture2D(inputImageTexture, topRight) * weight[i];
        
        sum += texture2D(inputImageTexture, left) * weight[i];
        sum += texture2D(inputImageTexture, right) * weight[i];
        
        sum += texture2D(inputImageTexture, bottomLeft) * weight[i];
        sum += texture2D(inputImageTexture, bottomCenter) * weight[i];
        sum += texture2D(inputImageTexture, bottomRight) * weight[i];
    }
    sum += texture2D(inputImageTexture, t_Coord) * weight[0];
    
    return sum;
}


void main()
{
    gl_FragColor = totalColor(22);
}
