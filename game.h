#ifndef GAME_H
#define GAME_H


class Game
{
public:
    Game* getInstance();
    void initialization();
private:
    Game();
    ~Game();
    static Game* instance;
private:

};

#endif // GAME_H
