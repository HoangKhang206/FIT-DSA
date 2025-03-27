#include <iostream>
using namespace std;
int findpivot(int a[], int left, int right) {
    int mid = left+(right-left)/ 2;
    while (mid!=right&&mid!=left) {
        if (a[mid]>a[right]) left = mid+1;
        else  right = mid;
        mid = (left+right)/2;
    }
    if (a[mid]<a[right]) return a[mid];
    else return a[right];
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
    int left = 0, right = n-1;
    int pivot = findpivot(a,left,right);
    cout << pivot << endl;
}
