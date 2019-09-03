#ifndef ACTOR_H_
#define ACTOR_H_
#include "GraphObject.h"
#include "GameConstants.h"
class StudentWorld;
class actor:public GraphObject{
public:
    actor(int imageID, int startX, int startY, Direction dir, double size , unsigned int depth ,StudentWorld *ap)
    :GraphObject(imageID,startX,startY,dir,size,depth){
                m_dead=false;
        m_hitpoint=0;
        m_world=ap;
    }
    virtual ~actor();
    void setdead();//let the actor dead
    StudentWorld*returnworld(){
        return m_world;
    }

    bool deadstaus()//return whether the actor is dead
    {
        return m_dead;
    }
    virtual void determinedead()=0;//different reactoin to change dead status for each actor
          void sethitpoint(int initial){
        m_hitpoint=initial;
        }//for each actor to set the hit point
    double gethitpoint(){
        return m_hitpoint;
    }
    void dechitpoint(){
        m_hitpoint-=2;
    }
    virtual void dosomething()=0;
    virtual void getannoyed()=0;
private:
    bool m_dead;
    double m_hitpoint;
    StudentWorld *m_world;
    };

class Dirt:public actor{
public:
    Dirt(int startX,StudentWorld* ap,int startY)
    :actor(IID_DIRT,startX,startY,right,0.25,3.0,ap )
    {  
        setVisible(true);}
    virtual~Dirt(){}
    virtual void determinedead()
    {}
    virtual void dosomething(){
    }
    virtual void getannoyed(){

    }
private:

};
class Frackman:public actor{
public:
    Frackman(StudentWorld *world);
    int getsonar(){
        return m_sonar;
    }
    virtual void determinedead();
    void decsonar(){
        m_sonar--;
    }
    void incsonar(){
        m_sonar++;
    }
    int getgold()
    {return m_gold;}
    bool firesquirt(int x,int y,Direction dir);

    void decgold(){
        m_gold--;
    }
    void incgold(){
        m_gold++;
    }
    void incsquirt(){
        m_squirt+=5;
    }
    int getsquirt(){
        return m_squirt;
    }
    
    virtual ~Frackman(){}
    
    virtual void dosomething();
    virtual void getannoyed(){
        return;
    }
private:
    int m_sonar;
    int m_gold;
    int m_squirt;
};
class Boulder:public actor{
public:
    Boulder(int x,int y,StudentWorld *world);
    virtual ~Boulder()
    {
    }
    bool state(){
        return m_stable;
    }
    virtual void determinedead(){}
    void hitFrackman();
    void checkstate();
    bool checkbottom();
    void setunstable(){
        m_stable=false;
    }
    int returnwaittime(){
        return m_waittime;
    }
    void setwaitime(){
        m_waittime=30;
    }
    void decreasewaittime();
    virtual void dosomething();
    virtual void getannoyed(){
        return;
    }
    
    
private:
    bool m_stable;
    int  m_waittime;
};
class Barrel:public actor{
public:
    Barrel(int x,int y,StudentWorld *m_world);
        virtual void dosomething();
    virtual ~Barrel(){}
    virtual void getannoyed()
    {}
    virtual void determinedead();
private:
};
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Nuggets:public actor{
public:
    Nuggets(int x,int y,StudentWorld *m_world);
       void settype(){
    m_type="drop";
    }
    virtual ~Nuggets(){}
    bool statestatus(){
        return m_state;
    }
    void setstatus(){
        m_state=false;
        m_length=100;
    }
    void setlength(){
        m_length--;
    }
    int returnlength(){
        return m_length;
    }
    virtual void dosomething();
    virtual void getannoyed(){}
    virtual void determinedead();

private:
    std::string m_type;
    bool m_state;
    int  m_length;
};
class Sonar:public actor
{public:
    Sonar(StudentWorld *m_world);
    virtual ~Sonar(){}
    void setlength(){
        m_length--;
    }
    virtual void dosomething();
    virtual void getannoyed(){}
    virtual void determinedead();
    
    
private:
    int m_length;
};
class Waterpool:public actor
{public:
    Waterpool(int x,int y, StudentWorld* m_world);
    virtual ~Waterpool(){}
    void setlength(){
        m_length--;
    }

    virtual void dosomething();
    virtual void getannoyed(){}
    virtual void determinedead();
private:
    int m_length;
};
class Squirt:public actor{
public:
    Squirt(int x,int y, Direction dir,StudentWorld *m_world);
    virtual ~Squirt(){}
    virtual void dosomething();
    virtual void getannoyed(){}
    virtual void determinedead(){}

private:
    int m_distance;
};
class Protestor:public actor{
public:
    Protestor(int imageID,StudentWorld*m_world);
    virtual~Protestor(){}
    virtual void pickupgold()=0;
    virtual void dosomething()=0;
    virtual void getannoyed()=0;
    virtual void determinedead();
private:
    bool m_state;
    int m_resttime;
    int m_numofmove;
};
#endif // ACTOR_H_
