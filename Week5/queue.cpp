#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;
struct NODE {
    int key ;
    NODE * p_next ;
};
struct Queue {
    NODE * head ;
    NODE * tail ;
};

Queue* initializeQueue() {
    Queue* q = new Queue ;
    q->head = q->tail = NULL;
    return q;
}

bool isEmpty(Queue* q) {
    return q->head == NULL;
}

void enqueue(Queue* q, int key) {
    NODE * node = new NODE ;
    node->key = key ;
    node->p_next = NULL;
    if(isEmpty(q)) {
        q->head = q->tail = node;
        return;
    }
    q->tail->p_next = node;
    q->tail = node;
}

int dequeue(Queue* q) {
    if(isEmpty(q)) return -1;
    NODE * temp = q->head ;
    q->head = q->head->p_next ;
    int key = temp->key ;
    delete temp ;
    return key ;
}

int size(Queue q) {
    int size = 0;
    NODE * temp = q.head ;
    while(temp != NULL) {
        size++ ;
        temp = temp->p_next ;
    }
    return size ;
}

void display(Queue *q, ostream &out) {
   if (isEmpty(q)) {
       out << "EMPTY" << endl ;
       return ;
   }
    NODE * temp = q->head ;
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
    Queue* q = NULL;
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
        if(strcmp(strfirst,"init")==0) q = initializeQueue();
        else if(strcmp(strfirst,"enqueue")==0) enqueue(q,atoi(strsecond));
        else if(strcmp(strfirst,"dequeue")==0) {
            if(isEmpty(q)) {
                output_file<<"EMPTY"<<endl;
                continue;
            }
            dequeue(q);
        }
        display(q,output_file);
    }
    input_file.close();
    output_file.close();
}
