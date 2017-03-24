//      Analysis of Algorithms I - HW 5
//      Can Yılmaz Altıniğne - 150130132

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

//  FOR NODE COLORING

enum Color {
    RED,
    BLACK
};

//  PERSON CLASS EACH NODE HAS A PERSON OBJECT TO KEEP DETAILS: AGE, NAME & GENDER

class Person {
    
    int age;
    string name;
    char gender;
    
public:
    
    Person(string name, char gender, int age){
        this->age = age;
        this->name = name;
        this->gender = gender;
    }
    
    int get_age(){
        return age;
    }
    
    string get_name(){
        return name;
    }
    
    char get_gender(){
        return gender;
    }
};

//  NODE CLASS FOR RED BLACK TREE
//  IT KEEPS PERSON OBJECT, COLOR VARIABLE AND TOTAL ADULT & NON-ADULT NUMBERS OF SUBTREE THAT THE NODE ROOTED

class Node {
    
    Person person;
    Color color;
    int num_adult;
    int num_non_adult;
    
public:
    
    Node * left_child;
    Node * right_child;
    Node * parent;
    
    
    Node(string name, char gender, int age, Color color): person(name, gender, age){
        this->left_child = NULL;
        this->right_child = NULL;
        this->parent = NULL;
        this->color = color;
        num_adult = 0;
        num_non_adult = 0;
    }
    
    Person get_person(){
        return person;
    }
    
    void set_color(Color color){
        this->color = color;
    }
    
    Color get_color(){
        return color;
    }
    
    void set_num_adult(int num){
        num_adult = num;
    }
    
    void set_num_non_adult(int num){
        num_non_adult = num;
    }
    
    int get_adult(){
        return num_adult;
    }
    
    int get_num_non_adult(){
        return num_non_adult;
    }
};

//  NIL NODE IS INHERITED FROM NODE THIS CLASS FOR NIL'S IN TREE
//  I TRIED TO USE NULL VALUE FOR NILS AT FIRST BUT WHEN I ROTATE I MIGHT ACCESS A NIL VALUE
//  IF IT WAS NULL VALUE THEN I COULD NOT USE SOME FUNCTIONS THAT I USE IN ROTATE OPERATIONS
//  SINCE NULL VALUE HAS NO FUNCTIONS OR VALUES

class Nil_Node: public Node {
    
public:
    Nil_Node():Node("Nil", 'X', 0, BLACK){}         // NIL NODES HAVE BLACK COLOR, THERE IS ONLY ONE NIL NODE WHICH IS PARENT OF ROOT (TO NOT MAKE IT NULL) AND CHILD OF LEAVES
};                                                  // AND NODES THAT DO NOT HAVE REAL CHILD

//  RED-BLACK TREE CLASS FOR TREE OPERATIONS

//  !   I have implemented all Red-Black Tree operations by benefiting from pseudocodes in
//      Introduction to Algorithms by Thomas H. Cormen
//      p.278, p.280, p.281

//  !   Finding Nth adult and Nth non-adult person function code is implemented by benefiting from lecture slide: Augmenting Data Structures
//      But this implementation we have to consider the situation of the node before increment adult or non-adult rank after finding left-subtree's total number of
//      adult and non-adults

class Red_Black_Tree {
    
    Node * root;
    Node * nil_node;
    
    void fix_position(Node * inserted_node){             //  THIS FUNCTION WORKS AT THE END OF RB-INSERT FUNCTION
                                                            //  TO DETERMINE THE EXACT POSITION OF NODE BY RECOLORING, MAKING ZIG-ZAG TO ZIG-ZIG AND ROTATING
        Node * uncle;
        
        refresh_child_nums_in_that_path(inserted_node);          // FIRST I FIND MY ADULT AND NON-ADULT NUMBER WHICH IS ZERO BECAUSE I AM INSERTING NEW NODE
                                                                //  BUT I NEED TO UPDATE FROM THAT NODE TO ROOT IN THAT PATH ALL NODES ADULT OR NON-ADULT VALUE MUST BE UPDATED
                                                                // THEY HAVE TO HAVE A INCREMENTED VALUE
        while (inserted_node->parent->get_color() == RED) {             // KEEP GOING UNTIL THE PARENT HAS BLACK COLOR IT MEANS THAT WE ENSURE BLACK HEIGHT PROPERTY AT THE END OF LOOP
            
            if (inserted_node->parent == inserted_node->parent->parent->left_child) {       //  MY PARENT IS LEFT CHILD OF MY GRANDPARENT
                
                uncle = inserted_node->parent->parent->right_child;                         //  FIND MY UNCLE
                
                if (uncle->get_color() == RED) {                                            // IF MY UNCLE IS RED THEN I CAN GIVE MY GRANDPARENT'S BLACKNESS TO MY PARENT AND MY UNCLE
                    inserted_node->parent->set_color(BLACK);
                    uncle->set_color(BLACK);
                    inserted_node->parent->parent->set_color(RED);                  // AFTER RECOLORING I DONT NEED TO UPDATE ADULT OR NON-ADULT VALUE
                    inserted_node = inserted_node->parent->parent;                  // AND I GO UP TWO STEPS AND CAME TO MY GRANDPARENT'S NODE
                } else {
                    if(inserted_node == inserted_node->parent->right_child){        // IF RECOLORING DOES NOT WORK I LOOK AT IF I HAVE A ZIG-ZAG SITUATION
                        inserted_node = inserted_node->parent;
                        left_rotate(inserted_node);                                 // I MAKE ZIG-ZAG TO ZIG-ZIG
                        refresh_child_nums_after_rotation(inserted_node);           // AND I UPDATE ADULT AND NON-ADULT VALUES FOR NEW CHILD (OLD PARENT) AND NEW PARENT(OLD CHILD)
                        refresh_child_nums_after_rotation(inserted_node->parent);
                    }
                    
                    inserted_node->parent->set_color(BLACK);                        // I MAKE ROTATING IN THIS PHASE, IN THIS PHASE I HAVE EXACT ZIG-ZIG NODES I MAKE ROTATE
                    inserted_node->parent->parent->set_color(RED);                  // AND I CHANGE COLORS OF MY OLD GRAND PARENT (BECOMES MY PARENT'S RIGHT CHILD) AND MY PARENT
                    right_rotate(inserted_node->parent->parent);
                    refresh_child_nums_after_rotation(inserted_node->parent->right_child);      //  I UPDATE ADULT AND NON-ADULT VALUES FOR MY PARENT AND MY NEW SIBLING (OLD GRANDPARENT)
                    refresh_child_nums_after_rotation(inserted_node->parent);
                }
                
            } else {                                                                // SAME THINGS LIKE ABOVE BUT IN THIS PART Y PARENT IS RIGHT CHILD OF MY GRANDPARENT
                
                uncle = inserted_node->parent->parent->left_child;
                
                if (uncle->get_color() == RED) {
                    inserted_node->parent->set_color(BLACK);
                    uncle->set_color(BLACK);
                    inserted_node->parent->parent->set_color(RED);
                    inserted_node = inserted_node->parent->parent;
                    
                } else {
                    
                    if(inserted_node == inserted_node->parent->left_child){
                        inserted_node = inserted_node->parent;
                        right_rotate(inserted_node);
                        refresh_child_nums_after_rotation(inserted_node);
                        refresh_child_nums_after_rotation(inserted_node->parent);
                    }
                    
                    inserted_node->parent->set_color(BLACK);
                    inserted_node->parent->parent->set_color(RED);
                    left_rotate(inserted_node->parent->parent);
                    refresh_child_nums_after_rotation(inserted_node->parent->left_child);
                    refresh_child_nums_after_rotation(inserted_node->parent);
                }
            }
        }
        
        root->set_color(BLACK);
    }
    
    void left_rotate(Node * x){                             // LEFT ROTATE FUNCTION
        
        Node * y = x->right_child;          // X IS PARENT OF INSERTED NODE, Y IS INSERTED NODE
        x->right_child = y->left_child;     // IN LEFT ROTATION  PARENT HAS LEFT CHILD OF INSERTED NODE AS RIGHT CHILD
        
        if (y->left_child != nil_node) y->left_child->parent = x;       // X BECOMES NEW PARENT OF Y'S LEFT CHILD
        
        y->parent = x->parent;      // OUR INSERTED NODE'S PARENT BECOMES OUR OLD GRANDPARENT
        
        if (x->parent == nil_node) root = y;    // IF NO PARENT THEN INSERTED NODE BECOMES ROOT
        else {
            if (x == x->parent->left_child)     // IF INSERTED NODE'S OLD PARENT WAS LEFT CHILD OF GRANDPARENT
                x->parent->left_child = y;      // INSERTED NODE BECOMES LEFT CHILD OF ITS NEW PARENT
            else
                x->parent->right_child = y;     // ELSE RIGHT CHILD
        }
        
        y->left_child = x;          // INSERTED NODE'S NEW LEFT CHILD IS OUR OLD PARENT
        x->parent = y;              // OLD PARENT'S NEW PARENT IS INSERTED NODE
    }
    
    void right_rotate(Node * x){            // SYMMETRIC TO LEFT ROTATE FUNCTION
        
        Node * y = x->left_child;
        x->left_child = y->right_child;
        
        if (y->right_child != nil_node) y->right_child->parent = x;
        
        y->parent = x->parent;
        
        if (x->parent == nil_node) root = y;
        else {
            if (x == x->parent->right_child)
                x->parent->right_child = y;
            else
                x->parent->left_child = y;
        }
        
        y->right_child = x;
        x->parent = y;
    }
    
    void refresh_child_nums_after_rotation(Node * ptr){             // REFRESH THE NODE'S ADULT AND NON-ADULT NUMBERS
        if ((ptr->get_person()).get_age() < 18) {                   // WE HAVE TO LOOK AT OUR CURRENT AGE STATUS WE CAN NOT INCREMENT BY 1 LIKE IN SIZE EXAMPLE IN SLIDES
            ptr->set_num_adult(ptr->left_child->get_adult() + ptr->right_child->get_adult());
            ptr->set_num_non_adult(ptr->left_child->get_num_non_adult() + ptr->right_child->get_num_non_adult() + 1);       // IF WE ARE NON-ADULT INCREMENT IT BY 1 BECAUSE OUR NON-ADULT RANK
        } else {
            ptr->set_num_adult(ptr->left_child->get_adult() + ptr->right_child->get_adult() + 1);                           // IF WE ARE ADULT INCREMENT IT BY 1 BECAUSE OUR ADULT RANK
            ptr->set_num_non_adult(ptr->left_child->get_num_non_adult() + ptr->right_child->get_num_non_adult());
        }
    }
    
    void refresh_child_nums_in_that_path(Node * ptr){                // THIS FUNCTION UPDATES ALL NODES IN PATH OF INSERTED NODE TO ROOT. AFTER BINARY TREE INSERT (BEFORE COLORING AND ROTATIONS)
        while (ptr != nil_node) {                               // NIL NODE IS PARENT OF ROOT (JUST INITIALIZE USELESS) TO THE ROOT UPDATE THE NODES ON THAT PATH
            if ((ptr->get_person()).get_age() < 18) {
                ptr->set_num_adult(ptr->left_child->get_adult() + ptr->right_child->get_adult());
                ptr->set_num_non_adult(ptr->left_child->get_num_non_adult() + ptr->right_child->get_num_non_adult() + 1);
            } else {
                ptr->set_num_adult(ptr->left_child->get_adult() + ptr->right_child->get_adult() + 1);
                ptr->set_num_non_adult(ptr->left_child->get_num_non_adult() + ptr->right_child->get_num_non_adult());
            }
            
            ptr = ptr->parent;
        }
    }
    
public:
    
    Red_Black_Tree(){
        nil_node = new Nil_Node;
        root = nil_node;
    }
    
    Node * get_root(){
        return root;
    }
    
    void binary_tree_insert(Node * inserted_node){           // SIMPLE BINARY TREE INSERT
        
        Node * y = nil_node;
        Node * x = root;
        inserted_node->left_child = nil_node;           // INITIALIZATIONS FOR INSERTED NODE
        inserted_node->right_child = nil_node;
        inserted_node->set_color(RED);
        
        while (x != nil_node) {         // FIND THE PLACE FOR INSERTING
            y = x;          // Y COMES FROM BEHIND
            (inserted_node->get_person()).get_name() < (x->get_person()).get_name() ? x = x->left_child : x = x->right_child;  // COMPARISON
        }
        
        inserted_node->parent = y;
        
        if (y == nil_node)
            root = inserted_node;           // FIRST NODE
        else {
            if ((inserted_node->get_person()).get_name() < (y->get_person().get_name())) y->left_child = inserted_node;     // WHICH CHILD LEFT OR RIGHT DECIDE
            else y->right_child = inserted_node;
        }
        
        fix_position(inserted_node);         // CALL FIX POSITION FUNCTION FOR COLORING AND ROTATION OPERATIONS
    }
    
    void preorder_traverse(Node * ptr, int x) {          // PREORDER TRAVERSE FOR RED BLACK TREE
        
        if (ptr != nil_node) {
            for (int a = 0; a < x; a++) cout << "-";                    // X IS THE LEVEL PARAMETER FOR FUNCTION SEND 0 FOR ROOT
            ptr->get_color() == RED ? cout << "(R) " : cout << "(B) ";
            cout << (ptr->get_person()).get_name() << " " << (ptr->get_person()).get_gender() << " " << (ptr->get_person()).get_age() << endl;      // PRINT NODE
            preorder_traverse(ptr->left_child, x+1);         // GET THE NEW LEVELS
            preorder_traverse(ptr->right_child, x+1);
        }
    }
    
    string find_adult_with_rank(Node * x, int i){
        
        int k;
        
	if(!x->left_child) return "Adult could not found";

        if ((x->get_person()).get_age() < 18)           // IF CURRENT NODE'S AGE IS AN ADULT AGE WE HAVE TO INCREMENT LEFT CHILD'S ADULT NUMBER TO FIND OUR RANK
            k = x->left_child->get_adult();
        else
            k = x->left_child->get_adult() + 1;
        
        if (i == k && x->left_child->get_adult() != k)      // IF WE HAVE THE SAME RANK WITH SEARCH VALUE RETURN THE CURRENT NODE'S NAME
            return (x->get_person()).get_name();            // SOMETIMES WE HAVE SAME VALUE WITH OUR LEFT CHILD BUT OUR ADULT AND NON-ADULT FEATURES ARE DIFFERENT
                                                            // AS A RESULT A ADULT MIGHT HAVE RETURNED FOR NON-ADULT SEARCH
                                                            // TO PREVENT THIS 'x->left_child->get_adult() != k' ADDED
        if (i <= k)                                         // IF SEARCH RANK IS LOW OR EQUAL THAN SEARCH LEFT SUBTREE
            return find_adult_with_rank(x->left_child, i);
        else                                                // ELSE SEARCH RIGHT SUBTREE
            return find_adult_with_rank(x->right_child, i-k);
    }
    
    string find_non_adult_with_rank(Node * x, int i){                 // SAME FOR FIND ADULT FUNCTION BUT THIS TIME LOOK AT NON ADULT VALUES
        
        int k;
    	if(!x->left_child) return "Non adult could not found";
   
        if ((x->get_person()).get_age() < 18)
            k = x->left_child->get_num_non_adult() + 1;
        else
            k = x->left_child->get_num_non_adult();
        
        
        if (i == k && x->left_child->get_num_non_adult() != k)
            return (x->get_person()).get_name();
        
        
        if (i <= k)
            return find_non_adult_with_rank(x->left_child, i);
        else
            return find_non_adult_with_rank(x->right_child, i-k);
    }
    
    void print_person(Node * x, int i, bool is_adult){          // FOR PRINTING NTH ADULT OR NON-ADULT PERSON
        
        cout << i;
            
        if (i % 10 == 1) cout << "st";
        else if (i % 10 == 2) cout << "nd";
        else if (i % 10 == 3) cout << "rd";
        else cout << "th";
            
        cout << " ";
        is_adult ? (cout << "adult: " << find_adult_with_rank(x, i)) : (cout << "non-adult: " << find_non_adult_with_rank(x, i));
        cout << endl;
    }
    
    void clean_tree(Node * ptr){               // POST-ORDER TREE DELETE FUNCTION
        if (ptr != nil_node) {
            clean_tree(ptr->left_child);
            clean_tree(ptr->right_child);
            delete ptr;
        }
    }
    
    ~Red_Black_Tree(){                              // DELETE NIL NODE THERE IS JUST ONE NIL NODE ONE ADDRESS
        delete nil_node;
    }
};

int main(int argc, const char * argv[]) {
    
    ifstream input_file;
    string name;
    char gender;
    int age;
    Red_Black_Tree red_black_tree;
    
    input_file.open(argv[1]);

    while (input_file >> name >> gender >> age) {                   // GET INPUT
        Node * node = new Node(name, gender, age, RED);
        red_black_tree.binary_tree_insert(node);
    }
    
    red_black_tree.preorder_traverse(red_black_tree.get_root(), 0);      // PREORDER TRAVERSAL
    
    cout << endl;
    
    red_black_tree.print_person(red_black_tree.get_root(), 5, true);        // PRINT NTH PERSON
    red_black_tree.print_person(red_black_tree.get_root(), 3, false);
    
    red_black_tree.clean_tree(red_black_tree.get_root());                      // FREE TREE
    input_file.close();
   
    return EXIT_SUCCESS;
}
