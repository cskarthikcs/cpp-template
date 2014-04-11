#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<list>
#include<vector>
#include <sstream>
#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

void print (vector<vector <int> >& B ){
	for(long long int x=0;x<B.size();x++){	
		for(int y=0;y<B[x].size();y++){
			cout<<B[x][y]<<" ";			
		}		
		cout<<endl;
	}
}

void print (vector <int> & B ){
		for(int y=0;y<B.size();y++){
			cout<<B[y]<<" ";			
		}		
		cout<<endl;
}

bool cover(vector< vector <int> >& B,vector<vector <int> >& A,int val){
	for(int i=0;i<B.size();i++){
		bool flag=false; 
		for(int j=0;j<A.size();j++){
			int b=0,a=0,count=0;
			while(1<2){
				if(B[i][b]==A[j][a]){
					b++;
					a++;
					count++;
				} else {
					if(B[i][b]>A[j][a])
						b++;
					else
						a++;
				}
				if(a>=2*val||b>=2*val)
					break;
			}
			if(count==val){
				flag=true;
				break;
			}	
		}
		if(flag==false)
			return false;
	}
	return true;
}

void subset(int arr[], int size, int left, int index, list<int> &l, vector<vector <int> > &B, int n, bool &flag){
    if(left==0){
	vector< vector <int> > A;
	for(list<int>::iterator it=l.begin(); it!=l.end() ; ++it)
		A.push_back(B[*it]);
	if(cover(B,A,n)==true){
		string s = SSTR(n) + ".txt";
		ofstream f(s.c_str());
		for(int r=0;r<A.size();r++){
			for(int j=0;j<A[r].size();j++){
				f<<A[r][j]<<" ";
			}	
			f<<endl;				
		}
		f.close();
		flag=true;
	}		
	A.clear();
	return;
    }
    if(flag==true)
	return;
    for(int i=index; i<size;i++){
        l.push_back(arr[i]);
        subset(arr,size,left-1,i+1,l,B,n,flag);
        l.pop_back();
    }
}     

int main(){
	for(int i=1;i<10;i++){	
		vector< vector <int> > B;
		for(long long int j=0;j<pow(2,4*i);j++){
			long long int temp=j, count=0;			
			for(int r=4*i -1;r>=0;r--){
				if(pow(2,r)<=temp){
					count++;
					temp-=pow(2,r);
				}
			}
			if(count==2*i){
				vector<int> A;
				temp=j;
				for(int r=4*i -1;r>=0;r--){
					if(pow(2,r)<=temp){
						A.push_back(r+1);
						temp-=pow(2,r);
					}
				}
				B.push_back(A);
			}
		}			
		for(int d=sqrt(i);d<=2*i;d++){
			cout<<"i="<<i<<" d="<<d<<" |B|="<<B.size()<<endl;
			vector< vector <int> > pos;	
			int array[B.size()];
			for(int r=0;r<B.size();r++)
				array[r]=r;
			list<int> lt;
			bool flag=false;
			subset(array,B.size(),d,0,lt,B,i,flag);
			if(flag==true)
				break;			
		}	
	}
	return 0;
}
