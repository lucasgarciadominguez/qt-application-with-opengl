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

#include "Renderer.hpp"
#include "Entity.hpp"
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

using glm::vec3;
using std::string;

namespace esne
{

    /** Esta clase hace uso de OpenGL para dibujar una escena sencilla en un framebuffer de OpenGL.
      * El código es genérico y no tiene dependencias con Qt, por lo que es fácilmente reusable en
      * otros proyectos.
      * La clase implementa la interfaz Renderer, de modo que puede ser asignado a un OpenGLWidget.
      * Dicho widget se encargará de invocar a los métodos reimplementados cuando sea oportuno.
      */
    class EntityDLL;
    class RendererExample : public Renderer
    {
    private:

        enum
        {
            COORDINATES_VBO,
            COLORS_VBO,
            INDICES_EBO,
            VBO_COUNT
        };

        static const string   vertex_shader_code;
        static const string fragment_shader_code;

        GLuint  shader_program_id;

        GLuint  vbo_ids[VBO_COUNT];
        GLuint  vao_id;

        GLsizei number_of_indices;

        GLint   model_view_matrix_id;
        GLint   projection_matrix_id;

        vec3    position;
        vec3    rotationAngles;
        vec3    scale;



    public:

        ~RendererExample();

        void initialize () override;
        void resize     (int new_viewport_width, int new_viewport_height) override;
        void render     () override;
        vector<Entity> entities;
        //vector<EntityDLL> entitiesDLL;

    public:

        void setPositionX(float newValue, int indexEntity) {entities[indexEntity].entityBackEnd
            ->setTransform(glm::vec3(newValue, entities[indexEntity].entityBackEnd->getTransform().position.y, entities[indexEntity].entityBackEnd->getTransform().position.z),
                entities[indexEntity].entityBackEnd->getTransform().rotation,
                entities[indexEntity].entityBackEnd->getTransform().scale) ; 
        }

        void setPositionY(float newValue, int indexEntity) {
            entities[indexEntity].entityBackEnd
                ->setTransform(glm::vec3(entities[indexEntity].entityBackEnd->getTransform().position.x, newValue, entities[indexEntity].entityBackEnd->getTransform().position.z),
                    entities[indexEntity].entityBackEnd->getTransform().rotation,
                    entities[indexEntity].entityBackEnd->getTransform().scale);
        }
        void setPositionZ(float newValue, int indexEntity) {
            entities[indexEntity].entityBackEnd
                ->setTransform(glm::vec3(entities[indexEntity].entityBackEnd->getTransform().position.x, entities[indexEntity].entityBackEnd->getTransform().position.y, newValue),
                    entities[indexEntity].entityBackEnd->getTransform().rotation,
                    entities[indexEntity].entityBackEnd->getTransform().scale);
        }

        void setRotationX(float newAngle, int indexEntity) {
            entities[indexEntity].entityBackEnd
                ->setTransform(
                    entities[indexEntity].entityBackEnd->getTransform().position,
                    glm::vec3(newAngle,entities[indexEntity].entityBackEnd->getTransform().position.y, entities[indexEntity].entityBackEnd->getTransform().position.z),
                    entities[indexEntity].entityBackEnd->getTransform().scale);
        }
        void setRotationY (float newAngle, int indexEntity) {
            entities[indexEntity].entityBackEnd
                ->setTransform(
                    entities[indexEntity].entityBackEnd->getTransform().position,
                    glm::vec3(entities[indexEntity].entityBackEnd->getTransform().position.x, newAngle, entities[indexEntity].entityBackEnd->getTransform().position.z),
                    entities[indexEntity].entityBackEnd->getTransform().scale);
        }
        void setRotationZ (float newAngle, int indexEntity) 
        {
            entities[indexEntity].entityBackEnd
                ->setTransform(
                    entities[indexEntity].entityBackEnd->getTransform().position,
                    glm::vec3(entities[indexEntity].entityBackEnd->getTransform().position.x, entities[indexEntity].entityBackEnd->getTransform().position.y, newAngle),
                    entities[indexEntity].entityBackEnd->getTransform().scale);
        
        }

        void setScaleX(float newValue, int indexEntity) 
        {
            entities[indexEntity].entityBackEnd
                ->setTransform(
                    entities[indexEntity].entityBackEnd->getTransform().position,
                    entities[indexEntity].entityBackEnd->getTransform().rotation,
                glm::vec3(newValue,entities[indexEntity].entityBackEnd->getTransform().scale.y, entities[indexEntity].entityBackEnd->getTransform().scale.z));
        }
        void setScaleY(float newValue, int indexEntity) 
        {
            entities[indexEntity].entityBackEnd
                ->setTransform(
                    entities[indexEntity].entityBackEnd->getTransform().position,
                    entities[indexEntity].entityBackEnd->getTransform().rotation,
                    glm::vec3( entities[indexEntity].entityBackEnd->getTransform().scale.x, newValue, entities[indexEntity].entityBackEnd->getTransform().scale.z));
        }
        void setScaleZ(float newValue,int indexEntity) 
        {
            entities[indexEntity].entityBackEnd
                ->setTransform(
                    entities[indexEntity].entityBackEnd->getTransform().position,
                    entities[indexEntity].entityBackEnd->getTransform().rotation,
                    glm::vec3(entities[indexEntity].entityBackEnd->getTransform().scale.x,entities[indexEntity].entityBackEnd->getTransform().scale.y, newValue));
        }

    private:

        GLuint compile_shaders        ();
        void   show_compilation_error (GLuint  shader_id);
        void   show_linkage_error     (GLuint program_id);
        void load_mesh();
        vec3   random_color           ();

    };

}
