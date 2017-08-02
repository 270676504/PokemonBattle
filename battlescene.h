#ifndef BATTLESCENE_H
#define BATTLESCENE_H
#include <QGraphicsScene>
class MainInfo;
namespace Ui {
class MainWindow;
}

class BattleScene : public QGraphicsScene
{
        Q_OBJECT
public:
    BattleScene(QObject *parent = Q_NULLPTR);
private:
    MainInfo* m_info;
    MainInfo* oppo_info;
};

#endif // BATTLESCENE_H
