#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
actor::~actor()
{}
void actor::setdead(){
    m_dead=true;
}
void Frackman::determinedead(){
    if (gethitpoint()==0) {
        returnworld()->playSound(SOUND_PLAYER_GIVE_UP);
        setdead();
    }

}
//Frackman class implement
Frackman::Frackman(StudentWorld *world): actor(IID_PLAYER,30,60,right,1.0,0,world)
{     sethitpoint(10);
    setVisible(true);
    m_sonar=1;
    m_gold=0;
    m_squirt=5;}
//constructor for frackman
void Frackman:: dosomething(){
    determinedead();
    if (deadstaus()==true) {
        return;
    }
    else{
        
    for (int i=getX(); i<=(getX()+3); i++) {
         for (int j=getY(); j<=(getY()+3); j++) {
             returnworld()->Frackmandeletedirt(i,j);
         }
     }
     //remove dirt
         int ch;
     if (returnworld()->getKey(ch) == true) {
         // user hit a key this tick! switch (ch)
         switch (ch){
             case  KEY_PRESS_LEFT:
                 if (getDirection()!=left) {
                     setDirection(left);
                 }
                 else if(getX()>0)
                     if(returnworld()->checkmove(getX()-1, getY())!=false){
                         moveTo(getX()-1, getY());}
                     break;
             case  KEY_PRESS_RIGHT:
                 if (getDirection()!=right) {
                     setDirection(right);
                 }

                 else if(getX()<60)
                     if(returnworld()->checkmove(getX()+1, getY())!=false)

                     {moveTo(getX()+1, getY());}
                 break;
             case KEY_PRESS_UP:
                 if (getDirection()!=up) {
                     setDirection(up);
                 }

                else if (getY()<60) {
                    if(returnworld()->checkmove(getX(), getY()+1)!=false)
                    {moveTo(getX(), getY()+1);}
                 }
                 break;
             case KEY_PRESS_DOWN:
                 if (getDirection()!=down) {
                     setDirection(down);
                 }

                else if (getY()>0) {
                    if(returnworld()->checkmove(getX(), getY()-1)!=false)

                    { moveTo(getX(), getY()-1);}
                 }
                 break;
             case KEY_PRESS_ESCAPE:
                 setdead();
                 break;
             case KEY_PRESS_TAB:
                 if (getgold()>0) {
                     returnworld()->addnuggets(getX(), getY());
                     decgold();

                 }
                 break;
             case KEY_PRESS_SPACE:
                 if (getsquirt()>0) {
                     switch (getDirection()) {
                         case left:
                             if (firesquirt(getX(), getY(), left)==false||returnworld()->firesquirt(getX()-4, getY())==false) {
                                 returnworld()->playSound(SOUND_PLAYER_SQUIRT);
                                 m_squirt--;
                             }
                             else{
                                 returnworld()->addsquirt(getX()-4, getY(), left);
                                 m_squirt--;
                             }
                             break;
                         case right:
                             if (firesquirt(getX(), getY(), right)==false||returnworld()->firesquirt(getX()+4, getY())==false) {
                                 returnworld()->playSound(SOUND_PLAYER_SQUIRT);
                                 m_squirt--;
                             }
                             else{
                                 returnworld()->addsquirt(getX()+4, getY(), right);
                                 m_squirt--;
                             }
                             break;
                         case up:
                             if (firesquirt(getX(), getY(), up)==false||returnworld()->firesquirt(getX(), getY()+4)==false) {
                                 returnworld()->playSound(SOUND_PLAYER_SQUIRT);
                                 m_squirt--;
                             }
                             else{
                                 returnworld()->addsquirt(getX(), getY()+4, up);
                                 m_squirt--;
                             }
                             break;
                         case down:
                             if (firesquirt(getX(), getY(), down)==false||returnworld()->firesquirt(getX(), getY()-4)==false) {
                                 returnworld()->playSound(SOUND_PLAYER_SQUIRT);
                                 m_squirt--;
                             }
                             else{
                                 returnworld()->addsquirt(getX(), getY()-4, down);
                                 m_squirt--;
                             }
                             break;
                             
                             
                             
                             
                         default:
                             break;
                     }

                 }                   break;
             case 'z':
             case 'Z':
                 if (getsonar()>0) {
                     returnworld()->usesonar();
                     decsonar();
                 }
                 break;
                 default:
                 break;
         
         }
     }

    return;
    }
}
bool Frackman::firesquirt(int x, int y, Direction dir){
    if (x<0||x>64||y<0||y>60) {
        return false;
    }
       switch (dir) {
        case left:
               for(int i=x;i>=x-4;i--){
                for (int j=y; j<y+4; j++) {
                    if (returnworld()->returndirtstate(i, j)==true) {
                        return false;
                    }

            }
               }
            return true;
            
            
            break;
        case right:
               for(int i=x+3;i<=x+7;i++){
                for (int j=y; j<y+4; j++) {
                    if (returnworld()->returndirtstate(i, j)==true) {
                        return false;
                    }
               
            }
       }
            return true;
            break;
        case up:
            for (int i=x;i<x+4; i++) {
                for(int j=y+3;j<=y+7;j++){
                    if (returnworld()->returndirtstate(i, j)==true) {
                        return false;
                }
                }
            }
            return true;
            break;
        case down:
            for (int i=x;i<x+4; i++) {
                for(int j=y;j>=y-4;j--){
                    if (returnworld()->returndirtstate(i, j)==true) {
                        return false;
                    }
            }
            }
            return true;
            break;
        default:
            return true;
            break;
        
    }

}

//Frackmanclass end;
//Boulder class implement;
Boulder:: Boulder(int x,int y,StudentWorld *world)
:actor( IID_BOULDER,x,y,down,1.0,3,world)
{
    setVisible(true);
 m_stable=true;
    for(int i=getX();i<getX()+4;i++){
        for (int j=getY(); j<getY()+4; j++) {
            returnworld()->dirtremove(i, j);
        }
    }
        
        }
void Boulder::hitFrackman(){
    double temp;
    temp=pow((returnworld()->returnfrackman()->getX()-getX()), 2)+pow((returnworld()->returnfrackman()->getY()-getY()), 2);
    if (sqrt(temp)<=3) {
        returnworld()->returnfrackman()->sethitpoint(0);
    }
    
}
void Boulder::decreasewaittime(){
    m_waittime--;
    if (m_waittime==0) {
        returnworld()->playSound(SOUND_FALLING_ROCK);
    }
}
void Boulder::checkstate(){
    
    if (returnworld()->returndirtstate(getX(), getY()-1)==false&&returnworld()->returndirtstate(getX()+1, getY()-1)==false&&returnworld()->returndirtstate(getX()+2, getY()-1)==false&&returnworld()->returndirtstate(getX()+3, getY()-1)==false)
    {
        setunstable();
        setwaitime();
    }
    else
        return;
}
bool Boulder::checkbottom(){
    if (returnworld()->returndirtstate(getX(), getY()-1)==false&&returnworld()->returndirtstate(getX()+1, getY()-1)==false&&returnworld()->returndirtstate(getX()+2, getY()-1)==false&&returnworld()->returndirtstate(getX()+3, getY()-1)==false)
    {
        return true;    }
    else
        return false;
}
void Boulder::dosomething()

{  if(deadstaus()==true)
     {return;}
    if (state()==true) {
        checkstate();
        return;
    }
    else{
        if (returnwaittime()!=0) {
            decreasewaittime();
        }
        else{
           
            if (getY()<=0||checkbottom()==false||returnworld()->bouldercollision(this, getX(), getY())==false)            {
                setVisible(false);
                setdead();
            }
            else{
                moveTo(getX(), getY()-1);
                
                hitFrackman();
            }
            
        }
    //did not implement hit actor
    }
}
//implement of Boulder end
//Implement of barrel
Barrel::Barrel(int x,int y, StudentWorld* m_world)
:actor( IID_BARREL,x,y,right,1.0,2,m_world)
{
    setVisible(false);

}
void Barrel::determinedead(){
    double temp=pow(returnworld()->returnfrackman()->getX()-getX(), 2)+pow(returnworld()->returnfrackman()->getY()-getY(), 2);
    if (sqrt(temp)<=3) {
        setdead();
        returnworld()->playSound( SOUND_FOUND_OIL);
        return;
    }


}
void Barrel::dosomething()
{  if (deadstaus()==true)
     {return;}
    if (isVisible()==false) {
        double temp= pow(returnworld()->returnfrackman()->getX()-getX(), 2)+pow(returnworld()->returnfrackman()->getY()-getY(), 2);
        if (sqrt(temp)<=4) {
            setVisible(true);
            return;
        }
    }
    else{
        determinedead();
        if (deadstaus()==true) {
            returnworld()->increaseScore(1000);
            returnworld()->barrelpickup();
        }
    }
}
//end of implement Barrel
//Nugget implement begin

Nuggets::Nuggets(int x,int y, StudentWorld *m_world)
:actor( IID_GOLD,x,y,right,1.0,2,m_world)
{ m_type="initial";
    setVisible(false);
    m_state=true;
    m_length=100;
}
void Nuggets::determinedead(){
    double temp=pow(returnworld()->returnfrackman()->getX()-getX(), 2)+pow(returnworld()->returnfrackman()->getY()-getY(), 2);
    if (sqrt(temp)<=3) {
        setdead();
        returnworld()->playSound( SOUND_GOT_GOODIE);
        return;
    }


}
void Nuggets::dosomething(){
    if (deadstaus()==true)
    {return;}
    if (m_type=="initial") {
        if (isVisible()==false) {
            double temp= pow(returnworld()->returnfrackman()->getX()-getX(), 2)+pow(returnworld()->returnfrackman()->getY()-getY(), 2);
            if (sqrt(temp)<=4) {
                setVisible(true);
                return;
            }
        }
        else{
            determinedead();
            if (deadstaus()==true) {
                returnworld()->increaseScore(10);
                returnworld()->returnfrackman()->incgold();
            }
        }
    }
    else{
        if (m_type=="drop") {
            if (statestatus()==true) {
                 setstatus();
                return;
            }
            else{
                if (returnlength()!=0) {
                    setlength();
                    //implement pick up by protestor here;
                }
                else{
                    setdead();}
            }
        }
    }
}
//end of implement of Nugget
//implement of Sonar Kits
Sonar::Sonar(StudentWorld*m_world)
:actor(IID_SONAR,0,60,right,1.0,2,m_world)
{setVisible(true);
    int temp=300-m_world->getLevel()*10;
    temp=max(100,temp);
    m_length=temp;
}
void Sonar::determinedead(){
    double temp=pow(returnworld()->returnfrackman()->getX()-getX(), 2)+pow(returnworld()->returnfrackman()->getY()-getY(), 2);
    if (sqrt(temp)<=3) {
        setdead();
        returnworld()->playSound( SOUND_GOT_GOODIE);
        return;
    }
}
void Sonar::dosomething(){
    if (deadstaus()==true)
    {return;}
    if (m_length!=0) {
        setlength();
        determinedead();
        if (deadstaus()==true) {
            returnworld()->increaseScore(75);
            returnworld()->returnfrackman()->incsonar();
        }
    }
    else{
        setdead();
    }
  }
//end of implement of sonar
//implement of Waterpool
Waterpool::Waterpool(int x,int y,StudentWorld* m_world)
:actor(IID_WATER_POOL,x,y,right,1.0,2,m_world)
{setVisible(true);
    int temp=300-m_world->getLevel()*10;
    temp=max(100,temp);
    m_length=temp;
}
void Waterpool::determinedead(){
    double temp=pow(returnworld()->returnfrackman()->getX()-getX(), 2)+pow(returnworld()->returnfrackman()->getY()-getY(), 2);
    if (sqrt(temp)<=3) {
        setdead();
        returnworld()->playSound( SOUND_GOT_GOODIE);
        return;
    }
}
void Waterpool::dosomething(){
    if (deadstaus()==true)
    {return;}
    if (m_length!=0) {
        setlength();
        determinedead();
        if (deadstaus()==true) {
            returnworld()->increaseScore(100);
            returnworld()->returnfrackman()->incsquirt();
        }
    }
    else{
        setdead();
    }
}
//end of implement of waterpool
//implement of Squirt
Squirt::Squirt(int x,int y,Direction dir,StudentWorld *m_world)
:actor(IID_WATER_SPURT,x,y,dir,1.0,1,m_world)
{setVisible(true);
    m_distance=4;
    
}
void Squirt::dosomething(){
    if (deadstaus()==true) {
        return;
    }
    if (m_distance==0) {
        setdead();
        return;
    }
    else{
    //implement hurt protestor
        switch (getDirection()) {
            case right:
                if (returnworld()->squirtset(getX()+1, getY(),right)==false) {
                    setdead();
                }
                else{
                    moveTo(getX()+1, getY());
                    m_distance--;   }
                break;
            case left:
                if (returnworld()->squirtset(getX()-1, getY(),left)==false) {
                    setdead();
                }
                else{
                    moveTo(getX()-1, getY());
                    m_distance--;}
                break;
            case up:
                if (returnworld()->squirtset(getX(), getY()+1,up)==false) {
                    setdead();
                }
                else{
                    moveTo(getX(), getY()+1);
                    m_distance--;}
                break;
            case down:
                if (returnworld()->squirtset(getX(), getY()-1,down)==false) {
                    setdead();
                }
                else{
                    moveTo(getX(), getY()-1);
                    m_distance--;}
                break;


    
            default:
                break;
        }
    }


}
//Implement of Squirt end
//Implement of Protestor
Protestor::Protestor(int imageID, StudentWorld* m_world)
:actor(imageID,60,60,left,1.0,0,m_world)
{setVisible(true);
    m_state=false;
    m_numofmove=rand()%53+8;
    int temp=3-returnworld()->getLevel()/4;
    m_resttime=max(0,temp);
}
void Protestor::determinedead(){
    if (gethitpoint()==0) {
        m_state=true;
        returnworld()->playSound(SOUND_PROTESTER_GIVE_UP);
    }

}
//implement of protestor end
//implement of regular protestor

