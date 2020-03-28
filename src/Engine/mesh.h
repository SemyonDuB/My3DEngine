#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QSharedPointer>
#include <memory>


#include <QVector>
#include <QVector2D>
#include <QVector3D>

class QOpenGLShaderProgram;

namespace SGE
{
    struct Vertex
    {
        QVector3D pos;
        QVector3D Normal;
        QVector2D texCoord;
    };


    struct Texture
    {
        std::size_t id;
        std::string type;
    };


    class Mesh
    {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);

        void draw(QOpenGLShaderProgram &program,
                  std::shared_ptr<const QMatrix4x4> projection,
                  std::shared_ptr<const QMatrix4x4> view,
                  std::shared_ptr<const QMatrix4x4> model);

        void setupMesh(); // initialize VBO, VAO, IBO

        std::vector<Vertex> getVertices() const { return vertices; }

        std::vector<GLuint> getIndices() const { return indices; }

        QVector3D getMeshColor() const { return meshColor; }

        void addVert(const Vertex &vert) { vertices.push_back(vert); }

        void addTexture(const SGE::Texture &tex) { textures.push_back(tex); }

        void addIndex(const GLuint &index) { indices.push_back(index); }

        void setColor(const QVector3D &color) { meshColor = color; }

    private:
        std::vector<Vertex> vertices;
        std::vector<Texture> textures;
        std::vector<GLuint> indices;

        QVector3D meshColor;

        std::shared_ptr<QOpenGLVertexArrayObject> vao;
        QOpenGLBuffer vbo;
        QOpenGLBuffer ibo;

        std::shared_ptr<QOpenGLFunctions> func;
    };
} // namespace SGE
