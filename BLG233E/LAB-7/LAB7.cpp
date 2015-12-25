#include <iostream>
#include <cstdlib>
#include <cstring>

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

using namespace std;

typedef struct d{
    int x;
    int y;
    int right;
    int left;
    int down;
    int up;
    int camefrom;
}StackDataType, position;

struct Node{
    StackDataType data;
    Node *next;
};

struct Stack{
    StackDataType element[80];
    int top;
    void create();
    void push(StackDataType);
    StackDataType pop();
    bool isempty();
};

void Stack::create(){
    top=0;
}

void Stack::push(StackDataType newelement){
    element[top++] = newelement;
}

StackDataType Stack::pop(){
    return element[--top];
}

bool Stack::isempty(){
    return (top == 0);
}

char lab[14][22]={"# ###################",
                "#     #      #    # #",
                "# ### # ###### ## # #",
                "# # #        # #  # #",
                "# # ### #### # # ## #",
                "#     # # ##   #    #",
                "### # # # ## # # ####",
                "# # # # #    #      #",
                "# # # # # ######### #",
                "# # # # # #       # #",
                "# # #   # # #####   #",
                "# # ##### # #   #####",
                "#         #   #     #",
                "###################E#"};

void printlab(char l[][22]) {
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 21; j++)
            cout << l[i][j];
        cout << endl;
    }
    cout << endl << endl;
}

int a = 0;

int main(){
    
    Stack s, final;
    s.create();
    position entrance = {1,0,0,0,0,0,0};
    position exit = {20,14,0,0,0,0,0};
    position p = entrance;
    p.camefrom = UP;
    printlab(lab);
    bool goback = false;
    position lastPoint;
    
    while (p.x != exit.x || p.y != exit.y) {
        
        lab[p.y][p.x]='o';
        
        printlab(lab);
        
        /*for (int i=0; i<100000; i++){
            for (int i=0; i<1000; i++);
        }*/
        
        //first find in how many directions we can move
        if (!goback) { //if not calculated before
            p.right = 0;
            p.left = 0;
            p.down = 0;
            p.up = 0;
            
            if (p.x<20 && lab[p.y][p.x+1]!='#' && lab[p.y][p.x+1]!='o')
                p.right=1;//right
            
            if (p.x>0 && lab[p.y][p.x-1]!='#' && lab[p.y][p.x-1]!='o')
                p.left=1;//left
            
            if (p.y<14 && lab[p.y+1][p.x]!='#' && lab[p.y+1][p.x]!='o')
                p.down=1;//down
            
            if (p.y>0 && lab[p.y-1][p.x]!='#' && lab[p.y-1][p.x]!='o')
                p.up=1;//up
        
        } else {
            goback = false;
        }
        
        
        bool moved = true;
        position past = p;
        final.push(past);
        a++;
        
        
        if (p.down && p.camefrom != DOWN){
            p.y++;
            p.camefrom = UP;
            past.down = 0;
       
        } else if (p.up && p.camefrom != UP){
            p.y--;
            p.camefrom = DOWN;
            past.up = 0;
        
        } else if (p.left && p.camefrom != LEFT){
            p.x--;
            p.camefrom = RIGHT;
            past.left = 0;
        
        } else if (p.right && p.camefrom != RIGHT){
            p.x++;
            p.camefrom = LEFT;
            past.right = 0;
        
        } else {
            moved = false;
        }
        
        if (p.x == exit.x || p.y == exit.y) {
            break;
        }
        
        if (p.x != exit.x || p.y != exit.y) {
            
            if ( (p.down + p.up + p.right + p.left) >= 2) {
                //there is more than one choice, push onto stack and
                //continue in that chosen direction. Let the choices
                //you have not selected remain marked on the stack.
                s.push(past);
            }
            
            if (!moved) { // has to go back
                if ( !s.isempty() ) {
                    lastPoint = s.pop();
                    
                    if (p.camefrom == RIGHT) {
                        lab[p.y][p.x] = ' ';
                        p.x++;
                    } else if (p.camefrom == LEFT) {
                        lab[p.y][p.x] = ' ';
                        p.x--;
                    } else if (p.camefrom == DOWN) {
                        lab[p.y][p.x] = ' ';
                        p.y++;
                    } else if (p.camefrom == UP) {
                        lab[p.y][p.x] = ' ';
                        p.y--;
                    }
                    
                    /*for (int i=0; i<100000; i++){
                        for (int i=0; i<1000; i++);
                    }*/
                    
                    printlab(lab);
                   
                    
                    while (p.x != lastPoint.x || p.y != lastPoint.y) {
                        
                        final.pop();
                        a--;
                        
                        lab[p.y][p.x] = ' ';
                        
                        if (lab[p.y][p.x+1] == 'o' ){
                             p.x++;//right
                        
                        } else if (lab[p.y][p.x-1] == 'o'){
                            p.x--;//left
                            
                        } else if (lab[p.y+1][p.x] == 'o'){
                            p.y++;//down
                            
                        } else if (lab[p.y-1][p.x] == 'o'){
                            p.y--;//up
                            
                        }
                        
                        /*for (int i=0; i<100000; i++){
                            for (int i=0; i<1000; i++);
                        }*/
                        
                        printlab(lab);
                        
                    }
                    
                    p = lastPoint;
                    goback = true;
                }
            }
        }
    }
    
    cout << "PATH found" << endl;
    
    cout << "Points" << endl;
    for (int i=0; i < a; i++) {
        cout << final.element[i].x << " " << final.element[i].y << endl;
    }

    return 0;
}


