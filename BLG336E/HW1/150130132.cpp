//  ANALYSIS OF ALGORITHMS II - PROJECT 1
//  CAN YILMAZ ALTINİĞNE - 150130132

//  g++ 150130132.cpp -std=c++11 -o project1

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

class Block {
    
    int bottom_left_y, bottom_left_x;
    char orientation;
    int block_num;
    int height;
    
public:
    
    Block(int y, int x, char pos, int hei, int ord){
        bottom_left_x = x;
        bottom_left_y = y;
        orientation = pos;
        block_num = ord;
        height = hei;
    }
    
    int move_down_or_right(){
        return orientation == 'v' ? bottom_left_y+=1 : bottom_left_x+=1;
    }
    
    int move_up_or_left(){
        return orientation == 'v' ? bottom_left_y-=1 : bottom_left_x-=1;
    }
    
    string stringify(){
        return to_string(bottom_left_y) + " " + to_string(bottom_left_x) + " " + to_string(height) + " " + orientation + '\n';      // RETURN i.e. 3 5 2 v
    }
    
    int get_bottom_left_column(){
        return bottom_left_x - 1;
    }
    
    int get_bottom_left_row(){
        return bottom_left_y - 1;
    }
    
    int get_block_num(){
        return block_num;
    }
    
    char get_orientation(){
        return orientation;
    }
    
    int get_height(){
        return height;
    }
};

class State {
    
    unsigned long parent_layer, parent_order;       // PARENT LAYER IN VECTOR OF VECTORS AND PARENT ORDER IN THAT VECTOR
    unsigned long order_for_dfs;                    // PARENT ORDER IN VECTOR FOR DFS
    
public:
    
    vector<Block> state_blocks;
    int visualize_grid[6][6];                       // TO INDICATE BLOCK POSITIONS ON GRID, IT IS USED FOR MOVE PREDICTION
    
    State(){
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                visualize_grid[i][j] = 0;
            }
        }
    }
    
    State(vector<Block> bl, int par_lay, unsigned long par_ord){
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                visualize_grid[i][j] = 0;
            }
        }
        
        state_blocks = bl;
        parent_layer = par_lay;
        parent_order = par_ord;
        prepare_the_grid();
    }
    
    void set_order_for_dfs(unsigned long x){
        order_for_dfs = x;
    }
    
    unsigned long get_order_for_dfs(){
        return order_for_dfs;
    }
    
    void set_parent(int lay, int ord){
        parent_order = ord;
        parent_layer = lay;
    }
    
    unsigned long get_parent_order(){
        return parent_order;
    }
    
    unsigned long get_parent_layer(){
        return parent_layer;
    }
    
    void prepare_the_grid(){
        for (int i = 0; i < state_blocks.size(); i++) {
            Block bl = state_blocks[i];
            char orientation = bl.get_orientation();
            int bottom_left_row = bl.get_bottom_left_row();
            int bottom_left_column = bl.get_bottom_left_column();
            int height = bl.get_height();
            int number = bl.get_block_num();
            int z = 0;
            
            while (z < height) {
                if (orientation == 'v') {
                    visualize_grid[bottom_left_row-z][bottom_left_column] = number;
                    
                } else {
                    visualize_grid[bottom_left_row][bottom_left_column+z] = number;
                    
                }
                
                z++;
            }
        }
    }
    
    bool check_down_or_right(int x){            // CHECK THE GRID IF Xth BLOCK CAN MOVE DOWN OR RIGHT ACCORDING TO ORIENTATION
        
        Block bl = state_blocks[x];
        char orientation = bl.get_orientation();
        
        if (orientation == 'v') {
            if (bl.get_bottom_left_row()+1 > 5) {           // THE BOTTOM LEFT Y CAN NOT GO DOWN ANYMORE
                return false;
            } else {
                if (visualize_grid[bl.get_bottom_left_row()+1][bl.get_bottom_left_column()] == 0) {  // IF THERE IS A PLACE DOWN TO BLOCK, CAN MOVE DOWN
                    return true;
                } else {                                                                                // ELSE NO
                    return false;
                }
            }
            
        } else {
            if (bl.get_bottom_left_column()+bl.get_height() > 5) {       // THE BLOCK CAN NOT GO RIGHT ANYMORE
                return false;
            } else {
                if (visualize_grid[bl.get_bottom_left_row()][bl.get_bottom_left_column()+bl.get_height()] == 0) {   // IF THERE IS A PLACE RIGHT TO BLOCK, CAN MOVE RIGHT
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    
    bool check_up_or_left(int x){
        
        Block bl = state_blocks[x];
        char orientation = bl.get_orientation();
        
        if (orientation == 'v') {
            if (bl.get_bottom_left_row()-bl.get_height() < 0) {     // THE BLOCK CAN NOT GO UP ANYMORE
                return false;
            } else {
                if (visualize_grid[bl.get_bottom_left_row()-bl.get_height()][bl.get_bottom_left_column()] == 0) {   // IF THERE IS A PLACE UP TO BLOCK, CAN MOVE UP
                    return true;
                } else {
                    return false;
                }
            }
            
        } else {
            if (bl.get_bottom_left_column()-1 < 0) {        // THE BLOCK CAN NOT GO LEFT ANYMORE
                return false;
            } else {
                if (visualize_grid[bl.get_bottom_left_row()][bl.get_bottom_left_column()-1] == 0) {     // IF THERE IS A PLACE LEFT TO BLOCK, CAN MOVE LEFT
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    
    string stringify(){                         // RETURN VALUE IS ADDED TO UNORDERED SET FOR CYCLE CHECK
        string str;
        
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                str += to_string((visualize_grid[i][j]));
            }
        }
        
        return str;
    }
    
    bool win_the_game(){                // IF THE ROAD IS OPEN AT THE RIGHT OF FIRST BLOCK THEN ITS WIN
        
        int start_point = state_blocks[0].get_bottom_left_column() + state_blocks[0].get_height();
        
        for (int j = start_point; j < 6; j++) {
            if (visualize_grid[2][j] != 0) {
                return false;
            }
        }
        
        return true;
    }
    
    string state_output_generator(){                // TO OUTPUT THE STATE AS IT IS SPECIFIED IN BLOCKS.TXT
        string res;
        
        for (int i = 0; i < state_blocks.size(); i++) {
            res += state_blocks[i].stringify();
        }
        
        res += '\n';
        
        return res;
    }
};

vector<vector<State> > state_list;          // LIST OF LISTS FOR BFS, LIST FOR DFS

class Algorithms {
    
    bool found;
    int cycle_prevented;
    ofstream output_file;
    
    State breadth_first_search(State& initial_state){               // BFS IMPLEMENTATION (ALGORITHM DESIGN PSEUDOCODE AND CYCLE CHECK ADDED)
        
        unordered_set<string> visited_states;                       // CYCLE CHECK UNORDERED SET
        int layer_counter = 0;
        State st;
        cycle_prevented = 0;
        
        visited_states.insert(initial_state.stringify());
        vector<State> ini_list;
        ini_list.push_back(initial_state);
        
        state_list.push_back(ini_list);
        
        while (!state_list[layer_counter].empty()) {
            state_list.push_back(vector<State>());
            
            for (int i = 0; i < state_list[layer_counter].size(); i++) {        // ALL STATES IN THAT LAYER
                st = state_list[layer_counter][i];
                
                if (st.win_the_game()) {
                    found = true;
                    return st;
                }
                
                for (int j = 0; j < st.state_blocks.size(); j++) {          // MOVE EVERY BLOCK IN RELATED DIRECTIONS BY 1 SQUARE
                    
                    if (st.check_up_or_left(j)){                            // IF IT CAN MOVE CHECK THE STATE IF IT IS VISITED, IF NOT ADD TO LAYER LIST
                        Block added = st.state_blocks[j];
                        added.move_up_or_left();
                        vector<Block> temp_blocks = st.state_blocks;
                        temp_blocks[j] = added;
                        
                        State new_st(temp_blocks, layer_counter, i);
                        
                        if (visited_states.find(new_st.stringify()) == visited_states.end()) {
                            visited_states.insert(new_st.stringify());
                            state_list[layer_counter+1].push_back(new_st);
                        } else {
                            cycle_prevented++;
                        }
                    }
                    
                    if (st.check_down_or_right(j)) {
                        Block added = st.state_blocks[j];
                        added.move_down_or_right();
                        vector<Block> temp_blocks = st.state_blocks;
                        temp_blocks[j] = added;
                        
                        State new_st(temp_blocks, layer_counter, i);
                        
                        if (visited_states.find(new_st.stringify()) == visited_states.end()) {
                            visited_states.insert(new_st.stringify());
                            state_list[layer_counter+1].push_back(new_st);
                        } else {
                            cycle_prevented++;
                        }
                    }
                }
            }
            
            layer_counter++;
            
        }
        
        found = false;
        return State();
    }
    
    State depth_first_search(State& initial_state){
        stack<State> states;
        unordered_set<string> visited_states;
        State st;
        state_list.push_back(vector<State>());                      // STATE LIST IS USED NOT TO LOSE PARENTS AT THE END
        cycle_prevented = 0;
        
        initial_state.set_order_for_dfs(state_list[0].size());
        states.push(initial_state);
        state_list[0].push_back(initial_state);                     // JUST USE state_list[0]
        
        while (!states.empty()) {
            
            st = states.top();
            states.pop();
            
            if (visited_states.find(st.stringify()) == visited_states.end()) {          // IF IT IS NOT VISITED
                
                visited_states.insert(st.stringify());
                
                if (st.win_the_game()){
                    found = true;
                    return st;
                }
                
                for (int j = 0; j < st.state_blocks.size(); j++) {                  // MOVE EVERY BLOCK IN RELATED DIRECTIONS BY 1 SQUARE
                    
                    if (st.check_up_or_left(j)){                                    // IF IT CAN MOVE ADD TO STACK
                        Block added = st.state_blocks[j];
                        added.move_up_or_left();
                        vector<Block> temp_blocks = st.state_blocks;
                        temp_blocks[j] = added;
                        
                        State new_st(temp_blocks, 0, st.get_order_for_dfs());
                        new_st.set_order_for_dfs(state_list[0].size());
                        
                        states.push(new_st);
                        state_list[0].push_back(new_st);
                    }
                    
                    if (st.check_down_or_right(j)) {
                        Block added = st.state_blocks[j];
                        added.move_down_or_right();
                        vector<Block> temp_blocks = st.state_blocks;
                        temp_blocks[j] = added;
                        
                        State new_st(temp_blocks, 0, st.get_order_for_dfs());
                        new_st.set_order_for_dfs(state_list[0].size());
                        
                        states.push(new_st);
                        state_list[0].push_back(new_st);
                    }
                }
            } else {
                cycle_prevented++;
            }
        }
        
        found = false;
        return State();
    }
    
public:
    
    Algorithms(string out){
        output_file.open(out);
    }
    
    ~Algorithms(){
        output_file.close();
    }
    
    void BFS(State& initial_state){                             // EXPLICIT BFS TO CALL IMPLICIT ONE AND SHOW RESULTS
        
        clock_t t = clock();
        State state = breadth_first_search(initial_state);
        t = clock() - t;
        
        if (found == true) {
            
            stack<State> results;
            unsigned long number_of_nodes_generated = 0;
            int maximum_size = 0;
            
            while (state.get_parent_order() != -1) {
                results.push(state);
                state = state_list[state.get_parent_layer()][state.get_parent_order()];
            }
            
            results.push(initial_state);
            
            number_of_nodes_generated = results.size();
            
            while (!results.empty()) {
                State st = results.top();
                output_file << st.state_output_generator();
                results.pop();
            }
            
            for (int i = 0; i < state_list.size(); i++) {
                maximum_size += state_list[i].size();
            }
            
            cout << endl << "BFS has worked !" << endl;
            cout << "Total number of prevented cycle:\t" << cycle_prevented << endl;
            cout << "The number of nodes generated:\t" << number_of_nodes_generated << endl;
            cout << "The maximum number of nodes kept in the memory:\t" << maximum_size << endl;
            cout << "The running time:\t" << double(t) / CLOCKS_PER_SEC << " sec" << endl;
            
        } else {
            
            cout << "NOT FOUND !" << endl;
        }
        
        
    }
    
    void DFS(State& initial_state){                     // EXPLICIT DFS TO CALL IMPLICIT ONE AND SHOW RESULTS

        clock_t t = clock();
        State state = depth_first_search(initial_state);
        t = clock() - t;
        
        if (found == true) {
            stack<State> results;
            unsigned long number_of_nodes_generated = 0;
            unsigned long maximum_size = state_list[0].size();
            
            while (state.get_parent_order() != -1) {
                results.push(state);
                state = state_list[state.get_parent_layer()][state.get_parent_order()];
            }
            
            results.push(initial_state);
            
            number_of_nodes_generated = results.size();
            
            while (!results.empty()) {
                State st = results.top();
                output_file << st.state_output_generator();
                results.pop();
            }
            
            cout << endl << "DFS has worked !" << endl;
            cout << "Total number of prevented cycle:\t" << cycle_prevented << endl;
            cout << "The number of nodes generated:\t" << number_of_nodes_generated << endl;
            cout << "The maximum number of nodes kept in the memory:\t" << maximum_size << endl;
            cout << "The running time:\t" << double(t) / CLOCKS_PER_SEC << " sec" << endl;
            
        } else {
            
            cout << "NOT FOUND !" << endl;
        }
    }
    
};

int main(int argc, const char * argv[]) {
    
    ifstream blocks_file;
    string algorithm(argv[1]), input_file_name(argv[2]), output_file_name(argv[3]);
    
    blocks_file.open(input_file_name);
    
    int y_axis, x_axis, n, count_q = 1;
    char b_type;
    Algorithms algorithms(output_file_name);
    
    State first_state;
    
    while (blocks_file >> y_axis >> x_axis >> n >> b_type)
        first_state.state_blocks.push_back(Block(y_axis, x_axis, b_type, n, count_q++));
    
    first_state.prepare_the_grid();
    first_state.set_parent(-1, -1);
    
    if (algorithm == "bfs") {
        algorithms.BFS(first_state);
    } else if (algorithm == "dfs") {
        algorithms.DFS(first_state);
    }
    
    blocks_file.close();
    
    return 0;
}
