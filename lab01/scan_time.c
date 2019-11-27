#include <stdio.h>

int main(int argc, const char* argv[]){
  int count = 0;
  int sumOfMin = 0;
  double sumOfSec = 0;

  scanf("%d", &count);
  scanf("%d", &sumOfMin);
  scanf("%lf", &sumOfSec);
  printf("%lf \n", (sumOfMin*60.0 + sumOfSec)/count );
  return 0;
}
