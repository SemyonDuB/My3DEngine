#include "engine.h"
#include "navigation.h"
#include "scene.h"
#include "shader.h"

#include <cstdio>
#include <iostream>
#include <unistd.h>


void SGE::initEngine(Shader &shaderProgram, Scene &scene, Navigation &nvg)
{
    shaderProgram.loadShader();
    scene.initScene();
    nvg.initNavigation();
}


void SGE::drawScene(Scene &scene, Shader &shaderProgram)
{
    scene.drawAllObj(shaderProgram);
}


std::string SGE::getAssetsFileName(std::string fileName)
{
    char working_dir[FILENAME_MAX];
    getcwd(working_dir, sizeof(working_dir));

    std::string full_path(working_dir);
    full_path = full_path + "/assets/" + fileName;

    return full_path;
}


std::string SGE::getProjectDir()
{
    char working_dir[FILENAME_MAX];
    getcwd(working_dir, sizeof(working_dir));

    return std::string(working_dir) + "/";
}
