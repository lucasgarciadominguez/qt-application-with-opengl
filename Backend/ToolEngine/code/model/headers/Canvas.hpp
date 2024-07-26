/// @copyright ...
/// @licence ...
/// @author Ángel

#pragma once

#include "Color.hpp"
#include <vector>

namespace photoshop2
{

    class Canvas
    {

        unsigned width;
        unsigned height;

        std::vector< Color > buffer;

    public:

        Canvas(unsigned given_width, unsigned given_height)
        :
            width(given_width),
            height(given_height),
            buffer(given_width* given_height)
        {

        }

        unsigned get_width() const
        {
            return width;
        }

        unsigned get_height() const
        {
            return height;
        }

        const Color * get_pixel(int x, int y) const
        {
            if (x >= 0 && x < int(width) && y >= 0 && y < int(height))
            {
                return &buffer[y * width + x];
            }
            else
                return nullptr;
        }

        void set_pixel(int x, int y, const Color& color)
        {
            if (x >= 0 && x < int(width) && y >= 0 && y < int(height))
            {
                buffer[y * width + x] = color;
            }
        }

        void set_pixel(unsigned offset, const Color & color)
        {
            if (offset < width * height)
            {
                buffer[offset] = color;
            }
        }

    };


}
