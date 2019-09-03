#include "Actor.h"
#include "StudentWorld.h"
#include <string>
#include<cstdlib>
#include<cmath>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}
void StudentWorld::addsquirt(int x,int y,Frackman::Direction dir){
    m_actor.push_back(new Squirt(x,y,dir,this));
    playSound(SOUND_PLAYER_SQUIRT);
}
bool StudentWorld::firesquirt(int x, int y){
    if (x<0||x>=64||y<0||y>=64) {
        return false;
    }
    list<actor*>::iterator it;
    it=m_actor.begin();
    while (it!=m_actor.end()) {
        if ((*it)->getID()==IID_BOULDER) {
            double temp;
            temp=pow(((*it)->getX()-x), 2)+pow(((*it)->getY()-y), 2);
            if (sqrt(temp)<=3) {
                return false;
            }
        }
        it++;
    }
    
    return true;
}
bool StudentWorld::squirtset(int x, int y,Squirt::Direction dir){
     
    if (x<0||x>=64||y<0||y>=64) {
        return false;
    }
    
    switch (dir) {
        case Squirt::left:
            
            for (int j=y; j<y+4; j++) {
                if (returndirtstate(x, j)==true) {
                    return false;
                }
                
            }
            break;
        case Squirt::right:
                for (int j=y; j<y+4; j++) {
                if (returndirtstate(x+3, j)==true) {
                    return false;
                }
                
            }
            break;
        case Squirt::up:
            
            for (int i=x;i<x+4; i++) {
                
                if (returndirtstate(i, y+3)==true) {
                    return false;
                }
            }
                        break;
        case Squirt::down:
            for (int i=x;i<x+4; i++) {
                
                if (returndirtstate(i, y)==true) {
                    return false;
                }
                
            }
            break;
        default:
            
            break;
            
    }
    list<actor*>::iterator it;
    it=m_actor.begin();
    while (it!=m_actor.end()) {
        if ((*it)->getID()==IID_BOULDER) {
            double temp;
            temp=pow(((*it)->getX()-x), 2)+pow(((*it)->getY()-y), 2);
            if (sqrt(temp)<=3) {
                return false;
            }
        }
        it++;
    }
    
    return true;
}
void StudentWorld::addgoodies(){
    int temp=getLevel()*25+300;
    int add=rand()%temp+1;
    if (add==1) {
        int choice=rand()%5+1;
        if (choice==1) {
            m_actor.push_back(new Sonar(this));
        }
        else{
            int tempx=0,tempy=0;
            bool addable=false;
            while (addable==false) {
                tempx=rand()%61+0;
                tempy=rand()%61+0;
                list<actor*>::iterator it;
                it=m_actor.begin();
                bool m_addable=true;
                while (it!=m_actor.end()) {
                    if ((*it)->getID()==IID_BOULDER) {
                        double temp;
                        temp=pow((*it)->getX()-tempx, 2)+pow((*it)->getY()-tempy, 2);
                        if (sqrt(temp)<=3) {
                            m_addable=false;
                        }
                    }
                    it++;
                }
                for (int i=tempx; i<tempx+4; i++) {
                    for (int j=tempy; j<tempy+4; j++) {
                        if (returndirtstate(i, j)==true) {
                            m_addable=false;
                            continue;
                        }
                    }
                }
                if (m_addable==true) {
                    addable=true;
                }
        }
        m_actor.push_back(new Waterpool(tempx,tempy,this));
        }
    }

}
void StudentWorld::usesonar(){
    playSound(SOUND_SONAR	);
    list<actor*>::iterator it;
    it=m_actor.begin();
    while (it!=m_actor.end()) {
        if ((*it)->getID()==IID_GOLD||(*it)->getID()==IID_BARREL) {
            double temp;
            temp=pow((*it)->getX()-m_frackman->getX(), 2)+pow((*it)->getY()-m_frackman->getY(), 2);
            if (sqrt(temp)<12) {
                (*it)->setVisible(true);
            }
        }
        it++;
    }
    


}
void StudentWorld::addnuggets(int x, int y){
    Nuggets *temp;
    temp=new Nuggets(x,y,this);
    temp->setVisible(true);
    temp->settype();
    m_actor.push_back(temp);
}
bool StudentWorld::bouldercollision(Boulder *ap, int x, int y)
{ list<actor*>::iterator it;
    it=m_actor.begin();
    while (it!=m_actor.end()) {
        if ((*it)->getID()==IID_BOULDER&&(*it)!=ap) {
            double temp;
            temp=pow((*it)->getX()-x, 2)+pow((*it)->getY()-y, 2);
            if (sqrt(temp)<4) {
                return false;
            }
        }
        it++;
    }
    
    
    
    return true;

}
bool StudentWorld::checkmove(int x,int y){
    list<actor*>::iterator it;
    it=m_actor.begin();
    while (it!=m_actor.end()) {
        if ((*it)->getID()==IID_BOULDER) {
            double temp;
            temp=pow((*it)->getX()-x, 2)+pow((*it)->getY()-y, 2);
            if (sqrt(temp)<=3) {
                return false;
            }
        }
        it++;
    }



    return true;
}
bool StudentWorld::duplicate(int x, int y){
    list<actor*>::iterator it;
    it=m_actor.begin();
    while (it!=m_actor.end()) {
        double temp;
        temp=pow(((*it)->getX()-x), 2)+pow(((*it)->getY()-y), 2);
        if (sqrt(temp)<=6) {
            return false;
        }
        it++;
    }


    return true;
}
void StudentWorld::setDisplayText(){
    int score=getScore();
    string scr;
    if (score<10) {
        scr="00000"+to_string(score);
    }
    if (score>=10&&score<100) {
        scr="0000"+to_string(score);
    }
    if (score>=100&&score<1000) {
        scr="000"+to_string(score);
    }
    if (score>=1000&&score<10000) {
        scr="00"+to_string(score);
    }
    if (score>=10000&&score<100000) {
        scr="0"+to_string(score);
    }
    if (score>=100000) {
        scr=to_string(score);
    }
    int level=getLevel();
    string lvl;
    if (level<10) {
        lvl=" "+to_string(level);
    }
    if (level>=10) {
        lvl=to_string(level);
    }
    int health=m_frackman->gethitpoint()*10;
    string heal;
    if (health==100) {
        heal=to_string(health)+"%";
    }
    else{
    heal=" "+to_string(health)+"%";
    }
    int lives=getLives();
    string live=to_string(lives);
    int squirts = m_frackman->getsquirt();
    string squirt;
    if (squirts<10) {
        squirt=" "+to_string(squirts);
    }
    else{
        squirt=to_string(squirts);
    }
    int gold = m_frackman->getgold();
    string gld;
    if (gold<10) {
        gld=" "+to_string(gold);
    }
    else{
        gld=to_string(gold);
    }
    int sonar =m_frackman->getsonar();
    string son;
    if (sonar<10) {
        son=" "+to_string(sonar);
    }
    else{
        son=to_string(sonar);
    }

    int barrelsLeft = m_barrel;
    string barrel;
    if (barrelsLeft<10) {
        barrel=" "+to_string(barrelsLeft);
    }
    else{
        barrel=to_string(barrelsLeft);
    }
    

    string s="Scr: "+scr+"  Lvl: "+lvl+"  Lives: "+live+"  Hlth: "+heal+"  Wtr: "+squirt+"  Gld: "+gld+"  Sonar: "+son+"  Oil Left: "+barrel;
    setGameStatText(s);
    
    //"Scr: 0321000 Lvl: 52 Lives: 3 Hlth: 80% Water: 20 Gld: 3 Sonar: 1 Oil Left: 2”
}
int StudentWorld::init()
{  int L=2+getLevel();
    m_barrel= min(L, 20);
    int G=5-getLevel() / 2;
    G=max(G, 2);
    m_frackman=new Frackman(this);
    for(int i=0;i<64;i++){
        for(int j=0;j<64;j++){
            if ((i>=30&&i<=33&&j>=4&&j<=59)||j>=60) {
               m_dirt[i][j]=nullptr;
            }
            else{
                m_dirt[i][j]=new Dirt(i,this,j);}
        }
    }
    int numberofboulder=getLevel()/2+2;
    for (int i=0; i<min(numberofboulder,6); i++) {
        int tempx=rand()%61+0;
        int tempy=rand()%37+20;
        if ((tempx>=27&&tempx<=33)||duplicate(tempx, tempy)==false) {
            i--;
            continue;
        }
        
        m_actor.push_back(new Boulder(tempx,tempy,this));
    }
    for (int i=0; i<m_barrel; i++) {
        int tempx=rand()%61+0;
        int tempy=rand()%37+20;
        if ((tempx>=27&&tempx<=33)||duplicate(tempx, tempy)==false) {
            i--;
            continue;
        }
        
        m_actor.push_back(new Barrel(tempx,tempy,this));
    }
    for (int i=0; i<G; i++) {
        int tempx=rand()%61+0;
        int tempy=rand()%37+20;
        if ((tempx>=27&&tempx<=33)||duplicate(tempx, tempy)==false) {
            i--;
            continue;
        }
        
        m_actor.push_back(new Nuggets(tempx,tempy,this));
    }


    return GWSTATUS_CONTINUE_GAME;
}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
