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

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "RendererExample.hpp"

using namespace glm;
using namespace std;

namespace esne
{
    
    const string RendererExample::vertex_shader_code =

        "#version 330\n"
        ""
        "uniform mat4 model_view_matrix;"
        "uniform mat4 projection_matrix;"
        ""
        "layout (location = 0) in vec3 vertex_coordinates;"
        "layout (location = 1) in vec3 vertex_color;"
        ""
        "out vec3 front_color;"
        ""
        "void main()"
        "{"
        "   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);"
        "   front_color = vertex_color;"
        "}";

    const string RendererExample::fragment_shader_code =

        "#version 330\n"
        ""
        "in  vec3    front_color;"
        "out vec4 fragment_color;"
        ""
        "void main()"
        "{"
        "    fragment_color = vec4(front_color, 1.0);"
        "}";

    
    RendererExample::~RendererExample()
    {
        glDeleteVertexArrays (1, &vao_id);
        glDeleteBuffers      (VBO_COUNT, vbo_ids);
        glDeleteProgram      (shader_program_id);
    }

    void RendererExample::initialize ()
    {


        GLenum glad_initialization =  gladLoadGL ();

        assert(glad_initialization != 0);

        // Se establece la configuración básica:

        glEnable     (GL_CULL_FACE );
        glEnable     (GL_DEPTH_TEST);
        glClearColor (.1f, .1f, .1f, 1.f);

        // Se compilan y se activan los shaders:

        shader_program_id = compile_shaders ();

        glUseProgram (shader_program_id);

        model_view_matrix_id = glGetUniformLocation (shader_program_id, "model_view_matrix");
        projection_matrix_id = glGetUniformLocation (shader_program_id, "projection_matrix");

        load_mesh();

        rotationAngles = vec3(0);
    }

    void RendererExample::resize (int new_viewport_width, int new_viewport_height)
    {
        glm::mat4 projection_matrix = glm::perspective (20.f, GLfloat(new_viewport_width) / new_viewport_height, 1.f, 5000.f);

        glUniformMatrix4fv (projection_matrix_id, 1, GL_FALSE, glm::value_ptr(projection_matrix));

        glViewport (0, 0, new_viewport_width, new_viewport_height);
    }

    void RendererExample::render ()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (const auto& entity : entities)
        {
            glm::mat4 model_view_matrix(1);
            model_view_matrix = glm::scale(model_view_matrix, glm::vec3(entity.entityBackEnd->getTransform().scale.x, entity.entityBackEnd->getTransform().scale.y,
                entity.entityBackEnd->getTransform().scale.z));

            model_view_matrix = glm::translate(model_view_matrix, glm::vec3(entity.entityBackEnd->getTransform().position.x, 
                entity.entityBackEnd->getTransform().position.y, entity.entityBackEnd->getTransform().position.z));
            model_view_matrix = glm::rotate(model_view_matrix, entity.entityBackEnd->getTransform().rotation.x, glm::vec3(1.f, 0.f, 0.f));
            model_view_matrix = glm::rotate(model_view_matrix, entity.entityBackEnd->getTransform().rotation.y, glm::vec3(0.f, 1.f, 0.f));
            model_view_matrix = glm::rotate(model_view_matrix, entity.entityBackEnd->getTransform().rotation.z , glm::vec3(0.f, 0.f, 1.f));

            glUniformMatrix4fv(projection_matrix_id* model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));

            glBindVertexArray(entity.getVAOID());
            glDrawElements(GL_TRIANGLES, entity.getNumberOfIndices(), GL_UNSIGNED_SHORT, 0);
        }
    }

    GLuint RendererExample::compile_shaders ()
    {
        GLint succeeded = GL_FALSE;

        // Se crean objetos para los shaders:

        GLuint   vertex_shader_id = glCreateShader (GL_VERTEX_SHADER  );
        GLuint fragment_shader_id = glCreateShader (GL_FRAGMENT_SHADER);

        // Se carga el código de los shaders:

        const char *   vertex_shaders_code[] = {          vertex_shader_code.c_str () };
        const char * fragment_shaders_code[] = {        fragment_shader_code.c_str () };
        const GLint    vertex_shaders_size[] = { (GLint)  vertex_shader_code.size  () };
        const GLint  fragment_shaders_size[] = { (GLint)fragment_shader_code.size  () };

        glShaderSource  (  vertex_shader_id, 1,   vertex_shaders_code,   vertex_shaders_size);
        glShaderSource  (fragment_shader_id, 1, fragment_shaders_code, fragment_shaders_size);

        // Se compilan los shaders:

        glCompileShader (  vertex_shader_id);
        glCompileShader (fragment_shader_id);

        // Se comprueba que si la compilación ha tenido éxito:

        glGetShaderiv   (  vertex_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) show_compilation_error (  vertex_shader_id);

        glGetShaderiv   (fragment_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) show_compilation_error (fragment_shader_id);

        // Se crea un objeto para un programa:

        GLuint program_id = glCreateProgram ();

        // Se cargan los shaders compilados en el programa:

        glAttachShader  (program_id,   vertex_shader_id);
        glAttachShader  (program_id, fragment_shader_id);

        // Se linkan los shaders:

        glLinkProgram   (program_id);

        // Se comprueba si el linkage ha tenido éxito:

        glGetProgramiv  (program_id, GL_LINK_STATUS, &succeeded);
        if (!succeeded) show_linkage_error (program_id);

        // Se liberan los shaders compilados una vez se han linkado:

        glDeleteShader (  vertex_shader_id);
        glDeleteShader (fragment_shader_id);

        return (program_id);
    }

    void RendererExample::show_compilation_error (GLuint shader_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetShaderInfoLog (shader_id, info_log_length, NULL, &info_log.front ());

        cerr << info_log.c_str () << endl;

        #ifdef _MSC_VER
            //OutputDebugStringA (info_log.c_str ());
        #endif

        assert(false);
    }

    void RendererExample::show_linkage_error (GLuint program_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetProgramiv (program_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetProgramInfoLog (program_id, info_log_length, NULL, &info_log.front ());

        cerr << info_log.c_str () << endl;

        #ifdef _MSC_VER
            //OutputDebugStringA (info_log.c_str ());
        #endif

        assert(false);
    }

    void RendererExample::load_mesh ()
    {
        Assimp::Importer importer;

        for ( auto& entity : entities)
        {
            //"entity.entityBackEnd->getModel()->getPath()"
            string path = entity.entityBackEnd->getModel()->getPath();
            const aiScene* scene = importer.ReadFile(entity.entityBackEnd->getModel()->getPath(), aiProcessPreset_TargetRealtime_Quality);
            assert(scene != nullptr);
            assert(scene->mNumMeshes > 0);

            for (unsigned int mesh_id = 0; mesh_id < scene->mNumMeshes; ++mesh_id)
            {
                const aiMesh* mesh = scene->mMeshes[mesh_id];

                vector<GLuint> vbo_id_set(3);
                glGenBuffers(3, vbo_id_set.data());

                GLuint vao_id;
                glGenVertexArrays(1, &vao_id);

                glBindVertexArray(vao_id);

                vector<GLfloat> coordinates;
                vector<GLfloat> colors;
                vector<GLushort> indices;

                for (unsigned int vertex_id = 0; vertex_id < mesh->mNumVertices; ++vertex_id)
                {
                    const aiVector3D* position = &mesh->mVertices[vertex_id];
                    coordinates.push_back(position->x);
                    coordinates.push_back(position->y);
                    coordinates.push_back(position->z);

                    vec3 color = random_color();
                    colors.push_back(color.r);
                    colors.push_back(color.g);
                    colors.push_back(color.b);
                }

                for (unsigned int face_id = 0; face_id < mesh->mNumFaces; ++face_id)
                {
                    const aiFace* face = &mesh->mFaces[face_id];
                    assert(face->mNumIndices == 3);
                    indices.push_back(face->mIndices[0]);
                    indices.push_back(face->mIndices[1]);
                    indices.push_back(face->mIndices[2]);
                }

                glBindBuffer(GL_ARRAY_BUFFER, vbo_id_set[0]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * coordinates.size(), &coordinates[0], GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                glEnableVertexAttribArray(0);

                glBindBuffer(GL_ARRAY_BUFFER, vbo_id_set[1]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colors.size(), &colors[0], GL_STATIC_DRAW);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                glEnableVertexAttribArray(1);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id_set[2]);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), &indices[0], GL_STATIC_DRAW);

                //entities.emplace_back(vao_id, vbo_id_set, static_cast<GLsizei>(indices.size()));
                entity.initialize(vao_id, vbo_id_set, static_cast<GLsizei>(indices.size()));
            }
        }
    }

    /** Genera un color al azar en el que los componentes de color están en el rango 0.0f - 1.0f.
      */
    vec3 RendererExample::random_color ()
    {
        return vec3
        (
            float(rand ()) / float(RAND_MAX),
            float(rand ()) / float(RAND_MAX),
            float(rand ()) / float(RAND_MAX)
        );
    }

}
