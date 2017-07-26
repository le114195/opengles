precision mediump float;
varying vec2 v_texCoord;
uniform sampler2D s_baseMap;
uniform float alpha;
uniform float offset;
uniform float fstep;
void main()
{
    vec4 sample0,sample1,sample2,sample3;
    sample0 = texture2D(s_baseMap,vec2(v_texCoord.x-fstep,v_texCoord.y-fstep));
    sample1 = texture2D(s_baseMap,vec2(v_texCoord.x+fstep,v_texCoord.y-fstep));
    sample2 = texture2D(s_baseMap,vec2(v_texCoord.x+fstep,v_texCoord.y+fstep));
    sample3 = texture2D(s_baseMap,vec2(v_texCoord.x-fstep,v_texCoord.y+fstep));
    vec4 bottom = (sample0+sample1+sample2+sample3) / 4.0;
    vec2 top1_texCoord = vec2(v_texCoord.x + offset, v_texCoord.y);
    sample0 = texture2D(s_baseMap,vec2(top1_texCoord.x-fstep,top1_texCoord.y-fstep));
    sample1 = texture2D(s_baseMap,vec2(top1_texCoord.x+fstep,top1_texCoord.y-fstep));
    sample2 = texture2D(s_baseMap,vec2(top1_texCoord.x+fstep,top1_texCoord.y+fstep));
    sample3 = texture2D(s_baseMap,vec2(top1_texCoord.x-fstep,top1_texCoord.y+fstep));
    vec4 top1 = (sample0+sample1+sample2+sample3) / 4.0;
    float r = alpha * top1.r + (1.0 - alpha) * bottom.r;
    float g = alpha * top1.g + (1.0 - alpha) * bottom.g;
    float b = alpha * top1.b + (1.0 - alpha) * bottom.b;
    bottom = vec4(r, g, b, 1.0);
    vec2 top2_texCoord = vec2(v_texCoord.x - offset, v_texCoord.y);
    sample0 = texture2D(s_baseMap,vec2(top2_texCoord.x-fstep,top2_texCoord.y-fstep));
    sample1 = texture2D(s_baseMap,vec2(top2_texCoord.x+fstep,top2_texCoord.y-fstep));
    sample2 = texture2D(s_baseMap,vec2(top2_texCoord.x+fstep,top2_texCoord.y+fstep));
    sample3 = texture2D(s_baseMap,vec2(top2_texCoord.x-fstep,top2_texCoord.y+fstep));
    vec4 top2 = (sample0+sample1+sample2+sample3) / 4.0;
    r = alpha * top2.r + (1.0 - alpha) * bottom.r;
    g = alpha * top2.g + (1.0 - alpha) * bottom.g;
    b = alpha * top2.b + (1.0 - alpha) * bottom.b;
    bottom = vec4(r, g, b, 1.0);
    gl_FragColor = bottom;
}
