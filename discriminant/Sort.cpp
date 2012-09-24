#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

class MyData{
	string key;
	double value;
	MyData();
public:
	MyData(string key,double value);
	bool operator<(const MyData&a);
	string&getKey();
	double getValue();
};

MyData::MyData(string key,double value){
	this->key=key;
	this->value=value;
}

bool MyData::operator<(const MyData&a){
	return value<a.value;
}

string&MyData::getKey(){
	return key;
}

double MyData::getValue(){
	return value;
}

int main(int argc,char*argv[]){
	if(argc!=3){
		cout<<"Usage:"<<endl;
		cout<<"Sort n file"<<endl;
		return 0;
	}
	list<MyData> myList;
	int n=atoi(argv[1]);
	ifstream f(argv[2]);
	for(int i=0;i<n;i++){
		string key;
		double value;
		f>>key>>value;
		MyData data(key,value);
		myList.push_back(data);
	}
	myList.sort();
	for(list<MyData>::iterator citer=myList.begin();citer!=myList.end();citer++){
		cout<<(*citer).getKey()<<" "<<(*citer).getValue()<<endl;
	}
	return 0;
}
