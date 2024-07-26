/// @copyright ...
/// @licence ...
/// @author Ángel

#include "Painter.hpp"

namespace photoshop2
{

    void Painter::clear()
    {
        const unsigned size = canvas->get_width() * canvas->get_height();
        const Color    color{ 0, 0, 0, 255 };

        for (unsigned offset = 0; offset < size; ++offset)
        {
            canvas->set_pixel (offset, color);
        }
    }

}
