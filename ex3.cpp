#include <iostream>
#include <time.h>
#include <deque>

class fight{
    
public : 
    
    void SetWisdom(int wisoom);
    void SetPower(int power);
    void SetHealth(int health);
    void SetDmg(int dmg);
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


void fight::SetDmg(int dmg){
    dmg_=dmg;
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

int mywar(std::string myAction, std::string enemyAction, me yj, enemy hw){
    
    int myDmg=(50-(hw.GetPower()-yj.GetPower()))/2;
    int enemyDmg=(50-(yj.GetPower()-hw.GetPower()))/2;
    if(myAction=="Attack"){
        if(enemyAction=="Attack"){
            return myDmg;
        }

        if(enemyAction=="Defend"){
            return 0;
        }

        if(enemyAction=="CounterAttack"){
            return 10;
        }

        if(enemyAction=="SpecialMove"){
            return myDmg;
        }

        if(enemyAction=="Invalid"){
            return myDmg; 
        }
        
    }

    if(myAction=="Defend"){
        if(enemyAction=="Attack"){
            return 0;
        }

        if(enemyAction=="Defend"){
            return 0;
        }

        if(enemyAction=="CounterAttack"){
            std::cout<<"상대의 다음 턴은 무효처리됩니다"<<std::endl;
            return -1;
        }

        if(enemyAction=="SpecialMove"){
            return 0;
        }

        if(enemyAction=="Invalid"){
            return 0; 
        }
    }

    if(myAction=="CounterAttack"){
        if(enemyAction=="Attack"){
            return enemyDmg;
        }

        if(enemyAction=="Defend"){
            return 20;
        }

        if(enemyAction=="CounterAttack"){
            return myDmg;
        }

        if(enemyAction=="SpecialMove"){
            return 0;
        }

        if(enemyAction=="Invalid"){
            return myDmg; 
        }
    }

    if(myAction=="SpecialMove"){
        
        float gain=0.1f;

        if(enemyAction=="Defend"){
            gain=0.2f;
        }


        int dmg=myDmg+((yj.GetWisdom()+abs(yj.GetPower()-hw.GetPower()))*gain);
        return dmg;
        
    }

    if(myAction=="Invalid"){
        std::cout<<"당신의 이번 턴은 무효입니다"<<std::endl;
        myAction="free";
        return 0;
    }

}


int enemywar(std::string myAction, std::string enemyAction, enemy hw, me yj){
    
    int myDmg=(50-(yj.GetPower()-hw.GetPower()))/2;
    int enemyDmg=(50-(hw.GetPower()-yj.GetPower()))/2;
    if(myAction=="Attack"){
        if(enemyAction=="Attack"){
            return myDmg;
        }

        if(enemyAction=="Defend"){
            return 0;
        }

        if(enemyAction=="CounterAttack"){
            return 10;
        }

        if(enemyAction=="SpecialMove"){
            return 0;
        }
        
        if(enemyAction=="Invalid"){
            return myDmg; 
        }
    }

    if(myAction=="Defend"){
        if(enemyAction=="Attack"){
            return 0;
        }

        if(enemyAction=="Defend"){
            return 0;
        }

        if(enemyAction=="CounterAttack"){
            
            std::cout<<"나의 다음 턴은 무효처리됩니다"<<std::endl;
            return -1;
        }

        if(enemyAction=="SpecialMove"){
            return 0;
        }

        if(enemyAction=="Invalid"){
            return 0; 
        }
    }

    if(myAction=="CounterAttack"){
        if(enemyAction=="Attack"){
            return enemyDmg;
        }

        if(enemyAction=="Defend"){
            return 20;
        }

        if(enemyAction=="CounterAttack"){
            return myDmg;
        }

        if(enemyAction=="SpecialMove"){
            return 0;
        }

        if(enemyAction=="Invalid"){
            return myDmg; 
        }
    }

    if(myAction=="SpecialMove"){
        int dmg=hw.GetHealth();
        if(enemyAction=="Attack"){
            return dmg;
        }

        if(enemyAction=="Defend"){
            return dmg/2;
        }

        if(enemyAction=="CounterAttack"){
            return dmg/2;
        }

        if(enemyAction=="SpecialMove"){
            return 0;
        }

        if(enemyAction=="Invalid"){
            return dmg; 
        }
        
    }

    if(myAction=="Invalid"){
        std::cout<<"상대의 이번 턴은 무효입니다"<<std::endl;
        return 0;
    }

}

int main(void){
    
    std::string myAction;
    srand(time(NULL));
    me yj;
    enemy hw;
    yj.SetPower((rand() % 21)+60);
    yj.SetWisdom((rand() % 31)+70);
    hw.SetPower(100);
    hw.SetWisdom(50);
    
    yj.SetDmg(yj.GetPower(),hw.GetPower());
    hw.SetDmg(hw.GetPower(),yj.GetPower());
    
    std::deque<std::string> hw_action=DequeGeneration();
    DequeShow(hw_action,yj.GetWisdom(),hw.GetWisdom());
    std::cout<<std::endl;
    std::cout<<"my Power : "<<yj.GetPower()<<" my Wisdom : "<<yj.GetWisdom()<<std::endl;
    int i=0;
    std::cout<<std::endl;
    std::cout<<"My Health : "<<yj.GetHealth()<<" Enemy's Health : "<<hw.GetHealth()<<std::endl;
    while(i<5){
        if(myAction=="Invalid"){
            int myhit=mywar(myAction,hw_action[i],yj,hw);
            int enemyhit=enemywar(hw_action[i],myAction,hw,yj);
            if(myhit==-1){
                hw_action[i+1]="Invalid";
            }
            if(myhit>=0){
                int hitdmg=hw.GetHealth()-myhit;
                hw.SetHealth(hitdmg);
            }

            if(enemyhit>=0){
                int hitdmg=yj.GetHealth()-enemyhit;
                yj.SetHealth(hitdmg);
            }
        
        
            std::cout<<"My Action : "<<myAction<<" Enemy's Action : "<<hw_action[i]<<std::endl;
            std::cout<<"My Health : "<<yj.GetHealth()<<" Enemy's Health : "<<hw.GetHealth()<<std::endl;
            i+=1;
            myAction="something";
        }
            
        
        else{    
        std::cin>>myAction;
        int myhit=mywar(myAction,hw_action[i],yj,hw);
        int enemyhit=enemywar(hw_action[i],myAction,hw,yj);
        if(myhit==-1){
            hw_action[i+1]="Invalid";
        }
        if(myhit>=0){
            int hitdmg=hw.GetHealth()-myhit;
            hw.SetHealth(hitdmg);
        }

        if(enemyhit==-1){
            myAction="Invalid";
        }
        if(enemyhit>=0){
            int hitdmg=yj.GetHealth()-enemyhit;
            yj.SetHealth(hitdmg);
        }

        
        std::cout<<"My Action : "<<myAction<<" Enemy's Action : "<<hw_action[i]<<std::endl;
        std::cout<<"My Health : "<<yj.GetHealth()<<" Enemy's Health : "<<hw.GetHealth()<<std::endl;
        i+=1;
        }
        
    }

    if(yj.GetHealth()>hw.GetHealth()){
        std::cout<<"축하합니다! 당신이 이겼습니다!"<<std::endl;
    }

    if(yj.GetHealth()<hw.GetHealth()){
        std::cout<<"아깝습니다. 조금 더 분발해보세요"<<std::endl;
    }

    
    /*std::cout<<"my Power : "<<yj.GetPower()<<" my Wisdom : "<<yj.GetWisdom()<<std::endl;
    std::cout<<"enemy Power : "<<hw.GetPower()<<" enemy Wisdom : "<<hw.GetWisdom()<<std::endl;
    std::cout<<"my dmg : "<<yj.GetDmg()<<" enemy dmg : "<<hw.GetDmg()<<std::endl;
    std::cout<<"my Health : "<<yj.GetHealth()<<" enemy Health : "<<hw.GetHealth()<<std::endl;*/
    
    return 0;
}