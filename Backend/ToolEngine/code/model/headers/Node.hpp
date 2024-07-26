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

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <memory>
#include <string>
#include "Model.hpp"
namespace toolsDLL
{
    class Transform {
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        Transform(glm::vec3 newposition, glm::vec3 newrotation, glm::vec3 newscale)
            : position(newposition), rotation(newrotation), scale(newscale) {}
    };

    class Node {
    public:
        //Node(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) 
        //{
        //    transform = std::make_shared<Transform>(position, rotation, scale);
        //}
        ~Node() = default;

        void setTransform(glm::vec3 newposition, glm::vec3 newrotation, glm::vec3 newscale)
        {
            transform->position = newposition;
            transform->rotation = newrotation;
            transform->scale = newscale;
        }
        Transform* getTransform() { return transform.get(); }

        //void setModel(const Model& model);
        //Model* getModel() const;


    private:
    public:
        std::shared_ptr < Transform > transform;
    };
}