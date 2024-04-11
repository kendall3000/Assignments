#include <stdio.h>
int main(void)
{
 unsigned int value = 0x12345678;
 char *r = (char *) &value;
 int i;
 for(i=0; i<4; i++) {
 printf("Address of 0x%x = %u \n", r[i], &r[i]);
 }
 return 0;
}
