#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "glm.hpp"


class Model
{
public:
    Model() {};
    Model(Model& model)
    {
        this->positions = model.positions;
        this->texCoords = model.texCoords;
        this->normals = model.normals;
        this->indices = model.indices;
    };
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
private:
    void CalcNormals();
};

#endif // MODEL_H
