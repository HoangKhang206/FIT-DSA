#include"Sort.h"

void Selection_Sort(int arr[],int n) {
    for (int i = 0; i < n; i++) {
        int min=i;
        for (int j = i+1; j < n; j++) {
            if(arr[j]<arr[min])
                min=j;
        }
        swap(arr[i],arr[min]);
    }
}

void Insertion_Sort(int arr[],int n) {
    for (int i = 1; i < n; i++) {
        int key=arr[i];
        int j = i-1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}

void Bubble_Sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for(int j=0; j < n-i-1; j++) {
            if(arr[j]>arr[j+1]) swap(arr[j],arr[j+1]);
        }
    }
}

void Shaker_Sort(int arr[], int n) {
    int left=0, right=n-1, k=n-1;
    while(left<right) {
        for(int i=left; i<right; i++) {
            if(arr[i]>arr[i+1]) {
                swap(arr[i],arr[i+1]);
                k=i;
            }
        }
        right=k;
        for(int j=right; j>left;j--) {
            if(arr[j-1]>arr[j]) {
                swap(arr[j-1],arr[j]);
                k=j;
            }
        }
        left=k;
    }
}

void Shell_Sort(int arr[], int n) {
    for(int gap=n/2; gap>0; gap/=2) {
        for(int i = gap; i < n; i++) {
            int temp=arr[i];
            int j;
            for(j = i; j >= gap && arr[j-gap] > temp; j-=gap) {
                arr[j]=arr[j-gap];
            }
            arr[j]=temp;
        }
    }
}

void Heapify(int arr[],int n,int i) {
    int largest=i;
    int l= 2*i+1;
    int r=2*i+2;
    if(l<n && arr[l]>arr[largest])
        largest=l;
    if(r<n && arr[r]>arr[largest])
        largest=r;
    if(largest!=i) {
        swap(arr[i],arr[largest]);
        Heapify(arr,n,largest);
    }
}

void Heap_Sort(int arr[], int n) {
    for(int i=n/2-1;i>=0;i--) {
        Heapify(arr,n,i);
    }
    for(int i=n-1;i>0;i--) {
        swap(arr[0],arr[i]);
        Heapify(arr,i,0);
    }
}

void Merge(int arr[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    int temp[right - left + 1];
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int x = 0; x < k; x++) {
        arr[left + x] = temp[x];
    }
}

void Merge_Sort(int arr[], int left, int right) {
    if(left<right) {
        int mid=left+(right-left)/2;
        Merge_Sort(arr,left,mid);
        Merge_Sort(arr,mid+1,right);
        Merge(arr,left,mid,right);
    }
}

int Partition(int arr[],int left,int right) {
    int pivot = arr[right];
    int i= left-1;
    for(int j=left;j<right;j++) {
        if(arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[right]);
    return i+1;
}

void Quick_Sort(int arr[], int left, int right) {
    if (left < right) {
        int Pi = Partition(arr, left, right);
        Quick_Sort(arr, left, Pi-1);
        Quick_Sort(arr, Pi+1, right);
    }
}

int Getmax(int arr[],int n) {
    int Max=arr[0];
    for (int i = 1; i < n; i++) {
        if(arr[i]>Max)
            Max=arr[i];
    }
    return Max;
}

void Counting_Sort(int arr[], int n) {
    int Max=Getmax(arr,n);
    int count[Max+1];
    for (int i = 0; i <= Max; i++) {
        count[i]=0;
    }
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    int k=0;
    for (int i=0;i<=Max;i++) {
        while(count[i] > 0) {
            arr[k++] = i;
            count[i]--;
        }
    }
}

void CountingSortExp(int arr[],int n,int exp) {
    int output[n];
    int count[10]={0};
    for(int i=0;i<n;i++) {
        count[arr[i]/exp%10]++;
    }
    for(int i=1;i<10;i++) {
        count[i]+=count[i-1];
    }
    for(int i=n-1;i>=0;i--) {
        output[count[arr[i]/exp%10]-1]=arr[i];
        count[arr[i]/exp%10]--;
    }
    for(int i=0;i<n;i++) {
        arr[i]=output[i];
    }
}

void Radix_Sort(int arr[], int n) {
    int Max=Getmax(arr,n);
    for(int exp=1;Max/exp>0;exp*=10) {
        CountingSortExp(arr,n,exp);
    }
}

void Flash_Sort(int arr[], int n) {
    int m = (int)(0.45 * n);
    int temp[m];
    for (int i = 0;i < m; i++) {
        temp[i] = 0;
    }
    int Max = INT_MIN;
    int Min = INT_MAX;
    int MaxIndex = 0;
    for (int i = 0;i < n; i++) {
        if (arr[i] > Max) {
            Max = arr[i];
            MaxIndex = i;
        }
        if (arr[i] < Min) {
            Min = arr[i];
        }
    }
    for (int i = 0;i < n; i++) {
        int k = (int)((double)(arr[i] - Min) * (m - 1) / (Max - Min));
        temp[k]++;
    }
    for (int i = 1;i < m; i++) {
        temp[i] += temp[i - 1];
    }
    swap(arr[MaxIndex], arr[0]);
    int count = 0, i = 0, k = m - 1;
    while (count < n - 1) {
        while (i >= temp[k]) {
            i++;
            k = (int)((double)(m - 1) * (arr[i] - Min) / (Max - Min));
        }
        int flash = arr[i];
        while (i < temp[k]) {
            k = (int)((double)(m - 1) * (flash - Min) / (Max - Min));
            int pos = --temp[k];
            swap(flash, arr[pos]);
            count++;
        }
    }
    for (int i = 1;i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

bool CheckSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}