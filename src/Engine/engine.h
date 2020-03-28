#pragma once
#include "string"

namespace SGE
{
    class Shader;
    class Scene;
    class Navigation;

    void initEngine(Shader &shaderProg, Scene &scene, Navigation &nvg);
    void setupScene(Scene &scene);
    void drawScene(Scene &scene, Shader &shaderProgram);
    [[nodiscard]] std::string getAssetsFileName(std::string fileName);
    [[nodiscard]] std::string getProjectDir();

} // namespace SGE
