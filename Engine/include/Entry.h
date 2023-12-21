#include "Application.h"
#include "Exception.h"
#include <cstdio>

extern Engine::Application* Engine::CreateNewApp();

int main(void) try
{
    //Create new application
    auto app = Engine::CreateNewApp();
    
    //Run the main app loop and obtain exit code after it finishes
    int ec = app->Run();

    //Detele app since it's not longer needed
    delete app;

    //Return previously obtained exit code
    return ec;

} catch(Engine::Exception& e)
{
    //If any exception happens during app runtime show details in the console
    printf("%s", e.what());
    return 1;
}