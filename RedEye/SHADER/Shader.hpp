#include "Header.hpp"

static const char * test_VERTEX = SHADER(
            layout (location = 0) in vec3 aPos;

            uniform mat4 projection;
            uniform mat4 view;
            uniform mat4 model;

            void main()
            {
                vec3 WorldPos = vec3(model * vec4(aPos, 1.0));
                gl_Position =  projection * view * vec4(WorldPos, 1.0);
            }

            );

static const char * test_FRAGMENT = SHADER(
            out vec4 color;

            void main()
            {
                color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
            }
            );









static const char * s_VERTEX = SHADER(
            layout (location = 0) in vec3 position;
            layout (location = 1) in vec3 texCoords;

            out vec2 TexCoords;

            void main()
            {
                gl_Position = vec4(position * 1.0, 1.0f);
                TexCoords = texCoords.xy;
            }
            );

static const char * s_FRAGMENT = SHADER(
            in vec2 TexCoords;
            out vec4 color;

            uniform sampler2D screenTexture;

            void main()
            {
                //vec4 c = texture(screenTexture, TexCoords);


                vec2 m_outUV = TexCoords;

                float fstep=0.01;
                vec4 sample0=texture(screenTexture,vec2(m_outUV.x-fstep,m_outUV.y-fstep));
                vec4 sample1=texture(screenTexture,vec2(m_outUV.x+fstep,m_outUV.y-fstep));
                vec4 sample2=texture(screenTexture,vec2(m_outUV.x+fstep,m_outUV.y+fstep));
                vec4 sample3=texture(screenTexture,vec2(m_outUV.x-fstep,m_outUV.y+fstep));
                vec4 c = (sample0+sample1+sample2+sample3) / 4.0;


                color = c;
            }
            );
