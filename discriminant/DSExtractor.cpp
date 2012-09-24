#include<iostream>
#include<string>
#include<map>
#include<sstream>
#include<fstream>
using namespace std;

int min(int a,int b){
	if(a<b)
		return a;
	return b;
}

void produce(string&s,int delta_m,int theta_m,ofstream&out){
	map<string,int> features;
	cout<<"Doing "<<s<<endl;
	for(int p=1;p<=(int)s.length()-1;p++){
		for(int delta=2;delta<=min(s.length()-p+1,delta_m);delta++){
			for(int theta_alpha=1;theta_alpha<=min(delta-1,theta_m);theta_alpha++){
				for(int theta_alpha_prime=1;theta_alpha_prime<=min(delta-theta_alpha,theta_m);theta_alpha_prime++){
					string alpha=s.substr(p-1,theta_alpha);
					int alpha_prime_start=p+delta-theta_alpha_prime;
					string alpha_prime=s.substr(alpha_prime_start-1,theta_alpha_prime);
					ostringstream s;
					s<<delta<<","<<alpha<<","<<alpha_prime;
					features[s.str()]++;
				}
			}
		}
	}
	map<string,int>::iterator it;
	for(it=features.begin();it!=features.end();it++){
		out<<it->first<<":"<<it->second<<" ";
	}
	out.seekp(-1,ios_base::cur);
	out<<endl;
}

int main(int argc,char*argv[]){
	if(argc!=6){
		cout<<"Usage:"<<endl;
		cout<<"Program sequenceFile sequenceAmount delta_m theta_m output"<<endl;
		return 0;
	}
	ifstream in(argv[1]);
	int sequenceAmount=atoi(argv[2]);
	int delta_m=atoi(argv[3]);
	int theta_m=atoi(argv[4]);
	ofstream out(argv[5]);
	for(int i=0;i<sequenceAmount;i++){
		string s;
		in>>s;
		produce(s,delta_m,theta_m,out);
	}
	return 0;
}
