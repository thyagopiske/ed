#include "stdio.h"
#include "stdlib.h"
#include "string.h"

long long int power(int base, int exp) {
  long long int result = 1;
  for (int i = 0; i < exp; i++) {
      result *= base;
  }
  return result;
}

unsigned long long hash(char *str, int base) 
{
  unsigned long long hash = 0;

  int i = strlen(str) - 1;
  for (int j = 0; j < strlen(str); j++, i--)
  {
    int c = (int) str[j];
    hash += c*power(base, i);
  }
  
  return hash;
}

int main() 
{
  int n, base;

  scanf("%d %d", &base, &n);

  for (int i = 0; i < n; i++)
  {
    char str[20];
    scanf("\n%s", str);
    unsigned long long h = hash(str, base);
    printf("%llu\n", h);
  }

  return 0;
}