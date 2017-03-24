//  ANALYSIS OF ALGORITHMS I - HOMEWORK 3   PART B: HEAPSORT
//  CAN YILMAZ ALTINİĞNE - 150130132

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include "algos.h"

#define CLAN_A_PLAYERS "ClanA.txt"
#define CLAN_B_PLAYERS "ClanB.txt"
#define LOGS_FILE "gamelogs.txt"

using namespace std;

int main(int argc, const char * argv[]) {
    
    ifstream file_opened;
    long int order, number;
    Algorithms algos;
    clock_t t = 0;
    
    if (atoi(argv[1]) == 1) {           // PART B: Q1
        
        long int N = atoi(argv[2]);
        file_opened.open(CLAN_A_PLAYERS);
        
        ofstream sorted_players;
        sorted_players.open("A_sorted.txt");
        
        Player * ptr = new Player[N];
        
        for (long int z = 0; z < N; z++) {              // GET THE UNSORTED PLAYERS
            file_opened >> order >> number;
            ptr[z].set_id(order);
            ptr[z].set_charisma_point(number);
        }
        
        t = clock();
        
        algos.heap_sort(ptr, N);                        // SORT THEM BY CHARISMA POINTS
        
        t = clock() - t;
        
        cout << "Wow ! It only took " << double(t) / CLOCKS_PER_SEC << " seconds to sort " << N << " players with heap sort." << endl << endl;
        
        for (long int z = N-1; z >= 0; z--){                        // PRINT SORTED PLAYERS
            sorted_players << setw(15) << left << ptr[z].get_id();
            sorted_players << ptr[z].get_charisma_point() << endl;
        }
        
        delete [] ptr;
        
        sorted_players.close();
        file_opened.close();
        
    } else {                            // PART B: Q2
        
        ifstream clan_a, clan_b, game_logs;
        int game_id, attacker_ps, attacked_ps;
        char clan_name;
        
        ofstream result_players;
        result_players.open("A_results.txt");
        
        Player * ptr_clan_a = new Player[10000];
        Player * ptr_clan_b = new Player[10000];
        
        clan_a.open(CLAN_A_PLAYERS);
        clan_b.open(CLAN_B_PLAYERS);
        game_logs.open(LOGS_FILE);
        
        for (long int z = 0; z < 10000; z++) {      //  GET 10000 PLAYERS FROM EACH CLANS
            clan_a >> order >> number;
            ptr_clan_a[z].set_id(order);
            ptr_clan_a[z].set_charisma_point(number);
            
            clan_b >> order >> number;
            ptr_clan_b[z].set_id(order);
            ptr_clan_b[z].set_charisma_point(number);
        }
        
        cout << "Attacks will be calculated for Second Q of Part B, Please wait ..." << endl;
        
        Player * attacker, * attacked;
        
        while (game_logs >> game_id >> clan_name >> attacker_ps >> attacked_ps) {       // IN EVERY LINE OF GAME LOGS FILE
            
            algos.heap_sort(ptr_clan_a, 10000);                                         // FIRST SORT TWO CLANS
            algos.heap_sort(ptr_clan_b, 10000);
            
            if (clan_name == 'A') {                                     // FIND THE ATTACKER AND ATTACKED PLAYERS
                attacker = &ptr_clan_a[9999 - attacker_ps];
                attacked = &ptr_clan_b[9999 - attacked_ps];
                
            } else {
                attacker = &ptr_clan_b[9999 - attacker_ps];
                attacked = &ptr_clan_a[9999 - attacked_ps];
            }
            
            if (attacker_ps == 0){                                      // IF ATTACKER IS THE LEADER OF THE CLAN
                
                attacker->increase_cp(attacked->get_charisma_point()/2);
                attacked->decrease_cp(attacked->get_charisma_point()/2);
                
            } else {
                
                bool isHenchmen = false;
                
                if (attacker_ps > 0 && attacker_ps < 8) isHenchmen = true;
                
                if (isHenchmen) {                                               // IF ATTACKER IS A HENCHMEN
                    
                    attacker->increase_cp(500);
                    attacked->decrease_cp(500);
                    
                } else {                                                                    // IF ATTACKER IS A SOLDIER
                    
                    int level_diff = abs(find_level(attacker_ps) - find_level(attacked_ps));
                    
                    attacker->increase_cp((level_diff+1)*30);
                    attacked->decrease_cp(120);
                }
            }
        }
        
        long int toplam_a = 0, toplam_b = 0;
        
        for (int a = 0; a < 10000; a++) {                                   // GET THE TOTAL CP
            toplam_a += ptr_clan_a[a].get_charisma_point();
            toplam_b += ptr_clan_b[a].get_charisma_point();
        }
        
        long int fark = abs(toplam_a-toplam_b);
        
        if (toplam_a > toplam_b) cout << endl << "Clan A wins by " << fark << " points.";                   // FIND THE WINNER
        else if (toplam_a < toplam_b) cout << endl << "Clan B wins by " << fark << " points.";
        else cout << endl << "Tie game !";
        
        cout << endl << endl << "Clan A Total CPs : " << toplam_a <<  endl << "Clan B Total CPs : " << toplam_b << endl;
        
        for (long int z = 9999; z >= 0; z--){                                       // PRINT THE CLAN A IN THE END OF THE WAR
            result_players << setw(15) << left << ptr_clan_a[z].get_id();
            result_players << ptr_clan_a[z].get_charisma_point() << endl;
        }
        
        clan_a.close();
        clan_b.close();
        game_logs.close();
        result_players.close();
        
        delete [] ptr_clan_a;
        delete [] ptr_clan_b;
        
    }
    
    return EXIT_SUCCESS;
}
