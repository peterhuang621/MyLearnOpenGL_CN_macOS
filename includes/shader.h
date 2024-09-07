#ifndef SHADER_H
#define SHADER_H

#include <OpenGL/gl3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>
using namespace std;

class Shader
{
public:
    unsigned int ID;
    Shader(const char *vertexPath, const char *fragmentPath);
    void use();
    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;

private:
    void checkCompileErrors(unsigned int shader, string type);
};

#endif