#include "game.h"

Game* Game::instance=nullptr;

Game::Game()
{

}

Game::~Game()
{
    delete instance;
}

Game *Game::getInstance()
{
    if(instance==nullptr)
        instance=new Game();
    return instance;
}

void Game::initialization()
{

}
