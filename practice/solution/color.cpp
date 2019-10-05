//by Lou Tiancheng
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
typedef long long int64;
 
class StairsColoring
{
public:
  int MODE;
  int left[10000];
  int mypower(int p,int e,int MODE)
  {
    if (e==0) return 1%MODE;
    if (e%2==0)
    {
      int t=mypower(p,e/2,MODE);
      return (int)(((int64)t*(int64)t)%MODE);
    }
    else
    {
      int t=mypower(p,e-1,MODE);
      return (int)(((int64)t*(int64)p)%MODE);
    }
  }
  void solveIt(int n,int &e,int &p)
  {
    if (n<MODE)
    {
      e=0;
      p=left[n];
    }
    else
    {
      solveIt(n/MODE,e,p);
      int c=left[MODE-1];
      int d=mypower(c,n/MODE,MODE);
      p=(p*d)%MODE;
      p=(p*left[n%MODE])%MODE;
      e+=n/MODE;
    }
  }
  int solve(int n,int _MODE)
  {
    MODE=_MODE;
    left[0]=1%MODE;
    for (int i=1;i<MODE;i++) left[i]=(i*left[i-1])%MODE;
    int e1,p1,e2,p2,e3,p3,s2=0,s3=0;
    solveIt(2*n,e1,p1);
    solveIt(n+1,e2,p2);
    solveIt(n,e3,p3);
    if (e1>e2+e3) return 0;
    for (int i=0;i<MODE;i++) 
    {
      if ((i*p2)%MODE==1) s2=i;
      if ((i*p3)%MODE==1) s3=i;
    }
    return (((p1*s2)%MODE)*s3)%MODE;
  }
  int coloringCount(int n, int k)
  {
    int64 m[5]={2,3,11,2089,7253};
    int64 b[5];
    for (int i=0;i<5;i++)
    {
      b[i]=solve(n,(int)m[i]);
    }
    int64 R=0;
    for (int i=0;i<5;i++)
    {
      int64 s=1;
      for (int j=0;j<5;j++) if (i!=j) s*=m[j];
      int64 t=0;
      while (t%m[i]!=b[i]) t+=s;
      R+=t;
    }
    int d=(int)(R%1000000122);
    int ret=mypower(k,d,1000000123);
    return ret;
  }
};

int main() {
  freopen("color.in","r",stdin);
  freopen("color.out","w",stdout);
  StairsColoring proc;
  int n,k;
  while (cin>>n>>k) cout<<proc.coloringCount(n,k)<<endl;
  return 0;
}
