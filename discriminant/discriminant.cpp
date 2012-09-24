/*
Sébastien Boisvert
Sebastien.Boisvert@usherbrooke.ca
BFT600 Projet d'intération en bio-informatique
Université de Sherbrooke
Hiver 2008
*/

#include <iostream>
#include <map>
using namespace std;

int main(int argc,char*argv[]){
	if(argc!=4){
		cout<<"Usage: ./discriminant phi alpha_y discriminant\n"<<endl;
		return 0;
	}
	FILE*phi=fopen(argv[1],"r");
	FILE*y_alpha=fopen(argv[2],"r");
	FILE*out=fopen(argv[3],"w+");
	double current;
	char buffer[1000];
	double value;
	map<string,double> discriminant;
	fscanf(y_alpha,"%lf",&current);
	
	while(EOF!=fscanf(phi,"%s",buffer)){
		char*first=strchr(buffer,':');
		first[0]='\0';
		first++;
		sscanf(first,"%lf",&value);
		string feature(buffer);
		double v=current*value;
		if(discriminant.count(feature)==0){
			discriminant[feature]=v;
		}else{
			discriminant[feature]+=v;
		}
		char c=fgetc(phi);
		if(c=='\n'){
			fscanf(y_alpha,"%lf",&current);
		}
	}
	map<string,double>::iterator it;
	for(it=discriminant.begin();it!=discriminant.end();it++){
		fprintf(out,"%s:%.64g\n",it->first.c_str(),it->second);
	}
	fclose(phi);
	fclose(y_alpha);
	fclose(out);
}
