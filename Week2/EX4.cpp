#include <iostream>
using namespace std;
bool check(int a[],int n, int target,int day) {
    int sum=0;
    int count_day=1;
    for(int i=0;i<n;i++) {
        sum+=a[i];
        if(sum>target) {
            count_day++;
            sum=a[i];
        }
    }
    return count_day<=day;
}
int solve(int a[],int n,int day) {
    int Max=0;
    int Min=INT_MIN;
    for(int i=0;i<n;i++) {
        if(a[i]>Min) Min=a[i];
        Max+=a[i];
    }
    while(Min<Max) {
        int mid=(Min+Max)/2;
        if(check(a,n,mid,day)) Max=mid;
        else Min=mid+1;
    }
    return Min;
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
    int day;
    cout << "Enter day number: ";
    cin >> day;
    cout << solve(a,n,day);
}
