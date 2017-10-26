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
                gl_Position = vec4(position, 1.0f);
                TexCoords = texCoords.xy;
            }
            );

static const char * s_FRAGMENT = SHADER(
            in vec2 TexCoords;
            out vec4 color;

            uniform sampler2D screenTexture;

            void main()
            {
                vec4 c = texture(screenTexture, TexCoords);

                float t = c.x;
                c.x = c.y;
                c.y = t;

                color = c;
            }
            );
