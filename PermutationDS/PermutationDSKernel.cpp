// Matrix generator for the case where asymmetry is allowed and where overlaps are not tolerated.
// DS Kernel Project
// 2008-04-10

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int min(int a,int b){
	if(a<b)
		return a;
	return b;
}



int bin(int j,int i){
	if(i>j)
		return 0;
	if(i==3&&j>=3){
		return j*(j-1)*(j-2)/6;
	}else if(i==2&&j>=2){
		return j*(j-1)/2;
	}
	cout<<"Error"<<endl;
	return 0;
}

int kernel(string s,string t,int delta_m,int theta_m){
	//cout<<"s "<<s<<" "<<s.length()<<endl;
	//cout<<"t "<<t<<" "<<t.length()<<endl;
	int c=0;
	int*i_=new int[delta_m+1];
	int*l_=new int[delta_m+1];
	for(int j_s=0;j_s<=(int)s.length()-1;j_s++){
		for(int j_t=0;j_t<=(int)t.length()-1;j_t++){
			if(s.at(j_s-1+1)==t.at(j_t-1+1)){ // -1 because index starts at 0
				int n=min(min(s.length()-j_s,t.length()-j_t),delta_m);
				//cout<<"n "<<n<<endl;
				//cout<<"j_s "<<j_s<<" j_t "<<j_t<<endl;
				int k=-1;
				int i=1;
				while(i<=n){
					//cout<<"i "<<i<<endl;
					k++;
					i_[2*k]=i;
					//cout<<"PAR_s "<<j_s-1+i<<endl;
					//cout<<"PAR_t "<<j_t-1+i<<endl;
					i++;
					while(i<=n&&s.at(j_s-1+i)==t.at(j_t-1+i))// -1 because index starts at 0
						i++;
					i_[2*k+1]=i;
					l_[k]=i_[2*k+1]-i_[2*k]+1;
					i++;
					//cout<<"i "<<i<<endl;
					while(i<=n&&s.at(j_s-1+i)!=t.at(j_t-1+i))// -1 because index starts at 0
						i++;
				}
				c+=bin(l_[0],3)-2*bin(l_[0]-theta_m,3)+bin(l_[0]-2*theta_m,3);
				int c1=0;
				for(int r=1;r<=k;r++){
					c1+=bin(l_[r],2)-bin(l_[r]-theta_m,2);
				}
				c+=min(theta_m,i_[1]-i_[0])*c1;
			}
		}
	}
	delete l_;
	delete i_;
	return c;
}

int main(int argc,char*argv[]){
	if(argc!=6){
		cout<<"Usage:"<<endl;
		cout<<"DSkernel l sequenceFile delta_m theta_m out"<<endl;
		return 0;
	}
	vector<string> sequences;
	int delta_m=atoi(argv[3]);
	int theta_m=atoi(argv[4]);
	ifstream f(argv[2]);
	ofstream out(argv[5]);
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
				K[i+j*l]=kernel(sequences.at(i),sequences.at(j),delta_m,theta_m);
				K[j+i*l]=K[i+j*l];
			}
			out<<"\t"<<K[i+j*l];
		}
		out<<endl;
	}
	delete K;
}
