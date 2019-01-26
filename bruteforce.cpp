#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<cmath>
#include<vector>

using namespace std;

struct point{
	int x;
	int y;
};

struct Result {
	double distance;
	vector<point> closePoints;
};

struct Result findClosestPair(point*,int);
void printResult(Result* result);

// read points from file to point array.
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
// Pre-requirements: The file must exist in the same directory
// Post-requirements: A array with struct point will returned
int main(int argc,char** argv){
	string input_file=argv[1];
	point p[1000000];
	int size=readfile(input_file,p);	
	struct Result result = findClosestPair(p,size);
	printResult(&result);

}


// Pre-requirement: The size of the input array must >= 2
// Post-requirement: A struct type result who contain mindistance and related pairs will returned

struct Result findClosestPair(point* candidates,int size){
	int i,j,dist;
	struct Result result;
	double x0 = candidates[0].x;
	double y0 = candidates[0].y;
	double x1 = candidates[1].x;
	double y1 = candidates[1].y;
	// initialize the resut struct by first two points and their distance 
	result.distance = sqrt(pow(x0 - x1, 2) + pow(y0 - y1,2));
	result.closePoints.push_back(candidates[0]);
	result.closePoints.push_back(candidates[1]);
	// cout << result.distance << endl;
	for(i=0;i<=size-1;i++){				//handle array[i]
		for(j=i+1;j<=size-1;j++){        //handle array[j]
			x0 = candidates[i].x;
			x1 = candidates[j].x;
			y0 = candidates[i].y;
			y1 = candidates[j].y;

			dist = sqrt(pow( x0 - x1 , 2) + pow( y0 - y1,2));

			if (dist < result.distance){			//if smalller, clear all gathered points and push the new pair
				result.distance = dist;
				result.closePoints.clear();
				result.closePoints.push_back(candidates[i]);
				result.closePoints.push_back(candidates[j]);
			}
			else if (dist == result.distance)		//if equal then push the pair points who has same distance
			{
				result.closePoints.push_back(candidates[i]);
				result.closePoints.push_back(candidates[j]);					
			}

		

		}

	}

	return result;
}

// pre-requirement: result must be initialized
// post-requirement: contents of the result will printed out 

void printResult(Result* result){
	int i,size = result -> closePoints.size();
	printf("%0.2lf\n",result->distance);
	for(i=0;i<size -1;i+=2){
		cout<<result -> closePoints[i].x << "\t" << result->closePoints[i].y << "\t" << result->closePoints[i+1].x <<"\t" << result->closePoints[i+1].y <<endl;
	}

}
