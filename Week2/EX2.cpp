#include <iostream>
using namespace std;
int LinearSearchWithsentinel(int a[], int n,int k) {
    int last = a[n-1];
    a[n-1] = k;
    int i=0;
    while(a[i]!= k) i++;
    a[n-1] = last;
    if(i<n-1||a[n-1]==k) return i;
    else return -1;
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
    int k;
    cout << "Enter Key: ";
    cin >> k;
    if(LinearSearchWithsentinel(a,n,k)!=-1) cout << "Key found at index " << LinearSearchWithsentinel(a,n,k);
    else cout << "Key not found";
}
