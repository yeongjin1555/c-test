#include <iostream>

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
    int countmove=0;
    int dt=1;

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
{   
    public:
    void Move();
    bool IsSpeedUpgrade(bool isFirstTargetReached);

    private:
    int movespeed=1;
    bool speedUpgrade=false;
    

};

bool Zergling::IsSpeedUpgrade(bool isFirstTargetReached)
{
    if((Zergling::posx==Zergling::firstTargetPosition.x)&&(Zergling::posy==Zergling::firstTargetPosition.y))
        {   Zergling::speedUpgrade=true;
            return Zergling::speedUpgrade;
        }
    else if((Zergling::posx!=Zergling::firstTargetPosition.x)&&(Zergling::posy!=Zergling::firstTargetPosition.y))
    {
        Zergling::speedUpgrade=false;
        return Zergling::speedUpgrade;
    }
}

void Zergling::Move()
{
    Location zp=Zergling::GetLocation();
    Zergling::posx=zp.x;
    Zergling::posy=zp.y;
    
    while(!Zergling::IsSpeedUpgrade(Zergling::speedUpgrade))
    {
        float ang=DifAng(Zergling::GetLocation(),Zergling::firstTargetPosition);
        Zergling::posx+=cos(ang)*dt*Zergling::movespeed;
        Zergling::posy+=sin(ang)*dt*Zergling::movespeed;
        //Zergling::DisplayCurrentLocation();
        if((Zergling::posx>=Zergling::firstTargetPosition.x)&&(Zergling::posy>=Zergling::firstTargetPosition.y))
        {
            Zergling::posx=Zergling::firstTargetPosition.x;
            Zergling::posy=Zergling::firstTargetPosition.y;
            Zergling::speedUpgrade=true;
        }
    }
    
    while((Zergling::posx<=Zergling::targetPosition.x)&&(Zergling::posy<Zergling::targetPosition.y))
    {   
        
            Zergling::movespeed=2;
            float ang2=DifAng(Zergling::GetLocation(),Zergling::targetPosition);
            Zergling::posx+=cos(ang2)*dt*Zergling::movespeed;
            Zergling::posy+=sin(ang2)*dt*Zergling::movespeed;
            
            if((Zergling::posx>=Zergling::targetPosition.x)&&(Zergling::posy>=Zergling::targetPosition.y))
            {
                Zergling::posx=Zergling::targetPosition.x;
                Zergling::posy=Zergling::targetPosition.y;
            }  
            //Zergling::DisplayCurrentLocation();  
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
    {   //Marine::DisplayCurrentLocation();
        //Marine::IsZerglingNear(Zergling::GetLocation());
        float ang=DifAng(Marine::GetLocation(),Marine::targetPosition);
        Marine::posx+=cos(ang)*dt*Marine::movespeed;
        Marine::posy+=sin(ang)*dt*Marine::movespeed;
        Marine::SetLocation(Marine::posx,Marine::posy);
        Marine::countmove+=dt;

    }
    if((Marine::posx>=Marine::targetPosition.x)&&(Marine::posy>=Marine::targetPosition.y))
        {
            Marine::posx=Marine::targetPosition.x;
            Marine::posy=Marine::targetPosition.y;
        }
    //cout<<"Marine이 target에 도달하는데 걸린 시간은 "<<countmove<<endl;
    
}

void Marine::IsZerglingNear(Location ZerglinCurrentLocation)
{   
    int distance=DifDis(Marine::GetLocation(),ZerglinCurrentLocation);
    if(distance<=5)
    {
        Marine::movespeed=2;
    }
    if(distance>5)
    {
        Marine::movespeed=1;
    }

}

class Stalker : public Unit
{   public:
    void Move();
    void Blink();

    private:
    int movespeed=1;
};

void Stalker::Move()
{
    Location zp=Stalker::GetLocation();
    Stalker::posx=zp.x;
    Stalker::posy=zp.y;
    
    while(!Stalker::IsSpeedUpgrade(Stalker::speedUpgrade))
    {	Stalker::Blink();
        float ang=DifAng(Stalker::GetLocation(),Stalker::firstTargetPosition);
        Stalker::posx+=cos(ang)*dt*Stalker::movespeed;
        Stalker::posy+=sin(ang)*dt*Stalker::movespeed;
        //Stalker::DisplayCurrentLocation();
        if((Stalker::posx>=Stalker::firstTargetPosition.x)&&(Stalker::posy>=Stalker::firstTargetPosition.y))
        {
            Stalker::posx=Stalker::firstTargetPosition.x;
            Stalker::posy=Stalker::firstTargetPosition.y;
            Stalker::speedUpgrade=true;
        }
    }
    
    while((Stalker::posx<=Stalker::targetPosition.x)&&(Stalker::posy<Stalker::targetPosition.y))
    {   
        
            Stalker::movespeed=1;
            float ang2=DifAng(Stalker::GetLocation(),Stalker::targetPosition);
            Stalker::posx+=cos(ang2)*dt*Stalker::movespeed;
            Stalker::posy+=sin(ang2)*dt*Stalker::movespeed;
            
            if((Stalker::posx>=Stalker::targetPosition.x)&&(Stalker::posy>=Stalker::targetPosition.y))
            {
                Stalker::posx=Stalker::targetPosition.x;
                Stalker::posy=Stalker::targetPosition.y;
            }  
            //Stalker::DisplayCurrentLocation();  
    }
    
    
}

void Stalker::Blink()
{   int a=5/(sqrt(2));
    if(Stalker::countmove%(dt*10)==0)
    {   
        float ang=DifAng(Stalker::GetLocation(),Stalker::targetPosition);
        Stalker::posx+=cos(ang)*dt*a;
        Stalker::posy+=sin(ang)*dt*a;
    }
}

int main(void)
{   
    Marine m;
    m.targetPosition.x=50;
    m.targetPosition.y=50;
    m.Move();
    m.DisplayCurrentLocation();
    
    cout<<" "<<endl;
    
    Zergling z;
    z.firstTargetPosition.x=50;
    z.firstTargetPosition.y=0;
    z.targetPosition.x=50;
    z.targetPosition.y=50;
    z.Move();
    z.DisplayCurrentLocation();
    
    cout<<" "<<endl;

    Stalker s;
    s.firstTargetPosition.x=10;
    s.firstTargetPosition.y=20;
    s.targetPosition.x=50;
    s.targetPosition.y=50;
    s.Move();
    s.DisplayCurrentLocation();
    return 0;
}