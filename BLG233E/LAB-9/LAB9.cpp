#include <iostream>
#include <time.h>

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define MAZESIZE 6

using namespace std;

struct cell{
    bool left, right, up, down; // right = false when a wall does not exist otherwise, right = true means there is a wall
    char val; // initially this is empty (' '), when the cell is used to reach the exit, this becomes 'o'
    bool visited; // this variable will be used while generating maze randomly (look the pseudo code for further information)
    int x,y;
    cell * next;
};

struct Stack{
    cell * head;
    void create();
    void close();
    void push(cell, int, int);
    int * pop();
    bool isempty();
};

void Stack::create(){
    head = NULL;       //init
}

void Stack::close(){    //deallocate all of the allocated memory
    cell *p;
    while (head){
        p = head;
        head = head->next;
        delete p;
    }
}

bool Stack::isempty(){
    return head == NULL;
}

void Stack::push(cell add, int x, int y){
    cell * newnode = new cell;
   
    newnode->left = add.left;
    newnode->right = add.right;
    newnode->up = add.up;
    newnode->down = add.down;
    
    newnode->visited = add.visited;
    newnode->val = add.val;
    
    newnode->x=x;
    newnode->y=y;
    
    newnode->next = NULL;
    
    if(isempty()){       //first push
        head = newnode;
    }
    else{                   //push to top
        newnode->next = head;
        head = newnode;
    }
}

int * Stack::pop(){
    
    cell *topnode;
    
    int * poz = new int [2];
    
    topnode = head;
    
    poz[0]=topnode->x;
    poz[1]=topnode->y;
    
    head = head->next;
    
    return poz;
}

cell m[MAZESIZE][MAZESIZE]; // this is the maze

void print(){
    
    for(int i = 0; i < MAZESIZE; i++){
        
        for(int j = 0; j < MAZESIZE; j++){
            if(m[i][j].up)
                cout << " -";
            else
                cout << "  ";
        }
        
        cout << endl;
        cout << "|";
        
        for(int j = 0; j < MAZESIZE; j++){
            
            if(m[i][j].right)
                cout << m[i][j].val << "|";
            else
                cout << m[i][j].val << " ";
        }
        
        cout << endl;
    }
   
    for(int i = 0; i < MAZESIZE; i++){
        if(m[MAZESIZE-1][i].down)
            cout << " -";
    }
    
    cout << endl;
}

int unvisitedCellNumber = MAZESIZE * MAZESIZE - 1;
int currentX = 0, currentY = 0;
int exit_row;
int exit_col;
Stack stack;

bool find_yol(cell l[MAZESIZE][MAZESIZE],int r,int c,int came) {
    l[r][c].val = 'o';
    if (r == exit_row && c == exit_col) {
        print();
        
        for (int i=0; i<100000000; i++);
        
        return true;
    }
    print();
    for (int i=0; i<100000000; i++);
    
    if (c > 0 && !l[r][c].left && came != LEFT) {
        if (find_yol(l, r, c - 1, RIGHT))
            return true;
    }
    if (r < MAZESIZE-1 && !l[r][c].down && came != DOWN) {
        if (find_yol(l, r+1, c, UP))
            return true;
    }
    if (r > 0 && !l[r][c].up && came != UP) {
        if (find_yol(l, r - 1, c, DOWN))
            return true;
    }
    if (c < MAZESIZE-1 && !l[r][c].right && came != RIGHT) {
        if (find_yol(l, r, c + 1, LEFT))
            return true;
    }
    
    l[r][c].val = ' ';
    print();
    for (int i=0; i<100000000; i++);
    return false;
}

int main(){
    
    srand(time(NULL));

    for(int i = 0; i < MAZESIZE; i++){
        for(int j = 0; j < MAZESIZE; j++){
            m[i][j].left=true;
            m[i][j].right=true;
            m[i][j].up=true;
            m[i][j].down=true;
            m[i][j].val=' ';
            m[i][j].visited=false;
        }
    }
    
    m[currentX][currentY].visited=true;
    
    while (unvisitedCellNumber > 0) {
        
        
        int i = 0;
        int komsuVar = 0;
        int chosen[4];
        int choose;
        
        if (currentY > 0 && m[currentX][currentY-1].visited == false) {
            chosen[i++] = LEFT;
            ++komsuVar;
        }
        
        if (currentY < MAZESIZE-1 && m[currentX][currentY+1].visited == false) {
            chosen[i++] = RIGHT;
            ++komsuVar;
        }
        
        if (currentX > 0 && m[currentX-1][currentY].visited == false) {
            chosen[i++] = UP;
            ++komsuVar;
        }
        
        if (currentX < MAZESIZE-1 && m[currentX+1][currentY].visited == false) {
            chosen[i++] = DOWN;
            ++komsuVar;
        }
        
        
        if (komsuVar > 0) {
            choose = chosen[rand() % i];
            
            stack.push(m[currentX][currentY],currentX,currentY);
            
            switch (choose) {
                case 1:
                    m[currentX][currentY].left = false;
                    m[currentX][currentY-1].right = false;
                    currentY = currentY - 1;
                    break;
                    
                case 2:
                    m[currentX][currentY].right = false;
                    m[currentX][currentY+1].left = false;
                    currentY = currentY + 1;
                    break;
                    
                    
                case 3:
                    m[currentX][currentY].up = false;
                    m[currentX-1][currentY].down = false;
                    currentX = currentX - 1;
                    break;
                    
                case 4:
                    m[currentX][currentY].down = false;
                    m[currentX+1][currentY].up = false;
                    currentX = currentX + 1;
                    break;
                    
                default:
                    break;
            }
            
            m[currentX][currentY].visited = true;
            unvisitedCellNumber--;
        
        } else if (!stack.isempty()){
            
            
            int * currentCell;
            currentCell = stack.pop();
            currentX = currentCell[0];
            currentY = currentCell[1];
            
        } else {
            
            currentX = rand() % MAZESIZE;
            currentY = rand() % MAZESIZE;
            
            m[currentX][currentY].visited=true;
            unvisitedCellNumber--;
        }
        
    }
    
    print();
    
    int entX, entY;
    
    cout << "Enter the Entrance Point X - Y: ";
    cin >> entX >> entY;
    
    cout << "Enter the Exit Point X - Y: ";
    cin >> exit_col >> exit_row;
    
    print();
    find_yol(m,entY,entX,-1);
    print();
    
    return 0;

}

