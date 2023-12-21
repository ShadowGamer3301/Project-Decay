#include "Application.h"
#include "Entry.h"

class DecayGame : public Engine::Application
{
public:
    DecayGame();
    ~DecayGame();

    int Run() override;
};

DecayGame::DecayGame() {}
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
    }
}