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

float diffAngle(Location myLocation, Location targetLocation)
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
    int moveSpeed_=1;
    bool speedUpgrade_=false;
};

bool Zergling::IsSpeedUpgrade(bool isFirstTargetReached)
{
    if (isFirstTargetReached)
    {
        moveSpeed_ = 2;
    }
    return (moveSpeed_ > 1);
}

void Zergling::Move(){

    Location position = GetLocation();
    float angle1=diffAngle(position, firstTargetPosition_);
    float angle2=diffAngle(position,targetPosition_);
    float distance1=diffDistance(position,firstTargetPosition_);
    float distance2=diffDistance(position,targetPosition_);
    bool need_upgrade = (diffDistance(position, firstTargetPosition_) < epsilon_);
    if(!IsSpeedUpgrade(need_upgrade))
    {
        position.x_-=cos(angle1)*dt_*moveSpeed_;
        position.y_+=sin(angle1)*dt_*moveSpeed_;
        SetLocation(position.x_,position.y_);  
    }
    else{
        position.x_-=cos(angle2)*dt_*moveSpeed_;
        position.y_+=sin(angle2)*dt_*moveSpeed_;
        SetLocation(position.x_,position.y_);
    }
}

class Marine : public Unit{
public:
    void Move();
    void IsZerglingNear(Location ZerlingCurrentLocation);
private:
    bool needSpeedUpgrade_ = false;
    int moveSpeed_=1;
};

void Marine::IsZerglingNear(Location ZerlingCurrentLocation){
    
    float d;
    d=diffDistance(GetLocation(),ZerlingCurrentLocation);
    if(d>5){
        moveSpeed_=1;
        needSpeedUpgrade_ = false;
    }
    else{
        moveSpeed_=2;
        needSpeedUpgrade_ = true;
    }
    
}

void Marine::Move(){
    Location position=GetLocation();
    float angle=diffAngle(position,targetPosition_);
    position.x_-=cos(angle)*dt_*moveSpeed_;
    position.y_+=sin(angle)*dt_*moveSpeed_;
    SetLocation(position.x_, position.y_);
}

class Stalker : public Unit{

public:
    void Move();
    void Blink();

    float ct_=0;
    const float t_=10;

private:
    const int moveSpeed_=1;
    bool firstTargetReached_=false;
};

void Stalker::Move(){

    Location position=GetLocation();
    float angle1=diffAngle(position,firstTargetPosition_);
    float angle2=diffAngle(position,targetPosition_);
    float distance1=diffDistance(position,firstTargetPosition_);
    float distance2=diffDistance(position,targetPosition_);
    if(distance1<epsilon_){
        firstTargetReached_=true;
    }

    if(!firstTargetReached_){
        position.x_-=cos(angle1)*dt_*moveSpeed_;
        position.y_+=sin(angle1)*dt_*moveSpeed_;
        SetLocation(position.x_,position.y_);
    }

    if(firstTargetReached_){
        position.x_-=cos(angle2)*dt_*moveSpeed_;
        position.y_+=sin(angle2)*dt_*moveSpeed_;
        SetLocation(position.x_,position.y_);
    }
}

void Stalker::Blink(){

    float q=5;
    Location position = GetLocation();
    float angle1=diffAngle(position, firstTargetPosition_);
    float angle2=diffAngle(position,targetPosition_);
    float distance1=diffDistance(position,firstTargetPosition_);
    float distance2=diffDistance(position,targetPosition_);
    if(distance1<epsilon_){
        firstTargetReached_=true;
    }

    if(!firstTargetReached_){
        position.x_-=cos(angle1)*q;
        position.y_+=sin(angle1)*q;
        SetLocation(position.x_,position.y_);

        if((abs(position.x_)>abs(firstTargetPosition_.x_))&&(abs(position.y_)>abs(firstTargetPosition_.y_))){

            SetLocation(firstTargetPosition_.x_,firstTargetPosition_.y_);
        }
    }

    if(firstTargetReached_){
        position.x_-=cos(angle2)*q;
        position.y_+=sin(angle2)*q;
        SetLocation(position.x_,position.y_);

        if((position.x_>targetPosition_.x_)&&(position.y_>targetPosition_.y_)){//절대값사용해보기 ㄱㄷ

            SetLocation(targetPosition_.x_,targetPosition_.y_);
        }
    }    
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

    Stalker s;
    s.firstTargetPosition_.x_=10;
    s.firstTargetPosition_.y_=20;
    s.targetPosition_.x_=50;
    s.targetPosition_.y_=50;

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
        if(diffDistance(s.GetLocation(),s.targetPosition_)>s.epsilon_){
           
           if(s.ct_>0){
            s.Move();
            s.DisplayCurrentLocation();
            s.countMove_+=s.dt_;
            s.ct_-=s.dt_;
           }
           
           if(s.ct_<=0){
            s.Blink();
            std::cout<<"Blink!!!"<<std::endl;
            s.DisplayCurrentLocation();
            s.countMove_+=s.dt_;
            s.ct_=s.t_;
            
           }

           
        }

        //std::cout<<std::endl;
    }
    //z.DisplayCurrentLocation();
    //m.DisplayCurrentLocation();
    //s.DisplayCurrentLocation();
    std::cout<<"저글링이 도착하는 시간 : "<<z.countMove_<<std::endl;
    std::cout<<"마린이 도착하는 시간 : "<<m.countMove_<<std::endl;
    std::cout<<"스터커가 도착하는 시간 : "<<s.countMove_<<std::endl;

    return 0;
}