#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
#include <cmath>
#include <sstream>
#include <algorithm>
using namespace std;

void Reverse(string& str);
int Cmpstr(const string& s1, const string& s2);
void DeletezeroinHead(string& str);
bool Isnegative(const string& str);
char Isdivisible(const string& str1, const string& str2);
int DecimalLength(const string& str);
int Processingdot(string& A, string& B);
void Insertdot(string& str, int MaxDecimal);
string Add(const string& a, const string& b);
string Sub(const string& a, const string& b);
string Mul(const string& a, const string& b);
string Div(const string& a, const string& b);
bool Isdigit(string& str);
bool IsOperator(char c);
int Prioritize(string& str);
string Strprocessingspace(const string& str);
string InfixToPostfix(const string& a);
string EvaluatePostfix(const string& a);
bool IsValidExpression(const string& str);


int main(int argc,char* argv[])
{
    string input;
    string output;
    input=argv[1];
    output=argv[2];
    cout << "main function argc: "<< argc << endl;
    cout << "input: "<<input<<endl;
    cout << "output: "<<output<<endl;
    string line;
    ifstream Fin;
    ofstream Fout;
    Fin.open(input,ios::in);
    Fout.open(output,ios::out);
    while(getline(Fin,line)) {
        if (line.empty()) continue;
        if(IsValidExpression(line)) {
            string rs=EvaluatePostfix(line);
            Fout<<rs<<endl;
        }
        else Fout<<"Invalid Expression"<<endl;
    }
    Fin.close();
    Fout.close();
}

void Reverse(string& str) {
    reverse(str.begin(), str.end());
}

int Cmpstr(const string& s1, const string& s2) {
    bool negative1 = Isnegative(s1);
    bool negative2 = Isnegative(s2);
    if (negative1 && negative2) {
        return -Cmpstr(s1.substr(1), s2.substr(1));
    }
    if (negative1) {
        return -1;
    }
    if (negative2) {
        return 1;
    }
    string str1 = s1;
    string str2 = s2;
    if (str1.find('.') != string::npos || str2.find('.') != string::npos) {
        Processingdot(str1, str2);
    }
    DeletezeroinHead(str1);
    DeletezeroinHead(str2);
    int len1 = str1.length();
    int len2 = str2.length();
    if (len1 < len2) {
        return -1;
    }
    if (len1 > len2) {
        return 1;
    }
    return str1.compare(str2);
}


void DeletezeroinHead(string& str) {
    int i = 0;
    int sign = 1;
    if (Isnegative(str)) {
        i = 1;
        sign = -1;
    }
    while (i < str.length() && str[i] == '0') i++;
    if (i == str.length()) {
        str = "0";
        return;
    }
    string rs;
    if (sign == -1) rs += '-';
    if (str[i] == '.') rs += '0';
    while (i < str.length()) {
        rs += str[i++];
    }

    str = rs;
}

bool Isnegative(const string& str) {
    return !str.empty() && str[0] == '-';
}

char Isdivisible(const string& str1, const string& str2) {
    int left = 0, right = 9;
    char ans;
    string check;
    while (left <= right) {
        int mid = (left + right) / 2;
        string strmid = to_string(mid);

        check = Mul(strmid, str2);
        if (Cmpstr(check, str1) <= 0) {
            ans = strmid[0];
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

int DecimalLength(const string& str) {
    size_t dot = str.find('.');
    if (dot == string::npos) return 0;
    return str.length() - dot - 1;
}


int Processingdot(string& A, string& B) {
    int DecimalA = DecimalLength(A);
    int DecimalB = DecimalLength(B);
    int MaxDecimal = max(DecimalA, DecimalB);
    if (MaxDecimal == DecimalA) {
        B.append(MaxDecimal - DecimalB, '0');
    }
    else {
        A.append(MaxDecimal - DecimalA, '0');
    }
    A.erase(remove(A.begin(), A.end(), '.'), A.end());
    B.erase(remove(B.begin(), B.end(), '.'), B.end());
    return MaxDecimal;
}

void Insertdot(string& str, int MaxDecimal) {
    int len = str.length();
    int targ = len - MaxDecimal;
    string newstr = "";
    if (targ > 0) {
        newstr = str.substr(0, targ);
        newstr += '.';
        newstr += str.substr(targ);
    } else {
        newstr = "0.";
        newstr.append(-targ, '0');
        newstr += str;
    }
    str = newstr;
    while (str.back() == '0') str.pop_back();
    if (str.back() == '.') str.pop_back();
}

string Add(const string& a, const string& b) {
    int sign = 1;
    string A = a;
    string B = b;
    if (Isnegative(A) && Isnegative(B)) {
        sign = -1;
        A = A.substr(1);
        B = B.substr(1);
    }
    else if (Isnegative(A) && !Isnegative(B)) return Sub(B, A.substr(1));
    else if (!Isnegative(A) && Isnegative(B)) return Sub(A, B.substr(1));
    bool Decimal = false;
    int MaxDecimal = 0;
    if (A.find('.') != string::npos || B.find('.') != string::npos) {
        Decimal = true;
        MaxDecimal = Processingdot(A, B);
    }
    DeletezeroinHead(A);
    DeletezeroinHead(B);
    if (A.length() < B.length()) {
        swap(A, B);
    }
    int n1 = A.length(), n2 = B.length();
    string rs = "";
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    while (B.length() < n1) {
        B += '0';
    }
    int save = 0;
    int numA, numB;
    for (int i = 0; i < n1; i++) {
        numA = A[i] - '0';
        numB = B[i] - '0';
        int sum = numA + numB + save;
        rs += (sum % 10) + '0';
        save = sum / 10;
    }
    if (save != 0) {
        rs += save + '0';
    }
    int i = rs.length() - 1;
    while (i > 0 && rs[i] == '0') i--;
    rs = rs.substr(0, i + 1);
    reverse(rs.begin(), rs.end());
    if (Decimal) {
        Insertdot(rs, MaxDecimal);
    }
    if (sign == -1 && !(rs.length() == 1 && rs[0] == '0')) {
        rs = "-" + rs;
    }
    return rs;
}

string Sub(const string& a, const string& b) {
    int sign = 1;
    string A = a;
    string B = b;
    if (!Isnegative(A) && Isnegative(B)) return Add(A, B.substr(1));
    else if (Isnegative(A) && !Isnegative(B)) {
        string temp = "-" + b;
        return Add(A, temp);
    }
    else if (Isnegative(A) && Isnegative(B)) return Sub(B.substr(1), A.substr(1));
    bool Decimal = false;
    int MaxDecimal = 0;
    if (A.find('.') != string::npos || B.find('.') != string::npos) {
        Decimal = true;
        MaxDecimal = Processingdot(A, B);
    }
    DeletezeroinHead(A);
    DeletezeroinHead(B);
    if (Cmpstr(A, B) < 0) {
        swap(A, B);
        sign = -1;
    }
    int n1 = A.length(), n2 = B.length(), n = 0;
    string rs;
    Reverse(A);
    Reverse(B);
    B.append(n1 - n2, '0');
    int save = 0;
    int numA, numB;
    for (int i = 0; i < n1; i++) {
        numA = A[i] - '0';
        numB = B[i] - '0';
        int sub = numA - numB - save;
        if (sub < 0) {
            save = 1;
            rs += (sub + 10) + '0';
        }
        else {
            rs += sub + '0';
            save = 0;
        }
    }
    int i = rs.length() - 1;
    while (i > 0 && rs[i] == '0') i--;
    rs = rs.substr(0, i + 1);
    Reverse(rs);
    if (Decimal) {
        Insertdot(rs, MaxDecimal);
    }
    if (sign == -1 && !(rs.length() == 1 && rs[0] == '0')) {
        rs = "-" + rs;
    }

    return rs;
}

string Mul(const string& a, const string& b) {
    int sign = 1;
    string A = a;
    string B = b;
    if (Isnegative(A) && Isnegative(B)) {
        A = A.substr(1);
        B = B.substr(1);
    }
    else if (Isnegative(A) && !Isnegative(B)) {
        sign = -1;
        A = A.substr(1);
    }
    else if (!Isnegative(A) && Isnegative(B)) {
        sign = -1;
        B = B.substr(1);
    }
    bool Decimal = false;
    int SumDecimal = DecimalLength(A) + DecimalLength(B);
    if (A.find('.') != string::npos || B.find('.') != string::npos) {
        Decimal = true;
        if (A.find('.') != string::npos) A.erase(remove(A.begin(), A.end(), '.'), A.end());
        if (B.find('.') != string::npos) B.erase(remove(B.begin(), B.end(), '.'), B.end());
    }
    DeletezeroinHead(A);
    DeletezeroinHead(B);
    if (A.length() < B.length()) {
        swap(A, B);
    }
    int n1 = A.length(), n2 = B.length();
    string rs;
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    rs.append(n1 + n2, '0');
    int save = 0;
    int numA, numB, numC;
    int i,j;
    for (i = 0; i < n2; i++) {
        save = 0;
        numB = B[i] - '0';
        for (j = 0; j < n1; j++) {
            numA = A[j] - '0';
            numC = rs[i + j] - '0';
            int mul = numA * numB + numC + save;
            rs[i + j] = (mul % 10) + '0';
            save = mul / 10;
        }
        if (save != 0) rs[i + j] = save + '0';
    }
    int k = rs.length() - 1;
    while (k > 0 && rs[k] == '0') k--;
    rs = rs.substr(0, k+1);
    reverse(rs.begin(), rs.end());
    if (Decimal) {
        Insertdot(rs, SumDecimal);
    }
    if (sign == -1 && !(rs.length() == 1 && rs[0] == '0')) {
        rs = "-" + rs;
    }
    return rs;
}

string Div(const string& a, const string& b) {
    int sign = 1;
    string A= a;
    string B= b;
    if (Isnegative(A) && Isnegative(B)) {
        A = A.substr(1);
        B = B.substr(1);
    } else if (Isnegative(A) && !Isnegative(B)) {
        sign = -1;
        A = A.substr(1);
    } else if (!Isnegative(A) && Isnegative(B)) {
        sign = -1;
        B = B.substr(1);
    }
    int DecimalA = DecimalLength(A), DecimalB = DecimalLength(B);
    if (A.find('.') != string::npos || B.find('.') != string::npos) {
        if (A.find('.') != string::npos) A.erase(remove(A.begin(), A.end(), '.'), A.end());
        if (B.find('.') != string::npos) B.erase(remove(B.begin(), B.end(), '.'), B.end());
    }
    int extraZeros = 5 + DecimalB - DecimalA;
    if (extraZeros < 0) extraZeros = 0;
    A.append(extraZeros, '0');
    DeletezeroinHead(A);
    DeletezeroinHead(B);
    if (Cmpstr(B, "0") == 0) return "NaN";
    string rs;
    string temp;
    for (size_t i = 0; i < A.length(); i++) {
        temp += A[i];
        DeletezeroinHead(temp);
        if (Cmpstr(temp, B) < 0) {
            rs += '0';
        } else {
            char mul = Isdivisible(temp, B);
            rs += mul;
            temp = Sub(temp, Mul(B, string(1, mul)));
        }
    }
    DeletezeroinHead(rs);
    DeletezeroinHead(temp);
    Insertdot(rs, 5);
    if (sign == -1 && !(rs.length() == 1 && rs[0] == '0')) {
        rs = "-" + rs;
    }
    return rs;
}

bool Isdigit(string& str) {
    if (str.empty()) return false;
    int i = 0;
    bool hasDot = false;
    if (str[0] == '-') {
        if (str.length() == 1) return false;
        i = 1;
    }
    for (; i < str.length(); i++) {
        if (str[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        }
        else if (str[i] < '0' || str[i] > '9') return false;
    }
    return true;
}

bool IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int Prioritize(string& str) {
    if (str == "+" || str == "-") return 1;
    if (str == "*" || str == "/") return 2;
    return 0;
}

string Strprocessingspace(const string& str) {
    string rs;
    string temp;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != ' ') temp += str[i];
    }
    for (int i=0; i<temp.length(); i++) {
        if(IsOperator(temp[i]) && temp[i-1]!='(') {
            rs += " ";
            rs += temp[i];
            rs += " ";
        }
        else if (temp[i] == '(') {
            rs += temp[i];
            rs += " ";
        }
        else if (temp[i] == ')') {
            rs += " ";
            rs += temp[i];
        }
        else rs += temp[i];
    }
    return rs;
}

string InfixToPostfix(const string& a) {
    stack<string> S;
    string str = Strprocessingspace(a);
    string rs = "";
    string temp;
    stringstream ss(str);
    while (ss >> temp) {
        if (Isdigit(temp)) {
            rs += temp + " ";
        } else if (temp == "(") {
            S.push(temp);
        } else if (temp == ")") {
            while (!S.empty() && S.top() != "(") {
                rs += S.top() + " ";
                S.pop();
            }
            S.pop();
        } else {
            while (!S.empty() && Prioritize(temp) <= Prioritize(S.top()) && S.top() != "(") {
                rs += S.top() + " ";
                S.pop();
            }
            S.push(temp);
        }
    }
    while (!S.empty()) {
        rs += S.top() + " ";
        S.pop();
    }
    return rs;
}

string EvaluatePostfix(const string& a) {
    stack<string> S;
    string str = InfixToPostfix(a);
    stringstream ss(str);
    string temp;
    while (ss >> temp) {
        if (Isdigit(temp)) {
            S.push(temp);
        } else {
            string Num2 = S.top();
            S.pop();
            string Num1 = S.top();
            S.pop();
            if (temp == "+") S.push(Add(Num1, Num2));
            else if (temp == "-") S.push(Sub(Num1, Num2));
            else if (temp == "*") S.push(Mul(Num1, Num2));
            else if (temp == "/") {
                DeletezeroinHead(Num2);
                if (Num2 == "0") return "Division by zero";
                S.push(Div(Num1, Num2));
            }
        }
    }
    return S.top();
}

bool IsValidExpression(const string& str) {
    string s = Strprocessingspace(str);
    istringstream ss(s);
    string token, prevToken;
    int paren = 0;
    while (ss >> token) {
        if (token == "(") {
            paren++;
        } else if (token == ")") {
            if (--paren < 0) return false;
        } else if (Isdigit(token)) {
            if (Isdigit(prevToken)) return false;
        } else if (IsOperator(token[0])) {
            if (prevToken.empty() || (IsOperator(prevToken[0])&&!Isdigit(prevToken))) return false;
        } else {
            return false;
        }
        prevToken = token;
    }
    if (IsOperator(prevToken[0])&&!Isdigit(prevToken)) return false;
    if (paren != 0) return false;
    return true;
}