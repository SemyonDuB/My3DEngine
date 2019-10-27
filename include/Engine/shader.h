#pragma once
#include <QMatrix4x4>
#include <QMap>

#include <QOpenGLShaderProgram>

class Shader
{
public:
    Shader();

    QOpenGLShaderProgram simpleShader;
    QOpenGLShaderProgram phongShader;
    QOpenGLShaderProgram lightShader;

	void shaderBind(const QString &shader) const;
	void shaderUnbind(const QString &shader) const;

    bool loadShader();
private:
    QMap<QString, QOpenGLShaderProgram*> shaders;
};

