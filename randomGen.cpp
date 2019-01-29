#include<iostream>
#include<cstdlib>
#include<set>
#include<iterator>
#include<time.h>
#include<fstream>

using namespace std;

struct point{
	int x;
	int y;
};

void printPoints(point* pointset,int size);

int main(int argc,char** argv){
        int i = 0;
        int x,y,x0,x1,y0,y1;
        int size = atoi(argv[1]);
        //     int candidates[size];
        struct point pointset[size];                    //array to store the generated points


        set <int> xIndex;                               //two sets to pust the random num use to test the uniqueness of the random variable
        set <int> yIndex;

        srand(time(NULL));


        while(i < size){
                x0 = xIndex.size();                     //random generate an unique x 
                do{
                        x = rand() % (size*10);
                        xIndex.insert(x);
                        x1 = xIndex.size();
                }while(x0 == x1);

                y0 = yIndex.size();                     //random generate an unique x 
                do{
                        y = rand() % (size*10);
                        yIndex.insert(y);
                        y1 = yIndex.size();

                }while(y0 == y1);
                pointset[i].x = x;
                pointset[i].y = y;
                i++;

                // cout << x << "\t" << y << endl;
        }
        

        
        printPoints(pointset,size);                 //print points to a file




}

void printPoints(point* pointset,int size){
        ofstream myfile;
        myfile.open("pointSet.txt");
        if(myfile.is_open()){
                for(int i = 0;i < size;i++){
                        myfile << pointset[i].x << " " << pointset[i].y << endl;
                }
        }
        else{
                cout << "Fail to open the file. " << endl;
        }


}