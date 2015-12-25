#include <iostream>
#include <stdlib.h>

#define SIZE 20

using namespace std;

struct Stack{
    char element[SIZE];
    float sayiDizisi[SIZE];
    int top;
    bool push(char);
    bool pushSayi(float);
    char pop();
    float popSayi();
    bool isempty();
    void create();
    float calculation(char *);
};

float Stack::calculation(char * postStr){
    
    int i = 0;
    float temp = 0, returnVal = 0;
    
    while (postStr[i] != '\0') {
        
        if (isdigit(postStr[i])) {
            pushSayi(postStr[i] - '0');
        
        } else {
            
            temp = popSayi();
            
            switch (postStr[i]) {
                case '+':
                    returnVal = temp + popSayi();
                    pushSayi(returnVal);
                    break;
                
                case '-':
                    returnVal = popSayi() - temp ;
                    pushSayi(returnVal);
                    break;
                    
                case '/':
                    returnVal = popSayi() / temp;
                    pushSayi(returnVal);
                    break;
                    
                case '*':
                    returnVal = temp * popSayi();
                    pushSayi(returnVal);
                    break;
                    
                default:
                    break;
            }
            
        }
        
        i++;
    }
    
    return sayiDizisi[top-1];
}

bool Stack::pushSayi(float newElement){
   
    if (top < SIZE) {
        sayiDizisi[top++] = newElement;
        return true;
    }
   
    return false;
}

bool Stack::push(char newElement){
    
    if (top < SIZE) {
        element[top++] = newElement;
        return true;
    }
    
    return false;
}

void Stack::create(){
    top = 0;
}

char Stack::pop(){
    return element[--top];
}

float Stack::popSayi(){
    return sayiDizisi[--top];
}

bool Stack::isempty(){
    return (top == 0);
}

int precedence(char);

int main(){
    
    Stack s, result;
    s.create();
    result.create();
    
    while(1){
        
        char dizi[40], postfix[40], ch;
        int a = 0, i = 0;
        
        cout << endl << "Enter the Infix Expression (E to exit): ";
        cin >> dizi;
        
        if (dizi[0] == 'E') {
            break;
        
        } else {
            
            while (dizi[a] != '\0') {
                
                if (isdigit(dizi[a])) {
                    postfix[i] = dizi[a];
                    i++;
                    
                } else {
                    
                    if (s.isempty() || dizi[a] == '(') {
                        
                        s.push(dizi[a]);
                        
                    } else if (!(s.isempty()) && dizi[a] != ')' && dizi[a] != '('){
                        
                        while (precedence(s.element[(s.top)-1]) >= precedence(dizi[a]) && !(s.isempty())) {
                            
                            ch = s.pop();
                            
                            if (ch != '(' || ch != ')') {
                                postfix[i] = ch;
                                i++;
                            }
                        }
                        
                        s.push(dizi[a]);
                        
                    } else if (dizi[a] == ')') {
                        
                        while (s.element[(s.top)-1] != '(') {
                            
                            ch = s.pop();
                            postfix[i] = ch;
                            i++;
                        }
                    }
                }
                
                a++;
            }
            
            while (!(s.isempty())) {
                
                ch = s.pop();
                
                if (ch == '(') {
                    continue;
                    
                } else {
                    postfix[i] = ch;
                    i++;
                    
                }
            }
            
            postfix[i] = '\0';
            cout << "Postfix Expression: " << postfix << "\t\tResult: " << result.calculation(postfix) << endl;
        
        }
    }
    
    return 0;
}

int precedence(char op){
    
    if (op == '+' || op == '-'){
        return 1;
    
    } else if (op == '/' || op == '*'){
        return 2;
    
    } else {
        return -1;
    }
}

