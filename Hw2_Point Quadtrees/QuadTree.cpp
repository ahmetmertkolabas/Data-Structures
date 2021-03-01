#include <string>
#include "QuadTree.h"
#include <iostream>
using namespace std;

void QuadTree::print(){//calls the printhelper function
	printhelper(root);
	return;
}


void QuadTree::printhelper(Node *tmp) //print the tree
{ 
	if(tmp!=NULL){
		cout<<tmp->data<<endl;
		printhelper(tmp->SE); // recursively print the south east subtree
		printhelper(tmp->SW); // recursively print the south west subtree
		printhelper(tmp->NE); // recursively print the north east subtree
		printhelper(tmp->NW); // recursively print the north west subtree
	}
} 

QuadTree::QuadTree(){//default constructor
	root=NULL;
}

string QuadTree:: compare(Node*P,Node*R){//compare two nodes x and y and decide where must be the next node and return string
	if(P->x<R->x){
		if(P->y<R->y){
			return "SW";
		}
		else{
			return "NW";
		}
	}
	else if(P->y<R->y){
		return "SE";
	}
	else{
		return "NE";
	}
}

void QuadTree::insert(int x,int y,string data){//insert the node to the tree
	Node* f;
	Node* temp=NULL;
	Node* p=new Node;
	string q;
	p->x=x;
	p->y=y;
	p->data=data;
	if(root==NULL){//if tree is empty
		root=p;
		return;
	}
	else{
		temp=root;
		while(temp!=nullptr && !(p->x==temp->x && p->y==temp->y)){
			f=temp;
			q=compare(p,temp);//compare two nodes x and y and decide where must be the next node and return string
			temp=SON(temp,q);//son fuction return roots position se,sw,nw,ne and equal it to the temp node*
		}
	}
	if(temp==NULL){

		if(q=="SW"){//make sw new node
			f->SW=p;
		}
		if(q=="NW"){//make nw new node
			f->NW=p;
		}
		if(q=="SE"){//make se new node
			f->SE=p;
		}
		if(q=="NE"){//make ne new node
			f->NE=p;
		}
	}
}





Node* QuadTree::SON(Node*t,string q){//this function take a string parameter of direction(se,sw,ne,nw) and return nodes->position
	Node* x;
	if(q=="SW"){//nodes's sw
		x=t->SW;
	}
	if(q=="NW"){//nodes's sw
		x=t->NW;
	}
	if(q=="SE"){//nodes's sw
		x=t->SE;
	}
	if(q=="NE"){//nodes's sw
		x=t->NE;
	}
	return x;
}

void QuadTree::QuadTreeHelper(Node* temp){//this function delete all nodes at the tree by a recursive action

	if(temp!=NULL){
		QuadTreeHelper(temp->SE);
		QuadTreeHelper(temp->SW);
		QuadTreeHelper(temp->NE);
		QuadTreeHelper(temp->NW);
		delete temp;
	}
	return;
}

QuadTree::~QuadTree(){//destructar

	QuadTreeHelper(root);
	root=NULL;
}

float distance(int x1, int y1, int x2, int y2) //find the distance between of to nodes point 
{ 
	return sqrt(pow(x2 - x1, 2) +  
		pow(y2 - y1, 2) * 1.0); 
} 



vector<string> directions(Node* tmp, Node* root, int radius, vector <string>& direction)//find the direction of the node which the given quary point is at
{

	if((tmp->x-radius)<=(root->x)){//if tmp->x-radius is smaller than root->x
		if(direction[0]=="NE"){
			direction.push_back("NW");//push back the NW string to the vector
		}
		if(direction[0]=="SE"){
			direction.push_back("SW");//push back the SW string to the vector
		}
	}
	if((tmp->x+radius)>=(root->x)){//if tmp->x+radius is bigger than root->x
		if(direction[0]=="NW"){
			direction.push_back("NE");//push back the NE string to the vector
		}
		if(direction[0]=="SW"){
			direction.push_back("SE");//push back the SE string to the vector
		}
	}

	if((tmp->y-radius)<=(root->y)){//if tmp->y-radius is smaller than root->y
		if(direction[0]=="NE"){
			direction.push_back("SE");//push back the SE string to the vector
		}
		if(direction[0]=="NW"){
			direction.push_back("SW");//push back the SW string to the vector
		}
	}

	if((tmp->y+radius)>=(root->y)){//if tmp->y+radius is bigger than root->y
		if(direction[0]=="SW"){
			direction.push_back("NW");//push back the NW string to the vector
		}
		if(direction[0]=="SE"){
			direction.push_back("NE");//push back the NE string to the vector
		}
	}
	if((tmp->x+radius>=root->x) && (tmp->y-radius<=root->y) && (distance(tmp->x,tmp->y,root->x,root->y)<=radius)){//if tmp->x+radius is bigger than root->x and if tmp->y-radius is smaller than root->y and the distance between<=radius

		if(direction[0]=="NW"){
			direction.push_back("SE");
		}
	}
	if((tmp->x-radius<=root->x) && (tmp->y-radius<=root->y) && (distance(tmp->x,tmp->y,root->x,root->y)<=radius)){//if tmp->x-radius is smaller than root->x and if tmp->y-radius is smaller than root->y and the distance between<=radius

		if(direction[0]=="NE"){
			direction.push_back("SW");
		}
	}

	if((tmp->x+radius>=root->x) && (tmp->y+radius>=root->y) && (distance(tmp->x,tmp->y,root->x,root->y)<=radius)){//if tmp->x+radius is bigger than root->x and if tmp->y+radius is bigger than root->y and the distance between<=radius

		if(direction[0]=="SW"){
			direction.push_back("NE");
		}
	}
	if((tmp->x-radius<=root->x) && (tmp->y+radius>=root->y) && (distance(tmp->x,tmp->y,root->x,root->y)<=radius)){//if tmp->y-radius is smaller than root->y and if tmp->y+radius is bigger than root->y and the distance between<=radius

		if(direction[0]=="SE"){
			direction.push_back("NW");
		}
	}
	return direction;
}


void QuadTree::search(Node *tmp2, Node* R,int xsearh,int ysearch,int radius,vector<string>&cities_visit,vector<string>&cities_inside){//search the direction of the node

	Node* ptr = R;
	int se=0,sw=0,ne=0,nw=0;

	if(ptr!=NULL){

		cities_visit.push_back(ptr->data);

		if(distance(tmp2->x,tmp2->y,ptr->x,ptr->y)<=radius){
			cities_inside.push_back(ptr->data);
		}
		vector <string> direction;
		direction.push_back(compare(tmp2,R));//push back the string which comes from the compare function according to 2 nodes
		direction = directions(tmp2, R, radius, direction);//call directions function
		

		se=0,sw=0,ne=0,nw=0;

		for(int i =0; i<direction.size();i++)//look if the elements of the direction vector contains se,sw,ne,nw
		{
			if(direction[i] == "SE")
				se=1;
			if(direction[i] == "SW")
				sw=1;
			if(direction[i] == "NE")
				ne=1;
			if(direction[i] == "NW")
				nw=1;
		}

		if(se == 1)
			search(tmp2,R->SE,xsearh,ysearch,radius,cities_visit,cities_inside); // recursively print the south east subtree
		if(sw == 1)
			search(tmp2,R->SW, xsearh,ysearch,radius,cities_visit,cities_inside); // recursively print the south west subtree
		if(ne == 1)
			search(tmp2,R->NE,xsearh,ysearch,radius,cities_visit,cities_inside); // recursively print the north east subtree
		if(nw == 1)
			search(tmp2,R->NW,xsearh,ysearch,radius,cities_visit,cities_inside); // recursively print the north west subtree
	}

	return;

}




void QuadTree::find(int xsearh,int ysearch,int radius){//it cout the inside_circle_cities elements and cities_visit elements
	vector<string>cities_visit;
	vector<string>inside_circle_cities;
	Node* tmp=new Node;
	vector<string>direction;
	tmp->x=xsearh;
	tmp->y=ysearch;

	search(tmp,root,tmp->x,tmp->y,radius,cities_visit,inside_circle_cities);//call the search function 

	if(inside_circle_cities.size()!=0)
	{
		for(int i=0;i<inside_circle_cities.size()-1;i++)//cout the elements of the inside_circle_cities elements
		{
			cout<<inside_circle_cities[i]<<", ";
		}
		cout<<inside_circle_cities.back()<<endl;
	}
	else
	{
		cout<<"<None>"<< endl;//if there is no elements in inside_circle_cities
	}
	for(int i=0;i<cities_visit.size()-1;i++)//cout the elements of the cities_visit elements
	{
		cout<<cities_visit[i]<<", ";
	}
	cout<<cities_visit.back()<<endl;
	cout<<endl;
}