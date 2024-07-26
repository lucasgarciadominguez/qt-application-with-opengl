/// @copyright ...
/// @licence ...
/// @author Ángel

#pragma once

#include "../../../code/API.hpp"
#include "Canvas.hpp"

namespace photoshop2
{

    class API Painter
    {
        Canvas * canvas;

    public:

        Painter(Canvas & given_canvas) : canvas(&given_canvas)
        {
        }

        void clear();

    };

}
