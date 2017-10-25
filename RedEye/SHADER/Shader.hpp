#include "Header.hpp"

static const char * test_VERTEX = SHADER(
            layout (location = 0) in vec3 aPos;

            void main()
            {
                gl_Position = vec4(aPos * 1.8,1.0);
            }

            );

static const char * test_FRAGMENT = SHADER(
            out vec4 color;

            void main()
            {
                color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
            }
            );
