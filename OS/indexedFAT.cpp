#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#define maxblocks 35

using namespace std;

class File{
    public:
        char name;
        int siz;
        int inds[5000];
        int getData(){
            cout<<name<<"\t\t"<<inds[0]<<"\n";
        }
};

char blocks[maxblocks]; // "\0"

int nonNegIntInput(string message) //include limits
{
    cout<<message;
    int input;
    cin >> input;
    while(true){
        if(cin.fail()){
            printf("OOPS! Wrong input! Try again: ");
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin>>input;
        }
        if(!cin.fail()){
     		if (input < 0)
            {
      			printf("Input needs to be positive integer! Enter again: ");
      			cin>>input;
            }
            else{
                break;
            }
        }
	}
    return input;
}

bool hasSpace(int space){
    int avl=0;
    for(int i=0; i<maxblocks; i++){
        if(blocks[i]=='\0'){
            avl++;
        }
    }
    if (avl>=space){return true;}
    else {return false;}
}

int getEmptyBlock(){
    int f;
    if (hasSpace(1)){
        while(true){
            f = rand() % (maxblocks - 1);
            //cout<<"picked "<<f;
            if(blocks[f]=='\0'){
                return f;
            }
        }
    }
}

void assignFile(File *file){
    int f, siz, indexblock;
    siz=file->siz+1;
    if (hasSpace(siz)){
        for(int i=0; i<siz; i++){
            f = getEmptyBlock();
            blocks[f]=file->name;
            file->inds[i]=f;
        }
    }
    else{
        cout<<"\nCould not assign file "<<file->name;
    }
}

int main(){
    int n=nonNegIntInput("How many files?: ");
    File files[n];
    for(int i=0; i<n; i++){
        cout<<"Enter file character: ";
        cin>>files[i].name;
        files[i].siz=nonNegIntInput("Enter file size: ");
    }
    for(int i=0; i<n; i++){
        assignFile(&files[i]);
    }
    for(int i=0; i<maxblocks; i++){
        if(i%5==0){printf("\n");}
        if(blocks[i]=='\0'){
            printf("\tNA");
        }
        else{
            printf("\t%c", blocks[i]);
        }
    }
    cout<<"\n\n\nFile name"<<"\t"<<"Index block\n";
    for(int i=0; i<n; i++){
        files[i].getData();
    }
    return 0;
}
