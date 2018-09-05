#include "client.h"
#include "ui_client.h"
#include "config.h"
#include <QJsonDocument>
#include <QMessageBox>

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    server = nullptr;
    socket = nullptr;
    player = new QMediaPlayer(this);
    ui->setupUi(this);
    connect(ui->board, SIGNAL(jsonReady(QJsonObject)), this, SLOT(sendJson(QJsonObject)));
}

Client::~Client()
{
    delete ui;
}

void Client::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerID){
        ui->time->display(ui->time->intValue() - 1);
        if (ui->time->intValue() == 0){
            killTimer(timerID);
            if (ui->board->viewSide == ui->board->current){
                //lose the game
                ui->board->gaming = false;
                QJsonObject json{{"timeout", true}};
                QJsonDocument doc(json);
                socket->write(doc.toJson());
                QMessageBox::about(this, "Result", "You have no time left.\nYou lose!");
            }
        }
    }
}

void Client::on_surrender_clicked()
{
    ui->board->gaming = false;
    killTimer(timerID);
    QJsonObject json{{"surrender", true}};
    QJsonDocument doc(json);
    socket->write(doc.toJson());
    QMessageBox::about(this, "Result", "You lose!");
}

void Client::on_actionPlay_triggered()
{
    Config config(server, socket, this);
    connect(&config, SIGNAL(sendStartGameInfo(bool,bool,QString)), this, SLOT(startGame(bool,bool,QString)));
    config.exec();
}

void Client::startGame(bool isClient, bool isNew, QString savedGame)//savedGame is text, not directory
{
    timerID = startTimer(1000);
    ui->time->display(timeOut);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readJson()));
    ui->board->gaming = true;
    if (!isClient){
        if (isNew) {
            ui->board->startNew(isClient);
            ui->current->setText("red");
            sendJson(QJsonObject{{"clientstart", true}});
        }
        else{
            if (savedGame[0] == 'r') ui->current->setText("red");
            else ui->current->setText("black");
            ui->board->startFromSaved(0, savedGame);
            socket->write(QByteArray(savedGame.toLatin1()));
        }
    }
}

void Client::on_actionSave_triggered()
{
    ui->board->save();
}

void Client::sendJson(QJsonObject json)
{
    if (json.contains("clientstart")){
        QJsonDocument doc(json);
        socket->write(doc.toJson());
        return;
    }
    if (json.contains("win")){
        killTimer(timerID);
        ui->board->gaming = false;
    }
    else{
        ui->current->setText(ui->current->text() == "black" ? "red" : "black");
        killTimer(timerID);
        timerID = startTimer(1000);
        ui->time->display(timeOut);
    }
    QJsonDocument doc(json);
    socket->write(doc.toJson());
    if (json.contains("win")){
        QMessageBox::about(this, "Result", "You win!");
    }
    if (json.contains("mov")){
        player->setMedia(QUrl::fromLocalFile("./chesses/sound.mp3"));
        player->play();
    }
    if (json.contains("jiangjun")){
        player->setMedia(QUrl::fromLocalFile("./chesses/jiangjun.mp3"));
        player->play();
    }
}

void Client::readJson()
{
    QByteArray data = socket->readAll();
    QJsonParseError e;
    QJsonDocument doc = QJsonDocument::fromJson(data, &e);
    if(e.error == QJsonParseError::NoError && !doc.isNull() && doc.isObject()){
        QJsonObject json = doc.object();
        if (json.contains("clientstart")){
            ui->board->startNew(1);
            ui->current->setText("red");
            return;
        }
        if (json.contains("timeout")){
            ui->board->gaming = false;
            killTimer(timerID);
            QMessageBox::about(this, "Result", "Your opponent runs out of time.\nYou win!");
            return;
        }
        if (json.contains("surrender")){
            ui->board->gaming = false;
            killTimer(timerID);
            QMessageBox::about(this, "Result", "Your opponent has surrendered.\nYou win!");
            return;
        }
        if (json.contains("mov")){
            player->setMedia(QUrl::fromLocalFile("./chesses/sound.mp3"));
            player->play();
            if (ui->board->viewSide == 0)
                ui->board->chess[json["mov"].toInt()]->moveTo(json["x"].toInt(), json["y"].toInt());
            else
                ui->board->chess[json["mov"].toInt()]->moveTo(8 - json["x"].toInt(), 9 - json["y"].toInt());
        }
        if (json.contains("del")){
            delete ui->board->chess[json["del"].toInt()];
            ui->board->chess[json["del"].toInt()] = nullptr;
        }
        if (json.contains("jiangjun")){
            player->setMedia(QUrl::fromLocalFile("./chesses/jiangjun.mp3"));
            player->play();
        }
        if (json.contains("win")){
            killTimer(timerID);
            ui->board->gaming = false;
            QMessageBox::about(this, "Result", "You lose!");
            return;
        }
        ui->board->current = !ui->board->current;
        killTimer(timerID);
        timerID = startTimer(1000);
        ui->time->display(timeOut);
        ui->current->setText(ui->board->current == 0 ? "red" : "black");
    }
    else{
        QString str(data);
        ui->current->setText(str[0] == 'r' ? "red" : "black");
        ui->board->startFromSaved(1, str);
    }
}
