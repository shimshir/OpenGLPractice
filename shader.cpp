#include "shader.h"
#include <fstream>
#include <iostream>

void Shader::add(ShaderType type, std::string shaderFilePath)
{
    m_shaderFilePaths[type].push_back(shaderFilePath);
}

void Shader::remove(ShaderType type, std::string shaderFilePath)
{
    int index = 0;
    for (std::string& shaderPath : m_shaderFilePaths[type])
    {
        if (shaderFilePath == shaderPath)
            remove(type, index);
        index++;
    }
}

void Shader::remove(ShaderType type, int index)
{
    m_shaderFilePaths[type].erase(m_shaderFilePaths[type].begin() + index);
}

void Shader::createAndCompile()
{
    load();
    std::map<ShaderType, std::vector<std::string>>::iterator iter;

    for (iter = m_shaderSources.begin(); iter != m_shaderSources.end(); ++iter)
    {
        GLuint shader = glCreateShader(iter->first);
        m_shaders.push_back(shader);

        char** sources = new char*[(iter->second).size()];
        for (unsigned i = 0; i < (iter->second).size(); i++) {
            sources[i] = (char*)(iter->second[i]).c_str();
        }

        glShaderSource(shader, 1, sources, &(m_shaderSourcesLengths[iter->first][0]));
        glCompileShader(shader);
        glAttachShader(m_program, shader);

        for (unsigned i = 0; i < (iter->second).size(); i++) {
            delete sources[i];
        }
        delete sources;
    }
}

void Shader::linkAndUse()
{
    glLinkProgram(m_program);
    glUseProgram(m_program);
}

Shader::~Shader()
{
    glDeleteProgram(m_program);
    for (GLuint& shader : m_shaders)
        glDeleteShader(shader);
}

void Shader::load()
{
    std::map<ShaderType, std::vector<std::string>>::iterator iter;

    for (iter = m_shaderFilePaths.begin(); iter != m_shaderFilePaths.end(); ++iter)
    {
        for (std::string& shaderPath : iter->second)
        {
            m_shaderSources[iter->first].push_back(readFile(shaderPath));
            m_shaderSourcesLengths[iter->first].push_back(readFile(shaderPath).length());
        }
    }
}

std::string Shader::readFile(std::string& filePath)
{
    std::string line, shaderSource;

    std::ifstream shaderFile;
    shaderFile.open(filePath);
    if (shaderFile.is_open())
    {
        while (getline(shaderFile, line))
            shaderSource.append(line + "\n");
        shaderFile.close();
    }
    return shaderSource;
}
