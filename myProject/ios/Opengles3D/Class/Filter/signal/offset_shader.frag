precision mediump float;

uniform sampler2D inputImageTexture;

varying highp vec2 textureCoordinate;

uniform float offsetY;

void main()
{
    float y = textureCoordinate.y - offsetY;
    if (y < 0.0) {
        y = y + 1.0;
    }
    if (y > 1.0) {
        y = y - 1.0;
    }
    vec2 location = vec2(textureCoordinate.x, y);
    
    gl_FragColor = texture2D(inputImageTexture, location);
}
