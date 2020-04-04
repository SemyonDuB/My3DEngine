#pragma once
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
