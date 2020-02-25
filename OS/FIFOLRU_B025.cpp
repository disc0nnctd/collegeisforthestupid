/*input
18
0\n1\n2\n0\n1\n2\n0\n3\n4\n5\n6\n0\n2\n1\n0\n3\n4\n5
1|2
*/
//------------------------------code starts here-------------------------------------
#include <iostream>
#include <stdio.h>
#include <limits>
#define pagesize 4
using namespace std;

int pg[pagesize];
int hitcount=0;

void initpg(){
    for(int i=0; i<pagesize; i++){
        pg[i]=-999;
    }
    hitcount=0;
}

bool checkHit(int n){
	for(int i=0; i<pagesize; i++){
		if (n==pg[i]){
			printf("Hit!\n");
			return true;
		}
	}
	printf("Miss!\n");
	return false;
}


void replaceLastOpen(int n){
	int i;
	for(i=0; i<pagesize; i++){
		if (pg[i]==-999){
			pg[i]=n;
			break;
		}
	}
}

bool vacancy(){ //check if there's vacancy in the page frame
    for(int i=0; i<pagesize; i++){
        if(pg[i]==-999){return true;}
    }
    return false;
}

//below function used in FIFO
void delE() { //take first element out
  int j;
  for (j = 0; j < pagesize - 1; j++) {
    pg[j] = pg[j + 1];
  }
  pg[j] = -999;
}

//below function used in LRU
void delE(int n){ //take element out and shift left and move the hit element to right
	int i, j;
	for(i=0; i<pagesize; i++){
		if(pg[i]==n){
			break;
		}
	}
	//got the index of the element to be deleted, i

	for(j=i; j<pagesize-1; j++){
		pg[j]=pg[j+1];
	}
	pg[j]=-999;
}


void FIFO(int n) {
  bool hit = checkHit(n);
  if (hit) {
    hitcount++; //increment hits
    //take out n
    delE();
    //replace last open position
  } else {
    if (vacancy()) {
      //replace last open
    } else {
      delE(); //delete first element
      //replace last open
    }
  }
  replaceLastOpen(n);
}

void LRU(int n){
	bool hit = checkHit(n);
	if(hit){
		hitcount++; //increment hits
		//take out n
		delE(n);
		//replace last open position
	}
	else{
        if (vacancy()){
        	//replace last open
        }
        else{
            delE(pg[0]); //delete first element
            //replace last open
        }

	}
	replaceLastOpen(n);
}


int main(){
	int seqsize;
	printf("How long sequence? ");
	cin>>seqsize;
	while(true){
        if(cin.fail()){
            printf("OOPS! Wrong input! Try again: ");
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin>>seqsize;
        }
        if(!cin.fail()){break;}
	}
	int seq[seqsize];
	//sequence input
	for(int i=0; i<seqsize; i++){
		printf("Enter %d page: ", i+1);
        cin>>seq[i];
        while(true){
            if(cin.fail()){
                printf("OOPS! Wrong input! Try again:");
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin>>seq[i];
            }
            if(!cin.fail()){break;}
        }
	}

	int ask;
	while(true){
        initpg();
        printf("\n\n\nWhich method do you want to use? \n1. FIFO\n2. LRU\n Choice: ");
        cin>>ask;
        if (cin.fail()){printf("Invalid input. Stopping..."); break;}
        if (ask==1){
            for(int i=0; i<seqsize; i++){
                printf("\nAt %d\t\t", seq[i]);
                LRU(seq[i]);
            }
        }
        else if(ask==2){
            for (int i = 0; i < seqsize; i++) {
                printf("\nAt %d\t\t", seq[i]);
                FIFO(seq[i]);
            }
        }
        else{
            printf("Unrecognized input. Stopping...");
            break;
        }

        printf("\n-------\nHits=%d\nHitRatio=%f", hitcount, hitcount / float(seqsize));
	}
    return 0;
}
