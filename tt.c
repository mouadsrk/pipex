#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>

int main() {
   char *a , *b ,*c;

   b = malloc(5);
   c = malloc (7);
   b[0] = 'm';
   b[1] = 'o';
   b[2] = 'u';
   b[3] = 'a';
   b[4] = '\0';
   a = b;
   printf("%s",a);
   free(b);
   // free(a);
   printf("%s",b);
   while(1)
   {}
}
