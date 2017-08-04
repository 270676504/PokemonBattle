#ifndef BATTLESCENE_H
#define BATTLESCENE_H
#include <QGraphicsScene>

class MainInfo;
class Pokemon;
namespace Ui {
class MainWindow;
}
class BattleScene : public QGraphicsScene
{
        Q_OBJECT
    enum Person{
        Self,Oppo
    };
public:
    BattleScene(Pokemon* pokemon1,Pokemon* pokemon2,QObject *parent = Q_NULLPTR);
    ~BattleScene();
    void changePokemon(Pokemon* pokemon,Person target = Self );
protected:
    void setupUi();
private:
    Pokemon* m_pokemon;
    Pokemon* oppo_pokemon;
    MainInfo* m_info;
    MainInfo* oppo_info;
};

#endif // BATTLESCENE_H
