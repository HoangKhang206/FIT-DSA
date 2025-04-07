#include <iostream>
#include <fstream>
#include "Sort.h"
#include <cstring>
#include <chrono>
using namespace std;
using namespace std::chrono;
int main(int argc,char* argv[])
{
    char* Optionsort= new char[100];
    char* Input= new char[100];
    char* Output= new char[100];
    for(int i=0;i<argc;i++) {
        if(strcmp(argv[i],"-a")==0) strcpy(Optionsort,argv[i+1]);
        else if(strcmp(argv[i],"-i")==0) strcpy(Input,argv[i+1]);
        else if(strcmp(argv[i],"-o")==0) strcpy(Output,argv[i+1]);
    }
    cout << "Input: " << Input << endl;
    cout << "Optionsort: " << Optionsort << endl;
    cout << "Output: " << Output << endl;
    ifstream infile;
    infile.open(Input,ios::in);
    int n;
    infile>>n;
    int arr[n];
    for(int i=0;i<n;i++) infile>>arr[i];
    infile.close();
    auto start = high_resolution_clock::now();
    if(strcmp(Optionsort,"selection-sort")==0) Selection_Sort(arr,n);
    if(strcmp(Optionsort,"insertion-sort")==0) Insertion_Sort(arr,n);
    if(strcmp(Optionsort,"bubble-sort")==0) Bubble_Sort(arr,n);
    if(strcmp(Optionsort,"shaker-sort")==0) Shaker_Sort(arr,n);
    if(strcmp(Optionsort,"shell-sort")==0) Shell_Sort(arr,n);
    if(strcmp(Optionsort,"heap-sort")==0) Heap_Sort(arr,n);
    if(strcmp(Optionsort,"merge-sort")==0) Merge_Sort(arr,0,n-1);
    if(strcmp(Optionsort,"quick-sort")==0) Quick_Sort(arr,0,n-1);
    if(strcmp(Optionsort,"counting-sort")==0) Counting_Sort(arr,n);
    if(strcmp(Optionsort,"radix-sort")==0) Radix_Sort(arr,n);
    if(strcmp(Optionsort,"flash-sort")==0) Flash_Sort(arr,n);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    ofstream outfile;
    outfile.open(Output,ios::out);
    for(int i=0;i<n;i++) {
        outfile<<arr[i]<<" ";
    }
    outfile.close();
    if(CheckSort(arr,n)==true) cout << "Sorting Successful" << endl;
    cout << "Thời gian chạy thuật toán: " << duration.count() << " microseconds <==> " << duration.count()/1000000<<" seconds.";
}
