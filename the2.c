#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_axiom(char **leftformula, int left_len,  char **rightformula, int right_len){
    int i, j;
    for(i=0; i<right_len; ++i){
        for(j=0; j<left_len; ++j){
           
            if(strcmp(*(leftformula+j),*(rightformula+i))==0){
                return 1;
            }
        }
    }
    return 0;
}



int continue_check(char **leftformula, int len_left, char **rightformula, int len_right){
    int i, j;

    for(i=0; i<len_left; ++i){
        for(j=0; j<strlen(leftformula[i]);++j){

            if(leftformula[i][j]=='&' || leftformula[i][j]=='|' || leftformula[i][j]=='>' || leftformula[i][j]=='-'  ){

                return 1;
            }
        }
    }
    for(i=0; i<len_right; ++i){

        for(j=0; j<strlen(rightformula[i]);++j){
            if(rightformula[i][j]=='&' || rightformula[i][j]=='|' || rightformula[i][j]=='>' ||rightformula[i][j]=='-'  ){
                return 1;
            }
        }
    }
    return 0;

}

int formula_generator(char *formula, char *oper, char**left, char**right){
    int i, j, count;
    if(formula[0]=='-'){
        for(i=0,count=0; formula[i]!=0; ++i){
            if( formula[i]=='('){
                count+=1;
            }
            if( formula[i]==')'){
                count-=1;
            }
            if (count==0 && (formula[i]=='>' || formula[i]=='|' || formula[i]=='&' )){
                break;
            }

        }
        if(formula[i]==0){
            count=i;
            *left=calloc(count+2,sizeof(char));
            *oper='-';
            for(i=1; i<count; ++i){
                (*left)[i-1]=formula[i];
            }
            *right=NULL;
            return 9;
        }



    }
    for(i=0,count=0; i<strlen(formula); ++i){
        if(formula[i]=='('){
            count+=1;
        }
        if(formula[i]==')'){
            count-=1;
        }
        if(formula[0]=='('){
            if(count==1 && (formula[i]=='&'|| formula[i]=='>'|| formula[i]=='|')){
                count=i;
                *oper=formula[i];
                break;
            }
        }
        if(formula[0]!='('){
            if(count==0 && (formula[i]=='&'|| formula[i]=='>'|| formula[i]=='|')){
                *oper=formula[i];
                count=i;
                break;
            }
        }
    }


    *left=calloc(count+1,sizeof(char*));
    if(formula[0]=='('){
        for(i=1; i<count; ++i){
            (*left)[i-1]=formula[i];
        }
        if(!formula[i])
        {
            *oper=0;
            *right=NULL;
            return 9;
        }
        for(i=count+1,j=0; formula[i]!=0; ++i){
            j+=1;
        }
        *right=calloc(j+1,sizeof(char));
        for(i=count+1,j=0; formula[i+1]!=0; ++i){
            (*right)[j]=formula[i];
            j+=1;
        }
    }
    else if(formula[0]!='('){
        for(i=0; i<count; ++i){
            (*left)[i]=formula[i];
        }
        if(!formula[i])
        {
            *oper=0;
            *right=NULL;
            return 9;
        }
        for(i=count+1,j=0; formula[i]!=0; ++i){
            j+=1;
        }
        *right=calloc(j+1,sizeof(char));
        for(i=count+1,j=0; i<strlen(formula); ++i){
            (*right)[j]=formula[i];
            j+=1;
        }
    }
    return 0;


}







int calculator(char **leftlist, int left_len, char **rightlist, int right_len){

    int i,temp_len, j, count, result;
    char oper, **temp, *left, *right;

    while(continue_check(leftlist, left_len, rightlist, right_len)){

        if(is_axiom(leftlist, left_len, rightlist, right_len)){
            break;
        }


        for(i=0; i<left_len; ++i){
            oper=0;
            formula_generator(leftlist[i],&oper,&left,&right);


            if(left[0]==0){
                continue;
            }
            

            if(oper=='&'){
                free(leftlist[i]);
                leftlist[i]=calloc(strlen(left)+1,sizeof(char));
                leftlist[i]=left;
                leftlist=realloc(leftlist,(left_len+2)*sizeof(char*));
                if(leftlist==0){
                    return 0;
                }
                leftlist[left_len]=calloc(strlen(right)+1,sizeof(char));
                leftlist[left_len]=right;
                leftlist[left_len+1]=0;
                left_len+=1;
                i-=1;

            }
            else if(oper=='-'){
                free(leftlist[i]);
                leftlist[i]=calloc(strlen(leftlist[left_len-1])+1,sizeof(char));
                leftlist[i]=leftlist[left_len-1];
                leftlist[left_len-1]=0;
                left_len-=1;
                rightlist=realloc(rightlist,(right_len+2)*sizeof(char*));
                if(rightlist==0){
                    return 0;
                }
                rightlist[right_len]=left;
                right_len+=1;
                

                i-=1;
            }
            if(oper=='>'){
                free(leftlist[i]);
                leftlist[i]=calloc(strlen(left)+strlen(right)+3,sizeof(char));
                strcat(leftlist[i],"-");
                strcat(leftlist[i],left);
                strcat(leftlist[i],"|");
                strcat(leftlist[i],right);
                i-=1;
            }

        }




        for(i=0; i<right_len; ++i){

            oper=0;
            formula_generator(rightlist[i],&oper,&left,&right);

            if(strlen(left)==0){
                continue;
            }



            if(oper=='|'){
                
                free(rightlist[i]);
                rightlist[i]=calloc(strlen(left)+1,sizeof(char));
                rightlist[i]=left;
                rightlist=realloc(rightlist,(right_len+2)*sizeof(char*));
                if(rightlist==0){
                    return 0;
                }
                rightlist[right_len]=calloc(strlen(right)+1,sizeof(char));
                rightlist[right_len]=right;
                rightlist[right_len+1]=0;
                right_len+=1;
                for(count=0; count<right_len; ++count){
                
                }
                i-=1;

            }

            else if(oper=='-'){
                free(rightlist[i]);
                rightlist[i]=calloc(strlen(rightlist[right_len-1])+1,sizeof(char));
                rightlist[i]=rightlist[right_len-1];
                rightlist[right_len-1]=0;
                right_len-=1;

                leftlist=realloc(leftlist,(left_len+2)*sizeof(char*));
                leftlist[left_len]=left;
                leftlist[left_len+1]=0;
                left_len+=1;

                i-=1;
            }


            if(oper=='>'){
                free(rightlist[i]);
                rightlist[i]=calloc(strlen(left)+strlen(right)+3,sizeof(char));
                strcat(rightlist[i],"-");
                strcat(rightlist[i],left);
                strcat(rightlist[i],"|");
                strcat(rightlist[i],right);
                free(left);
                free(right);
                i-=1;
            }



        }



        for(i=0; i<left_len; ++i){
            oper=0;
            formula_generator(leftlist[i],&oper,&left,&right);
            

            if(left[0]==0){
                continue;
            }

            if(oper=='|'){

                temp=calloc(left_len+1,sizeof(char*));
                for(j=0; j<left_len; ++j){
                    temp[j]=calloc(strlen(leftlist[j])+1,sizeof(char));
                    strcpy(temp[j],leftlist[j]);
                }


                free(leftlist[i]);
                leftlist[i]=calloc(strlen(left)+1,sizeof(char));
                leftlist[i]=left;
                
                free(temp[i]);
                temp[i]=calloc(strlen(right)+1,sizeof(char));
                temp[i]=right;
                

                result=( calculator(temp,left_len,rightlist,right_len)&&calculator(leftlist,left_len,rightlist,right_len) );
                for(count=0;count<left_len;++count){
                    free(temp[count]);
                }
                free(temp[count]);


                return result;

            }

        }


        for(i=0; i<right_len; ++i){
            oper=0;
            formula_generator(rightlist[i],&oper,&left,&right);
            
            if(left[0]==0){
                continue;
            }


            if(oper=='&'){

                temp=calloc(right_len+1,sizeof(char*));
                for(j=0; j<right_len; ++j){
                    temp[j]=calloc(strlen(rightlist[j])+1,sizeof(char));
                    strcpy(temp[j],rightlist[j]);
                }


                free(rightlist[i]);
                rightlist[i]=calloc(strlen(left)+1,sizeof(char));
                rightlist[i]=left;
                
                free(temp[i]);
                temp[i]=calloc(strlen(right)+1,sizeof(char));
                temp[i]=right;
                

                result=( calculator(leftlist,left_len,rightlist,right_len)&&calculator(leftlist,left_len,temp,right_len) );




                return result;

            }


        }









    }
    
    if(is_axiom(leftlist, left_len, rightlist, right_len)){
        return 1;
        }
    return 0;


}


int main()
{
    int i, lenleft, lenright, count, j, selen;
    char *mainlist, *leftlist, *rightlist,**leftformulas,**rightformulas;
    mainlist=calloc(201,sizeof(char));
    leftlist=calloc(201,sizeof(char));
    rightlist=calloc(201,sizeof(char));
    lenleft=0;
    lenright=0;
    scanf("%s", mainlist);
    for(i=0; *(mainlist+i)!='#'; ++i){
        *(leftlist+i)=*(mainlist+i);
        lenleft+=1;
    }

    if(strlen(leftlist)==0){
        leftlist[0]='!';
    }

    for(i+=1; *(mainlist+i)!='\0'; ++i){
        *(rightlist+lenright)=*(mainlist+i);
        lenright+=1;
    }

    if(strlen(rightlist)==0){
        rightlist[0]='$';
    }

    for(i=0, count=0; i<lenleft; ++i){
        if(*(leftlist+i)==','){
            count++;
        }
    }
    leftformulas=calloc((count+1),sizeof(char*));
    lenleft= count+1;

    for(i=0; *leftlist!=0; i++){
        if(*leftlist==','){
            leftlist+=1;
        }
        count=0;
        while( *(leftlist+count)!=',' && *(leftlist+count)!=0 ){
            count+=1;
        }
        *(leftformulas+i)=(char*)calloc(count+1,sizeof(char));
        j=0;
        while( j<count ){
            *(*(leftformulas+i)+j)=*leftlist;
            leftlist+=1;
            j +=1;
        }
    }




    for(i=0, count=0; i<lenright; ++i){
        if(*(rightlist+i)==','){
            count++;
        }
    }
    rightformulas=calloc((count+1),sizeof(char*));
    lenright= count+1;


    for(i=0; *rightlist!=0; i++){
        if(*rightlist==','){
            rightlist+=1;
        }
        count=0;
        while( *(rightlist+count)!=',' && *(rightlist+count)!=0 ){
            count+=1;
        }

        *(rightformulas+i)=(char*)calloc(count+1,sizeof(char));

        j=0;
        while( j<count ){
            *(*(rightformulas+i)+j)=*rightlist;
            rightlist+=1;
            j +=1;
        }
    }
    selen=calculator(leftformulas,lenleft,rightformulas,lenright);


    if(selen==1){
        printf("T\n");
    }

    else if(selen==0){
        printf("F\n");
    }

    return 0;
}
