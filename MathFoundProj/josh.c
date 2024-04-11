# include <stdio.h>
# include <math.h>

int find_passwords(int m, int n)
{

    return (int)(pow(26, m) * pow(10, n));

}

//m represents the 26 letters in the alphabet
//n represents the 10 numbers 
int main()
{
    
    int n, m;
    printf("Enter the amount of letters for password: ");
    scanf("%d", &n);
    printf("Enter the amount of digits for the password: ");
    scanf("%d", &m);
    printf( "Total number of possible passwords are: ");
    find_passwords(m,n);
    printf("%d", find_passwords(m,n));
    printf("\n");
    int res = 0;
    for (int i = 0; i <= n; i++)
    {
        res += find_passwords(m, i);
    }
    //Possible number of passwords with m letters at the most of n digits
    printf("Total possible passwords if at most n digits are present: %d \n", res);
    res = 0;
    
    for (int i = 0; i <= m; i++)
    {
 //Total result for final answer
        res += find_passwords(i, n);
    }
    printf("Total possible passwords if at most m letters are present: %d\n", res);

}