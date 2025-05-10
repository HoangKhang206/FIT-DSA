#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
constexpr int Size = 2000;
struct Company {
    string name;
    string profit_tax;
    string address;
};
struct NODE {
    Company company;
    NODE *Next;
};
struct HashTable {
    NODE** Table= new NODE*[Size];
};
NODE* CreateNode(Company company);
void InitHashTable(HashTable* H);
vector<Company> readCompanyList(string file_name);
long long hashString(string company_name);
HashTable* CreateHashTable(vector<Company> list_company);
void insert(HashTable* hash_table, Company company);
Company* search(HashTable* hash_table, string company_name);
void searchfile(HashTable* hash_table, string input,string output);

int main(int argc,char* argv[])
{
    string input;
    string output;
    string finfor;
    finfor = argv[1];
    input=argv[2];
    output=argv[3];
    cout << "main function argc: "<< argc << endl;
    cout << "information: " << finfor << endl;
    cout << "input: "<<input<<endl;
    cout << "output: "<<output<<endl;
    HashTable* hash_table = CreateHashTable(readCompanyList(finfor));
    searchfile(hash_table,input,output);
}

NODE* CreateNode(Company company) {
    NODE* new_node = new NODE;
    new_node->company = company;
    new_node->Next = NULL;
    return new_node;
}

void InitHashTable(HashTable* H) {
    for (int i = 0; i < Size; i++) {
        H->Table[i] = nullptr;
    }
}

vector<Company> readCompanyList(string file_name) {
    ifstream Fin;
    Fin.open(file_name,ios::in);
    vector<Company> company;
    Company temp;
    string name, profit_tax, address;
    while(!Fin.eof()) {
        getline(Fin,name,'|');
        getline(Fin,profit_tax,'|');
        getline(Fin,address);
        temp.name = name;
        temp.profit_tax = profit_tax;
        temp.address = address;
        company.push_back(temp);
    }
    Fin.close();
    return company;
}

long long hashString(string company_name) {
    const int p= 31;
    string s= (company_name.length()<=20)?company_name:company_name.substr(company_name.length()-20);
    long long hash= 0;
    int pow=1;
    for(int i=0;i<s.length();i++) {
        hash= (hash+(s[i]*pow))%Size;
        pow= (p*pow)%p;
    }
    return hash;
}

HashTable* CreateHashTable(vector<Company> list_company) {
    HashTable *H = new HashTable;
    InitHashTable(H);
    for (int i = 0; i < list_company.size(); i++) {
        insert(H,list_company[i]);
    }
    return H;
}

void insert(HashTable* hash_table, Company company) {
    long long index = hashString(company.name);
    NODE*p= hash_table->Table[index];
    while(p!=NULL) {
        if(p->company.name == company.name) {
            p->company.profit_tax = company.profit_tax;
            p->company.address = company.address;
            return;
        }
        p=p->Next;
    }
    NODE* new_node = CreateNode(company);
    new_node->Next = hash_table->Table[index];
    hash_table->Table[index] = new_node;
}

Company* search(HashTable* hash_table, string company_name) {
    long long index = hashString(company_name);
    NODE* p = hash_table->Table[index];
    while (p != NULL) {
        if (p->company.name == company_name) {
            return &p->company;
        }
        p=p->Next;
    }
    return NULL;
}

void searchfile(HashTable* hash_table, string input,string output) {
    ifstream Fin;
    ofstream Fout;
    string line;
    Company *company;
    Fin.open(input,ios::in);
    Fout.open(output,ios::out);
    while(getline(Fin,line)) {
        company=search(hash_table,line);
        Fout<<company->name<<"|"<<company->profit_tax<<"|"<<company->address<<endl;
    }
    Fin.close();
    Fout.close();
}