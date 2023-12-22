#include "Application.h"
#include "Entry.h"

class DecayGame : public Engine::Application
{
public:
    DecayGame();
    ~DecayGame();

    int Run() override;
};

DecayGame::DecayGame() {
#ifdef _WIN32
    pWindow->ChangeTitle(L"Project Decay (WIN32 | D3D11)");
#endif

}
DecayGame::~DecayGame() {}

Engine::Application* Engine::CreateNewApp()
{
    return new DecayGame();
}

int DecayGame::Run()
{
    while(true)
    {
        if(const auto ec = pWindow->ProcessMessage())
            return *ec;
        pGfxBase->StartRender();
        pGfxBase->EndRender();

    }
}