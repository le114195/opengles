precision mediump float;

uniform sampler2D inputImageTexture;
varying vec2 textureCoordinate;

uniform vec2 offset;

void main()
{
    vec2 tex_coord = textureCoordinate;
    
    vec4 color = texture2D(inputImageTexture, tex_coord);
    
    vec2 redCoord = vec2(tex_coord.x + offset.x, tex_coord.y + offset.y);
    vec4 redColor = texture2D(inputImageTexture, redCoord);
    redColor = vec4(redColor.r, 0.0, 0.0, 1.0);
    
    vec2 bgCoord = vec2(tex_coord.x - offset.x, tex_coord.y - offset.y);
    vec4 bgColor = texture2D(inputImageTexture, bgCoord);
    bgColor = vec4(0.0, bgColor.g, bgColor.b, 1.0);
    
    gl_FragColor = redColor + bgColor;
}

