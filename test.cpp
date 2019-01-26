#include<iostream>
#include<cstdlib>
#include<set>
#include<iterator>
#include<time.h>

using namespace std;


int main(int argc,char** argv){

    set <int> xIndex;
    cout << "size before insert: " << xIndex.size() << endl;
    xIndex.insert(20);
    cout << "size after insert: " << xIndex.size() << endl;
    xIndex.insert(2);
    cout << "size after seconde insert: " << xIndex.size() << endl;
    xIndex.insert(100);
    cout << "size after seconde insert: " << xIndex.size() << endl;

    set <int> :: iterator itr; 
    
    for(itr=xIndex.begin();itr!=xIndex.end();itr++){

        cout << '\t' << *itr;

    }




}