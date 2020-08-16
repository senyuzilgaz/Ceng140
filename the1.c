#include<stdio.h>
#include"loop.h"
int startt[57] ;
int current[57] ;
int endd[57] ;
int jumpp[57] ;
int countlist[57] ;
int check, control, checkx;
int k, j, count;
int main(){
int start, end, jump ;
char variable ;
int a ;
control= 0 ;
check= 0 ;
count= 0;

    while(1){
        int cha = getchar() ;
        if( cha == EOF ){
            break;
        }
        else{

            ungetc(cha,stdin);
            scanf(" %c %d %d %d", &variable, &start, &end, &jump);
            if((start>end && jump>=0) || (start<end && jump<=0) ){
                check = -1 ;
            }
            if(variable<92){
                a=variable-65;
            }
            else{
                a=variable-71;
            }
            startt[a] = start ;
            current[a] = start ;
            endd[a] = end ;
            jumpp[a] = jump ;
            countlist[count] = a ;
            count +=1 ;
        }
    }
    if (check == -1){
        return -1 ;
    }
    j = count-1 ;

    while(1){
         if( j==count-1 && current[countlist[j]]==startt[countlist[j]] && control==0 ){
            loop_execute();
            if(checkx==5){
                return 0 ;
            }
        }
        if (control==1){
            control=0;
        }
        k=countlist[j] ;

        while(((startt[k]<endd[k])&&((current[k]+jumpp[k])>endd[k])) || ((startt[k]>endd[k])&&((current[k]+jumpp[k]<endd[k]) )) || startt[k]==endd[k]){

            if(j==0){
                break ;
            }
            current[k]=startt[k];
            j= j-1 ;

            k=countlist[j] ;

            if(j==0){
                break ;
            }
        }
        k=countlist[j];
        if( ((startt[k]<endd[k])&&((current[k]+jumpp[k])>endd[k])) || ((startt[k]>endd[k])&&((current[k]+jumpp[k]<endd[k]) )) || startt[k]==endd[k]) {
            if(j==0){
                break ;
            }
            current[k]=startt[k];
            j= j-1 ;
        }
        k=countlist[j];
        current[k]+=jumpp[k];
         if( j==count-1 ){
            loop_execute();
            if(checkx==5){
                return 0 ;
            }
        }
        if(startt[k]==endd[k]){
            if(j==0){
            break ;
        }
            j= j-1 ;
        }

        else if( (j!=count-1)  && (current[k]!=startt[k]) ){
            j=count-1;
        }
    }
    return 0 ;
}
int loop_variable_value(char c) {
    int s ;
    if(c<92){
        s=c-65;
    }
    else{
        s=c-71;
    }
    return current[s];
}
void loop_continue(char c){
    int s, x, i ;
    if(c<92){
        s=c-65;
    }
    else{
        s=c-71;
    }
    for(x=0;x<=count-1;x++){
        if(countlist[x]==s){
            break ;
        }
    }
    for(i=x+1; i<=count-1; i++){
        current[countlist[i]]=startt[countlist[i]];
    }
    j=x;
    return ;

}
