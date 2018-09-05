#ifndef CHESS_H
#define CHESS_H
#include <QLabel>
#include <QMouseEvent>
#include <QGraphicsEffect>
#include <QJsonObject>
class Board;

class Chess : public QLabel
{
public:
    enum TYPE{SHUAI = 0, JU, MA, XIANG, SHI, PAO, BING} type;
    bool side;
    int xp, yp;
    Chess(bool _side, TYPE _type, int _x, int _y, QWidget* parent = nullptr);
    void moveTo(int newx, int newy);
};

class Board : public QLabel{
    Q_OBJECT
public:
    Board(QWidget* parent = nullptr);
    Chess* chess[32];
    Chess* selected = nullptr;
    void save();
    bool viewSide = 0;
    bool current = 0;
    bool gaming = 0;
signals:
    void jsonReady(QJsonObject json);
public slots:
    void startNew(bool _viewSide);
    void startFromSaved(bool _viewSide, QString data);
protected:
    void mousePressEvent(QMouseEvent* event) override;
private:
    bool canMove(Chess* c, int xx, int yy);
    Chess* search(int xx, int yy);
    void select(Chess* target);
};

#endif // CHESS_H
