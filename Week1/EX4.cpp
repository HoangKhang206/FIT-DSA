#include <iostream>
using namespace std;
//Towers of Hanoi puzzle
int towersofHanoi(int n, char from, char to, char aux) {
    if(n==1) {
        cout << "Move from " << from << " to " << to << endl;
        return 1;
    }
    else {
        int count =0;
        count += towersofHanoi(n-1, from, aux, to);
        cout << "Move from " << from << " to " << to << endl;
        count++;
        count += towersofHanoi(n-1, aux, to, from);
        return count;
    }
}
int main()
{
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;
    cout << towersofHanoi(n, 'A', 'B', 'C');
}
