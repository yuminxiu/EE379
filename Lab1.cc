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
    }
        float y = sum/num;
        printf("%f \n", y);
}


#include <stdio.h>
#include <math.h>

int main()
{
    float degree;
    int term;
    
    float sum = 1;
    float y = 1;
    
    printf("Enter angle in degree: \n");
    scanf("%f", &degree);
    float x = degree * M_PI/180;
    
    printf("How many terms? \n");
    scanf("%d", &term);
    
    
    
    for (int i = 1; i < term; i++){

        
        y *= (-x*x)/((2*i-1)*(2*i));
        sum = y + sum;
        
    }
    
    printf("math.h cos(%f) is %f.\nTaylor cos(%f), %d terms is %f\n", degree, cos(x), degree, term, sum );
    
    return 0;
}



#include <stdio.h>

int main(){

	int a[5];
	int store;

	printf("Enter five numbers: \n");
	for (int i = 0; i<5; i++){
		scanf("%d", &a[i]);
	}

	for (int j = i +1; j<5; j++){
		if (a[j] < a[i]){
		store = a[i];
		a[i] = a[j];
		a[j] = store;
		}
	for (int i = 0; i < 5; i++){
	printf("%d ", a[i]);
}

return 0;
}
