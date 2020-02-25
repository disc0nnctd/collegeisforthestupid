#include<stdio.h>
#include<iostream>

int maxR[]={2, 3, 4, 3}; //max resources since resources are limited
int req[4][4]={{2, 2, 1, 0}, //predefined required resources for processes
                   {3, 2, 1, 0},
                   {4, 0, 2, 3},
                   {1, 1, 3, 2}
};
int avail[]={2, 3, 4, 1}; //available resources
int uin[4], sequencein[10], siz=4;
int alloc[4][4];

int checkAvail(int n){ //n is process
    int available=1;
    for(int i = 0; i< 4; i++){
        if(req[i][n] > avail[i]){
                available=0;
                break;
        }
    }
    return available;
}

void allocate(int n){ //run if checkAvail returns true, n is process
    printf("Allocated!");
    for(int i = 0; i<4; i++){
        alloc[i][n] = alloc[i][n] + req[i][n]; //allocate resources
        avail[i] = avail[i]-req[i][n]; //reduce available
    }
}

void resetAvail(){
    for(int i=0; i<4; i++){
        avail[i]=maxR[i];
    }
}


void remProcess(){
    for(int i=0; i<siz-1; i++){
            uin[i]=uin[i+1];
    }
    siz=siz-1;
}

void deallocate(int n){
    printf("Deallocated!");
    for(int i = 0; i<4; i++){
        alloc[i][n] = alloc[i][n] - req[i][n]; //deallocate
        avail[i] = avail[i] + req[i][n]; //add to available
    }
    remProcess();
}

void manualAllocate(){
    for(int i=0; i<4; i++){
        printf("How many Resource %d allocated to\n", i+1);
        for(int j=0; j<4; j++){
            printf("Process %d: ", j+1);
            scanf("%d", &alloc[i][j]);
            if (alloc[i][j]>req[i][j]){printf("Cannot allocate more than required!"); return;}
        }
    }
}

void enterSeq(){
    printf("How many processes to enter in the sequence?");
        int ask;
        scanf("%d", &ask);
        if(ask<10){
            for(int i=0; i<ask; i++){
                printf("Enter process %d: ", i+1);
                scanf("%d", &uin[i]);
            }
        }
        else printf("Max is 10");
    siz=sizeof(uin)/sizeof(uin[0]);
}

int safety(int proc){
    int available;
    printf("At %d\n", proc);
    int n = proc-1;
    available = checkAvail(n);
    if (available){
            printf("Safe!\n");
            allocate(n);
        return 1;
    }
    else{
        printf("Unsafe!\n");
        return -1;
    }
}



void Final(){
    int tempar[4];
    for(int i=0; i<4; i++){tempar[i]=uin[i];}
    while(siz>0){
        int c=0;
        int a=safety(uin[0]);
        if(a==-1){
            c+=1;
        }
        if(c==5){
            deallocate(tempar[siz-1]);
        }

    }
}
int main(){
    for (int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            alloc[i][j]=0;
        }
    }
    for(int i=0; i<4; i++){for(int j=0; j<4; j++){alloc[i][j]=0;}}
    for(int i=0; i<4; i++) {
        printf("For resource %d\n", i+1);
        for(int j=0; j<4; j++){
            printf("Enter qty for process %d: ", j+1);
            scanf("%d", &req[i][j]);
            if (req[i][j]>maxR[i]){printf("Cannot be more than max."); return -1;}
        }
    }
    enterSeq();
    Final();
}
