#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;
struct NODE {
    int key ;
    NODE * p_next ;
};
struct Stack {
    NODE * top ;
};

Stack* initializeStack() {
    Stack* stack = new Stack;
    stack->top = NULL;
    return stack ;
}

void push(Stack* s, int key) {
    NODE * new_node = new NODE ;
    new_node->key = key ;
    new_node->p_next = s->top ;
    s->top = new_node ;
}

bool isEmpty(Stack* s) {
    return s->top == NULL ;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        return -1;
    }
    NODE * temp = s->top ;
    s->top = s->top->p_next ;
    int key = temp->key ;
    delete temp ;
    return key ;
}

int size(Stack* s) {
    NODE * temp = s->top ;
    int size = 0 ;
    while (temp != NULL) {
        temp = temp->p_next ;
        size++ ;
    }
    return size ;
}

void display(Stack *s, ostream &out) {
   if (isEmpty(s)) {
       out << "EMPTY" << endl ;
       return ;
   }
    NODE * temp = s->top ;
    while (temp != NULL) {
        out << temp->key <<" ";
        temp = temp->p_next ;
    }
    out << endl ;
}
int main()
{
    char* str=new char[100];
    char* strfirst=new char[100];
    char* strsecond=new char[100];
    Stack* s=NULL;
    ifstream input_file ;
    ofstream output_file ;
    input_file.open("input.txt",ios::in);
    output_file.open("output.txt",ios::out);
    while(input_file.getline(str,100)) {
        char* token=strtok(str," \n");
        if(token!=NULL) strcpy(strfirst,token);
        else continue;
        token=strtok(NULL," \n");
        if(token!=NULL) strcpy(strsecond,token);
        else strsecond[0]='\0';
        if(strcmp(strfirst,"init")==0) s=initializeStack();
        else if(strcmp(strfirst,"push")==0) push(s,atoi(strsecond));
        else if(strcmp(strfirst,"pop")==0) {
            if(isEmpty(s)) {
                output_file<<"EMPTY"<<endl;
                continue;
            }
            pop(s);
        }
        display(s,output_file);
    }
    input_file.close();
    output_file.close();
}
