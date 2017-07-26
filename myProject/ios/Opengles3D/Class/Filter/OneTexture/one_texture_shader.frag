precision mediump float;
varying vec2 vTextureCoord;
uniform sampler2D sTexture;
uniform float width;
uniform float height;


void main() {

    
    vec2 offset0=vec2(-1.0,-1.0); vec2 offset1=vec2(0.0,-1.0); vec2 offset2=vec2(1.0,-1.0);
    vec2 offset3=vec2(-1.0,0.0); vec2 offset4=vec2(0.0,0.0); vec2 offset5=vec2(1.0,0.0);
    vec2 offset6=vec2(-1.0,1.0); vec2 offset7=vec2(0.0,1.0); vec2 offset8=vec2(1.0,1.0);
    const float scaleFactor = 0.99;

    
    float kernelValue0 = 0.0; float kernelValue1 = 1.0; float kernelValue2 = 0.0;
    float kernelValue3 = 1.0; float kernelValue4 = -4.0; float kernelValue5 = 1.0;
    float kernelValue6 = 0.0; float kernelValue7 = 1.0; float kernelValue8 = 0.0;
    vec4 sum;


    vec2 temp0Coord = vec2(vTextureCoord.x + offset0.x / width, vTextureCoord.y + offset0.y / height);
    vec2 temp1Coord = vec2(vTextureCoord.x + offset1.x / width, vTextureCoord.y + offset1.y / height);
    vec2 temp2Coord = vec2(vTextureCoord.x + offset2.x / width, vTextureCoord.y + offset2.y / height);
    vec2 temp3Coord = vec2(vTextureCoord.x + offset3.x / width, vTextureCoord.y + offset3.y / height);
    vec2 temp4Coord = vec2(vTextureCoord.x + offset4.x / width, vTextureCoord.y + offset4.y / height);
    vec2 temp5Coord = vec2(vTextureCoord.x + offset5.x / width, vTextureCoord.y + offset5.y / height);
    vec2 temp6Coord = vec2(vTextureCoord.x + offset6.x / width, vTextureCoord.y + offset6.y / height);
    vec2 temp7Coord = vec2(vTextureCoord.x + offset7.x / width, vTextureCoord.y + offset7.y / height);
    vec2 temp8Coord = vec2(vTextureCoord.x + offset8.x / width, vTextureCoord.y + offset8.y / height);
    
    vec4 cTemp0,cTemp1,cTemp2,cTemp3,cTemp4,cTemp5,cTemp6,cTemp7,cTemp8;
    cTemp0=texture2D(sTexture, temp0Coord);
    cTemp1=texture2D(sTexture, temp1Coord);
    cTemp2=texture2D(sTexture, temp2Coord);
    cTemp3=texture2D(sTexture, temp3Coord);
    cTemp4=texture2D(sTexture, temp4Coord);
    cTemp5=texture2D(sTexture, temp5Coord);
    cTemp6=texture2D(sTexture, temp6Coord);
    cTemp7=texture2D(sTexture, temp7Coord);
    cTemp8=texture2D(sTexture, temp8Coord);
    
    sum = kernelValue0*cTemp0 + kernelValue1*cTemp1 + kernelValue2*cTemp2 +
    kernelValue3*cTemp3 + kernelValue4*cTemp4 + kernelValue5*cTemp5 +
    kernelValue6*cTemp6 + kernelValue7*cTemp7 + kernelValue8*cTemp8;
    
    gl_FragColor = sum * scaleFactor;
    
    gl_FragColor = kernelValue0*cTemp0 + kernelValue1*cTemp1 + kernelValue2*cTemp2 + kernelValue3*cTemp3 + kernelValue4*cTemp4;
}


