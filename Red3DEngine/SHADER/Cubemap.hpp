#pragma once

#include "Header.hpp"

static const char * Equirectangular_To_Cubemap_VERTEX = SHADER(
            layout (location = 0) in vec3 aPos;

            out vec3 WorldPos;

            uniform mat4 projection;
            uniform mat4 view;

            void main()
            {
                WorldPos = aPos;
                gl_Position =  projection * view * vec4(WorldPos, 1.0);
            }
            );


static const char * Equirectangular_To_Cubemap_FRAGMENT = SHADER(
            out vec4 FragColor;
            in vec3 WorldPos;

            uniform sampler2D equirectangularMap;

            const vec2 invAtan = vec2(0.1591, 0.3183);
            vec2 SampleSphericalMap(vec3 v)
            {
                vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
                uv *= invAtan;
                uv += 0.5;
                return uv;
            }

            void main()
            {
                vec2 uv = SampleSphericalMap(normalize(WorldPos));
                vec3 color = texture(equirectangularMap, uv).rgb;

                FragColor = vec4(color, 1.0);
            }
            );


