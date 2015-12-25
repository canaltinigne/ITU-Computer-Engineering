#include <iostream>
#include <time.h>
#include <cstdlib>
#include "tree.h"

using namespace std;

struct Queue {
    node *front;
    node *back;
    void create();
    void close();
    bool isempty();
    void enqueue(node*);
    node* dequeue();
};
struct Stack{
    node *head;
    void create();
    void close();
    void push(node*);
    node* pop();
    bool isempty();
};

void Stack::create(){
    head=NULL;
}

void Stack::close(){
    node *p;
    while (head){
        p = head;
        head = head->next;
        //delete [] p->data;
        delete p;
    }
}

void Stack::push(node *newdata){
    node *newnode = new node;
    newnode = newdata;
    newnode->number = newdata->number;
    newnode->next = head;
    head = newnode;
}

node *Stack::pop(){
    if (isempty())
        return NULL;
    node *topnode = head;
    head = head->next;
    //delete topnode;
    return topnode;
}
bool Stack::isempty(){
    return (head == NULL);
}

void Queue::enqueue(node* newdata){
    node *newnode = new node;
    newnode = newdata;
    newnode->left=newdata->left;
    newnode->right=newdata->right;
    newnode->number=newdata->number;
    newnode->next = NULL;
    if ( isempty() ) { // first element?
        back = newnode;
        front = back;
    }
    else {
        back->next = newnode;
        back = newnode;
    }
}

node *Queue::dequeue() {
    node *topnode;
    topnode = front;
    front = front->next;
    //delete topnode;
    return topnode;
}

bool Queue::isempty() {
    return front == NULL;
}

void Queue::create(){
    front = NULL; back = NULL;
}

void Queue::close(){
    node *p;
    while (front) {
        p = front;
        front = front->next;
        //delete [] p->data;
        delete p;
    }
}

void BFS(node * root, int search){
    
    Queue q;
    q.create();
    q.enqueue(root);
    node * u = NULL;
    int step = 0;
    
    while (!q.isempty()) {
        u = q.front;
        q.dequeue();
        
        if(u->left)
            q.enqueue(u->left);
        
        if(u->right)
            q.enqueue(u->right);
        
        cout << u->number << " ";
        
        
        ++step;
        
        if(u->number == search){
            cout << endl << "Found " << search << " in " << step << " steps";
            break;
        }
    }
}

int stepInorder = 0;

void inorderSearch(node * root, int search) {
    
    int n = search;
    
    if (root) {
        
        stepInorder++;
        
        inorderSearch(root->left, n);
        
        cout << root->number << " ";
        
        if (root->number == n) {
            cout << endl << "Found " << search << " in " << stepInorder << " steps";
            return;
        }
        
        inorderSearch(root->right, n);
        
    }
}


void DFS(node * root, int search){
    
    Stack s;
    s.create();
    s.push(root);
    node * u = NULL;
    int step = 0;
    
    while (!s.isempty()) {
        u = s.head;
        s.pop();
        
        if(u->left)
            s.push(u->left);
        
        if(u->right)
            s.push(u->right);
        
        cout << u->number << " ";
        
        ++step;
        
        if(u->number == search){
            cout << endl << "Found " << search << " in " << step << " steps";
            break;
        }
    }
}

bool add();
void PrintMenu();

tree agac;

int main() {
    
    srand(time(NULL));
    
	tree tree;
	tree.createTree();
    
    int number;
    
	cout << endl << "Postorder:   ";
	tree.printPostorder(tree.root);
    cout << endl;
	cout << endl << "Inorder:   ";
	tree.printInorder(tree.root);
    cout << endl;
	cout << endl << "Preorder:   ";
	tree.printPreorder(tree.root);
    cout << endl;
    cout << endl << "Enter a number to search: ";
    cin >> number;
    cout << endl << "BFS: ";
    BFS(tree.root,number);
    cout << endl;
    cout << endl << "DFS: ";
    DFS(tree.root,number);
    cout << endl;
    cout << endl << "Inorder Search: ";
    inorderSearch(tree.root,number);
    cout << endl;

	tree.temp_recursive = 0;
	cout << endl << "Node Number: " << tree.findNumNode(tree.root) << endl;
	
	tree.temp_recursive = 0;
	cout << endl << "Sum: " << tree.calculateSum(tree.root) << endl;
	
	tree.temp_recursive = 0;
	cout << endl << "Average: " << tree.calculateAverage(tree.root) << endl;
	
	tree.temp_recursive = 0;
	cout << endl << "Leaf Number: " << tree.findNumLeaf(tree.root) << endl;
	
	tree.temp_recursive = 0;
	if ( tree.root != NULL) {
		tree.temp_recursive = tree.root->number;
		cout << endl << "Find Max: " << tree.findMax(tree.root)<<endl;
		tree.temp_recursive = 0;
	}
	if (tree.root != NULL) {
		tree.temp_recursive = tree.root->number;
		cout << endl << "Find Min: " << tree.findMin(tree.root) << endl;
		tree.temp_recursive = 0;
	}

	tree.temp_recursive = 0;
	cout << endl << "Find Depth: " << tree.calculateDepth(tree.root)+1 << endl;
	tree.removeTree(tree.root);
	return 0;
}
