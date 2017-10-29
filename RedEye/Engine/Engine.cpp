#include "Engine.hpp"
#include "RedGL/RedGL.hpp"
#include "DEBUG/Debug.hpp"
#include "SHADER/Shader.hpp"
#include "File/File.hpp"
#include "Script/Test.hpp"

RedEyeBehaviour * test;

void Engine::Start()
{
    RedLog("Engine Start !!!!");

    test = new Test();
    test->Start();
}

void Engine::Update()
{
    test->Update();
}

void Engine::End()
{
    test->End();
    delete test;
}
