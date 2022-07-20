#include <iostream>
#include <cmath>
struct Location{
    float x_=0.f;
    float y_=0.f;
};

class Unit{
public:
    void SetLocation(float x, float y);
    virtual void Move()=0;
    void DisplayCurrentLocation();
    Location GetLocation();
    const float dt_=0.1f;
    const float epsilon_=0.1f;
    Location firstTargetPosition_;
    Location targetPosition_;
    float countMove_=0.f;

private:
    Location currentLocation_;
};

float diffDistance(Location myLocation, Location targetLocation)
{
    Location c;
    c.x_=myLocation.x_-targetLocation.x_;
    c.y_=myLocation.y_-targetLocation.y_;
    float distance=std::sqrt((c.x_*c.x_)+(c.y_*c.y_));
    return distance;
}

float diffAng(Location myLocation, Location targetLocation)
{
    Location c;
    c.x_=myLocation.x_-targetLocation.x_;
    c.y_=myLocation.y_-targetLocation.y_;
    float distance=std::sqrt((c.x_*c.x_)+(c.y_*c.y_));
    float a=c.x_/distance;
    float angle=acos(a);
    return angle;
}

Location Unit::GetLocation(){
    return Unit::currentLocation_;
}

void Unit::SetLocation(float x, float y){
    Unit::currentLocation_.x_=x;
    Unit::currentLocation_.y_=y;
}

void Unit::DisplayCurrentLocation(){
    std::cout<<"["<<Unit::currentLocation_.x_<<" "<<Unit::currentLocation_.y_<<"]"<<std::endl;
}


class Zergling : public Unit{
    public:
    void Move();
    bool IsSpeedUpgrade(bool isFirstTargetReached);
    private:
    int moveSpeed=1;
    bool speedUpgrade=false;
};

bool Zergling::IsSpeedUpgrade(bool isFirstTargetReached)
{
    if (isFirstTargetReached)
    {
        moveSpeed = 2;
    }
    return (moveSpeed > 1);
}

void Zergling::Move(){

    Location p = GetLocation();
    float ang1=diffAng(p, firstTargetPosition_);
    float ang2=diffAng(p,targetPosition_);
    float dis1=diffDistance(p,firstTargetPosition_);
    float dis2=diffDistance(p,targetPosition_);
    bool need_upgrade = (diffDistance(p, firstTargetPosition_) < epsilon_);
    if(!IsSpeedUpgrade(need_upgrade))
    {
        p.x_-=cos(ang1)*dt_*moveSpeed;
        p.y_+=sin(ang1)*dt_*moveSpeed;
        SetLocation(p.x_,p.y_);  
    }
    else{
        p.x_-=cos(ang2)*dt_*moveSpeed;
        p.y_+=sin(ang2)*dt_*moveSpeed;
        SetLocation(p.x_,p.y_);
    }
}

class Marine : public Unit{
public:
    void Move();
    void IsZerglingNear(Location ZerlingCurrentLocation);
private:
    bool needSpeedUpgrade_ = false;
    int moveSpeed=1;
};

void Marine::IsZerglingNear(Location ZerlingCurrentLocation){
    
    float d;
    d=diffDistance(GetLocation(),ZerlingCurrentLocation);
    if(d>5){
        moveSpeed=1;
        needSpeedUpgrade_ = false;
    }
    else{
        moveSpeed=2;
        needSpeedUpgrade_ = true;
    }
    
}

void Marine::Move(){
    Location p=GetLocation();
    float ang=diffAng(p,targetPosition_);
        p.x_-=cos(ang)*dt_*moveSpeed;
        p.y_+=sin(ang)*dt_*moveSpeed;
        SetLocation(p.x_, p.y_);
}
int main(void){

    Zergling z;
    z.firstTargetPosition_.x_=50;
    z.firstTargetPosition_.y_=0;
    z.targetPosition_.x_=50;
    z.targetPosition_.y_=50;

    Marine m;
    m.targetPosition_.x_=50;
    m.targetPosition_.y_=50;

    while(diffDistance(z.GetLocation(),z.targetPosition_) > z.epsilon_){
        
        z.Move();
        //z.DisplayCurrentLocation();
        z.countMove_+=z.dt_;

        if(diffDistance(m.GetLocation(),m.targetPosition_) > m.epsilon_){

            m.IsZerglingNear(z.GetLocation());
            m.Move();
            m.countMove_+=m.dt_;
            //m.DisplayCurrentLocation();
        }
        //std::cout<<std::endl;
    }
    z.DisplayCurrentLocation();
    m.DisplayCurrentLocation();
    std::cout<<"저글링이 도착하는 시간 : "<<z.countMove_<<std::endl;
    std::cout<<"마린이 도착하는 시간 : "<<m.countMove_<<std::endl;

    return 0;
}