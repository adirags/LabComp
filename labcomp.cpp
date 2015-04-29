/*
  The following code is a C++ execution of labcomp. The tunable parameters are:
  	  VecSize = Size of vector considered
  	  maxPCD = Maximum allowable Per Character Distortion
  The other variables used below are:
  	  dict = Array storing dictionary vectors in a 1D form
	  DictVecs = No. of vectors in the dictionary
  	  DictLen = Length of Dictionary(DictVecs*VecSize)
  	  len = Length of input text file
  	  dist = temporarily stores the highest distortion for a particular pair of input vector considered and dictionary vector considered
  	  	   If dist<maxPCD => Can suitably use that particular dictionary vector to represent input vector
	  i,j,k,l,m = Just a bunch of indices	   
*/

#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

int main()	{
	ifstream f1("QualVals.txt");		//Input text file
	ofstream f2("QuantQualVals.txt");	//Output file(Quantized Output)
	f1.seekg(0,ios::end);
	int len = f1.tellg();
	f1.seekg(0,ios::beg);
	int VecSize, maxPCD;
//Change the below two variables to test performance	
	VecSize = 5;	//Vector Size
	maxPCD = 5;	//max allowable per character distortion
	
	int it,i,j,k,l,m,DictLen,dist=0,DictVecs;
	char vector[VecSize], dict[100000], diff[VecSize];  //Notice arbitrary large size for dict
	it = len/VecSize;
	for(i=0;i<it;i++)	{
P:		j = VecSize;
		k=0;
		while(j>0)	{
			vector[k] = f1.get();
			k++;
			j--;
		}
		if(i==0)	{
			for(l=0;l<VecSize;l++)	{
				dict[l] = vector[l];
				f2.put(dict[l]);
			}
			DictLen = VecSize;
		}
		else	{
			m = 0;
			DictVecs = DictLen/VecSize;
			while(m<DictVecs)	{
				dist = 0;
				for(l=0;l<VecSize;l++)	{
					diff[l] = vector[l] - dict[m*VecSize + l];
					diff[l] = abs(diff[l]);
					dist = (dist>diff[l])?dist:diff[l];
					}
				if(dist<maxPCD)	{
					for(l=0;l<VecSize;l++)	{
						f2.put(dict[m*VecSize + l]);
					}
					++i;
					if(i==it){
						return 0;
					}
					goto P;
				}
			m++;
			}			
		}
		if(m==DictVecs)	{
			for(l=0;l<VecSize;l++)	{
				dict[m*VecSize + l] = vector[l];
				f2.put(vector[l]);
			}
			DictLen =  DictLen + VecSize;
		}
		
	}
	return 0;
}
