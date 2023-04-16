#include <stdio.h>
#include "../../steltype.h"

int main()
{
  for (;;)
  {
    double temp;

    printf("Test temp: ");
    scanf("%lf", &temp);
    
    printf("find_star_class %lf -> %s\n", temp, find_star_class(temp));
  }

  return 0;
}
