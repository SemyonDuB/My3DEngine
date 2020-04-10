#include "Engine.h"

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


fs::path SGE::find_file(const fs::path &file_name)
{
    using namespace fs;
    for (auto &file_path : recursive_directory_iterator(current_path()))
        if (path(file_path).filename() == file_name &&
            is_regular_file(path(file_path)))
            return path(file_path);

    using namespace std;
    throw filesystem_error("Can't find file",
                           make_error_code(errc::no_such_file_or_directory));
}
