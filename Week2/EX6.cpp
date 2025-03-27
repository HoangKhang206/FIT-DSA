#include <iostream>
using namespace std;
bool Sumtarget(int a[], int left,int right, int sum) {
    if (left < right) {
        if (a[left] + a[right] == sum) return true;
        if (a[left] + a[right] < sum) return Sumtarget(a, left+1, right, sum);
        else return Sumtarget(a, left, right-1, sum);
    }return false;
}
int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    int a[n];
    for(int i=0;i<n;i++) {
        cin >> a[i];
    }
    int sum;
    cout << "Enter Sum: ";
    cin >> sum;
    if (Sumtarget(a, 0, n-1, sum)) cout << "YES" << endl;
    else cout << "NO" << endl;
}
