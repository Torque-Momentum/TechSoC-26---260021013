
#include <iostream>
#include <vector>
#include <utility> //required for the pair/tuple function for storage of attack + move_power
#include <random> //required for the random + probabilistic things in the program.
#include <cmath>
using namespace std;

int total_crits = 0;
int total_sefs = 0;
int total_turns = 0;
class Bender {
public:
    string name;
    string element;
    int hp;
    int attack;
    int defense;
    int speed;
    int HP;
    std::vector<std::tuple<std::string,int,std::string>> moves;
    int type_counter = 0;
    int critical_counter = 0;
    double base_damage, final_damage;
    double type_multiplier = 0;
    double critical_multiplier = 0; 
    string status_move;
    string healing_move;
    string strongest_move;
    
    //this is for constructor
    Bender(string n, string el, int hp, int atk, int def, int spd,std::vector<std::tuple<std::string,int,std::string>> moves){
        name = n;
        element = el;
        this->hp = hp;
        attack = atk;
        defense = def;
        speed = spd;
        this->moves = moves;
        HP = hp;
        status_move =  get<0>(moves[3]);
        healing_move = get<0>(moves[2]);
        int k;
        for (int i = 0; i < 4; i++) {
        int max = 0;
            if (max <=  get<1>(moves[i])) {
                max = get<1>(moves[i]);
            }
            if(max ==  get<1>(moves[i])) {
                k = i;
            }
        }
        strongest_move = get<0>(moves[k]);
    } 
     bool has_status_move() {
        bool x = true;
        if (get<2>(moves[3]) == "No Effect") {x = false;}
        return x;
    }
     bool has_healing_move() {
        bool x = true;
        if (get<1>(moves[2]) == 0) {x = false;}
        return x;
    }
    //stat display function
    void display_stats() {
        cout << name << " " << "(" << element << ")" << " - ";
        if (hp < 0) {  cout << "HP:" << " " << 0 << "/" << HP << ", ";}
        else { cout << "HP:" << " " << hp << "/" << HP << ", ";}
        cout << "Attack:" << " " << attack << ", ";
        cout << "Defense:" << " " << defense << ", ";
        cout << "Speed:" << " " << speed << endl;
        cout << "Moves: ";
        cout << get<0>(moves[0]) << "(" << get<1>(moves[0]) << ") , " << endl;
        cout << get<0>(moves[1]) << "(" << get<1>(moves[1]) << ") , " << endl;
        cout << get<0>(moves[2]) << "(" << get<1>(moves[2]) << ") , " << endl;
        cout << get<0>(moves[3]) << "(" << get<1>(moves[3]) << ") , " << endl;
       


    }
    //status_effects

    //attack function
  
    void attacker(Bender& n, int idx) {
        if (idx >= 0 && idx < moves.size()) {
            cout << name << " used " <<  get<0>(moves[idx]) << "!"<< endl;
            base_damage = attack * get<1>(moves[idx])/n.defense;
            
            if ((element == "Fire" && n.element == "Water") ||
                (element == "Water" && n.element == "Earth") ||
                (element == "Earth" && n.element == "Air") ||
                (element == "Air" && n.element == "Fire")) {
                    type_multiplier = 0.5;
                }
            else if ((element == "Water" && n.element == "Fire") ||
                (element == "Earth" && n.element == "Water") ||
                (element == "Air" && n.element == "Earth") ||
                (element == "Fire" && n.element == "Air")) {
                    type_multiplier = 2.0;
                }
            else { type_multiplier = 1.0;}

            
            if (get<1>(moves[idx]) == 0) {
                hp = hp + 0.3 * HP; //HEALING MOVE RESTORES 30% of its TOTAL HP
                cout<< name << " is back to " << hp << " HP!" << endl;
            }
            if (type_multiplier == 2.0 && get<1>(moves[idx]) != 0) {
                cout << "Super Effective!" << endl;
                type_counter++;
                
            }
            else if (type_multiplier == 0.5) {
                cout << "It is not very effective!" << endl;
            }
           
            double critical_chance = 0.1;
            std::random_device rd;
            std::mt19937 Prob(rd());
            std::uniform_int_distribution<int> fav_case(1,100);
            if (fav_case(Prob) <=  critical_chance * 100) {critical_multiplier = 2.0;}
            else {critical_multiplier = 1.0;}
            if (critical_multiplier == 2.0 && get<1>(moves[idx]) != 0) {
                cout << "It's a critical hit!" << endl;
                critical_counter++;
                
            }

            final_damage = base_damage * type_multiplier * critical_multiplier;
            cout << n.name << " took " << final_damage << " damage!" << endl;
            n.hp -= final_damage;
            if (n.hp < 0) {n.hp = 0;}
            cout << n.name << " HP: " << n.hp << "/" << n.HP << endl;
        }
        
    }
    //check if fainted
    void is_fainted() {
        bool x;
        if (hp <= 0) {x = true;}
        else {x = false;}
        cout << std::boolalpha << x << endl;
    }
    //Display attacks
    void showAttacks() {
        for (int i = 0; i <= 3; i++) {
           cout << i+1 << "." << get<0>(moves[i]) <<"\n";
        }
    }
    //new constructor for variable objects (x,y)
    Bender() {
        name = "";
        element = "";
        this->hp = 0;
        attack = 0;
        defense = 0;
        speed = 0;
    }

};
class Duel : public Bender {
public:
    Duel() {};
    Bender b1;
    Bender b2;
    Duel (Bender b1, Bender b2) {
        this->b1 = b1;
        this->b2 = b2;
    }
    Bender* first;
    Bender* second;

    Bender *Winner;
    Bender *Loser;
    
    
    void start_duel() {
        cout<< "\n";cout<< "\n";cout<< "\n";
        cout << "=== DUEL BEGINS! ===" << endl;
        cout<< "\n";
        cout << b1.name << " " << "(" << b1.element << ", " << "HP:" << b1.hp << "/" << b1.HP << ") ";
        cout << "VS ";
        cout << b2.name << " " << "(" << b2.element << ", " << "HP:" << b2.hp << "/" << b2.HP << ") " << endl;
        cout<< "\n";cout<< "\n";cout<< "\n";
        int i = 1;
       do {
            if (b1.speed > b2.speed) {
                first = &b1;
                second = &b2;
            }
            else if (b1.speed < b2.speed) {
                first = &b2;
                second = &b1;
            }
            else {
                std::random_device rd;
                std::mt19937 assign(rd());
                std::uniform_int_distribution<int> choice(0,1);
                int h = choice(assign);
                if (h == 0) {
                    first = &b1;
                    second = &b2;
                }
                else if (h == 1) {
                    first = &b2;
                    second = &b1;
                }


            }

            cout << "Turn " << i << ": ";
            cout << first->name << " goes first!" << endl;
            cout<< "\n";
            first->attacker(*second,Rand_Move());
            cout<< "\n";
            i++;

            if (second->hp == 0) {break;}
            cout << "Turn " << i << ": ";
            cout << second->name << " strikes back!" << endl;
            cout<< "\n";
            second->attacker(*first,Rand_Move());
            cout << "\n";
            i++;

        }  while(!((first->hp == 0 || second->hp == 0))) ;




        if (first->hp == 0) {
            cout << first->name << " fainted!" << endl;
            cout << second->name << " wins the duel!" << endl;
            cout << "\n" ;
            cout << "Duel Summary:" << endl;
            cout << "-Winner: "<< second->name << endl;
            cout << "-Turns:  "<< i-1 << endl;
            total_turns += (i-1);
            cout << "-Critical Hits: "<< first->critical_counter + second->critical_counter << endl;
            total_crits += (first->critical_counter + second->critical_counter);
            cout << "-Super Effective Hits: "<< first->type_counter + second->type_counter << endl;
            total_sefs += (first->type_counter + second->type_counter);
            Winner = second;
            Loser = first;
        }
        else if (second->hp == 0) {
            cout << second->name << " fainted!" << endl;
            cout << first->name << " wins the duel!" << endl;
            cout << "\n" ;
            cout << "Duel Summary:" << endl;
            cout << "-Winner: "<< first->name << endl;
            cout << "-Turns:  "<< i-1 << endl;
            total_turns += (i-1);
            cout << "-Critical Hits: "<< first->critical_counter + second->critical_counter << endl;
            total_crits += (first->critical_counter + second->critical_counter);
            cout << "-Super Effective Hits: "<< first->type_counter + second->type_counter << endl;
            total_sefs += (first->type_counter + second->type_counter);
            Winner = first;
            Loser = second;
        }

    }
    int Rand_Move() {
        std::random_device moveseed;
        std::mt19937 movegen(moveseed());
        std::uniform_int_distribution<int> moves(0,3);
        return moves(movegen);
    }
};
class Tournament : public Bender, public Duel {
public:
    //we must create a system to choose players now, from the below players
    std::vector<Bender> Players;
    std::vector<Bender> Sort;
    std::vector<Bender> winnersof2; // To get the winners of duels
    std::vector<Bender> winnersof2in4; // To get the winners of semifinals
    Tournament() {};
    Tournament (std::vector<Bender> Players) {
        this-> Players = Players;
    }
    void roundof_2 (int x, int y) {
        Duel tour(Sort.at(x), Sort.at(y));
        tour.start_duel();
        winnersof2.push_back(*tour.Winner);
    }
    void roundof_2in4() {
        Duel tour1(winnersof2.at(0),winnersof2.at(1));
        tour1.start_duel();
        winnersof2in4.push_back(*tour1.Winner);  
    }
    void roundof_4 () {
        cout << "======TOURNAMENT BRACKETS======" << endl;
        cout << "Semifinals 1 : " << Sort.at(0).name << " VS " << Sort.at(1).name << endl;
        cout << "Semifinals 2 : " << Sort.at(2).name << " VS " << Sort.at(3).name << endl;
        cout<< "\n\n\n";
        cout << "SEMIFINALS 1 : " << endl;
        cout << "==========================================================" << endl;
        roundof_2(0,1);
        cout << "==========================================================" << endl;
        cout<< "\n\n\n";
        cout << "SEMIFINALS 2 : " << endl;
        cout << "==========================================================" << endl;
        roundof_2(2,3);
        cout << "==========================================================" << endl;
        cout << "\n\n\n";
        cout << "Winners of SEMIFINALS are : " << endl;
        for (int i = 0; i < winnersof2.size(); i++) {
            cout << i+1 << ". " << winnersof2.at(i).name << endl;
        }
        cout << "======TOURNAMENT BRACKETS======" << endl;
        cout << "Finale : " << winnersof2.at(0).name << " VS " << winnersof2.at(1).name << endl;
        cout << "\n\n\n";
        cout << "==========================================================" << endl;
        roundof_2in4();
        cout << "==========================================================" << endl;
        cout << "======END OF TOURNAMENT!======" << endl;
        cout << "THE WINNER IS : " << winnersof2in4.at(0).name << " !!!!!!!!!" << endl;
        cout << "\n";
        cout << winnersof2in4.at(0).name << "HAS WON THE CHAMPIONSHIP" << endl;
        cout << "======TOURNAMENT STATISTICS======" << endl;
        cout << "Champion : " << winnersof2in4.at(0).name;
        cout << "Total Battles : 3" << endl;
        cout << "Total Turns : " << total_turns << endl;
        cout << "Total Critical Hits : " << total_crits << endl;
        cout << "Total Super Effective Hits : " << total_sefs << endl;

    }
    void roundof_8() {
        cout << "======TOURNAMENT BRACKETS======" << endl;
        cout << "Quaterfinals 1 : " << Sort.at(0).name << " VS " << Sort.at(1).name << endl;
        cout << "Quaterfinals 2 : " << Sort.at(2).name << " VS " << Sort.at(3).name << endl;
        cout << "Quaterfinals 3 : " << Sort.at(4).name << " VS " << Sort.at(5).name << endl;
        cout << "Quaterfinals 4 : " << Sort.at(6).name << " VS " << Sort.at(7).name << endl;
        cout<< "\n\n\n";
        cout << "QUATERFINALS 1 : "<< endl;
            cout << "==========================================================" << endl;
            roundof_2(0,1);
            cout << "==========================================================" << endl;
            cout<< "\n\n\n";
        cout << "QUATERFINALS 2 : "<< endl;
            cout << "==========================================================" << endl;
            roundof_2(2,3);
            cout << "==========================================================" << endl;
            cout<< "\n\n\n";
        cout << "QUATERFINALS 3 : "<< endl;
            cout << "==========================================================" << endl;
            roundof_2(4,5);
            cout << "==========================================================" << endl;
            cout<< "\n\n\n";
        cout << "QUATERFINALS 4 : "<< endl;
            cout << "==========================================================" << endl;
            roundof_2(6,7);
            cout << "==========================================================" << endl;
            cout<< "\n\n\n";
        cout << "Winners of Quaterfinals are : " << endl;
        for (int i = 0; i < winnersof2.size(); i++) {
            cout << i+1 << ". " << winnersof2.at(i).name << endl;
        }

        //FOR RANDOMLY shuffling the benders for semifinals
        std::vector<Bender> random;
        std::random_device seed;
        std::mt19937 gen(seed());
        std::uniform_int_distribution<int> k(0,winnersof2.size()-1);
        while (random.size() < winnersof2.size()) { 
            int m;
            m = k(gen);
            bool found = false;
            for (int i = 0; i < random.size(); i++) { //checker
                    if (random.size() != 0 && random.at(i).name == winnersof2.at(m).name) {
                        found = true;
                    }
                }
            if (found == true) {
                continue;
            }
            else if (found == false) {
                random.push_back(winnersof2.at(m));
            }
        }
        //RANDOM SHUFFLING DONE

        cout << "======TOURNAMENT BRACKETS======" << endl;
        cout << "Semifinals 1 : " << random.at(0).name << " VS " << random.at(1).name << endl;
        cout << "Semifinals 2 : " << random.at(2).name << " VS " << random.at(3).name << endl;
        cout<< "\n\n\n";
        cout << "SEMIFINALS 1 : " << endl;
        cout << "==========================================================" << endl;
        roundof_2(0,1);
        cout << "==========================================================" << endl;
        cout<< "\n\n\n";
        cout << "SEMIFINALS 2 : " << endl;
        cout << "==========================================================" << endl;
        roundof_2(2,3);
        cout << "==========================================================" << endl;
        cout << "\n\n\n";
        cout << "Winners of SEMIFINALS are : " << endl;
        for (int i = 0; i < winnersof2.size(); i++) {
            cout << i+1 << ". " << winnersof2.at(i).name << endl;
        }
        cout << "======TOURNAMENT BRACKETS======" << endl;
        cout << "Finale : " << winnersof2.at(0).name << " VS " << winnersof2.at(1).name << endl;
        cout << "\n\n\n";
        cout << "==========================================================" << endl;
        roundof_2in4();
        cout << "==========================================================" << endl;
        cout << "======END OF TOURNAMENT!======" << endl;
        cout << "THE WINNER IS : " << winnersof2in4.at(0).name << " !!!!!!!!!" << endl;
        cout << "\n";
        cout << winnersof2in4.at(0).name << "HAS WON THE CHAMPIONSHIP" << endl;
        cout << "======TOURNAMENT STATISTICS======" << endl;
        cout << "Champion : " << winnersof2in4.at(0).name;
        cout << "Total Battles : 3" << endl;
        cout << "Total Turns : " << total_turns << endl;
        cout << "Total Critical Hits : " << total_crits << endl;
        cout << "Total Super Effective Hits : " << total_sefs << endl;

    }
  
    void start_tournament() {
        cout << "==========================ELEMENTAL CHAMPIONSHIP=========================="<< endl;
        cout << "Participants :" << endl;
        cout << "\n\n";
        for (int i = 0; i < Players.size() ; i++) {
            cout << i+1 << ". " << Players.at(i).name << endl;
        }
        //Making a new vector with randomised order of Benders
        
        std::random_device seed;
        std::mt19937 gen(seed());
        std::uniform_int_distribution<int> k(0,Players.size()-1);
        while (Sort.size() <= Players.size()-1) { 
            int m;
            m = k(gen);
            bool found = false;
            for (int i = 0; i < Sort.size(); i++) { //checker
                    if (Sort.size() != 0 && Sort.at(i).name == Players.at(m).name) {
                        found = true;
                    }
                }
            if (found == true) {
                continue;
            }
            else if (found == false) {
                Sort.push_back(Players.at(m));
            }
        } 
        
         cout << "\n\n";
        if (Players.size() == 2) {roundof_2(0,1);}
        else if(Players.size() == 4) {roundof_4();}
        else if(Players.size() == 8) {roundof_8();}
        else {cout<< "We are sorry but 16 and above players option is not available for now" << endl;}

    }

};
class AI : public Bender, public Duel {
public:
    AI () {};
    std::vector<Bender> AllPlayers;
    Bender UP;
    Bender AP;
    string difficulty;
    AI (Bender AP, Bender UP, string d ) {
        this->AP = AP;
        this->UP = UP; 
        this->difficulty = d;
    }

    Bender* pehla;
    Bender* dusra;
    void AI_duel() {
    
      cout << "=======DUEL BEGINS!=======" << endl;
        cout<< "\n";
        cout << UP.name << " " << "(" << UP.element << ", " << "HP:" << UP.hp << "/" << UP.HP << ") ";
        cout << "VS ";
        cout << AP.name << " " << "(" << AP.element << ", " << "HP:" << AP.hp << "/" << AP.HP << ") " << endl;
        cout<< "\n";cout<< "\n";cout<< "\n";
        int i = 1;
       do {
            if (UP.speed > AP.speed) {
                pehla = &UP;
                dusra = &AP;
            }
            else if (UP.speed < AP.speed) {
                pehla = &AP;
                dusra = &UP;
            }
            else {
                std::random_device rd;
                std::mt19937 assign(rd());
                std::uniform_int_distribution<int> choice(0,1);
                int h = choice(assign);
                if (h == 0) {
                    pehla = &UP;
                    dusra = &AP;
                }
                else if (h == 1) {
                    pehla = &AP;
                    dusra = &UP;
                }

            }

            //Turn n
            cout << "Turn " << i << ": ";
            cout << pehla->name << " goes first!" << endl;
            cout<< "\n";
            if (pehla == &AP) {
                int k;
                if (difficulty == "Easy" ) {
                    pehla->attacker(*dusra,Rand_Move());

                }
                else if (difficulty == "Medium") {
                    std::random_device rd;
                    std::mt19937 gen;
                    std::uniform_int_distribution<int> p(0,1);
                    int h = p(gen);
                    if (h == 0) {
                        pehla->attacker(*dusra,Rand_Move());
                    }
                    else if (h == 1) {
                        for ( int i = 0; i < pehla->moves.size(); i++) {
                            if (get<0>(pehla->moves.at(i)) == AI_Atk(*pehla,*dusra)) {
                                k = i;
                            }
                        }
                        pehla->attacker(*dusra,k);

                    }
                }
                else if (difficulty == "Hard") {
                    for ( int i = 0; i < pehla->moves.size(); i++) {
                            if (get<0>(pehla->moves.at(i)) == AI_Atk(*pehla,*dusra)) {
                                k = i;
                            }
                        }
                        pehla->attacker(*dusra,k);

                }

            }
            else if (pehla == &UP) {
                cout << "Choose your move" << endl;
                for (int i = 0; i < pehla->moves.size(); i++) {
                    cout << i+1 << ". " << get<0>(pehla->moves.at(i)) << endl;
                }
                int k; 
                cout<<"\n";
                cout << "Your Choice : " ;
                cin>> k;
                cout<<"\n";
                pehla->attacker(*dusra, k-1);
            }
            cout<< "\n";
            i++;

            if (dusra->hp == 0) {break;}

            //Turn n+1
            cout << "Turn " << i << ": ";
            cout << dusra->name << " strikes back!" << endl;
            cout<< "\n";
            if (dusra == &AP) {
               int k;
                if (difficulty == "Easy" ) {
                    dusra->attacker(*pehla,Rand_Move());

                }
                else if (difficulty == "Medium") {
                    std::random_device rd;
                    std::mt19937 gen;
                    std::uniform_int_distribution<int> p(0,1);
                    int h = p(gen);
                    if (h == 0) {
                        dusra->attacker(*pehla,Rand_Move());
                    }
                    else if (h == 1) {
                        for ( int i = 0; i < dusra->moves.size(); i++) {
                            if (get<0>(dusra->moves.at(i)) == AI_Atk(*dusra,*pehla)) {
                                k = i;
                            }
                        }
                        dusra->attacker(*pehla,k);

                    }
                }
                else if (difficulty == "Hard") {
                    for ( int i = 0; i < dusra->moves.size(); i++) {
                            if (get<0>(dusra->moves.at(i)) == AI_Atk(*dusra,*pehla)) {
                                k = i;
                            }
                        }
                        dusra->attacker(*pehla,k);

                }
            }
            else if (dusra == &UP) {
                cout << "Choose your move" << endl;
                for (int i = 0; i < dusra->moves.size(); i++) {
                    cout << i+1 << ". " << get<0>(dusra->moves.at(i)) << endl;
                }
                int k; 
                cout<< "\n";
                cout << "Your Choice : " ;
                cin>> k;
                cout<< "\n";
                dusra->attacker(*pehla, k-1);
            }
            cout << "\n";
            i++;

        }  while(!((pehla->hp == 0 || dusra->hp == 0))) ;


        if (pehla->hp == 0) {
            cout << pehla->name << " fainted!" << endl;
            cout << dusra->name << " wins the duel!" << endl;
            cout << "\n" ;
            cout << "Duel Summary:" << endl;
            cout << "-Winner: "<< dusra->name << endl;
            cout << "-Turns:  "<< i-1 << endl;
            cout << "-Critical Hits: "<< pehla->critical_counter + dusra->critical_counter << endl;
            cout << "-Super Effective Hits: "<< pehla->type_counter + dusra->type_counter << endl;
        }
        else if (dusra->hp == 0) {
            cout << dusra->name << " fainted!" << endl;
            cout << pehla->name << " wins the duel!" << endl;
            cout << "\n" ;
            cout << "Duel Summary:" << endl;
            cout << "-Winner: "<< pehla->name << endl;
            cout << "-Turns:  "<< i-1 << endl;
            cout << "-Critical Hits: "<< pehla->critical_counter + dusra->critical_counter  << endl;
            cout << "-Super Effective Hits: "<< pehla->type_counter + dusra->type_counter << endl;
        }


    }


string AI_Atk( Bender AI, Bender User) {
    if (AI.hp < 0.3 * AI.HP && AI.has_healing_move()) {
        return AI.healing_move;
    }
    else if (User.hp > 0.7 * User.HP && AI.has_status_move()) {
        return AI.status_move;
    }
    else if (User.hp < 0.25 * User.HP ) {
        return AI.strongest_move;
    }
    else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> moves(0,3);
        int k = moves(gen);
        return get<0>(AI.moves[k]); // BECAUSE EVERY MOVE IS SUPER EFFECTIVE IN MY CODE :(
    }

    }


};


int main() {
//Create Kael
Bender Kael("Kael", "Fire", 100, 58, 38, 88,
    {{"Ember Slash", 40 , "No Effect"}, {"Quick Jab", 30 , "No Effect"}, {"Focus", 0, "No Effect"}, {"Flame Surge", 10, "Burnt"}});

//Create Mira
Bender Mira("Mira", "Water", 92, 50, 45, 60,
     {{"Water Whip", 35 , "No Effect"}, {"Tide Push", 25, "No Effect"}, {"Mist Veil", 0, "No Effect"}, {"Blizzard", 15, "Frozen"}});

//Create Terra
Bender Terra("Terra", "Earth", 105, 52, 48, 72,
     {{"Rock Throw", 35, "No Effect"}, {"Stone Wall", 25, "No Effect"}, {"Grounding", 0, "No Effect"}, {"Litholisation", 20, "Buried"}});

//Create Zephyr
Bender Zephyr("Zephyr", "Air", 90, 62, 35, 92,
      {{"Gust", 35, "No Effect"}, {"Air Dash", 25, "No Effect"}, {"Meditate", 0, "No Effect"}, {"Cyclone", 65, "No Effect"}});
//Create Nadia
Bender Nadia("Nadia", "Water", 85, 48, 60, 72,
              {{"Wave Crash", 35, "No Effect"}, {"Splash Kick", 25, "No Effect"}, {"Guard", 0, "No Effect"}, {"Freeze", 0, "Frozen"}});
//Create Talon
Bender Talon("Talon", "Air", 90, 52, 55, 72,
              {{"Gale Strike", 38, "No Effect"}, {"Wind Cutter", 28, "No Effect"}, {"Updraft", 0, "No Effect"}, {"Cyclone Blast", 48, "No Effect"}});
// Create Sable
Bender Sable("Sable", "Air", 95, 60, 58, 85,
             {{"Arctic Gust", 0, "No Effect"}, {"Wind Blade", 52, "No Effect"}, {"Tailwind", 0, "No Effect"}, {"Cyclone Fang", 58, "No Effect"}});

// Create Boran
Bender Boran("Boran", "Earth", 110, 68, 62, 50,
             {{"Rockslide", 55, "No Effect"}, {"Quicksand Trap", 0, "No Effect"}, {"Stone Wall", 0, "No Effect"}, {"Seismic Toss", 70, "Buried"}});

//Create Ignis
Bender Ignis("Ignis", "Fire", 120, 82, 70, 95,
             {{"Inferno Slash", 60, "No Effect"}, {"Flame Dash", 38, "No Effect"}, {"Ember Guard", 0, "No Effect"}, {"Flame Wheel", 45, "Buried"}});

//Create Kestra
Bender Kestra("Kestra", "Water", 128, 78, 85, 68,
             {{"Tidal Crush", 65, "No Effect"}, {"Ice Shard", 45, "No Effect"}, {"Mist Shield", 0, "No Effect"}, {"Hailstrom", 10, "Frozen"}});

// Create Terrak
Bender Terrak("Terrak", "Earth", 135, 88, 90, 45,
             {{"Stone Avalanche", 70, "No Effect"}, {"Quake Punch", 48, "No Effect"}, {"Bulwark", 0, "No Effect"}, {"Mountain's Wrath", 60, "Buried"}});

//Create Squall
Bender Squall("Squall", "Air", 105, 65, 55, 100,
             {{"Thunder Gale", 58, "No Effect"}, {"Razor Wind", 35, "No Effect"}, {"Updraft", 0, "No Effect"}, {"Tempest Strike", 72, "No Effect"}});

std::vector<Bender> AllPlayers = { Kael , Mira , Terra , Zephyr , Nadia , Talon , Sable , Boran , Ignis , Kestra , Terrak , Squall };


std::vector<Bender> FireType;
for (int i = 0; i < AllPlayers.size(); i++) {
    if (AllPlayers.at(i).element == "Fire") {
        FireType.push_back(AllPlayers.at(i));
    }
}
 
std::vector<Bender> WaterType;
for (int i = 0; i < AllPlayers.size(); i++) {
    if (AllPlayers.at(i).element == "Water") {
        WaterType.push_back(AllPlayers.at(i));
    }
}
 
std::vector<Bender> EarthType;
for (int i = 0; i < AllPlayers.size(); i++) {
    if (AllPlayers.at(i).element == "Earth") {
        EarthType.push_back(AllPlayers.at(i));
    }
}
 
std::vector<Bender> AirType;
for (int i = 0; i < AllPlayers.size(); i++) {
    if (AllPlayers.at(i).element == "Air") {
        AirType.push_back(AllPlayers.at(i));
    }
}
 

cout<< "Hello! This is the ELEMENTAL BATTLE CHAMPIONSHIP game" << endl;
cout<< "Modes:" << endl;
cout<< "1. Player Vs Player Duel" << endl;
cout<< "2. AI Duel" << endl;
int chooser;
cout << "Choose your gamemode : " ;
cin >> chooser;
cout<< "\n";


if (chooser == 1) {
    
    cout << "No. of players allowed is 2,4,8,16 and so on (2^n)" << endl;
    int h;
    int o,n;
    cout << "Choose the number of players : ";
    cin >> h;
    if (h % 2 != 0) {
        cout << "No. of players allowed is 2,4,8,16 and so on (2^n)" << endl;
        return 0;
    }
 
    if (h == exp2(o)) {
        n = o;
    }
    
    cout<< "Choose the characters for battle" << endl;
    cout<< "1. Kael (Fire)" << endl;
    cout<< "2. Mira (Water)" << endl;
    cout<< "3. Terra (Earth)" << endl;
    cout<< "4. Zephyr (Air)" << endl;
    cout<< "5. Nadia (Water)" << endl;
    cout<< "6. Talon (Air)" << endl;
    cout<< "7. Sable (Air)" << endl;
    cout<< "8. Boran (Earth)" << endl;
    cout<< "9. Ignis (Fire)" << endl;
    cout<< "10. Kestra (Water)" << endl;
    cout<< "11. Terrak (Earth)" << endl;
    cout<< "12. Squall (Air)" << endl;
    std::vector<Bender> collector;
   int u;
   cout << "\n\n" << "Your Choices (Choose Number) : " << endl;
    for ( int i = 0; i < h; i++) {
        cin >> u;
        collector.push_back(AllPlayers.at(u-1));
    }
    Tournament tournament(collector);
    tournament.start_tournament();

}

if (chooser == 2) {
    
    cout << "Choose your character : " << endl;
    cout << "\n";
    for (int i = 0; i < AllPlayers.size() ; i++) {
        cout<< i+1 << ". " << AllPlayers.at(i).name << "(" << AllPlayers.at(i).element << ")" << endl;
    }
    cout << "\n";

    int k;
    cout << "Your Choice(Choose Number) : " ;
    cin >> k;
    cout<< "\n";
    Bender User_Player = AllPlayers.at(k-1);
    Bender AI_Player;

    std::random_device seed;
    std::mt19937 gen;
    std::uniform_int_distribution<int> numb(0,3);
    int h = numb(gen);
    if (User_Player.element == "Fire" ) {
        if (h <= WaterType.size()-1) {
        AI_Player = WaterType.at(h);
        }
        else {
        std::uniform_int_distribution<int> numb(0,WaterType.size()-1);
        int k = numb(gen);
        AI_Player = WaterType.at(k);
        }
    }

    
    if (User_Player.element == "Water" ) {
        if (h <= EarthType.size()-1) {
        AI_Player = EarthType.at(h);
        }
        else {
        std::uniform_int_distribution<int> numb(0,EarthType.size()-1);
        int k = numb(gen);
        AI_Player = EarthType.at(k);
        }
    }

    if (User_Player.element == "Earth" ) {
        if (h <= AirType.size()-1) {
        AI_Player = AirType.at(h);
        }
        else {
        std::uniform_int_distribution<int> numb(0,AirType.size()-1);
        int k = numb(gen);
        AI_Player = AirType.at(k);
        }
    }

    if (User_Player.element == "Air" ) {
        if (h <= FireType.size()-1) {
        AI_Player = FireType.at(h);
        }
        else {

        std::uniform_int_distribution<int> numb(0,FireType.size()-1);
        int k = numb(gen);
        AI_Player = FireType.at(k);
        }
    }

    cout << "The AI chooses " << AI_Player.name << "!" << endl;
    cout<< "\n\n";
    cout << "Choose your difficulty : " << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    string difficulty;
    cout<< "\nYour Choice : " ;
    cin>> difficulty;

    AI Players( AI_Player, User_Player, difficulty );
    Players.AI_duel();

}
}

