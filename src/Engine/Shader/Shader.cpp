#include "Shader.h"

SGE::Shader::Shader()
    : shaders({{"simpleshader", &simpleShader},
               {"phongshader", &phongShader},
               {"lightshader", &lightShader}}) // initializer list for map
{
}

bool SGE::Shader::loadShader()
{
    // load all shaders using map container
    for (auto &shader : shaders)
    {
        QString path_to_vertShader =
            ":/" + shader.first + "/" + shader.first + ".vert";
        QString path_to_fragShader =
            ":/" + shader.first + "/" + shader.first + ".frag";

        if (!shader.second->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                                    path_to_vertShader))
            return false;

        if (!shader.second->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                                    path_to_fragShader))
            return false;

        if (!shader.second->link()) return false;
        if (!shader.second->bind()) return false;
    }

    return true;
}
