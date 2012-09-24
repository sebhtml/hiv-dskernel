/*

	Web server for HIV predictions
    Copyright (C) 2008 Sébastien Boisvert, Mario Marchand, François Laviolette, Jacques Corbeil

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


*/


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
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

class Classifier{
	double threshold;
	vector<int> supportVectors;
	vector<double> alphaY;
	int kernelParameter;
	string title;
	vector<string>*sequences;
public:
	Classifier(string title,string file,int kernelParameter,vector<string>*sequences);
	string getTitle();
	string classify(string sequence);
};

Classifier::Classifier(string title,string file,int kernelParameter,vector<string>*sequences){
	this->kernelParameter=kernelParameter;
	this->title=title;
	this->sequences=sequences;
	ifstream f(file.c_str());
	string buffer;
	while(buffer!="documents"){
		f>>buffer;
	}
	int supportVectorsPlus1;
	f>>supportVectorsPlus1;
	while(buffer!="1")
		f>>buffer;
	f>>threshold;
	while(buffer!="alpha*y)")
		f>>buffer;;
	supportVectorsPlus1--;
	for(int i=0;i<supportVectorsPlus1;i++){
		double first;
		string middle;
		int last;
		f>>first>>middle>>last;
		alphaY.push_back(first);
		supportVectors.push_back(last);
	}
	f.close();
}
string Classifier::getTitle(){
	return title;
}
string Classifier::classify(string sequence){
	if(sequence.length()>1000){
		return "";
	}
	double value=-threshold;
	for(int i=0;i<supportVectors.size();i++){
		value+=alphaY[i]*kernel(sequence,(*sequences)[supportVectors[i]],kernelParameter,kernelParameter);
	}
	if(value>0){
		return "yes";
	}
	return "no";
}



/*
 * replace query with replacement in string aString
 */

string stringReplace(string aString,string query,string replacement){
	int found=aString.find(query);
	while(found!=string::npos){
		aString=aString.substr(0,found)+replacement+aString.substr(found+query.length());
		found=aString.find(query);
	}
	return aString;
}

void processQuery(char*query){
	cout<<("V3 sequences:");
	cout<<"<center>";
	//cout<<("<table><tr><td class=\"sequences\"><pre>");
	//cout<<("%s",query);
	//%3E => >
	string queryString(query);
	queryString=stringReplace(queryString,"sequences=","");
	queryString=stringReplace(queryString,"%3E",">");
	queryString=stringReplace(queryString,"%0A","\n");
	queryString=stringReplace(queryString,"%0D","\r");
	queryString=stringReplace(queryString,"%23","#");
	vector<string> trainingSequences;
	//cout<<"QUERY <br />";
	//cout<<""<<endl<<queryString<<""<<endl;
	//cout<<("</pre></td></tr></table>");
	vector<string> sequences;
	ifstream f("../models/X");
	while(!f.eof()){
		string sequence;
		f>>sequence;
		sequences.push_back(sequence);
	}
	f.close();
	Classifier ccr5("CCR5","../models/DS.CCR5",30,&sequences);
	Classifier cxcr4("CXCR4","../models/DS.CXCR4",30,&sequences);
	Classifier ccr5Cxcr4("CCR5 and CXCR4","../models/DS.CCR5_CXCR4",35,&sequences);
	vector<Classifier*> classifiers;
	classifiers.push_back(&ccr5);
	classifiers.push_back(&cxcr4);
	classifiers.push_back(&ccr5Cxcr4);
	string header;
	string sequence;
	istringstream stream(queryString);
	cout<<"<table><tr><td>";
	while(stream){
		header="";
		sequence="";
		stream>>header>>sequence;
		if(header==""||sequence=="")
			break;
		cout<<"<table width=\"100%\"><tr><td class=\"classification\">";
		//cout<<"HEADER";
		cout<<"<p class=\"header\">"<<header<<"</p>"<<endl;
		//cout<<"SEQUENCE";
		cout<<"<p class=\"sequence\">"<<sequence<<"</p>"<<endl;
		for(vector<Classifier*>::iterator it=classifiers.begin();
			it!=classifiers.end();it++){
			cout<<(*it)->getTitle()<<": ";
			cout<<(*it)->classify(sequence)<<"<br />"<<endl;
		}
		cout<<"</td></tr></table>";
	}
	cout<<"</td></tr></table>";
	cout<<"</center>";

}

void dumpForm(){
	cout<<("Paste your V3 sequences here using the fasta format.<br />");
	cout<<("<form method=\"POST\">");
	cout<<("<textarea rows=\"10\" cols=\"50\" name=\"sequences\">");
	cout<<("</textarea><br />");
	cout<<("<input type=\"submit\" value=\"Classify!\" /></form>");
	cout<<("<br /><br />Example:");
	cout<<("<center><table><tr><td class=\"sequences\">");
	cout<<("<pre>");
	cout<<(">B.FR.83.IIIB.A04321\n");
	cout<<("CTRPNNNTRKSIRIQRGPGRAFVTIGKIGNMRQAHC\n");
	cout<<(">01_AE.JP.96.NH2_II_a1.AB014775\n");
	cout<<("CTRPSNNTRTGITIGPGQVWYRTGDIIGDIRKAYC\n");
	cout<<(">01_AE.JP.96.NH2_II_a2.AB014776\n");
	cout<<("CTRPSNNTRTSITIGPGQVWYRTGDIIGDIRQAYC\n");
	cout<<(">01_AE.JP.96.NH2_II_a3.AB014777\n");
	cout<<("CTRPSNNTRTGITIGPGQVWYRTGDIIGDIRKAYC\n");
	cout<<(">01_AE.JP.96.NH2_II_a6.AB014778\n");
	cout<<("CTRPSNNTRTSITIGPGQVWYRTGDIIGDIRKAYCA");
	cout<<("</pre>");
	cout<<("</td></tr></table></center>");
}

int main(int argc,char*argv[]){
	char*queryString=getenv("QUERY_STRING");
	char*requestMethod=getenv("REQUEST_METHOD");
	int contentLength=atoi(getenv("CONTENT_LENGTH"));
	
	char*postData=(char*)malloc(contentLength+1);
	size_t values=fread(postData,1,contentLength,stdin);

	cout<<("Content-type: text/html\n\n");
	cout<<("<html><head><title>HIV-1 coreceptor usage prediction without multiple alignments: an application of string kernels</title>");
	cout<<"<style>.body{ text-align: center;} .sequences{background: #efefff; border-style: dashed; padding: 1cm; }";
	cout<<".classification{padding: 0.5cm; border-style: dotted; background: #eefefe;}";
	cout<<"</style>";
	cout<<("<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"></head>");
	cout<<("<body class=\"body\">");
	cout<<("<h1>HIV-1 coreceptor usage prediction without sequence alignments: an application of string kernels</h1>");
	cout<<("<br /><i>Sébastien Boisvert, Mario Marchand, François Laviolette and Jacques Corbeil</i><br /><br /><br />");

	cout<<("<a href=\"\">Reference</a><br /><br />");
	//cout<<contentLength<<endl;
	if(contentLength==0){
		dumpForm();
	}else{
		processQuery(postData);
	}
	cout<<"<p class=\"footer\">";
	cout<<"<a href=\"http://graal.ift.ulaval.ca/\">GRAAL</a> | ";
	cout<<"<a href=\"http://genome.ulaval.ca/corbeillab\">Corbeil Research Group</a><br />";
	cout<<"The source code is available for the stand-alone program and for the web server in supplements.<br />";
	cout<<"</p>";
	cout<<("</body></html>");
	free(postData);
	return 0;
}
