#include "Engine/import.h"
#include <QDebug>

Import::Import(const char *pFile, Scene &sceneObj)
{
    this->pFile = pFile;
    accTransform.setToIdentity();

    loadScene();
    nodeHandler(scene->mRootNode, sceneObj, accTransform);
}

bool Import::loadScene()
{

    scene = importer.ReadFile(pFile, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene)
    {
        qDebug() << importer.GetErrorString();
        return false;
    }

    return true;
}

QMatrix4x4 transleAiMatrix4x4(const aiMatrix4x4 &tran)
{
    QMatrix4x4 returnMatrix;
    returnMatrix.setRow(0, QVector4D(tran.a1, tran.a2, tran.a3, tran.a4));
    returnMatrix.setRow(1, QVector4D(tran.b1, tran.b2, tran.b3, tran.b4));
    returnMatrix.setRow(2, QVector4D(tran.c1, tran.c2, tran.c3, tran.c4));
    returnMatrix.setRow(3, QVector4D(tran.d1, tran.d2, tran.d3, tran.d4));

    return returnMatrix;
}

void Import::nodeHandler(const aiNode *node, Scene &sceneObj,
                         QMatrix4x4 &accTransform)
{
    // Recursive func!

								// Its my func, above
	QMatrix4x4 mTransformation = transleAiMatrix4x4(node->mTransformation);
    QMatrix4x4 transform = mTransformation * accTransform; // For global coord

    if(node->mNumMeshes > 0)
    {
        Object obj;

        // Copy meshes
        for (quint16 n = 0; n < node->mNumMeshes; n++)
        {
			const aiMesh *mesh = scene->mMeshes[node->mMeshes[n]];
            obj.meshes.push_back(meshHandler(mesh));
            obj.model = transform;
        }

        sceneObj.objects.push_back(obj);
    }
    for(quint16 i = 0; i < node->mNumChildren; i++ )
    {
        nodeHandler(node->mChildren[i], sceneObj, transform);
    }
}

Mesh Import::meshHandler(const aiMesh *mesh)
{
    // this just copy 1 mesh with vertices, normals, etc.
    QVector<Vertex> vertices;
    QVector<GLuint> indices;

    Vertex vert;

    // copy vertices, normals and texCoord into mesh
    for(quint32 i = 0; i < mesh->mNumVertices; i++  )
    {
        // Maybe it can fix.
        // But Qt tell me that QVector3d contain int.
		const int tranI = static_cast<int>(i); // translate quint32 to int

        // copy vertices
        vert.pos.setX(mesh->mVertices[tranI].x);
        vert.pos.setY(mesh->mVertices[tranI].y);
        vert.pos.setZ(mesh->mVertices[tranI].z);

        // copy normals
        vert.Normal.setX(mesh->mNormals[tranI].x);
        vert.Normal.setY(mesh->mNormals[tranI].y);
        vert.Normal.setZ(mesh->mNormals[tranI].z);

        if(mesh->mTextureCoords[0])
        {
            // it needs to be supplemented
            vert.texCoord.setX(
                        mesh->mTextureCoords[0][tranI].x);

            vert.texCoord.setY(
                        mesh->mTextureCoords[0][tranI].y);
        }else{
            vert.texCoord.setX(0);
            vert.texCoord.setY(0);
        }
        vertices.push_back(vert);
    }

    // copy indices. Its need to our mesh
    for(quint32 f = 0; f < mesh->mNumFaces; f++)
    {
		const aiFace face = mesh->mFaces[f];
        for(quint32 i = 0; i < face.mNumIndices; i++)
        {
            indices.push_back(face.mIndices[i]);
        }
    }

	// This return copy constructor
    return Mesh(vertices, indices);
}
