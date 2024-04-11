# include <stdio.h>
# include <math.h>

// A function to print all prime factors of a given number n
void primeFactors(int i){
    //Print the number of 2s that divide n
    while (i%2 == 0){
        printf("%d ", 2);
        i = i/2;
    }
    /*n must be odd at this point.  So we can skip one element (Note i = i +2)*/
    for (int r = 3; r <= sqrt(i); r = r+2){
        // While i divides n, print i and divide n
        while (i%r == 0){
            printf("%d ", r);
            i = i/r;
        }
    }
    // This condition is to handle the case when n is a prime number greater than 2
    if (i > 2)
    printf ("%d ", i);
}

//A function to print the gcd of the two integers
void gcd(int num1, int num2){
    int i, gcd;

    for(i=1; i <= num1 && i <= num2; ++i)
    {
        // Checks if i is factor of both integers
        if(num1%i==0 && num2%i==0)
            gcd = i;
    }

    printf("G.C.D of %d and %d is %d \n", num1, num2, gcd);

}
//A function to print the lcm of the two integers
void lcm(int num1, int num2){
    int max;

    // maximum number between n1 and n2 is stored in max
    max = (num1 > num2) ? num1 : num2;

    while (1) {
        if ((max % num1 == 0) && (max % num2 == 0)) {
            printf("The LCM of %d and %d is %d.", num1, num2, max);
            break;
        }
        ++max;
    }
}

int find_passwords(int m, int n){
    return (int)(pow(26, m) * pow(10, n));
}

/* Driver program to test above function */
int main(){
    char choice = 'Y';
    int n=0;
    int m=0;
    int num1 = 0;
    int num2 = 0;
    int mainOpt;
    int res = 0;

    do{
        if(choice == 'Y'){
            printf("Main menu: Pick an option (1-9) ");
            printf("\n(1)Select New Integers");
            printf("\n(2)Select New Number of Possible Passwords");
            printf("\n(3)Find the Prime Factors");
            printf("\n(4)Find GCD");
            printf("\n(5)Find LCM");
            printf("\n(6)Find Total Number of Possible Passwords");
            printf("\n(7)Find Total Number of Possible Passwords if at most M Digits in the Password");
            printf("\n(8)total number of possible passwords if at most N letters in the password");
            printf("\n(9)All of the above");
            printf("\n(10)Exit\n");
            printf("Option: ");
            scanf("%d", &mainOpt);
        }
        if((mainOpt != 1) && (mainOpt != 2) && (mainOpt !=3)&&(mainOpt !=4) && (mainOpt != 5)&& (mainOpt != 6)&& (mainOpt != 7)&& (mainOpt != 8)&& (mainOpt != 9)&& (mainOpt != 10)){
            printf("Error: Please pick an option (1-9) only ");
        }
        if(mainOpt == 10){
            printf("You will now be exiting the main menu. \n");
            break;
        }
        if(mainOpt == 1){//picks integers
            printf("Enter two positive integers.\n");
            printf("Enter integer 1: ");
            scanf("%d", &num1);
            printf("Enter integer 2: ");
            scanf("%d", &num2);
        }
        if(mainOpt == 2){//picks possible passwords 
            printf("Enter the amount of letters for password: ");
            scanf("%d", &n);
            printf("Enter the amount of digits for the password: ");
            scanf("%d", &m);
        }
        if(mainOpt == 3){//finds prime factors
            printf("Prime factors of %d: ", num1);
            primeFactors(num1);
            printf("\n");
            printf("Prime factors of %d: ", num2);
            primeFactors(num2);
            printf(" \n");
        }
        if(mainOpt == 4){//finds gcd
            gcd(num1,num2);
            printf("\n");
        }
        if(mainOpt == 5){//finds lcm
            lcm(num1,num2);
            printf("\n");
        }
        if(mainOpt == 6){//Finds Total Number of Possible Passwords
            printf( "Total number of possible passwords are: ");
            find_passwords(m,n);
            printf("%d", find_passwords(m,n));
            printf("\n");
        }
        if(mainOpt == 7){ //Find Total Number of Possible Passwords if at most M Digits in the Password
            res = 0;
            for (int i = 0; i <= m; i++){
            //Total result for final answer
                res += find_passwords(i, n);
            }
            printf("Total possible passwords if at most m letters are present: %d\n", res);
        }
        if(mainOpt == 8){//Find Total Number of Possible Passwords if at most N Digits in the Password
            res = 0;
            for (int i = 0; i <= n; i++){
                res += find_passwords(m, i);
            }
            //Possible number of passwords with m letters at the most of n digits
            printf("Total possible passwords if at most n digits are present: %d \n", res);
            res = 0;
        }
        if(mainOpt == 9){
            printf("Enter two positive integers.\n");
            printf("Enter integer 1: ");
            scanf("%d", &num1);
            printf("Enter integer 2: ");
            scanf("%d", &num2);
            printf("Prime factors of %d: ", num1);
            primeFactors(num1);
            printf("\n");
            printf("Prime factors of %d: ", num2);
            primeFactors(num2);
            printf(" \n");
            gcd(num1,num2);
            printf("\n");
            lcm(num1,num2);
            printf("\n");
            printf("Enter the amount of letters for password: ");
            scanf("%d", &n);
            printf("Enter the amount of digits for the password: ");
            scanf("%d", &m);
            printf( "\nTotal number of possible passwords are: ");
            find_passwords(m,n);
            printf("%d", find_passwords(m,n));
            printf("\n");
            printf( "Total number of possible passwords are: ");
            find_passwords(m,n);
            printf("%d", find_passwords(m,n));
            printf("\n");
            for (int i = 0; i <= n; i++){
                res += find_passwords(m, i);
            }
            //Possible number of passwords with m letters at the most of n digits
            printf("Total possible passwords if at most n digits are present: %d \n", res);
            res = 0;
            
            for (int i = 0; i <= m; i++){//Total result for final answer
                res += find_passwords(i, n);
            }
            printf("Total possible passwords if at most m letters are present: %d\n", res);

        }

        printf("Do you want to continue to the main menu? ");
        scanf(" %c", &choice);
        printf("\n");
        if((choice == 'Y') || (choice == 'N')){
            if(choice == 'N'){
                break;
            }
        }else{
            printf("Error: Please enter Y or N only ");
        }

    }while(choice == 'Y');
    printf("\n");
    printf("Created by < Kendall Ramos & Joshua Mayfield >\n");
    printf("Thank You.\n");
    printf("\n");
    return 0;
}