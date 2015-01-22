#ifndef MESH_H
#define MESH_H

#include <string>
#include "model.h"
#include "glew.h"

class Mesh
{
public:
    Mesh(const std::string& fileName);
	Mesh(Model& model);
	void draw();
	virtual ~Mesh();
protected:
private:
    GLuint m_vao, m_vbo, m_ebo;
    Model m_model;
};

#endif
