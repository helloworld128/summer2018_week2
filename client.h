#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QMediaPlayer>
const int timeOut = 60;

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

protected:
    void timerEvent(QTimerEvent* event) override;

private slots:
    void on_surrender_clicked();
    void on_actionPlay_triggered();
    void startGame(bool isClient, bool isNew, QString savedGame);
    void on_actionSave_triggered();
    void sendJson(QJsonObject json);
    void readJson();

private:
    int timerID;
    QMediaPlayer* player;
    QTcpServer* server;
    QTcpSocket* socket;
    Ui::Client *ui;
};

#endif // CLIENT_H
