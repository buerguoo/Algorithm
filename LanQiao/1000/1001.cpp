#include <iostream>
using namespace std;
int main()
{
  int n, m1 = 0, m2 = 0, tp;
  scanf("%d", &n);
  for(int i = 0;i < n;++i){
      scanf("%d", &tp);
      if(tp >= 65) m1++;
      if(tp >= 85) m2++;
  }
  printf("%.0lf%%\n%.0lf%%\n", 1.0*m1/n*100, 1.0*m2/n*100);
  return 0;
}