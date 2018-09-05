#include "chess.h"
#include <QDebug>
#include <QFileDialog>

Chess::Chess(bool _side, TYPE _type, int _x, int _y, QWidget *parent) : QLabel(parent), side(_side), type(_type)
{
    if (side == 0){
        switch (type){
        case JU:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Rju.png")));
            break;
        case MA:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Rma.png")));
            break;
        case XIANG:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Rxiang.png")));
            break;
        case SHI:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Rshi.png")));
            break;
        case SHUAI:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Rshuai.png")));
            break;
        case PAO:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Rpao.png")));
            break;
        case BING:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Rbing.png")));
            break;
        }
    }
    else{
        switch (type){
        case JU:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Bju.png")));
            break;
        case MA:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Bma.png")));
            break;
        case XIANG:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Bxiang.png")));
            break;
        case SHI:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Bshi.png")));
            break;
        case SHUAI:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Bshuai.png")));
            break;
        case PAO:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Bpao.png")));
            break;
        case BING:
            setPixmap(QPixmap::fromImage(QImage("./chesses/Bbing.png")));
            break;
        }
    }
    moveTo(_x, _y);
    show();
}

void Chess::moveTo(int newx, int newy)
{
    setGeometry(10 + 74 * newx, 55 + 74 * (9 - newy), 68, 68);
    xp = newx; yp = newy;
}

/**************************** Board *************************/
Board::Board(QWidget *parent) : QLabel(parent)
{
    QLabel::setPixmap(QPixmap::fromImage(QImage("./chesses/board.jpg")));
    for (int i = 0; i < 32; ++i){
        chess[i] = nullptr;
    }
}

void Board::save()
{
    QString name = QFileDialog::getSaveFileName(this, QString(), QString(), tr("Plain text(*.txt)"));
    if (name.length() == 0) return;
    QFile file(name);
    file.open(QFile::WriteOnly);
    QTextStream stream(&file);
    std::vector<QString> str0, str1;
    if (viewSide == 0){
        for (int i = 8; i >= 0; --i)
            if (chess[i]) str0.push_back(QString(" <%1,%2>").arg(chess[i]->xp).arg(chess[i]->yp));
        for (int i = 9; i < 16; ++i)
            if (chess[i]) str0.push_back(QString(" <%1,%2>").arg(chess[i]->xp).arg(chess[i]->yp));
        for (int i = 24; i >= 16; --i)
            if (chess[i]) str1.push_back(QString(" <%1,%2>").arg(chess[i]->xp).arg(chess[i]->yp));
        for (int i = 25; i < 32; ++i)
            if (chess[i]) str1.push_back(QString(" <%1,%2>").arg(chess[i]->xp).arg(chess[i]->yp));
    }
    else{
        for (int i = 8; i >= 0; --i)
            if (chess[i]) str0.push_back(QString(" <%1,%2>").arg(8 - chess[i]->xp).arg(9 - chess[i]->yp));
        for (int i = 9; i < 16; ++i)
            if (chess[i]) str0.push_back(QString(" <%1,%2>").arg(8 - chess[i]->xp).arg(9 - chess[i]->yp));
        for (int i = 24; i >= 16; --i)
            if (chess[i]) str1.push_back(QString(" <%1,%2>").arg(8 - chess[i]->xp).arg(9 - chess[i]->yp));
        for (int i = 25; i < 32; ++i)
            if (chess[i]) str1.push_back(QString(" <%1,%2>").arg(8 - chess[i]->xp).arg(9 - chess[i]->yp));
    }

    int count = 0, num;
    QString s0, s1;
    QTextStream tmp(&s0);
    tmp << "red\n" << (chess[8] != nullptr) << str0[count++] << '\n';
    num = (chess[7] != nullptr) + (chess[6] != nullptr); tmp << num;
    for (int i = 0; i < num; ++i) tmp << str0[count++]; tmp << '\n';
    num = (chess[5] != nullptr) + (chess[4] != nullptr); tmp << num;
    for (int i = 0; i < num; ++i) tmp << str0[count++]; tmp << '\n';
    num = (chess[3] != nullptr) + (chess[2] != nullptr); tmp << num;
    for (int i = 0; i < num; ++i) tmp << str0[count++]; tmp << '\n';
    num = (chess[1] != nullptr) + (chess[0] != nullptr); tmp << num;
    for (int i = 0; i < num; ++i) tmp << str0[count++]; tmp << '\n';
    num = (chess[9] != nullptr) + (chess[10] != nullptr); tmp << num;
    for (int i = 0; i < num; ++i) tmp << str0[count++]; tmp << '\n';
    num = (chess[11] != nullptr) + (chess[12] != nullptr)+ (chess[13] != nullptr)+ (chess[14] != nullptr)+ (chess[15] != nullptr);
    qDebug() << (chess[11] != nullptr);
    qDebug() << (chess[12] != nullptr);
    qDebug() << (chess[13] != nullptr);
    qDebug() << (chess[14] != nullptr);
    qDebug() << (chess[15] != nullptr);
    tmp << num;
    for (int i = 0; i < num; ++i) tmp << str0[count++]; tmp << '\n';

    count = 0;
    QTextStream tmp1(&s1);
    tmp1 << "black\n" << (chess[24] != nullptr) << str1[count++] << '\n';
    num = (chess[23] != nullptr) + (chess[22] != nullptr); tmp1 << num;
    for (int i = 0; i < num; ++i) tmp1 << str1[count++]; tmp1 << '\n';
    num = (chess[21] != nullptr) + (chess[20] != nullptr); tmp1 << num;
    for (int i = 0; i < num; ++i) tmp1 << str1[count++]; tmp1 << '\n';
    num = (chess[19] != nullptr) + (chess[18] != nullptr); tmp1 << num;
    for (int i = 0; i < num; ++i) tmp1 << str1[count++]; tmp1 << '\n';
    num = (chess[17] != nullptr) + (chess[16] != nullptr); tmp1 << num;
    for (int i = 0; i < num; ++i) tmp1 << str1[count++]; tmp1 << '\n';
    num = (chess[25] != nullptr) + (chess[26] != nullptr); tmp1 << num;
    for (int i = 0; i < num; ++i) tmp1 << str1[count++]; tmp1 << '\n';
    num = (chess[27] != nullptr) + (chess[28] != nullptr)+ (chess[29] != nullptr)+ (chess[30] != nullptr)+ (chess[31] != nullptr);
    tmp1 << num;
    for (int i = 0; i < num; ++i) tmp1 << str1[count++]; tmp1 << '\n';

    if (current == 0) stream << s0 << s1;
    else stream << s1 << s0;
    file.close();
}

void Board::startNew(bool _viewSide)
{
    viewSide = _viewSide;
    if (viewSide == 0)
        for (int i = 0; i < 2; ++i){
            chess[i * 16 + 0] = new Chess(i, Chess::JU, 0, 9 * i, this);
            chess[i * 16 + 1] = new Chess(i, Chess::JU, 8, 9 * i, this);
            chess[i * 16 + 2] = new Chess(i, Chess::MA, 1, 9 * i, this);
            chess[i * 16 + 3] = new Chess(i, Chess::MA, 7, 9 * i, this);
            chess[i * 16 + 4] = new Chess(i, Chess::XIANG, 2, 9 * i, this);
            chess[i * 16 + 5] = new Chess(i, Chess::XIANG, 6, 9 * i, this);
            chess[i * 16 + 6] = new Chess(i, Chess::SHI, 3, 9 * i, this);
            chess[i * 16 + 7] = new Chess(i, Chess::SHI, 5, 9 * i, this);
            chess[i * 16 + 8] = new Chess(i, Chess::SHUAI, 4, 9 * i, this);
            chess[i * 16 + 9] = new Chess(i, Chess::PAO, 1, 2 + 5 * i, this);
            chess[i * 16 + 10] = new Chess(i, Chess::PAO, 7, 2 + 5 * i, this);
            chess[i * 16 + 11] = new Chess(i, Chess::BING, 0, 3 + 3 * i, this);
            chess[i * 16 + 12] = new Chess(i, Chess::BING, 2, 3 + 3 * i, this);
            chess[i * 16 + 13] = new Chess(i, Chess::BING, 4, 3 + 3 * i, this);
            chess[i * 16 + 14] = new Chess(i, Chess::BING, 6, 3 + 3 * i, this);
            chess[i * 16 + 15] = new Chess(i, Chess::BING, 8, 3 + 3 * i, this);
        }
    else{
        for (int i = 0; i < 2; ++i){
            chess[(1 - i) * 16 + 0] = new Chess(1 - i, Chess::JU, 8, 9 * i, this);
            chess[(1 - i) * 16 + 1] = new Chess(1 - i, Chess::JU, 0, 9 * i, this);
            chess[(1 - i) * 16 + 2] = new Chess(1 - i, Chess::MA, 7, 9 * i, this);
            chess[(1 - i) * 16 + 3] = new Chess(1 - i, Chess::MA, 1, 9 * i, this);
            chess[(1 - i) * 16 + 4] = new Chess(1 - i, Chess::XIANG, 6, 9 * i, this);
            chess[(1 - i) * 16 + 5] = new Chess(1 - i, Chess::XIANG, 2, 9 * i, this);
            chess[(1 - i) * 16 + 6] = new Chess(1 - i, Chess::SHI, 5, 9 * i, this);
            chess[(1 - i) * 16 + 7] = new Chess(1 - i, Chess::SHI, 3, 9 * i, this);
            chess[(1 - i) * 16 + 8] = new Chess(1 - i, Chess::SHUAI, 4, 9 * i, this);
            chess[(1 - i) * 16 + 9] = new Chess(1 - i, Chess::PAO, 7, 2 + 5 * i, this);
            chess[(1 - i) * 16 + 10] = new Chess(1 - i, Chess::PAO, 1, 2 + 5 * i, this);
            chess[(1 - i) * 16 + 11] = new Chess(1 - i, Chess::BING, 8, 3 + 3 * i, this);
            chess[(1 - i) * 16 + 12] = new Chess(1 - i, Chess::BING, 6, 3 + 3 * i, this);
            chess[(1 - i) * 16 + 13] = new Chess(1 - i, Chess::BING, 4, 3 + 3 * i, this);
            chess[(1 - i) * 16 + 14] = new Chess(1 - i, Chess::BING, 2, 3 + 3 * i, this);
            chess[(1 - i) * 16 + 15] = new Chess(1 - i, Chess::BING, 0, 3 + 3 * i, this);
        }
    }
}

void Board::startFromSaved(bool _viewSide, QString data)
{
    viewSide = _viewSide;
    QTextStream in(&data);
    QString d; char u; int n, xx, yy;
    int f = 0;
    in >> d; if (d == "black") current = f = 1;
    qDebug() << data;
    in >> n; for (int i = 8; i < 8 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*f + i] = new Chess(f, Chess::SHUAI, xx, yy, this);
    }
    in >> n; for (int i = 6; i < 6 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*f + i] = new Chess(f, Chess::SHI, xx, yy, this);
    }
    in >> n; for (int i = 4; i < 4 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*f + i] = new Chess(f, Chess::XIANG, xx, yy, this);
    }
    in >> n; for (int i = 2; i < 2 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*f + i] = new Chess(f, Chess::MA, xx, yy, this);
    }
    in >> n; for (int i = 0; i < 0 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*f + i] = new Chess(f, Chess::JU, xx, yy, this);
    }
    in >> n; for (int i = 9; i < 9 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*f + i] = new Chess(f, Chess::PAO, xx, yy, this);
    }
    in >> n; for (int i = 11; i < 11 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*f + i] = new Chess(f, Chess::BING, xx, yy, this);
    }

    in >> d;
    in >> n; for (int i = 8; i < 8 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*(1-f) + i] = new Chess(1-f, Chess::SHUAI, xx, yy, this);
    }
    in >> n; for (int i = 6; i < 6 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*(1-f) + i] = new Chess(1-f, Chess::SHI, xx, yy, this);
    }
    in >> n; for (int i = 4; i < 4 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*(1-f) + i] = new Chess(1-f, Chess::XIANG, xx, yy, this);
    }
    in >> n; for (int i = 2; i < 2 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*(1-f) + i] = new Chess(1-f, Chess::MA, xx, yy, this);
    }
    in >> n; for (int i = 0; i < 0 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*(1-f) + i] = new Chess(1-f, Chess::JU, xx, yy, this);
    }
    in >> n; for (int i = 9; i < 9 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*(1-f) + i] = new Chess(1-f, Chess::PAO, xx, yy, this);
    }
    in >> n; for (int i = 11; i < 11 + n; ++i){
        in >> u; in >> u; in >> xx; in >> u; in >> yy; in >> u;
        chess[16*(1-f) + i] = new Chess(1-f, Chess::BING, xx, yy, this);
    }

    if (viewSide == 1){
        for (int i = 0; i < 32; ++i){
            if (chess[i]) chess[i]->moveTo(8 - chess[i]->xp, 9 - chess[i]->yp);
        }
    }
}

void Board::mousePressEvent(QMouseEvent *event)
{
    if (!gaming || current != viewSide) goto END;
    int cnt = 0;
    for (int i = 0; i < 32; ++i){
        if (chess[i] != nullptr) cnt++;
    }
    qDebug() << cnt;
    int xx = (event->x() - 10) / 74, yy = 9 - (event->y() - 55) / 74;
    if (xx >= 0 && xx <= 8 && yy >= 0 && yy <= 9){
        Chess* find = search(xx, yy);
        if (find && find->side == viewSide){
            select(find);
        }
        else{
            if (selected){
                if (canMove(selected, xx, yy)){
                    QJsonObject json;
                    selected->moveTo(xx, yy);
                    if (viewSide == 0 && xx == chess[24]->xp && yy == chess[24]->yp
                            || viewSide == 1 && xx == chess[8]->xp && yy == chess[8]->yp)
                        json.insert("win", true);
                    for (int i = 0; i < 16; ++i){
                        if (chess[viewSide * 16 + i] && canMove(chess[viewSide * 16 + i], chess[24 - 16 * viewSide]->xp, chess[24 - 16 * viewSide]->yp)){
                            json.insert("jiangjun", true);
                            break;
                        }
                    }
                    int j;
                    for (j = 0; j < 32; ++j){
                        if (chess[j] == selected) break;
                    }
                    json.insert("mov", j);
                    if (viewSide == 0){
                        json.insert("x", xx);
                        json.insert("y", yy);
                    }
                    else{
                        json.insert("x", 8 - xx);
                        json.insert("y", 9 - yy);
                    }
                    if (find){
                        for (j = 0; j < 32; ++j){
                            if (chess[j] == find) break;
                        }
                        delete chess[j];
                        chess[j] = nullptr;
                        json.insert("del", j);
                    }
                    emit jsonReady(json);
                    current = !current;
                }
            }
            select(nullptr);
        }
    }
    else select(nullptr);
END: QWidget::mousePressEvent(event);
}

bool Board::canMove(Chess *c, int xx, int yy)
{
    int x0 = c->xp, y0 = c->yp;
    Chess* find = search(xx, yy);
    if (find && find->side == viewSide) return false;

    switch (c->type) {
    case Chess::JU:
        if (x0 == xx){
            for (int i = std::min(y0, yy) + 1; i < std::max(y0, yy); ++i){
                if (search(x0, i)) return false;
            }
            return true;
        }
        else if (y0 == yy){
            for (int i = std::min(x0, xx) + 1; i < std::max(x0, xx); ++i){
                if (search(i, y0)) return false;
            }
            return true;
        }
        else return false;
        break;
    case Chess::MA:{
        int dir[8][2] = {2, -1, 1, -2, -1, -2, -2, -1, -2, 1, -1, 2, 1, 2, 2, 1};
        int obs[8][2] = {1, 0, 0, -1, 0, -1, -1, 0, -1, 0, 0, 1, 0, 1, 1, 0};
        for (int i = 0; i < 8; ++i){
            if (x0 + dir[i][0] == xx && y0 + dir[i][1] == yy && !search(x0 + obs[i][0], y0 + obs[i][1]))
                return true;
        }
        return false;
        break;
    }
    case Chess::XIANG:
        if (yy < 5 && std::abs(xx - x0) == 2 && std::abs(yy - y0) == 2
                && !search(x0 + (xx - x0) / 2, y0 + (yy - y0) / 2)) return true;
        else return false;
        break;
    case Chess::SHI:
        if (xx > 2 && xx < 6 && yy < 3 && std::abs(xx - x0) == 1 && std::abs(yy - y0) == 1) return true;
        else return false;
        break;
    case Chess::SHUAI:
    {
//        int oldx = c->xp, oldy = c->yp; c->moveTo(xx, yy);
//        for (int i = 0; i < 16; ++i){
//            if (i == 8) continue;
//            if (chess[(1-viewSide)*16 + i] && canMove(chess[(1-viewSide)*16 + i], xx, yy)){
//                c->moveTo(oldx, oldy);
//                return false;
//            }
//            c->moveTo(oldx, oldy);
            Chess* other = chess[24 - 16 * viewSide];
            if (other->xp == xx){
                for (int i = y0 + 1; i < other->yp; ++i){
                    if (search(xx, i)) goto OK;
                }
                return false;
            }
            OK: if (xx > 2 && xx < 6 && yy < 3 && std::abs(xx - x0) + std::abs(yy - y0) == 1) return true;
            else return false;
            break;
        }
    case Chess::BING:
            if (xx == x0 && yy == y0 + 1) return true;
            if (yy > 4 && std::abs(xx - x0) == 1 && yy == y0) return true;
            else return false;
            break;
        case Chess::PAO:{
            if (x0 != xx && y0 != yy) return false;
            int midCount = 0;
            if (x0 == xx){
                for (int i = std::min(y0, yy) + 1; i < std::max(y0, yy); ++i){
                    if (search(x0, i)) midCount++;
                }
            }
            else if (y0 == yy){
                for (int i = std::min(x0, xx) + 1; i < std::max(x0, xx); ++i){
                    if (search(i, y0)) midCount++;
                }
            }
            if (search(xx, yy)) {if (midCount == 1) return true;}
            else if (midCount == 0) return true;
            return false;
            break;
        }
        }
        qDebug() << "Error! not judged";
        return false;
    }


    Chess *Board::search(int xx, int yy)
    {
        for (int i = 0; i < 32; ++i){
            if (chess[i] && chess[i]->xp == xx && chess[i]->yp == yy){
                return chess[i];
            }
        }
        return nullptr;
    }

    void Board::select(Chess *target)
    {
        if (target == nullptr){
            if (selected){
                selected->setGraphicsEffect(nullptr);
                selected = nullptr;
            }
        }
        else if (selected == target){
            selected->setGraphicsEffect(nullptr);
            selected = nullptr;
        }
        else{
            if (selected) selected->setGraphicsEffect(nullptr);
            selected = target;
            QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(this);
            effect->setOpacity(0.5);
            selected->setGraphicsEffect(effect);
        }
    }
