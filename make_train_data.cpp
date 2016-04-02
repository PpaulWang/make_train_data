#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>
using namespace std;
int pictureNum;
void get_grand_truth(string fileName,vector<vector<bool> > grandTruth){
	grandTruth.resize(pictureNum);
	ifstream fin(fileName.c_str()); 
	string str;
	for(int i=0;i<pictureNum;i++){
		grandTruth[i].resize(pictureNum);
		fin>>str;
		for(int j=0;j<pictureNum;j++){
			grandTruth[i][j]=(str[j]=='1');
		}
	}
	fin.close();
}
void get_features(string fileName,vector<vector<float> > features){
	features.resize(pictureNum);
	float sum;
	int id;
	int len;
	ifstream fin(fileName.c_str());
	for(int i=0;i<pictureNum;i++){
		fin>>id;
		//CHECK(id-1==i);
		fin>>len;
		features[i].resize(len);
		for(int j=0;j<len;j++)fin>>features[i][j];
		fin>>sum;
	}
	fin.close();
}

void get_data(string outFileName,const vector<vector<bool> >& grandTruth,const vector<vector<float> >& features){
	ofstream fout(outFileName.c_str());
	for(int i=0;i<pictureNum;i++){
		for(int j=0;j<i;j++){
			if(grandTruth[i][j]){
				fout<<1<<" ";
				for(int k=0;k<features[i].size();k++){
					if(k)fout<<" ";
					fout<<k<<":"<<features[i][k]-features[j][k];
				}
				fout<<endl;
			}
		}
	}
	fout.close();
	
}
int main(int argc,char** argv){
	if(argc<2){
		cerr<<"usage: "<<argv[0]<<" [config file name]"<<endl;
		return -1;
	}
	string layerName ;
	
	string grandTruthFileName;
	
	string featureFileName ;


		
	ifstream finConfig(argv[1]);

	finConfig>>pictureNum;

	finConfig>>grandTruthFileName;
	
	finConfig>>layerName;
	
	finConfig>>featureFileName;
	
	finConfig.close();
	
	vector< vector<bool> > grandTruth;
	vector< vector<float> > features;
	
	
	get_grand_truth(grandTruthFileName,grandTruth);
	get_features(featureFileName,features);

	string outFileName="train_data"+layerName+".txt";
	get_data(outFileName,grandTruth,features);

	
}