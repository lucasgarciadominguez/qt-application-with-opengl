#pragma once
/**********************************************************************
*Project           : First Practice Middleware
*
*Author : Lucas García
*
*
*Purpose : Connects Backend Tool Engine (.dll) to a QT scene loader called MiddlewarePracticaFinal(.exe)
*
**********************************************************************/

#include "Scene.hpp"
#include <functional>
//#include <LuaState.h>

//using namespace lua;

namespace toolsDLL
{

    class Controller
    {
        Scene* scene;

    public:

        Controller(Scene& given_scene) : scene(&given_scene)
        {
            //lua::State state;

        }

        ~Controller() = default;
        //void clear();

    };

}