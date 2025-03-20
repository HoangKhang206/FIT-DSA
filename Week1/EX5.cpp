#include <iostream>
using namespace std;
//Given an array , check whether the array is in sorted order with recursion
bool IsSorted(int a[], int n) {
    if (n == 1) return true;
    if (a[n] < a[n-1]) return false;
    return IsSorted(a, n - 1);
}
int main()
{
    int n;
    cout << "Enter number of arr: ";
    cin >> n;
    int a[n];
    for (int i = 1; i <=n; i++) {
        cout <<"arr["<<i<<"]: ";
        cin >> a[i];
    }
    if (IsSorted(a, n)) cout << "Sorted" << endl;
    else cout << "Not Sorted" << endl;
}
