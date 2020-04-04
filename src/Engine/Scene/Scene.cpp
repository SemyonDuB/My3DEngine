#include "Scene.h"
#include <iostream>


SGE::Scene::Scene()
    : m_projection(new QMatrix4x4), m_view(new QMatrix4x4),
      background_color(QVector4D(0, 0, 0, 1))
{
}


SGE::Scene::Scene(const QMatrix4x4 &projection, const QMatrix4x4 &view)
    : m_projection(new QMatrix4x4(projection)), m_view(new QMatrix4x4(view))
{
}


void SGE::Scene::initScene()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);

    glClearColor(background_color[0], background_color[1], background_color[2],
                 background_color[3]);
}


void SGE::Scene::drawAllObj(Shader &shaderProg)
{
    glClearColor(background_color[0], background_color[1], background_color[2],
                 background_color[3]);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);

    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    auto it = objects.begin();
    for (std::size_t i = 0; i < objects.size(); ++i)
    {
        glStencilFunc(GL_ALWAYS, i + 1, 0xFF);
        it->drawObject(shaderProg.phongShader);
        ++it;
    }
}


void SGE::Scene::removeSelections()
{
    if (!objects.empty())
    {
        auto it = objects.begin();
        for (auto &selObj : selectionsObj)
        {
            std::advance(it, selObj);
            it->changeSelection();
        }
    }
    selectionsObj.clear();
}


void SGE::Scene::selectCurrentObj(qint32 objId)
{
    // remove all previous selections
    removeSelections();

    if (!objects.empty())
    {
        selectionsObj.push_back(objId);

        // select new object
        auto it = std::next(objects.begin(), objId);
        it->changeSelection();
    }
}


void SGE::Scene::moveSelectObjects(QVector3D offsetObj)
{
    if (!objects.empty())
    {
        auto it = objects.begin();
        for (auto &selObj : selectionsObj)
        {
            std::advance(it, selObj);
            it->setObjLocation(offsetObj);
        }
    }
}


bool SGE::Scene::selectionObjectExist()
{
    for (auto &obj : objects)
    {
        if (obj.isSelected()) return true;
    }
    return false;
}
