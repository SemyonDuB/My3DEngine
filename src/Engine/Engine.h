#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include "Navigation.h"
#include "Shader.h"
#include "Scene.h"

namespace fs = std::filesystem;

namespace SGE
{
    void initEngine(Shader &shaderProg, Scene &scene, Navigation &nvg);
    void setupScene(Scene &scene);
    void drawScene(Scene &scene, Shader &shaderProgram);
    [[nodiscard]] std::string getAssetsFileName(std::string fileName);
    [[nodiscard]] std::string getProjectDir();
    [[nodiscard]] fs::path find_file(const fs::path &file_name);
} // namespace SGE
