/*
 * copyright (c) 2016 Zhang Rui <bbcallen@gmail.com>
 *
 * This file is part of ijkPlayer.
 *
 * ijkPlayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ijkPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ijkPlayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "ijksdl/gles2/internal.h"

static const char g_shader[] = IJK_GLES_STRING(
    precision highp float;
    varying   highp vec2 vv2_Texcoord;
    uniform   lowp  sampler2D us2_SamplerX;
    uniform   float u_screenWidth;
    uniform int u_Interlaced;

    void main()
    {
        float coordx = vv2_Texcoord.x;
        if (u_Interlaced != 0)
        {
            float idx = floor(u_screenWidth * vv2_Texcoord.x);
            int factor = (mod(idx, 2.0) == 0.0 ? 0 : 1);
            
            coordx = (factor == 0 ? 0.5 * vv2_Texcoord.x : 0.5 * vv2_Texcoord.x + 0.5);
        }
        
        highp vec2 coord = vec2(coordx, vv2_Texcoord.y);
        gl_FragColor = vec4(texture2D(us2_SamplerX, coord).rgb, 1);
    }
);

const char *IJK_GLES2_getFragmentShader_rgb()
{
    return g_shader;
}
