#include <cstdio>

using namespace std;

const int p2[4]={6,2,4,8};
const int p3[4]={1,3,9,7};

int n,f2,f3,f5,f7,f9;

int main() {
  freopen("fact.in","r",stdin);
  freopen("fact.out","w",stdout);
  while (scanf("%d",&n)!=EOF) {
    f2 = f3 = f5 = f7 = f9 = 0;
    while (n>0) {
      for (int i = n; i>0; i /= 5) {
        int p = i/10,q = i%10;
        f3 += p+(q>=3);
        f5 += p+(q>=5);
        f7 += p+(q>=7);
        f9 += p+(q>=9);
      }
      f2 += n/2;
      n /= 2;
    }
//    printf("%d %d %d %d %d\n",f2,f3,f5,f7,f9);
    long long tmp = (long long)f3+2*f9+3*f7;
    if (f2==f5) printf("%d\n",p3[tmp%4]);
    else printf("%d\n",(p2[(f2-f5)%4]*p3[tmp%4])%10);
  }
  return 0;
}
