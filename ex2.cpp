#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Location
{
    float x;
    float y;
};

class Unit
{   public:
    void SetLocation(float x, float y);
    Location GetLocation();
    virtual void Move()=0;
    void DisplayCurrentLocation();
    Location firstTargetPosition;
    Location targetPosition;
    float countmove=0;
    float dt=1;

    protected:
    float posx=0;
    float posy=0;

    private:
    Location currentLocation_;
    


};

float DifAng(Location me, Location target)
{
    Location c;
    c.x=0; c.y=0;
    c.x=target.x-me.x;
    c.y=target.y-me.y;
    float a=sqrt((c.x*c.x)+(c.y*c.y));
    float b=c.x/a;
    float d=acos(b);
    return d;
    
}

float DifDis(Location me, Location target)
{
    Location c;
    c.x=0; c.y=0;
    c.x=target.x-me.x;
    c.y=target.y-me.y;
    float a=sqrt((c.x*c.x)+(c.y*c.y));
    return a;
    
}



Location Unit::GetLocation()
{   Location l;
    l.x=Unit::posx;
    l.y=Unit::posy;
    return l;
}

void Unit::Move()
{   

}

void Unit::DisplayCurrentLocation()
{   
    cout<<"["<<Unit::posx<<" "<<Unit::posy<<"]"<<endl;
}


void Unit::SetLocation(float x, float y)
{
    Unit::posx=x;
    Unit::posy=y;
}


class Zergling : public Unit
{   public:
    void Move();
    bool IsSpeedUpgrade(bool isFirstTargetReached);

    private:
    int movespeed=1;
    bool speedUpgrade=false;
    

};

bool Zergling::IsSpeedUpgrade(bool isFirstTargetReached)
{
    if((Zergling::posx=Zergling::firstTargetPosition.x)&&(Zergling::posy==Zergling::firstTargetPosition.y))
        {
            return true;
        }
}

void Zergling::Move()
{
    Location zp=Zergling::GetLocation();
    Zergling::posx=zp.x;
    Zergling::posy=zp.y;

    while((Zergling::posx<=Zergling::firstTargetPosition.x)&&(Zergling::posy<=Zergling::firstTargetPosition.y))
    {
        float ang=DifAng(Zergling::GetLocation(),Zergling::firstTargetPosition);
        Zergling::posx+=cos(ang)*dt*Zergling::movespeed;
        Zergling::posy+=sin(ang)*dt*Zergling::movespeed;
        Zergling::DisplayCurrentLocation();
    }

    while((Zergling::posx<=Zergling::targetPosition.x)&&(Zergling::posy<=Zergling::targetPosition.y))
    {   
        /*if(!Zergling::IsSpeedUpgrade(Zergling::speedUpgrade))
        {   
            float ang=DifAng(Zergling::GetLocation(),Zergling::firstTargetPosition);
            Zergling::posx+=cos(ang)*dt*Zergling::movespeed;
            Zergling::posy+=sin(ang)*dt*Zergling::movespeed;
        }
        */
        //if(Zergling::IsSpeedUpgrade(Zergling::speedUpgrade))
        {   
            Zergling::movespeed=2;
            float ang2=DifAng(Zergling::GetLocation(),Zergling::targetPosition);
            Zergling::posx+=cos(ang2)*dt*Zergling::movespeed;
            Zergling::posy+=sin(ang2)*dt*Zergling::movespeed;
            
        }
    }
    
    if((Zergling::posx>=Zergling::targetPosition.x)&&(Zergling::posy>=Zergling::targetPosition.y))
    {   
        Zergling::SetLocation(Zergling::targetPosition.x,Zergling::targetPosition.y);
    }
}

class Marine : public Unit
{   public:
    void Move();
    void IsZerglingNear(Location zerglingCurrentLocation);

    private:
    int movespeed=1;

};

void Marine::Move()
{   
    Location mp=Marine::GetLocation();
    Marine::posx=mp.x;
    Marine::posy=mp.y;
    while((Marine::posx<=Marine::targetPosition.x) && (Marine::posy<=Marine::targetPosition.y))
    {
        float ang=DifAng(Marine::GetLocation(),Marine::targetPosition);
        Marine::posx+=cos(ang)*dt*Marine::movespeed;
        Marine::posy+=sin(ang)*dt*Marine::movespeed;
        Marine::SetLocation(Marine::posx,Marine::posy);
        Marine::countmove+=dt;

    }
    if (Marine::posx>Marine::targetPosition.x)
    {
        Marine::posx=Marine::targetPosition.x;
    }
    if(Marine::posy>Marine::Marine::targetPosition.y)
    {
        Marine::posy=targetPosition.y;
    }
    Marine::SetLocation(posx,posy);
    cout<<"Marine이 target에 도달하는데 걸린 시간은 "<<countmove<<endl;
    
}

class Stalker : public Unit
{
    void Move();
    void Blink();

    private:
    int movespeed=1;
};

void Stalker::Move()
{

}


int main(void)
{   
    /*Marine m;
    m.targetPosition.x=50;
    m.targetPosition.y=50;
    m.Move();
    m.DisplayCurrentLocation();
    */
    Zergling z;
    z.firstTargetPosition.x=50;
    z.firstTargetPosition.y=0;
    z.targetPosition.x=50;
    z.targetPosition.y=50;
    z.Move();
    z.DisplayCurrentLocation();

    return 0;
}