#include <iostream>
using namespace std;
int Linearsearch(int a[],int n,int k) {
    for(int i=0;i<n;i++) {
        if(a[i]==k) return i;
    }
    return -1;
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
    if(Linearsearch(a,n,k)!=-1) cout << "Key found at index " << Linearsearch(a,n,k);
    else cout << "Key not found at index ";
}
