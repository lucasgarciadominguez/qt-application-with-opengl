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

    class EntityDLL {
    public:
        EntityDLL(const std::string& newname,std::string& newFilepath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :name(newname)
        {
            //name = newname;
            model = std::make_shared<Model>(newFilepath, position, rotation, scale);

        }
        ~EntityDLL() = default;

        void setTransform(glm::vec3 newposition, glm::vec3 newrotation, glm::vec3 newscale)
        {
            //model->transform->position = newposition;
            //transform->rotation = newrotation;
            //transform->scale = newscale;
            model->setTransform(newposition,newrotation,newscale);
        }
        Transform getTransform() 
        {
            return *model->transform.get();
        };

        //void setModel(const Model& model);
        Model* getModel() const
        {
            return model.get();
        }


    private:
        std::shared_ptr<Model> model;
    public:
        const std::string name;
    };
}