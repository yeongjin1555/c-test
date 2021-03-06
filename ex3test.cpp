#include <iostream>
#include <time.h>
#include <deque>

class fight{
    
public : 
    
    void SetWisdom(int wisoom);
    void SetPower(int power);
    void SetHealth(int health);
    void SetDmg(int myPower, int enemyPower);
    int GetWisdom();
    int GetPower();
    int GetHealth();
    int GetDmg();
private:

    int power_;
    int wisdom_;
    int health_=100;
    int dmg_;

};



class me : public fight{   

public :
    

private:
    int power_;
    int wisdom_;
    int dmg_;
    int health_=100;
};


class enemy : public fight{
    
public : 
    
private:
    int power_;
    int wisdom_;
    int dmg_;
    int health_=100;
};

void fight::SetPower(int power){
    power_=power;
}

void fight::SetWisdom(int wisdom){
    wisdom_=wisdom;
}

void fight::SetHealth(int health){
    health_=health;
}

void fight::SetDmg(int myPower, int enemyPower){
    dmg_=(50-(enemyPower-myPower))/2;
}
int fight::GetHealth(){
    return health_;
}

int fight::GetWisdom(){
    return wisdom_;
}

int fight::GetPower(){
    return power_;
}

int fight::GetDmg(){
    return dmg_;
}



std::deque<std::string> DequeGeneration(){//항우의 랜덤한 모션 덱에 생성해서 저장 후 출력

    std::deque<std::string> dq={};
    

    for(int i=0; i<5;i++){   
        
        int a= (rand()%3); //a random함수 생성위한 임의변수
        
        if (a==0)
        {
            dq.push_back("Attack");
        }
        if (a==1)
        {
            dq.push_back("Defend");
        }

        if (a==2)
        {
            dq.push_back("CounterAttack");
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

void DequeShow(std::deque<std::string> enemy_action, int myWisdom, int enemyWisdom){//지력에 따라 항우의 action을 랜덤으로 보여줌
    
    int a=(myWisdom-enemyWisdom)/10;
    int count=0;
    int b=0;
    //std::cout<<"Hangwoo's Move Prediction : ";
    std::deque<int> c(5,0);
    
    while(b<a){
        int r=(rand()%2);
        if(r==0){
            int j=(rand()%5);
            if(c[j]==0){
                c[j]=1;
                b+=1;    
            } 

        }
    }
    
    /*for(int i=0;i<enemy_action.size();i++){
        std::cout<<enemy_action[i]<<" ";
    }

    std::cout<<std::endl;
    
    for(int i=0;i<c.size();i++){
        std::cout<<c[i]<<" ";
    }

    std::cout<<std::endl;
*/
    for(int i=0;i<enemy_action.size();i++){
        if(c[i]==1){
            std::cout<<enemy_action[i]<<" ";
        }
        else{
            std::cout<<"? ";
        }
    }

   }


int main(void){
    
    srand(time(NULL));
    me yj;
    enemy hw;
    yj.SetPower((rand() % 21)+60);
    yj.SetWisdom((rand() % 31)+70);
    hw.SetPower(100);
    hw.SetWisdom(50);
    
    std::cout<<yj.GetPower()<<" "<<yj.GetWisdom()<<std::endl;
    yj.SetDmg(yj.GetPower(),hw.GetPower());
    hw.SetDmg(hw.GetPower(),yj.GetPower());
    //std::cout<<"my dmg : "<<yj.GetDmg()<<" enemy dmg : "<<hw.GetDmg()<<std::endl;

    std::deque<std::string> hw_action=DequeGeneration();
    DequeShow(hw_action,yj.GetWisdom(),hw.GetWisdom());
    
   
    return 0;
}