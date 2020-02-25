#include<iostream>
#include<stdio.h>
#include<limits>
#define blockcount 5
#define addressstart 3000
using namespace std;

struct fragment{
	int startaddress, endaddress;
};

struct memblock{
	int no;
	int sz;
	int currentpart=0;
	fragment parts[100];
	int startAdd, endAdd;
	int tempstartadd;
	char processes[100];
};

memblock memblocks[blockcount];
int blockszs[blockcount]={1, 100, 150, 50, 25};

int currentBlockIndex=0;

void initBlocks(){
    currentBlockIndex=0;
    int currentAddress=addressstart;
	for(int i=0; i<blockcount; i++){
		memblocks[i].no=i+1;
		memblocks[i].sz=blockszs[i];
		memblocks[i].startAdd=currentAddress;
		memblocks[i].tempstartadd=currentAddress;
		memblocks[i].endAdd=currentAddress+blockszs[i];
		currentAddress++;
	}
}


void createPartition(memblock *block, int siz){ //don't run if sz > blocksz
	int currpart=block->currentpart;
	//printf("Current part is %d\n", currpart);
	if (currpart>0){
		block->parts[currpart].startaddress=block->tempstartadd;
		//printf("startaddress set to %d\n", block->parts[currpart].startaddress);
		}
	else if(currpart==0){
		block->parts[0].startaddress=block->startAdd;
	}
	block->parts[currpart].endaddress=block->parts[currpart].startaddress+siz;
	printf("Allocated at block: %d | start address: %d | end address: %d | parition no: %d | from cell %d to cell %d\n",
	block->no, block->parts[currpart].startaddress, block->parts[currpart].endaddress, currpart, block->parts[currpart].startaddress%block->sz,
	block->parts[currpart].endaddress - block->parts[currpart].startaddress);
	block->currentpart+=1;
	//printf("Currentpart incremented to %d\n", block->currentpart);
	block->tempstartadd=block->parts[currpart].endaddress+1; //virtual start address will be after where the current partition ends
	//printf("-----changed block start to %d\n", block->tempstartadd);
	block->sz-=siz; //virtual block size reduced
	//printf("blocksize temp reduced to %d\n", block->sz);
}

int allocate(memblock *block, int siz, char pname){
    if (block->sz>0){
        //printf("blocksize is %d\n", block->sz);
        if(siz<block->sz){
            createPartition(block, siz);
            block->processes[block->currentpart-1]=pname;
            return 1;
        }
        else if(siz==block->sz){
            int currpart=block->currentpart;
            block->sz=0;
            block->parts[currpart].startaddress = block->startAdd;
            block->parts[currpart].endaddress = block->endAdd;
            printf("Allocated at entire block: %d | start address: %d | end address: %d\n", block->no, block->startAdd, block->endAdd);
            block->processes[block->currentpart]=pname;
            return 1;
        }
        else if(siz>block->sz){
            printf("Cannot allocate to block %d\n", block->no);
            return -1;
        }
    }
}


void printseq(char arr[]){
    for(int i=0; i<(sizeof(arr)/sizeof(arr[0])); i++){
        printf("%c ", arr[i]);
    }
}

void printBlocksFinal(){
    printf("\n----------------------\n");
    printf("Block\tState\tProcesses\n");
    for(int i=0; i<blockcount; i++){
        string statez;
        if (memblocks[i].sz==0){statez="F";}
        else if(memblocks[i].sz==blockszs[memblocks[i].no-1]){statez="E";}
        else {statez="PF";}
        cout<<"\n  "<<memblocks[i].no<<"\t "<<statez<<"\t ";
        printseq(memblocks[i].processes);
    }
    printf("\n----------------------\n");
}

void FF(int siz, char pname){
    printf("\n\nTrying to allocate %c (size %d)\n\n", pname, siz);
	for(int i=currentBlockIndex; i<blockcount; i++){
		int a=allocate(&memblocks[i], siz, pname);
		if(a==1){
			printf("Allocation success!\n\n");
			currentBlockIndex=i; //change currentblockindex to where the last item was allocated
			return;
		}
	}
	printf("Cannot allocate!\n\n");
}

void BF(int siz, int pname){
    printf("\n\nTrying to allocate %c (size %d)\n\n", pname, siz);
    int minsize=10000000000;
    memblock *minblock; //pointer to block to allocate
    for(int i=0; i<blockcount; i++){
        if (minsize>memblocks[i].sz && memblocks[i].sz>=siz){
            minblock=&memblocks[i];
            minsize=minblock->sz;
        }
    }
    int a=allocate(minblock, siz, pname);
    if(a==-1){printf("Cannot allocate!\n\n");}
}

void WF(int siz, char pname){
    printf("\n\nTrying to allocate %c (size %d)\n\n", pname, siz);
    int maxsize=-99;
    memblock *maxblock; //pointer to block to allocate
    for(int i=0; i<blockcount; i++){
        if (maxsize<memblocks[i].sz){
            maxblock=&memblocks[i];
            maxsize=maxblock->sz;
        }
    }
    int a=allocate(maxblock, siz, pname);
    if(a==-1){printf("Cannot allocate!\n\n");}
}

int nonnegint()
{
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

int main(){
    initBlocks();
    printf("----Blocks details:----\n");
    for(int i=0; i<blockcount; i++){
        printf("%d : size %d\n", memblocks[i].no,
        memblocks[i].sz);
    }
    int seqsize;
    printf("How many processes? ");
	seqsize=nonnegint();

    int seq[seqsize];
	//sequence input
	char startchar=65;
	for(int i=0; i<seqsize; i++){
        char charval=char(startchar++);
		printf("Enter size of process %c: ", charval);
        seq[i]=nonnegint();
	}

	int ask;
    printf("--------------PROGRAM RUN-----------\n");
    while(true){
        printf("\n\n\nWhich method do you want to use? \n1. First Fit\n2. Best Fit\n3. Worst Fit\n  Choice: ");
        ask=nonnegint();
        if (ask==1){
            int chars=65;
            for(int i=0; i<seqsize; i++){
                char charval=char(chars++);
                FF(seq[i], charval);
            }
            printBlocksFinal();
            break;
        }
        else if(ask==2){
            int chars=65;
            for (int i = 0; i < seqsize; i++) {
                char charval=char(chars++);
                BF(seq[i], charval);
            }
            printBlocksFinal();
            break;
        }
        else if(ask==3){
            int chars=65;
            for(int i=0; i<seqsize; i++){
                char charval=char(chars++);
                WF(seq[i], charval);
            }
            printBlocksFinal();
            break;
        }
        else{
            printf("Unrecognized input. Retry....");
        }
    }
}

