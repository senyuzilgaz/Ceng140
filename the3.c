#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define isNumber(o) ( ( (o)>='0' && (o)<='9') || (o)=='.' )
#define isLeftass(o) ((o)=='+' || (o)=='-' || (o)=='*' || (o)=='/')
#define isRightass(o) ((o)=='^')
#define isFunction(o) ((o)=='c' || (o)=='s' || (o)=='k' || (o)=='l' || (o)=='~')
#define isHigh(o) ((o)=='*' || (o)=='/')
#define isLow(o) ((o)=='+' || (o)=='-')
#define isLetter(o) ((o)>='A' && (o)<='Z')
#define isParant(o) ((o)=='(' || (o)==')')
#define isOperator(o) (isLeftass((o)) || isRightass((o)) || (o)=='(' || (o)==')' || isFunction((o)))

char mainlist[205];
float letterlist[27];
float bounds[26][2];
int *letters;

int draw(int**prob_list, int letter, int in){
    int number, i, interval;
    float part,k;
    part=(bounds[letter-'A'][1]-bounds[letter-'A'][0])/in;
    number=rand()%1000;
    for(i=0; i<in; ++i){
        if(i==0){
            if(number<prob_list[letter-'A'][i]){
                interval=i;
                break;
            }
        }
        else if( number>=prob_list[letter-'A'][i-1] && number<prob_list[letter-'A'][i]){
                interval=i;
                break;
        }
    }


    number=rand()%((int)(part*1000));
    k=((float)number/1000.000);
    letterlist[letter-'A']=bounds[letter-'A'][0]+interval*part+k;

    return 1;

}


float postfix_eval(char **postfix, int plen){

    int i,cur,slen=0;
    float *stack;
    float sum=0;
    stack=calloc(plen+1,sizeof(float));
    for(i=0; i<plen; ++i){
        cur=postfix[i][0];

        if(isOperator(cur)&& (!isFunction(cur))){

            if(cur=='+'){
                stack[slen-2]=stack[slen-2]+stack[slen-1];
                slen--;
            }
            else if(cur=='-'){
                stack[slen-2]=stack[slen-2]-stack[slen-1];
                slen--;
            }
            else if(cur=='*'){
                stack[slen-2]=stack[slen-2]*stack[slen-1];
                slen--;
            }
            else if(cur=='/'){
                stack[slen-2]=stack[slen-2]/stack[slen-1];
                slen--;
            }
            else if(cur=='^'){
                if(stack[slen-2]<0){
                    stack[slen-2]=-1*pow(-1*stack[slen-2],stack[slen-1]);
                    slen--;
                }
                else{
                    stack[slen-2]=pow(stack[slen-2],stack[slen-1]);
                    slen--;
                }
            }
        }

        else if (isFunction(cur)){
            if(cur=='k'){
                stack[slen-1]=sqrt(stack[slen-1]);
            }
            if(cur=='s'){
                stack[slen-1]=sin(stack[slen-1]);
            }
            if(cur=='c'){
                stack[slen-1]=cos(stack[slen-1]);
            }
            if(cur=='l'){
                stack[slen-1]=log(stack[slen-1]);
            }
            if(cur=='~'){
                stack[slen-1]=(stack[slen-1])*(-1);
            }
        }

        else if(isLetter(cur)){
            stack[slen]=letterlist[cur-'A'];
            slen++;
        }
        else if(isNumber(cur)){
            stack[slen]=atof(postfix[i]);
            slen++;
        }
    }
    sum=stack[slen-1];
    free(stack);
    return sum;

}





int main()
{
    int i,j,k,slen=0,plen=0,int_num, **prob_list, lc=0;;
    long int exp,e;
    char **stack, **postfix, letter;
    float temp,a,start,end,*results,max,min,*intervals;
    double *int_results;
    srand(time(0));
    fgets (mainlist, 205, stdin);


    for(i=0;i<26;++i){
        if(strchr(mainlist,('A'+i))!=NULL){
            lc++;
        }
    }
    letters=calloc(lc,sizeof(int));
    for(i=0,j=0;i<26;++i){
        if(strchr(mainlist,('A'+i))!=NULL){
            letters[j++]=('A'+i);
        }
    }



    for(i=0, j=0, k=0; i<strlen(mainlist); ++i ){
        if(mainlist[i]==32){
            continue;
        }
        if( isOperator(mainlist[i]) ){
            j++;
        }
        if( isLetter(mainlist[i])){
            k++;
        }
        if( isNumber(mainlist[i]) ){
            k++;
            while(isNumber(mainlist[i+1])){
                ++i;
            }
        }
    }

    stack=calloc(j,sizeof(char*));
    postfix=calloc(j+k,sizeof(char*));

    for(i=0, j=0, k=0; i<strlen(mainlist); ++i ){
        if(mainlist[i]==32){
            continue;
        }
        if( isOperator(mainlist[i]) ){
            if (isParant(mainlist[i])){
                if( mainlist[i]=='(' ){
                stack[slen]=calloc(2,sizeof(char));
                stack[slen][0]=mainlist[i];
                slen++;
                }
                else if(mainlist[i]==')'){
                    while(stack[slen-1][0]!='('){
                        postfix[plen]=calloc(2,sizeof(char));
                        postfix[plen][0]=stack[slen-1][0];
                        free(stack[slen-1]);
                        plen++;
                        slen--;
                    }
                    free(stack[slen-1]);
                    slen--;
                    if(slen!=0){
                        postfix[plen]=calloc(2,sizeof(char));
                        postfix[plen][0]=stack[slen-1][0];
                        free(stack[slen-1]);
                        plen++;
                        slen--;
                    }

                }
            }
            else if( isFunction(mainlist[i])){
                if(mainlist[i]=='s' && mainlist[i+1]=='q' ){
                    stack[slen]=calloc(2,sizeof(char));
                    strcat(stack[slen],"k");
                    slen++;
                }
                else if(mainlist[i]=='s' && mainlist[i+1]=='i' ){
                    stack[slen]=calloc(2,sizeof(char));
                    strcat(stack[slen],"s");
                    slen++;
                }
                else if(mainlist[i]=='c' ){
                    stack[slen]=calloc(2,sizeof(char));
                    strcat(stack[slen],"c");
                    slen++;
                }
                else if(mainlist[i]=='l' ){
                    stack[slen]=calloc(2,sizeof(char));
                    strcat(stack[slen],"l");
                    slen++;
                }
                else if(mainlist[i]=='~' ){
                    stack[slen]=calloc(2,sizeof(char));
                    strcat(stack[slen],"~");
                    slen++;
                }
            }
            else{
                if(isRightass(mainlist[i])){
                    while(slen>=1){
                        while( isRightass(stack[slen-1][0])){
                            postfix[plen]=calloc(2,sizeof(char));
                            postfix[plen][0]=stack[slen-1][0];
                            free(stack[slen-1]);
                            plen++;
                            slen--;
                            if(slen==0){
                                    break;
                            }
                        }
                        break;
                    }
                    stack[slen]=calloc(2,sizeof(char));
                    stack[slen][0]=mainlist[i];
                    slen++;

                }
                else if(isHigh(mainlist[i])){
                    while(slen>=1){
                        while( isHigh(stack[slen-1][0]) || isRightass(stack[slen-1][0])){
                            postfix[plen]=calloc(2,sizeof(char));
                            postfix[plen][0]=stack[slen-1][0];
                            free(stack[slen-1]);
                            plen++;
                            slen--;
                            if(slen==0){
                                break;
                            }
                        }
                        break;
                    }
                    stack[slen]=calloc(2,sizeof(char));
                    stack[slen][0]=mainlist[i];
                    slen++;

                }
                else if(isLow(mainlist[i])){
                    while(slen>=1){
                        while( isRightass(stack[slen-1][0]) || isLeftass(stack[slen-1][0])){
                            postfix[plen]=calloc(2,sizeof(char));
                            postfix[plen][0]=stack[slen-1][0];
                            free(stack[slen-1]);
                            plen++;
                            slen--;
                            if(slen==0){
                                break;
                            }
                        }
                        break;
                    }
                    stack[slen]=calloc(2,sizeof(char));
                    stack[slen][0]=mainlist[i];
                    slen++;
                }


            }



        }
        else if( isLetter(mainlist[i])){
            postfix[plen]=calloc(2,sizeof(char));
            postfix[plen][0]=mainlist[i];
            plen++;
        }
        else if( isNumber(mainlist[i]) ){
            j=i;
            while(isNumber(mainlist[++j])){
                k++;
            }
            postfix[plen]=calloc(k+1,sizeof(char));
            k=0;
            while(isNumber(mainlist[i+1])){
                postfix[plen][k++]=mainlist[i++];
            }
            postfix[plen][k]=mainlist[i];
            plen++;

        }
    }
    while(slen>=1){
        postfix[plen]=calloc(strlen(stack[slen-1]),sizeof(char));
        strcat(postfix[plen],stack[slen-1]);
        free(stack[slen-1]);
        slen--;
        plen++;
    }
    free(stack);

    scanf("%d  %ld", &int_num, &exp);
    prob_list=calloc(27,sizeof(int*));
    results=calloc(exp+1,sizeof(float));
    for(i=0; i<27; ++i){
        prob_list[i]=calloc(int_num+1,sizeof(int));
    }



    for(j=0; j<lc; ++j){

        scanf(" %c", &letter);
        scanf("%f %f", &start, &end);
        bounds[letter-'A'][0]=start;
        bounds[letter-'A'][1]=end;

        for(i=0;i<int_num;++i){
            scanf("%f", &temp);
            if(i==0){
                a=temp*1000;
                prob_list[letter-'A'][i]=(int)a;
            }
            else{
                a=temp*1000;
                prob_list[letter-'A'][i]=(int)a+prob_list[letter-'A'][i-1];
            }
        }


    }

    for(i=0,e=0;i<exp;++i){

        for(j=0;j<lc;++j){
            draw(prob_list,letters[j],int_num);
        }
        results[e]=postfix_eval(postfix,plen);


        if(e==0){
            max=results[e];
            min=results[e];
        }
        else{
            if(results[e]>max){
                max=results[e];
            }
            if(results[e]<min){
                min=results[e];
            }
        }
        ++e;

    }
    free(letters);
    free(postfix);

    a=(max-min)/int_num;
    intervals=calloc(int_num,sizeof(float));
    int_results=calloc(int_num,sizeof(double));
    intervals[0]=min+a;
    for(i=1;i<int_num;++i){
        intervals[i]=intervals[i-1]+a;
    }
    for(e=0;e<exp;++e){
        for(i=0;i<int_num;++i){
            if(i==0){
                if(results[e]<intervals[0]){
                    int_results[0]+=1;
                }
            }
            else{
                if(results[e]>=intervals[i-1] && results[e]<intervals[i]){
                    int_results[i]+=1;
                }
            }
        }
    }
    free(results);
    free(intervals);

    printf("%.3f %.3f", min, max);
    for(i=0;i<int_num;++i){
        printf(" %.3f",int_results[i]/exp);
    }

    free(int_results);






    return 0;
}
