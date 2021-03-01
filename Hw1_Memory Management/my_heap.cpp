#include <iostream>
#include <string>
#include"my_heap.h"
using namespace std;

My_heap::My_heap(){//constructor of My_heap class
	heap_begin=NULL;
	blk=NULL;
	used_bytes=0;

} 

memory_block * My_heap::bump_allocate(int num_bytes){//add new memory_blocks to the my_heap nodes. This function ad new nodes at the tail of the heap
	if(heap_begin==NULL){//if there is no memory blocks
		memory_block*tmp= new memory_block;
		tmp->left=NULL;
		tmp->right=NULL;
		tmp->size=num_bytes;
		tmp->used=true;
		tmp->starting_address=0;
		used_bytes=num_bytes+used_bytes;
		heap_begin=tmp;
		blk=tmp;
		return blk;
	}
	else{
		if(used_bytes+num_bytes<=MAX_CAPACITY){// add ne memory blocks
			memory_block*tmp= new memory_block;
			tmp->size=num_bytes;
			tmp->used=true;
			tmp->starting_address=blk->starting_address+blk->size;
			used_bytes=num_bytes+used_bytes;
			tmp->left=blk;
			blk->right=tmp;
			tmp->right=NULL;
			blk=tmp;
			return blk;
		}
		return nullptr;
	}
}

void My_heap::deallocate(memory_block* to_delete){//makes memory block used info to false  and decrese (used bytes-block_address->size)
	if(heap_begin==NULL){
		return;
	}

	if(to_delete->right==NULL && to_delete->left==NULL){//check to delete right and left is null
		to_delete->used = false;
		used_bytes=used_bytes-to_delete->size;
		return;
	}
	if(to_delete->left->used==true && to_delete->right==NULL){//check to delete left->used info is true and right is null
		to_delete->used = false;
		used_bytes=used_bytes-to_delete->size;
		return;
	}
	if(to_delete->left->used==false && to_delete->right==NULL){//check to delete left->used info is false and right is null
		memory_block*tmp;
		tmp=to_delete;
		used_bytes=used_bytes-to_delete->size;
		to_delete->left->size = to_delete->left->size+to_delete->size;
		blk=tmp->left;
		blk->right=NULL;
		delete to_delete;
		return;
	}
	if(to_delete->left->used==false && to_delete->right->used==true){//check to delete left->used info is false and left->used info is true
		memory_block*tmp;
		memory_block*tmp2;
		used_bytes=used_bytes-to_delete->size;
		tmp=to_delete->right;
		tmp2=to_delete->left;
		tmp2->size = tmp2->size+to_delete->size;
		tmp2->right=tmp;
		tmp->left=tmp2;
		delete to_delete;
		return;
	}
	if(to_delete->left->used==true && to_delete->right->used==false){//check to delete left->used info is true and left->used info is false
		if(blk==to_delete->right){
			memory_block*tmp=to_delete->right;
			used_bytes=used_bytes-to_delete->size;
			to_delete->size=tmp->size + to_delete->size;
			to_delete->right=NULL;
			blk=to_delete;
			delete tmp;
			return;
		}
		else{
			memory_block*tmp=to_delete->right->right;
			used_bytes=used_bytes-to_delete->size;
			to_delete->size=to_delete->right->size + to_delete->size;
			delete to_delete->right;
			to_delete->right=tmp;
			tmp->left=to_delete;
			return;
		}
	}
	if(to_delete->left->used==false && to_delete->right->used==false){//check to delete left->used info is false and left->used info is false
		if(blk==to_delete->right){
			memory_block*tmp=to_delete->right;
			memory_block*tmp2=to_delete->left;
			used_bytes=used_bytes-to_delete->size;
			tmp2->size=tmp2->size + to_delete->size + tmp->size;
			delete tmp;
			delete to_delete;
			tmp2->right=NULL;
			blk=tmp2;
			return;
		}
		else{
			memory_block*tmp=to_delete->right;
			memory_block*tmp2=to_delete->left;
			used_bytes=used_bytes-to_delete->size;
			tmp2->size=tmp2->size + to_delete->size + tmp->size;
			tmp2->right=tmp->right;
			tmp->right->left=tmp2;
			delete tmp;
			delete to_delete;
			return;
		}
	}
	used_bytes=used_bytes-to_delete->size;////to delete left->used info is true and left->used info is true
	to_delete->used=false;
	return;
}

float My_heap::get_fragmantation(){/*This function will calculate the fragmentation percentage of your heap and will return that value
as a float. We can calculate the fragmentation of a heap using this equation:*/

	if(heap_begin==NULL){
		return 0;
	}

	float fragmentation;
	float free_memory=MAX_CAPACITY-used_bytes;
	float biggest_free_block=0;
	memory_block*tmp;
	tmp=heap_begin;


	while(tmp!=NULL){
		if(tmp->size>biggest_free_block && tmp->used==false){
			biggest_free_block=tmp->size;
		}
		tmp=tmp->right;
	}
	if(biggest_free_block<MAX_CAPACITY-(blk->starting_address+blk->size)){
		biggest_free_block=MAX_CAPACITY-(blk->starting_address+blk->size);
	}

	fragmentation = ((free_memory - biggest_free_block)/free_memory) * 100;

	return fragmentation;
}

void  My_heap::print_heap(){/*Prints statistics about the heap and the information about all the blocks in the heap*/


	int curently_used_memory=used_bytes;
	memory_block*tmp=heap_begin;
	int Total_memory_blocks=0;
	int Total_free_memory_blocks=0;
	int count=0;
	string space="  ";
	while(tmp!=NULL){
		if(tmp->used==false){//find Total_memory_blocks and Total_free_memory_blocks
			Total_free_memory_blocks++;

		}
		Total_memory_blocks++;
		tmp=tmp->right;
	}//Prints statistics about the heap
	cout<<"Maximum capacity of heap: "<<MAX_CAPACITY<<"B"<<endl;
	cout<<"Currently used memory (B): "<<curently_used_memory<<endl;
	cout<<"Total memory blocks: "<<Total_memory_blocks<<endl;
	cout<<"Total used memory blocks: "<<Total_memory_blocks-Total_free_memory_blocks<<endl;
	cout<<"Total free memory blocks: "<<Total_free_memory_blocks<<endl;
	cout<<"Fragmentation: "<<get_fragmantation()<<"%"<<endl;
	if(heap_begin==NULL){
		cout<<"------------------------------"<<endl;
		cout<<"------------------------------"<<endl;
		cout<<"------------------------------"<<endl;
		return;
	}
	tmp=heap_begin;
	string check;
	cout<<"------------------------------"<<endl;
	while(tmp!=NULL){
		if(tmp->used==true){
			check="True";
		}
		else{
			check="False";
		}
		if(check=="False"){
			space=" ";
		}
		else{
			space="  ";
		}
		cout<<"Block "<<count<<"    used: "<<check<<space<<"size (B): "<<tmp->size<<"	Starting address: "<<"0x"<<hex<<tmp->starting_address<<dec<<endl;/*print information about blocks in the heap*/
		tmp=tmp->right;
		count++;
	}

	cout<<"------------------------------"<<endl;
	cout<<"------------------------------"<<endl;
	return;
}

My_heap::~My_heap(){//destructor to deallocate all the memory of the linked list 
	memory_block*tmp=blk;
	while(tmp!=NULL){
		tmp=blk->left;
		delete blk;
		blk=tmp;
	}
	cout<<"At destruction, the heap had a memory leak of "<<used_bytes<<" bytes"<<endl;//print the memory leakage in the heap
}

memory_block* My_heap::first_fit_allocate(int num_bytes){/*this function will search, starting from the beginning of My_heap  for the first memory_block that is used == false and
that can fit at least num_bytes bytes.*/

	int total=0;
	memory_block*tmp=heap_begin;
	while(tmp!=NULL){
		if(tmp->used==false && tmp->size >= num_bytes){
			tmp->used=true;
			used_bytes=used_bytes+tmp->size;
			return tmp;
		}
		total=total+tmp->size;
		tmp=tmp->right;
	}
	if(MAX_CAPACITY-total<num_bytes){
		return nullptr;
	}
	else{
		tmp=bump_allocate(num_bytes);
		return tmp;
	}
}
memory_block* My_heap::best_fit_allocate(int num_bytes){/*this function will search My_heap for a free block that can fit the required bytes but it will use the block that will lead to the smallest amount
of wasted memory*/
	memory_block*tmp=heap_begin;
	int total=0;
	int num=-1;
	bool flag=true;
	while(tmp!=NULL){
		if(tmp->used==false && tmp->size >= num_bytes){
			if(flag){
				num=tmp->size;
			}
			if(!flag && tmp->size-num_bytes<num-num_bytes && tmp->size-num_bytes>=0){//chose the best fit memory block
				num=tmp->size;
			}
			flag=false;
		}
		if(tmp->used==true){
			total=total+tmp->size;
		}
		tmp=tmp->right;
	}
	if(num!=-1){
		tmp=heap_begin;
		while(tmp->size!=num){//this loop find the best fit memory block and point it with tmp
			tmp=tmp->right;
		}
		tmp->used=true;
		used_bytes=used_bytes+tmp->size;
		return tmp;
	}
	else{
		if(MAX_CAPACITY-total<num_bytes){//if max_capacity is full
			return nullptr;
		}
		else{
			tmp=bump_allocate(num_bytes);//if there is no suitable memory blocks and make a new one
			return tmp;
		}
	}
}

memory_block* My_heap::first_fit_split_allocate(int num_bytes){/* it will split free blocks into smaller blocks and allocate the exact amount of memory it
requires*/
	int total=0;
	memory_block*tmp=heap_begin;
	while(tmp!=NULL){
		if(tmp->size==num_bytes && tmp->used==false){//check tmp->size is same as num_bytes and tmp->used==false
			tmp->used=true;
			used_bytes=used_bytes+tmp->size;
			return tmp;
		}
		if(tmp->size>num_bytes && tmp->used==false && tmp->right!=NULL){//check tmp->size is bigger than num_bytes and tmp->used==false and tmp->right!=NULL
			memory_block*tmp2;
			memory_block*tmp3= new memory_block;
			tmp2=tmp->right;
			tmp3->size=tmp->size-num_bytes;
			tmp->size=num_bytes;
			tmp->used=true;
			tmp3->used=false;
			tmp3->starting_address=tmp->starting_address+num_bytes;
			tmp->right=tmp3;
			tmp3->left=tmp;
			tmp3->right=tmp2;
			tmp2->left=tmp3;
			used_bytes=used_bytes+tmp->size;
			return tmp;
		}
		if(tmp->size>num_bytes && tmp->used==false && tmp->right==NULL){//check tmp->size is bigger than num_bytes and tmp->used==false and tmp->right==NULL
			memory_block*tmp3= new memory_block;
			tmp3->size=tmp->size-num_bytes;
			tmp->size=num_bytes;
			tmp->used=true;
			tmp3->used=false;
			tmp3->starting_address=tmp->starting_address+num_bytes;
			tmp->right=tmp3;
			tmp3->left=tmp;
			tmp3->right=NULL;
			blk=tmp3;
			used_bytes=used_bytes+tmp->size;
			return tmp;
		}
		if(tmp->used==true){
			total=total+tmp->size;
		}
		tmp=tmp->right;
	}
	if(MAX_CAPACITY-total<num_bytes){//if max_capacity is full
		return nullptr;
	}
	else{
		tmp=bump_allocate(num_bytes);//if there is no suitable memory blocks and make a new one
		return tmp;
	}
}