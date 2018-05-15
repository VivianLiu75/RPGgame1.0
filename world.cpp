#include "world.h"
#include "icon.h"
#define ROW 18
#define COL 25

void World::initWorld(string mapFile){
    //TODO 下面这部分逻辑应该是读入地图文件，生成地图上的对象
    //player 5 5
    this->_player.initObj("player");
    this->_player.setPosX(5);
    this->_player.setPosY(5);

    //stone 4 5
    //RPGObj obj1, obj2, obj3 ,obj4 ,obj5 ,obj6;
    RPGObj obj1, obj2,  obj5 ,obj6;
    obj1.initObj("stone");
    obj1.setPosX(4);
    obj1.setPosY(3);

    obj2.initObj("stone");
    obj2.setPosX(8);
    obj2.setPosY(5);

    /*QTime m;
    m= QTime::currentTime();
    qsrand(m.msec()+m.second()*1000);
    bombs.initObj("bomb");
    bombs.setPosX(qrand()%COL);
    bombs.setPosY(qrand()%ROW);*/

    obj5.initObj("bonus");
    obj5.setPosX(18);
    obj5.setPosY(7);

    obj6.initObj("fun");
    obj6.setPosX(12);
    obj6.setPosY(9);

    /*QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    obj3.initObj("fruit");
    obj3.setPosX(qrand()%COL);
    obj3.setPosY(qrand()%ROW);*/

    this->_objs.push_back(obj1);
    this->_objs.push_back(obj2);
    //this->_objs.push_back(obj3);
    //this->_objs.push_back(bombs);
    this->_objs.push_back(obj5);
    this->_objs.push_back(obj6);

    varyfruit();
    varybomb();
}


void World::show(QPainter * painter){
    vector<RPGObj>::iterator it;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
        (*it).show(painter);
    }
    this->_player.show(painter);
}

void World::handlePlayerMove(int direction, int steps){
    vector<RPGObj>::iterator it;
    int x=this->_player.getPosX();
    int y=this->_player.getPosY();
    switch (direction){
    case 1:
        y -= steps;
        break;
    case 2:
        y += steps;
        break;
    case 3:
        x -= steps;
        break;
    case 4:
        x += steps;
        break;
    }

    if(x==-1||x==25||y==-2||y==18) return;

    for(it=this->_objs.begin();it!=this->_objs.end();it++)
    {
        if(x==(*it).getPosX()&& y==(*it).getPosY()-1)
        {
            if((*it).canCover()==true)
            {
                this->_player.move(direction,steps);
                if((*it).canEat()==true&&(*it).candoit()==true)
                    this->_objs.erase(it);
                if((*it).canEat()==true&&(*it).candoit()==false)
                {
                    this->_objs.erase(it);
                        varyfruit();
                }
            }
        else this->_player.move(direction,0);
        if((*it).canCover()==false&&(*it).canEat()==true) this->_player.move(direction,2);
        return;
        }
    }
    this->_player.move(direction,steps);

}

void World::varyfruit()
{
        vector<RPGObj>::iterator it;
        RPGObj obj3;

        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        obj3.initObj("fruit");
        obj3.setPosX(qrand()%COL);
        obj3.setPosY(qrand()%ROW);
        this->_objs.push_back(obj3);

        int x=obj3.getPosX(),y=obj3.getPosY();
        if(x>25||y>18||x<-1||y<0)
        {
            varyfruit();
        }
        for(it=this->_objs.begin();it!=this->_objs.end();it++)
        {
            if(x==(*it).getPosX()&&y==(*it).getPosY()-1)
            {
                //this->_objs.erase(it);
                varyfruit();
                return;
            }

        }
}

void World::varybomb()
{
        vector<RPGObj>::iterator it;

        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        bombs.initObj("bomb");
        bombs.setPosX(qrand()%COL);
        bombs.setPosY(qrand()%ROW);
        this->_objs.push_back(bombs);

        int x=bombs.getPosX(),y=bombs.getPosY();
        if(x>25||y>18||x<-1||y<0)
        {
            varybomb();
        }
        for(it=this->_objs.begin();it!=this->_objs.end();it++)
        {
            if(x==(*it).getPosX()&&y==(*it).getPosY()-1)
            {
                //this->_objs.erase(it);
                varybomb();
                return;
            }

        }
}
