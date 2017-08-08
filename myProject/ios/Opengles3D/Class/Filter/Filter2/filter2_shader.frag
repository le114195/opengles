precision mediump float;
varying vec2 v_texCoord;
uniform sampler2D s_baseMap;
uniform float alpha;
uniform float offset;
uniform float fstep;
void main()
{

  vec2 out_texCoord = vec2(v_texCoord.x + offset, v_texCoord.y);

  vec4 sample0,sample1,sample2,sample3;
  sample0=texture2D(s_baseMap,vec2(out_texCoord.x-fstep,out_texCoord.y-fstep));
  sample1=texture2D(s_baseMap,vec2(out_texCoord.x+fstep,out_texCoord.y-fstep));
  sample2=texture2D(s_baseMap,vec2(out_texCoord.x+fstep,out_texCoord.y+fstep));
  sample3=texture2D(s_baseMap,vec2(out_texCoord.x-fstep,out_texCoord.y+fstep));
  vec4 color=(sample0+sample1+sample2+sample3) / 4.0;

  gl_FragColor = vec4(color.b, color.g, color.r, alpha);
}                                                                  
