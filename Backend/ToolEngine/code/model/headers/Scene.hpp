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
#include "EntityDLL.hpp"
#include <vector>
#include <memory>
#include <string>
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr
namespace toolsDLL
{
    class Scene {
    public:
        Scene()
        {
            std::string str = "../../assets/stanford-bunny.obj";

            // Tamaño de la cadena en bytes
            std::size_t sizeInBytes = str.size() * sizeof(char);
            entities = std::make_shared<std::vector<std::shared_ptr<EntityDLL>>>();
            std::string path1 = "../../assets/stanford-bunny.obj";
            std::shared_ptr<EntityDLL> entity = std::make_shared<EntityDLL>("modelOne", path1,
                glm::vec3(0.f, 0.f, -2.75f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
            std::string path2 = "../../assets/stanford-bunny.obj";

            std::shared_ptr<EntityDLL> entity2 = std::make_shared<EntityDLL>("modelTwo", path2,
                glm::vec3(0.f, 0.f, -2.75f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));

            //std::shared_ptr<EntityDLL> entity3 = std::make_shared<EntityDLL>("modelThree", path2,
            //    glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));

            addEntity(entity);
            addEntity(entity2);
            //addEntity(*entity3);

        }
        ~Scene() = default;

        void addEntity(std::shared_ptr<EntityDLL> entity)
        {
            entities->push_back(entity);
        }
        //void removeEntity(const EntityDLL& entity);

        //EntityDLL* getEntityById(int id);
        std::shared_ptr< std::vector<std::shared_ptr<EntityDLL>>> getEntities()
        { return entities; }


    private:
        std::shared_ptr< std::vector<std::shared_ptr<EntityDLL>>> entities;
    };
}