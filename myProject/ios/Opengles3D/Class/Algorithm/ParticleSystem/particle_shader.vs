attribute vec2 a_startPosition;
attribute vec2 a_endPosition;
attribute float a_lifetime;
uniform float u_time;
uniform vec2 u_centerPosition;

varying float v_lifetime;
void main()
{
    if (u_time <= a_lifetime) {
        
        gl_Position.xy = a_startPosition + (u_time * a_endPosition) + u_centerPosition;
        gl_Position.z = 1.0;
        gl_Position.w = 1.0;
    }else {
        gl_Position = vec4(-1000.0, -1000.0, 0.0, 0.0);
    }
    v_lifetime = 1.0 - (u_time / a_lifetime);
    v_lifetime = clamp (v_lifetime, 0.0, 1.0);
    
    gl_PointSize = (v_lifetime * v_lifetime) * 40.0;
}
