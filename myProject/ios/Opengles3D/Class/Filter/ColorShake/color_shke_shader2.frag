precision highp float;
uniform sampler2D inputImageTexture;
const highp vec3 params = vec3(0.6, 0.8, 0.25);
uniform sampler2D leftFilterTexture;
uniform sampler2D rightFilterTexture;
uniform sampler2D hotsoonFilterTexture;
uniform float filterPos;
uniform int leftFilterLookup;
uniform int rightFilterLookup;
uniform int hotsoonFilterLookup;
uniform int isHotsoonFilter;
vec4 skinSmooth;
lowp vec4 skinSmoothColor2;
vec4 fake3dSkinSmoothColor;
vec4 fake3dShiftSkinSmoothColor;
vec4 fake3dShiftSkinSmoothColor2;
uniform int effecttype;
uniform lowp float mixturePercent;
uniform highp float scalePercent;
uniform float fake3DScale;
uniform int exchange;
varying highp vec2 textureCoordinate;
highp vec4 Lookup4x4Fragment(sampler2D tex, highp vec4 texCoord)
{
    highp float blueColor = texCoord.b * 15.0;
    highp vec2 quad1;
    quad1.y = floor(floor(blueColor) / 4.0);
    quad1.x = floor(blueColor) - (quad1.y * 4.0);
    highp vec2 quad2;
    quad2.y = floor(ceil(blueColor) / 4.0);
    quad2.x = ceil(blueColor) - (quad2.y * 4.0);
    highp vec2 texPos1;
    texPos1.x = (quad1.x * 0.25) + 0.5/64.0 + ((0.25 - 1.0/64.0) * texCoord.r);
    texPos1.y = (quad1.y * 0.25) + 0.5/64.0 + ((0.25 - 1.0/64.0) * texCoord.g);
    highp vec2 texPos2;
    texPos2.x = (quad2.x * 0.25) + 0.5/64.0 + ((0.25 - 1.0/64.0) * texCoord.r);
    texPos2.y = (quad2.y * 0.25) + 0.5/64.0 + ((0.25 - 1.0/64.0) * texCoord.g);
    lowp vec4 newColor1 = texture2D(tex, texPos1);
    lowp vec4 newColor2 = texture2D(tex, texPos2);
    lowp vec4 newColor = mix(newColor1, newColor2, fract(blueColor));
    return vec4(newColor.rgb, 1.0);
}
highp vec4 Lookup8x8Fragment(sampler2D tex, highp vec4 texCoord)
{
    highp float blueColor = texCoord.b * 63.0;
    highp vec2 quad1;
    quad1.y = floor(floor(blueColor) / 8.0);
    quad1.x = floor(blueColor) - (quad1.y * 8.0);
    highp vec2 quad2;
    quad2.y = floor(ceil(blueColor) / 8.0);
    quad2.x = ceil(blueColor) - (quad2.y * 8.0);
    highp vec2 texPos1;
    texPos1.x = (quad1.x * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * texCoord.r);
    texPos1.y = (quad1.y * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * texCoord.g);
    highp vec2 texPos2;
    texPos2.x = (quad2.x * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * texCoord.r);
    texPos2.y = (quad2.y * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * texCoord.g);
    lowp vec4 newColor1 = texture2D(tex, texPos1);
    lowp vec4 newColor2 = texture2D(tex, texPos2);
    lowp vec4 newColor = mix(newColor1, newColor2, fract(blueColor));
    return vec4(newColor.rgb, 1.0);
}
void main()
{
    if (effecttype == 5) {
        vec2 newTextureCoordinate = vec2((fake3DScale - 1.0) *0.5 + textureCoordinate.x / fake3DScale , (fake3DScale - 1.0) *0.5 + textureCoordinate.y /fake3DScale);
        fake3dSkinSmoothColor = texture2D(inputImageTexture, newTextureCoordinate);
        fake3dShiftSkinSmoothColor = texture2D(inputImageTexture, newTextureCoordinate+vec2(-0.05 * (fake3DScale - 1.0), - 0.05 *(fake3DScale - 1.0)));
        fake3dShiftSkinSmoothColor2 = texture2D(inputImageTexture, newTextureCoordinate+vec2(-0.1 * (fake3DScale - 1.0), - 0.1 *(fake3DScale - 1.0)));
    } else {
        skinSmooth = texture2D(inputImageTexture, textureCoordinate);
    }
    if( isHotsoonFilter == 1 )
    {
        if( hotsoonFilterLookup == 1 ) {
            skinSmooth = Lookup4x4Fragment(hotsoonFilterTexture, skinSmooth);
        }
        else if( hotsoonFilterLookup == 2 ){
            skinSmooth = Lookup8x8Fragment(hotsoonFilterTexture, skinSmooth);
        }
    }
    vec4 filterColor;
    vec4 filterColor2;
    vec4 fake3dFilterColor;
    vec4 fake3dShiftFilterColor;
    vec4 fake3dShiftFilterColor2;
    if( textureCoordinate.x <= filterPos ){
        if( leftFilterLookup == 1 ) {
            filterColor = Lookup4x4Fragment(leftFilterTexture, skinSmooth);
        }
        else if( leftFilterLookup == 2 ){
            if (effecttype == 5) {
                fake3dFilterColor= Lookup8x8Fragment(leftFilterTexture, fake3dSkinSmoothColor);
                fake3dShiftFilterColor = Lookup8x8Fragment(leftFilterTexture, fake3dShiftSkinSmoothColor);
                fake3dShiftFilterColor2 = Lookup8x8Fragment(leftFilterTexture, fake3dShiftSkinSmoothColor2);
            } else {
                filterColor = Lookup8x8Fragment(leftFilterTexture, skinSmooth);
            }
            if (effecttype == 4) {
                filterColor2 = Lookup8x8Fragment(leftFilterTexture, skinSmoothColor2);
            }
        }
        else{
            filterColor = skinSmooth;
        }
    }
    else{
        if( rightFilterLookup == 1 ) {
            filterColor = Lookup4x4Fragment(rightFilterTexture, skinSmooth);
        }
        else if( rightFilterLookup == 2 ){
            if (effecttype == 5) {
                fake3dFilterColor= Lookup8x8Fragment(rightFilterTexture, fake3dSkinSmoothColor);
                fake3dShiftFilterColor = Lookup8x8Fragment(rightFilterTexture, fake3dShiftSkinSmoothColor);
                fake3dShiftFilterColor2 = Lookup8x8Fragment(rightFilterTexture, fake3dShiftSkinSmoothColor2);
            } else {
                filterColor = Lookup8x8Fragment(rightFilterTexture, skinSmooth);
            }
            if (effecttype == 4) {
                filterColor2 = Lookup8x8Fragment(rightFilterTexture, skinSmoothColor2);
            }
        }
        else{
            filterColor = skinSmooth;
        }
    }
    vec4 tempColor = filterColor;
    if (effecttype == 4) {
        tempColor = mix(filterColor, filterColor2, mixturePercent);
    } else if (effecttype == 5) {
        vec3 blendFirstColor = vec3(fake3dFilterColor.r, fake3dFilterColor.g, fake3dShiftFilterColor.b);
        vec3 blend3DColor = vec3(fake3dShiftFilterColor2.r, blendFirstColor.g, blendFirstColor.b);
        tempColor = vec4(blend3DColor, fake3dFilterColor.a);
    }
    if(exchange != 0) {
        gl_FragColor = vec4(tempColor.b, tempColor.g, tempColor.r, 1.0);
    } else {
        gl_FragColor = vec4(tempColor.r, tempColor.g, tempColor.b, 1.0);
    }
}
