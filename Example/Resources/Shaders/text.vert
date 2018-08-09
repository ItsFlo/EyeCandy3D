#include "Common.glsl"

in vec4 pos_uv;
out vec2 uv;

void main()
{
    gl_Position = vec4(pos_uv.xy, 0, 1);
    uv = pos_uv.zw;
}