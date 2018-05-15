#include "mw1.h"
#include "ui_mw1.h"
#include "icon.h"
#include <map>
#include <iostream>
#define ROW 18
#define COL 25

using namespace std;

MW1::MW1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MW1)
{
    ui->setupUi(this);

    //init game world
    _game.initWorld("");//TODO 应该是输入有效的地图文件
}

MW1::~MW1()
{
    delete ui;
}

void MW1::paintEvent(QPaintEvent *e){
    QPainter *pa;
    pa = new QPainter();
    pa->begin(this);
    this->_game.show(pa);
    pa->end();
    delete pa;
}

void MW1::keyPressEvent(QKeyEvent *e)
{

    //direction = 1,2,3,4 for 上下左右
    if(e->key() == Qt::Key_A)
    {
        this->_game.handlePlayerMove(3,1);
    }
    else if(e->key() == Qt::Key_D)
    {
        this->_game.handlePlayerMove(4,1);
    }
    else if(e->key() == Qt::Key_W)
    {
        this->_game.handlePlayerMove(1,1);
    }
    else if(e->key() == Qt::Key_S)
    {
         this->_game.handlePlayerMove(2,1);
    }
    if(_game.bombs.getPosX()==_game._player.getPosX()&&_game.bombs.getPosY()-1==_game._player.getPosY())
    {
        if(QMessageBox::question(this,"提示","游戏结束,是否重新游戏",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
        {
            varybombs();
        }
        else exit(0);
    }
    this->repaint();
}

void MW1::varybombs()
{
        vector<RPGObj>::iterator it;
        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        _game.bombs.initObj("bomb");
        _game.bombs.setPosX(qrand()%COL);
        _game.bombs.setPosY(qrand()%ROW);
        this->_game._objs.push_back(_game.bombs);

        int x=_game.bombs.getPosX(),y=_game.bombs.getPosY();
        if(x>25||y>18||x<-1||y<0)
        {
            varybombs();
        }
        for(it=this->_game._objs.begin();it!=this->_game._objs.end();it++)
        {
            if(x==(*it).getPosX()&&y==(*it).getPosY()-1)
            {
                //this->_game._objs.erase(it);
                varybombs();
                return;
            }

        }
}
