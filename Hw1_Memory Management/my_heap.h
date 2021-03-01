#ifndef My_heap_H
#define My_heap_H


struct memory_block{
memory_block* right; // node to the right
memory_block* left; // node to the left
bool used; // if this memory block is reserved or not
int size; // the number of bytes reserved in Img_heap
int starting_address; // the starting address in Img_heap
// of the memory reserved by this block
};


#define MAX_CAPACITY 512
class My_heap{
private:
memory_block* heap_begin;
memory_block* blk;
int used_bytes;


public:
My_heap();//constructor
~My_heap();//destructor
memory_block* bump_allocate(int num_bytes);//add new memory_blocks to the my_heap nodes. This function ad new nodes at the tail of the heap
memory_block* first_fit_allocate(int num_bytes);/*this function will search, starting from the beginning of My_heap  for the first memory_block that is used == false and
that can fit at least num_bytes bytes.*/
memory_block* best_fit_allocate(int num_bytes);/*this function will search My_heap for a free block that can fit the required bytes but it will use the block that will lead to the smallest amount
of wasted memory*/
memory_block* first_fit_split_allocate(int num_bytes);/* it will split free blocks into smaller blocks and allocate the exact amount of memory it
requires*/
void deallocate(memory_block* block_address);//makes memory block used info to false and decrese (used bytes-block_address->size)
void print_heap();//Prints statistics about the heap and the information about all the blocks in the heap
float get_fragmantation();//This function will calculate the fragmentation percentage
};
#endif
