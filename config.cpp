#include "config.h"
#include "ui_config.h"
#include <QRegExp>
#include <QFileDialog>

Config::Config(QTcpServer *&_server, QTcpSocket *&_socket, QWidget *parent) :
    QDialog(parent), server(_server), socket(_socket),
    ui(new Ui::Config)
{
    ui->setupUi(this);
    ui->accept->setFocus();
    ui->load->setEnabled(false);
    ui->loadEdit->setEnabled(false);
    QRegExp rx("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    ui->ipEdit->setValidator(new QRegExpValidator(rx, this));
}

Config::~Config()
{
    delete ui;
}

void Config::on_accept_clicked()
{
    mConnecting = true;
    if (ui->rclient->isChecked()){
        socket = new QTcpSocket(parent());
        socket->connectToHost(QHostAddress(ui->ipEdit->text()), ui->portEdit->text().toInt());
        connect(socket, SIGNAL(connected()), this, SLOT(onConnectionEstablished()));
    }
    else{
        server = new QTcpServer();
        server->listen(QHostAddress::AnyIPv4, ui->portEdit->text().toInt());
        connect(server, SIGNAL(newConnection()), this, SLOT(onConnectionEstablished()));
    }
    ui->accept->setEnabled(false);
    ui->accept->setText("Connecting...");
}

void Config::on_cancel_clicked()
{
    if (mConnecting){
        mConnecting = false;
        ui->accept->setEnabled(true);
        ui->accept->setText("Accept");
        if (ui->rclient->isChecked()) socket->deleteLater();
        else server->deleteLater();
    }
}

void Config::on_load_clicked()
{
    ui->loadEdit->setText(QFileDialog::getOpenFileName(this, QString(), QString(), tr("Plain text(*.txt)")));
}

void Config::onConnectionEstablished()
{
    ui->accept->setEnabled(true);
    ui->accept->setText("Accept");
    mConnecting = false;
    if (ui->rhost->isChecked()) {
        socket = server->nextPendingConnection();
        //server->deleteLater();
    }
    QString savedGame = QString();
    if (ui->rload->isChecked() && ui->rhost->isChecked()){
        QFile file(ui->loadEdit->text());
        file.open(QFile::ReadOnly);
        QTextStream stream(&file);
        savedGame = stream.readAll();
    }

    emit sendStartGameInfo(ui->rclient->isChecked(), ui->rnew->isChecked(), savedGame);
    close();
}

void Config::on_rclient_toggled(bool checked)
{
    ui->load->setEnabled(!checked);
    ui->loadEdit->setEnabled(!checked);
    ui->groupBox_2->setEnabled(!checked);
}

void Config::on_rload_toggled(bool checked)
{
    ui->load->setEnabled(checked);
    ui->loadEdit->setEnabled(checked);
}
