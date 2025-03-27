#include <iostream>
using namespace std;
int subarray(int a[],int n, int sum) {
    int S=0;
    int l=0;
    int r=0;
    int cntmin=INT_MAX;
    while(r<=n) {
        if(S<=sum) S+=a[r++];
        else {
            S-=a[l++];
        }
        if(S==sum) {
            cntmin=min(cntmin,r-l);
        }
    }
    return cntmin;
}
int main()
{
    int n,sum;
    cout<<"Enter the number of elements: ";
    cin>>n;
    int a[n];
    cout<<"Enter the elements: ";
    for(int i=0;i<n;i++) {
        cin>>a[i];
    }
    cout<<"Enter the sum: ";
    cin>>sum;
    cout<<subarray(a,n,sum);
}
