#include <iostream>
#include <time.h>
#include <deque>

class fight{
    
public : 
    int power_;
    int wisdom_;
    int health_=100;
    int dmg_;
    
    void Attack();
    void Defend();
    void Counterattack();
    void SpecialMove();

    

};



class me : public fight
{   

public :
    int power_;
    int wisdom_;
    int dmg_;
    int health_=100;

    void Attack();
    void Defend();
    void Counterattack();
    void SpecialMove();
    void DequeShow(std::deque<std::string> enemy_action);
    
};


class enemy : public fight{
    
public : 
    int power_=100;
    int wisdom_=50;
    int dmg_;
    int health_=100;

    void Attack();
    void Defend();
    void Counterattack();
    void SpecialMove();
    
};

std::deque<std::string> DequeGeneration(){//항우의 랜덤한 모션 덱에 생성해서 저장 후 출력

    std::deque<std::string> dq;
    

    for(int i=0; i<5;i++){   
        
        int a= (rand()%3); //a random함수 생성위한 임의변수
        
        if (a==0)
        {
            dq[i]="Attack";
        }
        if (a==1)
        {
            dq[i]="Defend";
        }

        if (a==2)
        {
            dq[i]="CounterAttack";
        }
    }
        
    
    int b= (rand()%2);//b,c Specialmove 넣기 위한 임의의 변수
        if(b==1)
        {
            int c= (rand()%5);
            dq[c]="SpecialMove";
        }

        
    return dq;

 
}

void me::DequeShow(std::deque<std::string> enemy_action){//지력에 따라 항우의 action을 랜덤으로 보여줌
    
    int a=(wisdom_-50)/10;
    
    for(int i=0;i<5;i++){

        std::cout<<enemy_action[i];
    }
    //std::cout<<a<<std::endl;

}


int main(void){
    
    srand(time(NULL));
    me yj;
    enemy hw;
    yj.power_=(rand() % 21)+60;
    yj.wisdom_=(rand() % 31)+70;
    
    std::cout<<yj.power_<<" "<<yj.wisdom_<<std::endl;
    
    std::deque<std::string> hw_action=DequeGeneration();
    yj.DequeShow(hw_action);
    /*for(int i=0;i<5;i++){

        std::cout<<hw_action[i]<<" ";
    }*/
}