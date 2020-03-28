#pragma once
#include <QMatrix4x4>

#include <QOpenGLShaderProgram>

namespace SGE
{

    class Shader
    {
    public:
        Shader();

        QOpenGLShaderProgram simpleShader;
        QOpenGLShaderProgram phongShader;
        QOpenGLShaderProgram lightShader;

        bool loadShader();

    private:
        std::map<QString, QOpenGLShaderProgram *> shaders;
    };

} // namespace SGE
