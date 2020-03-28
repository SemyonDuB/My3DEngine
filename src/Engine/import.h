#pragma once

#include <QOpenGLShaderProgram>
#include <QVector3D>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "mesh.h"
#include "object.h"


QMatrix4x4 translateAiMatrix4x4(const aiMatrix4x4 &tran);

namespace SGE
{
    class Scene;

    class Import
    {
    public:
        Import(std::string FileLoc, Scene &sceneObj);
        void importObj(std::string fileLoc, Scene &sceneObj);

    private:
        Import(const Import &);            //	Noncopybale
        Import &operator=(const Import &); // 	Noncopyable

        Assimp::Importer importer;
        const aiScene *scene;
        std::string m_File;
        QMatrix4x4 accTransform;

        bool loadScene();
        void nodeHandler(const aiNode *node, SGE::Scene &sceneObj,
                         QMatrix4x4 &accTransform);

        SGE::Mesh meshHandler(const aiMesh *mesh);
    };
} // namespace SGE
