/**********************************************************************
*Project           : First Practice Middleware
*
*Author : Lucas García
*
*
*Purpose : Connects Backend Tool Engine (.dll) to a QT scene loader called MiddlewarePracticaFinal(.exe)
*
**********************************************************************/

#pragma once
#include <string>
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include "Node.hpp"
#include <memory>
namespace toolsDLL
{
    class Model : public Node {
    public:
        Model(std::string& newFilepath, glm::vec3 newposition, glm::vec3 newrotation, glm::vec3 newscale)
            : filepath(newFilepath)
        {
            transform = std::make_shared<Transform>(newposition, newrotation, newscale);
        }
        ~Model() = default;

        std::string getPath()
        {
            return filepath;
        }


    private:
        std::string filepath;
    };
}