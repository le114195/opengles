precision mediump float;

varying vec2 textureCoord;
uniform sampler2D inputImageTexture;

uniform float location[3];
uniform float width[3];

uniform float step_offset[3];

void main()
{
    vec4 colorMap = texture2D(inputImageTexture, textureCoord);
    
    if (textureCoord.y > location[0] && textureCoord.y < location[0] + width[0]) {
        vec2 offset = vec2(textureCoord.x, textureCoord.y - step_offset[0]);
        colorMap = texture2D(inputImageTexture, offset);
    }
    
    if (textureCoord.y > location[1] && textureCoord.y < location[1] + width[1]) {
        vec2 offset = vec2(textureCoord.x, textureCoord.y - step_offset[1]);
        colorMap = texture2D(inputImageTexture, offset);
    }
    
    if (textureCoord.y > location[2] && textureCoord.y < location[2] + width[2]) {
        vec2 offset = vec2(textureCoord.x, textureCoord.y - step_offset[2]);
        colorMap = texture2D(inputImageTexture, offset);
    }
    
    
    gl_FragColor = vec4(colorMap.b, colorMap.g, colorMap.r, 1.0);
}