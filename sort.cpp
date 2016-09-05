#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include <ctime>
using namespace std;
const int size_of_string = 10000;
int num_string[size_of_string];//-------------------------------
//int run_times = 0;
//Bubble sort
void bubbleSort(int A[], int n){
	bool swapped = true;
	while (swapped){
		swapped=false;
		for(int i=0; i<n-1; i++){
			if(A[i]>A[i+1]){
				swap(A[i],A[i+1]);
				//run_times++;
				swapped=true;
			}
		}
	}
}

//Insertion sort
void insertionSort(int A[], int n){
	int key, i;
	for(int j=1; j<n; j++){
		key=A[j];
		i=j-1;
		while(i>=0 && A[i]>key){
			A[i+1]=A[i];
			//run_times++;
			i=i-1;
		}
		A[i+1]=key;
	}
}
//Quick sort
int partition(int A[], int p, int r){
	int x=A[r];
	int i=p-1;
	for(int j=p; j<r; j++){
		if(A[j]<=x){
			i++;
			swap(A[i],A[j]);
		}
	}
	swap(A[i+1],A[r]);
	return (i+1);
}
void quickSort(int A[], int p, int r){
	if (p>=r) {return;}
	int q=partition(A,p,r);
	quickSort(A,p,q-1);
	quickSort(A,q+1,r);
}
int main(){
	srand(time(0));
	clock_t begin, end;
	double time_spent;

	for(int i=0; i<size_of_string;i++){
		num_string[i]=   (double) rand() / RAND_MAX * 2147483647;
		//num_string[i] = i; // a sorted input
	}
	//swap(num_string[size_of_string/2],num_string[size_of_string]);


	begin = clock();
	bubbleSort(num_string,size_of_string);
	//insertionSort(num_string,size_of_string);
	//quickSort(num_string, 0, size_of_string-1);
	end = clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	cout<<time_spent<<endl;
	//cout<<run_times<<endl;
	return 0;
}


