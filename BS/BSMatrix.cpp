
#include <iostream>
#include<string>
#include <fstream>
#include <vector>
using namespace std;


int suffix(string s,int i_p,string t,int j_p,int p){
	if(p==0)
		return 0;
	if(s.at(i_p)==t.at(j_p))
		return 1+suffix(s,i_p-1,t,j_p-1,p-1);
	else
		return 0;
}
int kernel(string s,string t,int p){
	int i;
	int j;
	int k=0;
	for(i=0;i<(int)s.length()-p;i++)
		for(j=0;j<(int)t.length()-p;j++)
			k+=suffix(s,i+p,t,j+p,p);
	return k;
}


int main(int argc,char*argv[]){
	if(argc!=5){
		cout<<"Usage:"<<endl;
		cout<<"DSkernel l sequenceFile p out"<<endl;
		return 0;
	}
	vector<string> sequences;
	int p=atoi(argv[3]);
	cout<<"p="<<p<<endl;
	ifstream f(argv[2]);
	ofstream out(argv[4]);
	int l=atoi(argv[1]);
	int*K=new int[l*l];
	for(int i=0;i<l;i++){
		for(int j=0;j<l;j++){
			K[i+j*l]=-1;
		}
	}
	for(int i=0;i<l;i++){
		string sequence;
		f>>sequence;
		sequences.push_back(sequence);
	}
	f.close();
	out<<"x";
	for(int i=0;i<l;i++){
		out<<"\t"<<i;
	}
	out<<endl;
	
	for(int i=0;i<l;i++){
		out<<i;
		for(int j=0;j<l;j++){
			if(K[i+j*l]==-1){
				K[i+j*l]=kernel(sequences.at(i),sequences.at(j),p);
				K[j+i*l]=K[i+j*l];
			}
			out<<"\t"<<K[i+j*l];
		}
		out<<endl;
	}
	delete K;
}
