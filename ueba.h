#include<stdlib.h>



/*
 *
 * UEBA stands for Ultra Efficient Boolean Array
 * Instead of using an entire byte to represent a boolean an UEBA uses only one bit for each boolean variable
 * Its read/write times are slower but it only uses 1 eighth the memory of a boolean array
 *
 *
 *
 *

 * */
struct UEBA{
	unsigned char* array;
};

int checkUEBA(struct UEBA* arr,unsigned int index);
void setUEBA(struct UEBA* arr,unsigned int index,int value);
void freeUEBA(struct UEBA* ueba);
struct UEBA* createUEBA(unsigned int bits);
struct UEBA* copyUEBA(struct UEBA* ueba,unsigned int size);
void printBytesUEBA(struct UEBA* ueba,unsigned int bytes);
struct UEBA* fromBlobUEBA(void* BLOB,unsigned int bytes);
void printBitsUEBA(struct UEBA* ueba,unsigned int bytes);


int checkUEBA(struct UEBA* arr,unsigned int index)
{
	unsigned char shift = (index%8);
	unsigned char byte = arr->
		array[index/8];
	unsigned char bit = 128>>shift;

	unsigned char result = bit&(byte);

	switch (result){
	
		case 0:
			return 0;
		default:
			return 1;
	}
}
void setUEBA(struct UEBA* arr,unsigned int index,int value)
{
	unsigned char shift = index%8;
	unsigned char* byte = arr->array+index/8;
	unsigned char bit = 128>>(shift);

	unsigned char result; 
	if(value !=0 ){	
		result = bit|(*byte);
	}
	else{
		result = (~bit)&(*byte);

	}


	(*byte) = result;


}
void freeUEBA(struct UEBA* ueba)
{
	free(ueba->array);
	free(ueba);
}
struct UEBA* createUEBA(unsigned int bits)
{
	struct UEBA* ueba = malloc(sizeof(struct UEBA));
	ueba->array = malloc(bits/8+1);
	return ueba;
}

struct UEBA* copyUEBA(struct UEBA* ueba,unsigned int size)
{
	struct UEBA* new_ueba = createUEBA(size);
	for(unsigned int i=0; i<size; i++){
		setUEBA(new_ueba,i,checkUEBA(ueba,i));
	}
	return new_ueba;



}
// BLOB = Binary Large OBject
// Basically can be any pointer 
struct UEBA* fromBlobUEBA(void* BLOB,unsigned int bytes)
{
	struct UEBA* ueba = malloc(sizeof(struct UEBA));
	ueba->array = BLOB;
	return ueba;

		
}


//prints binary but with spaces every eight bits
void printBytesUEBA(struct UEBA* ueba,unsigned int bytes)
{
	for(unsigned int i= 0;  i<bytes*8; i++){
	
		if(i%8==0&&i!=0){
			printf(" ");
		}
		printf("%u",checkUEBA(ueba,i));
	}
}

void printBitsUEBA(struct UEBA* ueba,unsigned int bytes)
{
	for(unsigned int i= 0;  i<bytes*8; i++){
	
		printf("%u",checkUEBA(ueba,i));
	}
}

