#ifndef SORT_H
#define SORT_H
#include <iostream>
using namespace std;
extern long long cnt;
void Selection_Sort(int arr[], int n);
void Insertion_Sort(int arr[], int n);
void Bubble_Sort(int arr[], int n);
void Shaker_Sort(int arr[], int n);
void Shell_Sort(int arr[], int n);
void Heapify(int arr[],int n,int i);
void Heap_Sort(int arr[], int n);
void Merge_Sort(int arr[], int left, int right);
int Partition(int arr[],int left,int right);
void Quick_Sort(int arr[], int left, int right);
int Getmax(int arr[],int n);
void Counting_Sort(int arr[], int n);
void CountingSortExp(int arr[],int n,int exp);
void Radix_Sort(int arr[], int n);
void Flash_Sort(int arr[], int n);
void GenerateData(int arr[], int n, int dataType);
bool CheckSort(int arr[], int n);
#endif //SORT_H
