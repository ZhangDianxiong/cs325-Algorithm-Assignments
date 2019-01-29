#include<iostream>
#include<cmath>
#include<cstdlib>
#include<fstream>
#include<string>
#include <algorithm> 
#include <sys/time.h>
using namespace std;


struct point{
	int x;
	int y;
	bool operator==(const point& p)
	{
		return (x==p.x && y==p.y);
	}
};

struct point_pair{
	point a;
	point b;
};

point_pair pair_arr[200000];
int  pair_size=0;

int readfile(string input_file,point* p){
	ifstream myfile (input_file.c_str());
	string line;
	int j=0;
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			string n1="",n2="";
			int i=0;
			while(line[i]!=' '){
				n1=n1+line[i];
				i++;
			}
			i++;
			while(i<line.length()){
				n2=n2+line[i];
				i++;
			}
			p[j].x=atoi(n1.c_str());
			p[j].y=atoi(n2.c_str());
			j++;
		}
		myfile.close();
	}
	return j;
}

void merge(point arr[], int l, int m, int r,char axis) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    point L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
		if(axis=='x'){
			if (L[i].x <= R[j].x) 
			{ 
				arr[k] = L[i]; 
				i++; 
			} 
			else
			{ 
				arr[k] = R[j]; 
				j++; 
			} 
		}
		else
		{
			if (L[i].y <= R[j].y) 
			{ 
				arr[k] = L[i]; 
				i++; 
			} 
			else
			{ 
				arr[k] = R[j]; 
				j++; 
			} 
		}
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
	return;
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(point arr[], int l, int r,char axis) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m,axis); 
        mergeSort(arr, m+1, r,axis); 
  
        merge(arr, l, m, r,axis); 
    } 
	return;
} 

float get_distance(point p1,point p2){
	return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

float cloest_cross_pair(point* left,int n1,point* right,int n2,float dmin){
    float result=dmin;
	for(int i=0;i<n1;i++){
        for(int j=0;j<n2;j++){
            float d=get_distance(right[i],left[j]);
            if(d<=result){
                result=d;
                pair_arr[pair_size].a=right[i];
			    pair_arr[pair_size].b=left[j];
			    pair_size++;
            }
        }
    }
    return result;
}

float closet_pair(point *p,int size){
	if(size<=3){
		float d1,d2,d3,dmin1;
		d1=get_distance(p[0],p[1]);
		if(size==2){
			pair_arr[pair_size].a=p[0];
		 	pair_arr[pair_size].b=p[1];
		 	pair_size++;
			return d1;
		}
		else{
			d1=get_distance(p[0],p[1]);
			d2=get_distance(p[1],p[2]);
			d3=get_distance(p[0],p[2]);
			dmin1=min(d1,d2);
			dmin1=min(dmin1,d3);
			if(dmin1==d1){
				pair_arr[pair_size].a=p[0];
				pair_arr[pair_size].b=p[1];
				pair_size++;
			}
			if(dmin1==d2){
				pair_arr[pair_size].a=p[1];
				pair_arr[pair_size].b=p[2];
				pair_size++;
			}
			if(dmin1==d3){
					pair_arr[pair_size].a=p[0];
					pair_arr[pair_size].b=p[2];
					pair_size++;
			}
			return dmin1;
		}
	}
	else
	{
		int medin=size/2;
		int n1=medin,n2=size-medin;
		point left[n1],right[n2];
		for(int i=0;i<n1;i++){
			left[i]=p[i];
		}
		for(int j=0;j<n2;j++){
			right[j]=p[j+medin];
		}
		//cout<<n1<<" "<<n2<<endl;
		float dL=closet_pair(left,n1);
		float dR=closet_pair(right,n2);
		float dmin2=min(dL,dR);
		dmin2=cloest_cross_pair(left,n1,right,n2,dmin2);
        //cout<<dmin2<<endl;
		return dmin2;
	}
}

bool pairExist(point_pair* arr,int size,point a,point b){
	if(size==0){
		return false;
	}
	for(int i=0;i<size;i++){
		if(arr[i].a==a && arr[i].b==b){
			//cout<<1<<endl;
			return true;
		}
		if(arr[i].a==b && arr[i].b==a){
			//cout<<1<<endl;
			return true;
		}
	}
	//cout<<0<<endl;
	return false;
}

int main(int argc,char **argv){

	string input_file=argv[1];
	point p[200000];
	point_pair final_result[200000];
	int result_size=0;
	int size=readfile(input_file,p);	
	mergeSort(p,0,size-1,'x');//sort in x-axis
	typedef struct timeval time;
	time stop, start;
	gettimeofday(&start, NULL);
	float dim=closet_pair(p,size);
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl; 
    
	ofstream myfile;
	myfile.open("result.txt");
	myfile<<dim<<endl;
	// cout<<pair_size<<endl;
	for(int i=0;i<pair_size;i++)
	{
		float d=get_distance(pair_arr[i].a,pair_arr[i].b);
		//cout<<"("<<pair_arr[i].a.x<<","<<pair_arr[i].a.y<<"), ";
		//cout<<"("<<pair_arr[i].b.x<<","<<pair_arr[i].b.y<<")"<<endl;
		if(d-dim<0.00001 && d-dim>-0.00001){
			final_result[result_size].a=pair_arr[i].a;
			final_result[result_size].b=pair_arr[i].b;
			if(!pairExist(final_result,result_size,pair_arr[i].a,pair_arr[i].b)){
				myfile<<"("<<pair_arr[i].a.x<<","<<pair_arr[i].a.y<<"), ";
				myfile<<"("<<pair_arr[i].b.x<<","<<pair_arr[i].b.y<<")"<<endl;
			}
			result_size++;
		}
	}
	myfile.close();
  
  return 0;
}
