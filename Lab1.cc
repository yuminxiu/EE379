#include <stdio.h>

int main()
{
    int num;
    
    printf("Enter an odd number: \n");
    scanf("%d", &num);
    
    if (num % 2 == 0){
        printf("Error! That is not an odd number.\n");
    }
    else {
        for(int row = 0; row <num; row++){
            int star = 2 * row + 1;
            int indent = num - row - 1;
            
            for(int i = 0; i<indent; i++)
            printf(" ");
            
            for (int i = 0; i < star; i++) 
            printf("*");
            printf("\n");
        }
    }

    return 0;
}


// problem 3

int main()
{
    int num;
    printf("Enter the amount of numbers: \n");
    scanf("%d", &num);
    
    float sum = 0;
    for(int i = 0; i < num; i++){
        float x;
        printf("Enter number %d: \n", i+1);
        scanf("%f", &x);
        sum += x;
        
        float y = sum/num;
        printf("%f \n", y);
    }
}
