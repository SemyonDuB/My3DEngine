#include "import.h"
#include "scene.h"


SGE::Import::Import(std::string FileLoc, Scene &sceneObj) : m_File(FileLoc)
{
    accTransform.setToIdentity();

    loadScene();
    nodeHandler(scene->mRootNode, sceneObj, accTransform);
}


bool SGE::Import::loadScene()
{
    scene =
        importer.ReadFile(m_File, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene)
    {
        qDebug() << importer.GetErrorString();
        return false;
    }

    return true;
}


QMatrix4x4 translateAiMatrix4x4(const aiMatrix4x4 &tran)
{
    QMatrix4x4 matrix;
    matrix.setRow(0, QVector4D(tran.a1, tran.a2, tran.a3, tran.a4));
    matrix.setRow(1, QVector4D(tran.b1, tran.b2, tran.b3, tran.b4));
    matrix.setRow(2, QVector4D(tran.c1, tran.c2, tran.c3, tran.c4));
    matrix.setRow(3, QVector4D(tran.d1, tran.d2, tran.d3, tran.d4));

    return matrix;
}


void SGE::Import::nodeHandler(const aiNode *node, Scene &sceneObj,
                              QMatrix4x4 &accTransform)
{
    // Recursive func!

    // call translateAiMatrix4x4 func for translate Asimp aiMatrix4x4
    // to Qt QMatrix4x4
    QMatrix4x4 mTransformation = translateAiMatrix4x4(node->mTransformation);

    // For global coord
    QMatrix4x4 transform = mTransformation * accTransform;

    if (node->mNumMeshes > 0)
    {
        Object obj;

        // Copy meshes
        for (std::size_t n = 0; n < node->mNumMeshes; n++)
        {
            const aiMesh *mesh = scene->mMeshes[node->mMeshes[n]];
            obj.addMesh(meshHandler(mesh));
        }

        obj.setObjLocation(transform);

        // set projection ptr and view ptr for obj from scene
        obj.setupObj(sceneObj.getProj(), sceneObj.getView());
        sceneObj.addObject(obj);
    }
    for (std::size_t i = 0; i < node->mNumChildren; i++)
    {
        nodeHandler(node->mChildren[i], sceneObj, transform);
    }
}


SGE::Mesh SGE::Import::meshHandler(const aiMesh *mesh)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    Vertex vert;

    for (std::size_t i = 0; i < mesh->mNumVertices; i++)
    {
        // copy vertices
        vert.pos.setX(mesh->mVertices[i].x);
        vert.pos.setY(mesh->mVertices[i].y);
        vert.pos.setZ(mesh->mVertices[i].z);

        // copy normals
        vert.Normal.setX(mesh->mNormals[i].x);
        vert.Normal.setY(mesh->mNormals[i].y);
        vert.Normal.setZ(mesh->mNormals[i].z);

        if (mesh->mTextureCoords[0])
        {
            vert.texCoord.setX(mesh->mTextureCoords[0][i].x);

            vert.texCoord.setY(mesh->mTextureCoords[0][i].y);
        }
        else
        {
            vert.texCoord.setX(0);
            vert.texCoord.setY(0);
        }
        vertices.push_back(vert);
    }

    // copy indices
    for (std::size_t f = 0; f < mesh->mNumFaces; f++)
    {
        const aiFace face = mesh->mFaces[f];
        for (std::size_t i = 0; i < face.mNumIndices; i++)
        {
            indices.push_back(face.mIndices[i]);
        }
    }

    return Mesh(vertices, indices);
}
