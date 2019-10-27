#include "Engine/mesh.h"

Mesh::Mesh(QVector<Vertex> vertices,
           QVector<GLuint> indices)
		   : vertices(vertices),
			 indices(indices),
			 ibo(QOpenGLBuffer::IndexBuffer)
{
}

Mesh::Mesh(const Mesh &mesh)
	: vertices(mesh.vertices),
	  indices(mesh.indices),
	  ibo(QOpenGLBuffer::IndexBuffer)
{
}

Mesh::~Mesh()
{
}

Mesh &Mesh::operator=(const Mesh &mesh)
{
    this->vertices = mesh.vertices;
    this->indices = mesh.indices;

    return *this;
}

void Mesh::Draw(QOpenGLShaderProgram &program,
				const QMatrix4x4 *projection,
				const QMatrix4x4 *view,
				const QMatrix4x4 &model)
{
    // Uniform value from phong shader, i dont know
    // how can make uniform value for separate shaders
	program.bind();
    program.setUniformValue("projection", *projection);
    program.setUniformValue("view", *view);
    program.setUniformValue("model", model);
    program.setUniformValue("objectColor", QVector3D(0.0, 0.5, 0.75));
    program.setUniformValue("lightColor", QVector3D(1.0, 1.0, 1.0));
    program.setUniformValue("lightPos", QVector3D(1.0f, 1.0f, 2.0f));
    program.setUniformValue("Kd", QVector3D(1.0f, 1.0f, 1.0f));
    program.setUniformValue("Ld", QVector3D(1.0f, 1.0f, 1.0f));

    // Draw mesh
    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    vao.release();
    program.release();
}

void Mesh::setupMesh()
{
    // initializeOpenGL... for
    // gl... functions
    initializeOpenGLFunctions();

    vao.create();
    vbo.create();
    ibo.create();

    vao.bind();
    vbo.bind();
    vbo.allocate(vertices.data(),
                 vertices.length() * int(sizeof(Vertex)));

    ibo.bind();
    ibo.allocate(indices.data(),
                 indices.length() * int(sizeof(GLuint)));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    // This vars for more readable code
    void *offsetof_Normal = reinterpret_cast<void*>(
                            offsetof(Vertex, Normal));
    void *offsetof_texCoord = reinterpret_cast<void*>(
                            offsetof(Vertex, texCoord));

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), offsetof_Normal);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), offsetof_texCoord);
    glEnableVertexAttribArray(2);

    vbo.release();
    vao.release();
}
