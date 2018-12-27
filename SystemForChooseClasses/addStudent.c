#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void addStudent(){
    char pass[20] = "123456";
    char input[20];
    printf("please input the pass code:  ");
    scanf("%s", input);
    if(strcmp(input, pass)){
        printf("ok!\n");
    }
    else printf("fail!\n");
    return;
}
