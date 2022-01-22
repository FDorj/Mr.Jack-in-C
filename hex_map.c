#include <stdio.h>

int main(){
    int i, j;
    for(i=0;i<9;i++){
        if(i==0){
            for(j=0;j<13;j++){
                if(j%2==0){
                    printf("  ______  ");
                }else{
                    printf("      ");
                }
            }
        }
        printf("\n");
        for(j=0;j<13;j++){
            if(j%2==0){
                printf(" /      \\ ");
            }else{
                printf("      ");
            }
        }
        printf("\n");
        for(j=0;j<13;j++){
            if(j%2==0){
                printf("/        \\");
            }else{
                printf("______");
            }
        }
        printf("\n");
        for(j=0;j<13;j++){
            if(j%2==0){
                printf("\\        /");
            }else{
                printf("      ");
            }
        }
        printf("\n");
        for(j=0;j<13;j++){
            if(j%2==0){
                printf(" \\______/ ");
            }else{
                printf("      ");
            }
        }

    }

    return 0;
}