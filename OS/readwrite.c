#include <stdio.h>
#define maxbuffer 3
buffer = 0;
access = 0;
readcount=0;
char ar[maxbuffer];
ci=0;

void takeinput(){
    printf("Enter a character(only first character will be registered):\n");
    fflush(stdin);
    scanf("%c", &ar[ci]);
    ci+=1;
}
void giveoutput(){
    printf("output: %c\n", ar[0]);
    for(int i=0; i<ci-1; i++){
        ar[i]=ar[i+1];
    }
    ci-=1;

}
void read(){
    int r;
    printf("ReadStart(1) or ReadStop?(2)\n");
    scanf("%d", &r);
    if(r==1){
        if(access==0){
            if(buffer>0){
                readcount++;
                buffer-=1;
                giveoutput();
                printf("Read success.\n");
            }
            else{printf("Nothing to read!\n");}
        }
        else{printf("A process is still writing!\n");}
    }
    else if(r==2){
        if(readcount>0){
            if(access==0){
                readcount--;
                printf("Read count updated to %d\n", readcount);
            }
            else{printf("A process is writing!\n");}
        }
        else{printf("No process is reading!!\n");}
    }
    else{printf("Invalid input!\n");}
}

void write(){
    int w;
    printf("WriteStart(1) or WriteStop?(2)\n");
    scanf("%d", &w);
    if(w==1){
        if(readcount==0){
            if(access==0){
                if(buffer<maxbuffer){
                    access=1;
                    buffer+=1;
                    printf("Enter character:");
                    takeinput();
                    printf("Write success!\n");
                }
                else{printf("Buffer full! Read to clear buffer.\n");}
            }
            else{printf("A process is still writing!!\n");}
        }
        else{printf("%d process(es) is/are still reading!!\n", readcount);}
    }
    else if(w==2){
        if(access!=0){
            if(readcount==0){
                access=0;
                printf("Stopped writing!\n");
            }
            else{printf("%d process(es) is/are still reading!\n", readcount);}
        }
        else{printf("No process is writing!\n");}
    }
    else{printf("Invalid input!\n");}
}

int main(){
    int ask, loop=1;
    while(loop==1){
        fflush(stdin);
        printf("\nRead(1) or Write(2) or Stop(3)?: ");
        scanf("%d", &ask);
        switch(ask){
        case 1:
            read();
            break;
        case 2:
            write();
            break;
        case 3:
            printf("\nStopped");
            loop=0;
            break;
        default:
            printf("Incorrect input!\n");
        }
    }
    return 0;
}

