precision mediump float;
//varying vec2 v_texCoord;
//uniform sampler2D s_baseMap;
//uniform float fstep;
//void main()
//{
//    vec4 sample0,sample1,sample2,sample3;
//    
//    sample0 = texture2D(s_baseMap,vec2(v_texCoord.x-fstep,v_texCoord.y-fstep));
//    sample1 = texture2D(s_baseMap,vec2(v_texCoord.x+fstep,v_texCoord.y-fstep));
//    sample2 = texture2D(s_baseMap,vec2(v_texCoord.x+fstep,v_texCoord.y+fstep));
//    sample3 = texture2D(s_baseMap,vec2(v_texCoord.x-fstep,v_texCoord.y+fstep));
//    gl_FragColor = (sample0+sample1+sample2+sample3) / 4.0;
//}


varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D CC_Texture0;
uniform vec2 resolution;
uniform vec2 direction;
uniform float radius;

void main() {
    vec4 sum = vec4(0.0);
    float pixelsizex = radius/resolution.x;
    float pixelsizey = radius/resolution.y;
    
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x - 7.0*pixelsizex*direction.x, v_texCoord.y - 8.0*pixelsizey*direction.y)) * 0.003799;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x - 7.0*pixelsizex*direction.x, v_texCoord.y - 7.0*pixelsizey*direction.y)) * 0.008741;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x - 6.0*pixelsizex*direction.x, v_texCoord.y - 6.0*pixelsizey*direction.y)) * 0.017997;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x - 5.0*pixelsizex*direction.x, v_texCoord.y - 5.0*pixelsizey*direction.y)) * 0.033159;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x - 4.0*pixelsizex*direction.x, v_texCoord.y - 4.0*pixelsizey*direction.y)) * 0.054670;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x - 3.0*pixelsizex*direction.x, v_texCoord.y - 3.0*pixelsizey*direction.y)) * 0.080657;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x - 2.0*pixelsizex*direction.x, v_texCoord.y - 2.0*pixelsizey*direction.y)) * 0.106483;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x - 1.0*pixelsizex*direction.x, v_texCoord.y - 1.0*pixelsizey*direction.y)) * 0.125794;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x, v_texCoord.y)) * 0.137401;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x + 1.0*pixelsizex*direction.x, v_texCoord.y + 1.0*pixelsizey*direction.y)) * 0.125794;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x + 2.0*pixelsizex*direction.x, v_texCoord.y + 2.0*pixelsizey*direction.y)) * 0.106483;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x + 3.0*pixelsizex*direction.x, v_texCoord.y + 3.0*pixelsizey*direction.y)) * 0.080657;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x + 4.0*pixelsizey*direction.x, v_texCoord.y + 4.0*pixelsizey*direction.y)) * 0.054670;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x + 5.0*pixelsizex*direction.x, v_texCoord.y + 5.0*pixelsizey*direction.y)) * 0.033159;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x + 6.0*pixelsizex*direction.x, v_texCoord.y + 6.0*pixelsizey*direction.y)) * 0.017997;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x + 7.0*pixelsizex*direction.x, v_texCoord.y + 7.0*pixelsizey*direction.y)) * 0.008741;
    sum += texture2D(CC_Texture0, vec2(v_texCoord.x - 8.0*pixelsizex*direction.x, v_texCoord.y - 8.0*pixelsizey*direction.y)) * 0.003799;
    
    gl_FragColor = v_fragmentColor*sum;
}
