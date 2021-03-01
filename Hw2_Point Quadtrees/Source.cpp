#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "QuadTree.h";

using namespace std;

int main(){
	string filename="cities.txt";
	ifstream cordinates;
	string line1;
	string line2;
	int xbound;
	int ybound;
	cordinates.open(filename);
	QuadTree tree;//create the class element

	while(cordinates.fail()){//if it cant open the file
		cordinates.clear();
		cout<<"Cannot find a file named "<<filename<< endl;
		return 0;
	}
	getline(cordinates,line1);//getline the bounds from the first line
	stringstream ss1(line1);
	ss1>>xbound>>ybound;


	while(!cordinates.eof()){
		if(getline(cordinates,line2)){
			stringstream ss2(line2);
			string city;
			int xdirection;
			int ydirection;
			ss2>>city>>xdirection>>ydirection;
			if(xdirection<xbound && ybound>ydirection){
				tree.insert(xdirection,ydirection,city);//call the function for create a new node according to the points and data
			}
		}
	}
	tree.print();
	cout<<endl;
	string filename2="queries.txt";
	ifstream searchcordinates;
	string line;
	searchcordinates.open(filename2);
	while(searchcordinates.fail()){//if it cant open the file
		searchcordinates.clear();
		cout<<"Cannot find a file named "<<filename2<< endl;
		return 0;
	}

	while(!searchcordinates.eof()){
		if(getline(searchcordinates,line)){
			stringstream ss2(line);
			string xsearch, ysearch, radius;
			ss2>>xsearch>>ysearch>>radius;//divide the line as xsearch,ysearch,radius
			if(stoi(xsearch)<=xbound && ybound>=stoi(ysearch)){//make the string int for comparing the bounds

			tree.find(stoi(xsearch),stoi(ysearch),stoi(radius));//make the string int and call the find function
			}
		}
	}

	return 0;
}