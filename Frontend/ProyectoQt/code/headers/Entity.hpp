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

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include <memory>
#include "EntityDLL.hpp"

using glm::vec3;
using std::vector;
using namespace toolsDLL;
class Entity
{
public:
    Entity(std::shared_ptr<toolsDLL::EntityDLL> entityDLL)
        : entityBackEnd(entityDLL)
    {
        //position.x = 0;
        //position.y = 0;
        //position.z = -2.75f;
        //entityBackEnd->setTransform(glm::vec3(0,0,-2.75), glm::vec3(), glm::vec3());

        //scale.x = 1;
        //scale.y = 1;
        //scale.z = 1;
    }
    void initialize(GLuint vao, const vector<GLuint>& vbos, GLsizei indicesCount)
    {
        vaoID = vao;
        vboIDs = vbos;
        numberOfIndices = indicesCount;
    }

    GLuint getVAOID() const { return vaoID; }
    const vector<GLuint>& getVBOIDs() const { return vboIDs; }
    GLsizei getNumberOfIndices() const { return numberOfIndices; }

private:
    GLuint vaoID;
    vector<GLuint> vboIDs;
    GLsizei numberOfIndices;

public:
    std::shared_ptr<toolsDLL::EntityDLL> entityBackEnd;
    //vec3    position;
    //vec3    rotationAngles;
    //vec3    scale;

};