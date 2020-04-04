#include "Mesh.h"

#include <QOpenGLShaderProgram>

SGE::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
    : vertices(vertices), indices(indices), meshColor(0.f, 0.f, 0.f),
      vao(new QOpenGLVertexArrayObject), ibo(QOpenGLBuffer::IndexBuffer),
      func(new QOpenGLFunctions)
{
}


void SGE::Mesh::draw(QOpenGLShaderProgram &program,
                     std::shared_ptr<const QMatrix4x4> projection,
                     std::shared_ptr<const QMatrix4x4> view,
                     std::shared_ptr<const QMatrix4x4> model)
{
    // Uniform value from phong shader, i dont know
    // how can make uniform value for separate shaders
    program.bind();
    program.setUniformValue("projection", *projection);
    program.setUniformValue("view", *view);
    program.setUniformValue("model", *model);
    program.setUniformValue("objectColor", meshColor);
    program.setUniformValue("lightColor", QVector3D(1.0, 1.0, 1.0));
    program.setUniformValue("lightPos", QVector3D(1.0f, 1.0f, 2.0f));
    program.setUniformValue("Kd", QVector3D(1.0f, 1.0f, 1.0f));
    program.setUniformValue("Ld", QVector3D(1.0f, 1.0f, 1.0f));

    vao->bind();
    // Draw mesh
    func->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,
                         nullptr);
}


void SGE::Mesh::setupMesh()
{
    // initializeOpenGL... for
    // gl... functions
    func->initializeOpenGLFunctions();

    vao->create();
    vbo.create();
    ibo.create();

    vao->bind();
    vbo.bind();
    vbo.allocate(vertices.data(), vertices.size() * sizeof(SGE::Vertex));

    ibo.bind();
    ibo.allocate(indices.data(), indices.size() * sizeof(GLuint));

    func->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SGE::Vertex),
                                nullptr);
    func->glEnableVertexAttribArray(0);

    // This vars for more readable code
    void *offsetof_Normal =
        reinterpret_cast<void *>(offsetof(SGE::Vertex, Normal));
    void *offsetof_texCoord =
        reinterpret_cast<void *>(offsetof(SGE::Vertex, texCoord));

    func->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SGE::Vertex),
                                offsetof_Normal);
    func->glEnableVertexAttribArray(1);

    func->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SGE::Vertex),
                                offsetof_texCoord);
    func->glEnableVertexAttribArray(2);
}
