#include <fstream>
#include <iostream>
using namespace std;

int main(int argc,char*argv[]){
	if(argc!=4){
		cout<<"Usage:"<<endl;
		cout<<"stats discriminants labels n"<<endl;
		return 0;
	}
	int tp=0;
	int tn=0;
	int fn=0;
	int fp=0;
	int a=1;
	int n=atoi(argv[3]);
	ifstream predictions(argv[a++]);
	ifstream examples(argv[a++]);

	double prediction;
	for(int i=0;i<n;i++){
		predictions>>prediction;
		string buffer;
		int y;
		examples>>y;
		if(y>0)
			if(prediction>0)
				tp++;
			else
				fn++;
		else
			if(prediction<=0)
				tn++;
			else
				fp++;
	}

	double accuracy=(0.0+tp+tn)/(tp+tn+fp+fn);
	double precision=(0.0+tp)/(tp+fp);
	double recall=(0.0+tp)/(tp+fn);
	double fMeasure=2*precision*recall/(precision+recall);
	double specificity=tn/(0.0+tn+fp);
	double sensitivity=tp/(0.0+tp+fn);
	cout<<"TP: "<<tp<<endl;
	cout<<"FP: "<<fp<<endl;
	cout<<"TN: "<<tn<<endl;
	cout<<"FN: "<<fn<<endl;
	cout<<"Accuracy: "<<accuracy<<endl;
	cout<<"Precision: "<<precision<<endl;
	cout<<"Recall: "<<recall<<endl;
	cout<<"F-measure: "<<fMeasure<<endl;
	cout<<"Specificity: "<<specificity<<endl;
	cout<<"Sensitivity: "<<sensitivity<<endl;

	return 0;
}
