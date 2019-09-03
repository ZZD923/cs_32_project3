#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include<list>
using namespace std;
class actor;
class Dirt;
class Frackman;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
    {delete m_frackman;
        
        for(int i=0;i<64;i++){
            for(int j=0;j<64;j++){
                delete m_dirt[i][j];
            }
        }
        list<actor*>::iterator it;
        it=m_actor.begin();
        while (it!=m_actor.end()) {
            m_actor.erase(it);
            it++;
        }
	}
    void barrelpickup(){
        m_barrel--;
    
    }
    bool squirtset(int x,int y,Squirt::Direction dir);
    bool firesquirt(int x,int y);
    void addgoodies();
    void addsquirt(int x,int y,Frackman::Direction dir);
    int returnbarrel(){
        return m_barrel;
    }
    Frackman* returnfrackman(){
        return m_frackman;
    }
    void setDisplayText();
    virtual~StudentWorld(){
        
        cout<<"fuck";
    }
    virtual int init();
   	virtual int move()
	{
		  // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		  // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
        if (m_frackman->deadstaus()==true) {
            decLives();
            return GWSTATUS_PLAYER_DIED;
           
        }
        else {
            if (returnbarrel()==0) {
                playSound(SOUND_FINISHED_LEVEL);
                return GWSTATUS_FINISHED_LEVEL;
            }
            setDisplayText();
            m_frackman->dosomething();
            addgoodies();
            list<actor*>::iterator it;
            it=m_actor.begin();
            while (it!=m_actor.end()) {
                if ((*it)->deadstaus()==true) {
                    delete *it;
                    m_actor.erase(it);
                }
                it++;
            }

            it=m_actor.begin();
            while (it!=m_actor.end()) {
                (*it)->dosomething();
                it++;
            }
         
            return GWSTATUS_CONTINUE_GAME;
        }
        
    }
   void dirtremove(int x,int y)//for other actor to remove dirt
    {
             delete m_dirt[x][y];
       m_dirt[x][y]=nullptr;
    
    }
	virtual void cleanUp()
    {
        delete m_frackman;
        
        for(int i=0;i<64;i++){
            for(int j=0;j<64;j++){
                delete m_dirt[i][j];
            }
        }
        if (m_actor.empty()!=true) {
            cout<<"Smallberg!";
        }
        list<actor*>::iterator it;
        it=m_actor.begin();
        while (it!=m_actor.end()) {
            delete (*it);
            m_actor.erase(it);
            it++;
        }
        if (m_actor.empty()==true) {
            cout<<"Nachenburg!";
        }
    }
    void usesonar();
    void addnuggets(int x,int y);
    bool bouldercollision(Boulder *ap,int x,int y);
    bool checkmove(int x,int y);//to check whether frackman could encounter a boulder
    bool duplicate(int x,int y);//when initiate check whether 2 actor in close place
    bool returndirtstate(int x,int y)//check  whether the dirt x y is nullptr
    {
        if (m_dirt[x][y]==nullptr) {
            return false;
        }
        else
            return true;
    }
    void Frackmandeletedirt(int x,int y)//Frackman use to remove dirt while move
    {
        if(x>=64||y>=64||(x>=30&&x<=33&&y>=4&&y<=59))
            return;
        else if (m_dirt[x][y]!=nullptr) {
            playSound(SOUND_DIG);
            dirtremove(x, y);
                     }
        
        else{
            return;        }
    }
private:
    Frackman *m_frackman;
    Dirt  *m_dirt[64][64];
    list<actor*> m_actor;
    int m_barrel;
};

#endif // STUDENTWORLD_H_
