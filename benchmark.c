#include<stdio.h>
#include<stdlib.h>

#include "ueba.h"

//for benchmarking purposes
#include<time.h>
#include<stdbool.h>
#include<malloc.h>

int main(){

	unsigned int testSize = 100000000*10;


	struct UEBA* ueba=createUEBA(testSize);
	clock_t start_time = clock();
	for(int i=0; i<testSize; i++){
		setUEBA(ueba,i,1);
	}
	clock_t end_time = clock();
	printf("UEBA write time: %u\n",end_time-start_time);

	unsigned int uebaWriteTime = end_time-start_time;



	bool* arr = malloc(sizeof(bool)*testSize);	
	start_time = clock();
	for(int i=0; i<testSize; i++){
		arr[i]=true;
	}
	end_time = clock();
	printf("bool array write time %u\n",end_time-start_time);
	unsigned int arrWriteTime = end_time-start_time;




	double writeRatio = (1.0*uebaWriteTime)/(1.0*arrWriteTime);










	//testing read time;	
	start_time = clock();
	for(int i=0; i<testSize; i++){
		checkUEBA(ueba,i);
	}
	end_time = clock();
	printf("UEBA read time: %u\n",end_time-start_time);

	unsigned int uebaReadTime = end_time-start_time;


	start_time = clock();
	for(int i=0; i<testSize; i++){
		arr[i];
	}
	end_time = clock();
	printf("bool array read time %u\n",end_time-start_time);


	unsigned int arrReadTime = end_time-start_time;
	double readRatio = (1.0*uebaReadTime)/(1.0*arrReadTime);



	//testing memory efficencytime;	


	unsigned int uebaStorage = 0;
	uebaStorage+=malloc_usable_size(ueba->array);	
	printf("UEBA storage for %u items: %u bytes \n",testSize,uebaStorage);


	unsigned int arrStorage = 0;

	arrStorage+=malloc_usable_size(arr);
	printf("array storage for %u items: %u bytes \n",testSize,arrStorage);











	double memoryRatio = (1.0*uebaStorage)/(1.0*arrStorage);


	printf("Summary:\n");


	printf("UEBA has %lfX write time compared to a bool array\n",writeRatio );
	printf("UEBA has %lfX read time compared to a bool array\n",readRatio );
	printf("UEBA has %lfX memory usage to a bool array\n",memoryRatio );
		


	//stored the const char* hello as a blob and prints in binary	
		struct UEBA* hello_ueba = fromBlobUEBA("hello",5*sizeof(char));
		for(int i=0; i<5*8; i++){
			printf("%u",checkUEBA(hello_ueba,i));
		}
		printf("\n");
		printBytesUEBA(hello_ueba,5);




		//prints numbers in binary as a blob
		int pX []= {0,1,2,3,255}; 
		struct UEBA* x_UEBA = fromBlobUEBA(pX,5*sizeof(int));
		printf("\n");
		printBytesUEBA(x_UEBA,5*sizeof(int));
		printf("\n");
		printBitsUEBA(x_UEBA,5*sizeof(int));




		


		

}
