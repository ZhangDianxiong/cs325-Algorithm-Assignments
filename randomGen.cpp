#include<iostream>
#include<cstdlib>
#include<set>
#include<iterator>
#include<time.h>

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
        struct point pointset[size];


        set <int> xIndex;
        set <int> yIndex;

        srand(time(NULL));


        while(i < size){
                x0 = xIndex.size();
                do{
                        x = rand() % size;
                        xIndex.insert(x);
                        x1 = xIndex.size();
                }while(x0 == x1);

                y0 = yIndex.size();
                do{
                        y = rand() % size;
                        yIndex.insert(y);
                        y1 = yIndex.size();

                }while(y0 == y1);
                pointset[i].x = x;
                pointset[i].y = y;
                i++;

                cout << x << "\t" << y << endl;
        }
        

        
        // printPoints(pointset,size);




}

void printPoints(point* pointset,int size){

        for(int i=0;i<size;i++){
                cout << pointset[i].x << "\t" << pointset[i].y;

                if((i+1)%2 == 0)
                        cout << endl;
                else
                        cout << "\t";
                

        }

}
