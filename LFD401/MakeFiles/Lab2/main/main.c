#include "addHeader.h"
#include "mulHeader.h"
int main(){

	int num1 , num2;
	printf("Enter the two numbers for add, sub, mul and division operation\n");
	scanf("%d%d",&num1, &num2);
	printf("The addition of two numbers are %d\n",add(num1, num2));
	printf("The subtraction of two numbers are %d\n",sub(num1, num2));
	printf("The multiplication of two numbers are %d\n",mul(num1, num2));
	if(num2 == 0){
		printf("Divide by zero is not allowed\n");
	}
	printf("The division of two numbers are %d\n",div(num1, num2));
	return 0;


}
