#ifndef MPQ_H
#define MPQ_H
#include <vector>
using namespace std;



struct queueObject{
	int value;
	int label;
};


class MPQ
{
public:

	MPQ(int);
	~MPQ();
	bool isEmpty();//look if the current size is 0
	int GetMax();//returns the first index value of the heaplist 
	void insert(int,int);//insert the element to the heaplist
	int MPQ::element_delete(int);//delete element and change the location index and call percolateDown for sort
	int MPQ::find_index(int);//find the index of the heaplist element from the location vector

private:
	int currentSize;//siz of the heap
	vector<queueObject> heap;//class object
	vector<int> location;//location vector
	void percolateDown( int hole );//take a index which the element is in and percolateDown it and sort

}; 
#endif