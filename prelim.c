#include <stdio.h>

int main ()
{
    int task;
    
    scanf("%d", &task);

    if(task == 1) {
        long double bank;
        float ec, dc;
        int numtran, i;
        scanf("%Lf %f %f", &bank , &ec , &dc );
        scanf("%d", &numtran );
        for(i=0; i<numtran; i++){
            char type1, currency;
            float amount;
            scanf(" %c %c %f", &type1, &currency, &amount);
            if (type1 == 'D' && currency == 'D'){
                    bank += (dc*amount) ;
                    
            }else if (type1 == 'D' && currency == 'E'){
                    bank += (ec*amount) ;
                    
                    
            }else if (type1 == 'W' && currency == 'D'){
                    bank -= (dc*amount) ;
                    
                    
            }else if (type1 == 'W' && currency == 'E'){
                    bank -= (ec*amount) ;
                    
                    
            }
        }printf("Final balance: %.2Lf TL.",bank);
        
            
    } else if(task == 2) {
        
        char exam, sub_exam;
        float penalty, total_score;
        int lesson1, lesson2,lesson3, lesson4;
        float value1, value2, value3, value4;
        scanf(" %c", &exam);
        if(exam=='T'){
            
            scanf(" %f", &penalty);
            scanf(" %d %f %d %f %d %f %d %f", &lesson1, &value1, &lesson2, &value2, &lesson3, &value3, &lesson4, &value4);
            
            total_score=lesson1*value1-(40-lesson1)*penalty*value1+lesson2*value2-(40-lesson2)*penalty*value2+lesson3*value3-(40-lesson3)*penalty*value3+lesson4*value4-(40-lesson4)*penalty*value4;
            
            printf("T result: %.2f points.", total_score);
        }
        else if(exam=='A'){
            
            scanf(" %c %f", &sub_exam, &penalty);
            if(sub_exam=='E'){
                scanf(" %d %f %d %f %d %f %d %f", &lesson1, &value1, &lesson2, &value2, &lesson3, &value3, &lesson4, &value4);
                total_score=lesson1*value1-(30-lesson1)*penalty*value1+lesson2*value2-(30-lesson2)*penalty*value2+lesson3*value3-(30-lesson3)*penalty*value3+lesson4*value4-(30-lesson4)*penalty*value4;
                printf("A-E result: %.2f points.", total_score);
            }
            if(sub_exam == 'O' || sub_exam== 'C'){
                scanf(" %d %f %d %f", &lesson1, &value1, &lesson2, &value2);
                total_score=lesson1*value1-(30-lesson1)*penalty*value1+lesson2*value2-(30-lesson2)*penalty*value2;
                printf("A-%c result: %.2f points.", sub_exam, total_score);
            }            
        }        
    }
    return 0;
}
