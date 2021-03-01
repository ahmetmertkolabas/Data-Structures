#ifndef QUADTREE_H
#define QUADTREE_H
#include <string>
using namespace std;
#include<vector> 

struct Node //node struct
{ 
	int x;
	int y;
	string data;
	Node *NW; 
	Node *NE; 
	Node *SW; 
	Node *SE; 
	
	Node(){
	x=0;
	y=0;
	data="";
	NW=NULL;
	NE=NULL;
	SW=NULL;
	SE=NULL;
	
	}
	
	Node(int x_,int y_, string _data,Node *NW_,Node *NE_,Node *SW_,Node *SE_) //node constructor
	{ 
		x=x_;
		y=y_;
		data = _data; 
		NW=NW_;
		NE=NE_;
		SW=SW_;
		SE=SE_;
	} 
}; 


class QuadTree
{ 
private:

	Node* root; 

public: 
	QuadTree();//default constructor
	~QuadTree();//destructar
	void insert(int,int,string);//insert the node to the tree
	void printhelper(Node*);//print the tree
	void print();//calls the printhelper function
	string compare(Node*,Node*);//compare two nodes x and y and decide where must be the next node and return string
	Node* QuadTree::SON(Node*,string);//this function take a string parameter of direction(se,sw,ne,nw) and return nodes->position
	void QuadTreeHelper(Node*);//this function delete all nodes at the tree by a recursive action
	void QuadTree::find(int,int,int);//it cout the inside_circle_cities elements and cities_visit elements
	void QuadTree::search(Node*,Node*,int,int,int,vector<string>&,vector<string>&);//search the direction of the node
	
}; 
#endif