#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(QTcpServer*& _server, QTcpSocket*& _socket, QWidget *parent = 0);
    ~Config();

signals:
    void sendStartGameInfo(bool isHost, bool isNew, QString savedGame);

private slots:
    void on_accept_clicked();

    void on_cancel_clicked();

    void on_load_clicked();

    void onConnectionEstablished();

    void on_rclient_toggled(bool checked);

    void on_rload_toggled(bool checked);

private:
    QTcpServer*& server;
    QTcpSocket*& socket;
    bool mConnecting = false;
    Ui::Config *ui;
};

#endif // CONFIG_H
