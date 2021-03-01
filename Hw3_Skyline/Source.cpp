#include <iostream>
#include <fstream>
#include <vector>
#include "MPQ.h"
#include "string"
#include <sstream>

using namespace std;

struct coordinate{//create the cordinate struct for cordinates vector
	int label,xcoord;
	int value;
	string side;
};


void Sort (vector <coordinate> & a)//this function sort the cordinates vector
{
	bool flag=false;
	int num=-1;
	int j;
	for (int p = 1;  p < a.size(); p++)
	{
		coordinate tmp = a[p];

		for (j = p; (j > 0) && (tmp.xcoord < a[j-1].xcoord); j--){

			a[j] = a[j-1];

		}
		if((j > 0)){
			if(tmp.xcoord==a[j-1].xcoord){

				for (j; (j > 0) && (tmp.value > a[j-1].value) && (tmp.xcoord==a[j-1].xcoord) ; j--){

					a[j] = a[j-1];

				}
			}
		}
		a[j] = tmp;
	}
}





int main(){
	string filename="input.txt";
	ifstream cities;
	string line1;
	string line2;
	cities.open(filename);
	int total_city;

	while(cities.fail()){//if it cant open the file
		cities.clear();
		cout<<"Cannot find a file named "<<filename<< endl;
		return 0;
	}

	getline(cities,line1);//getline the bounds from the first line
	stringstream ss1(line1);
	ss1>>total_city;
	if(total_city==0){
	cout << 0 << " " << 0 << endl;
	return 0;
	}
	int index=0;
	int b=1;
	vector<coordinate> coordinates(total_city*2);//create coordinates vector
	while(!cities.eof()){
		if(getline(cities,line2)){
			stringstream ss2(line2);
			int height;
			int xdirection_left;
			int xdirection_right;
			ss2>>xdirection_left>>height>>xdirection_right;

			coordinates[index].xcoord=xdirection_left;
			coordinates[index].label=b;
			coordinates[index].value=height;
			coordinates[index].side="left";

			index++;

			coordinates[index].xcoord=xdirection_right;
			coordinates[index].label=b;
			coordinates[index].value=height;
			coordinates[index].side="right";

			index++;
			b++;
		}
	}
	Sort(coordinates);//sort the coordinates vector
	int size=coordinates.size();
	int x=coordinates[size-1].xcoord;
	
	int val=coordinates[0].value;
	bool flag2=true;
	for(int a=1;a<size;a++){
		if(coordinates[a].value!=val){
		flag2=false;
		break;
		}
	}

	
	int currentmax= -1;

	MPQ heaplist(total_city);//create the heaplist object of the MPQ class
	

	if (coordinates[0].xcoord != 0) 
		cout << 0 << " " << 0 << endl;

	for(int i = 0; i < coordinates.size();i++){//if the cordinates side is left
		if(coordinates[i].side =="left"){ 
			heaplist.insert(coordinates[i].value, coordinates[i].label);//insert the element in the heaplist

		}

		else{ // if the coordinate is right one
			int a=coordinates[i].label;
			heaplist.element_delete(a);

		}
		if(heaplist.GetMax() !=currentmax){ // if the height changes

			currentmax = heaplist.GetMax();

			if(coordinates[i].xcoord!=x ){
				cout << coordinates[i].xcoord << " " <<currentmax << endl;
				if(flag2){
				cout << coordinates[coordinates.size()-1].xcoord << " " <<0<< endl;
				break;
				}
			
			}

			else{
				cout << coordinates[i].xcoord << " " <<0<< endl;//if it is the last xcord and right side
				break;
			}
		
		}

	}

	return 0;




}