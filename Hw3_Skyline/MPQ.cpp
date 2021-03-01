#include <string>
#include "MPQ.h"
#include <iostream>
using namespace std;


MPQ::MPQ(int size=0)//constructor which takes size parameters for heap vector and location vector
	: heap( size + 1 ), location(size + 1), currentSize(0){}


MPQ::~MPQ(){

}


bool MPQ::isEmpty(){//look if the current size is 0
	if(currentSize==0){
		return true;
	}
	return false;
}


int MPQ::GetMax(){//returns the first index value of the heaplist 
	int num;
	if(isEmpty()==true){
		return 0;
	}
	else{
		num=heap[ 1 ].value;
	}
	return num;
}




void  MPQ::insert(int value,int label){//insert the element to the heaplist

	
	int hole = ++currentSize;

	for( ; hole > 1 && value > heap[ hole -1].value; hole-- ){
		heap[ hole ].label = heap[ hole-1].label;
		heap[ hole ].value = heap[ hole-1].value;
		 location[hole] = heap[hole-1].label;
	}
	heap[hole].label = label;
	heap[hole].value = value;
	location[hole] = label;
}

int MPQ::find_index(int label){//find the index of the heaplist element from the location vector

	int i=0;
	while(label!=location[i]){
		i++;
	}
	return i;

}




int  MPQ::element_delete(int label){//delete element and change the location index and call percolateDown for sort
	
	int i=find_index(label);
	int value2=heap[i].value;
	if(heap[i].value == heap[ currentSize ].value && heap[i].label == heap[currentSize].label){
	heap[i].value=0;
	heap[i].label=0;
	currentSize--;

	return value2;
	}
	heap[i].value = heap[ currentSize ].value;
	heap[i].label = heap[currentSize].label;
	currentSize--;
	percolateDown(i);
	location[currentSize+1] = -1;

	return value2;
}

void MPQ:: percolateDown( int hole ){//take a index which the element is in and percolateDown it and sort
  
        int child;
        int tmpValue = heap[ hole ].value; 
        int tmpLabel = heap[hole].label;
       
        
    for( ; hole+1 <= currentSize; hole = child ){
        
        child = hole+1;
        
        if( child != currentSize && heap[ child + 1 ].value > heap[ child ].value )
            child++;
        
        if( heap[ child ].value > tmpValue ){
            
            heap[ hole ].value = heap[ child ].value; // swap hole and min child
            heap[hole].label = heap[child].label;
            location[hole] =heap[hole].label;
        }
        else
            break;
    }
    heap[ hole ].value = tmpValue; // place tmp in its final position
    heap[hole].label = tmpLabel;
    location[hole] =heap[hole].label;
}






