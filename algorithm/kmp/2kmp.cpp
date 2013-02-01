#include <iostream>
#include <string>
using namespace std;
int main() 
{
  string A = " ababababafcbaababafcb";
  string B = " ababafcb";
  int p[20];
  int n = A.size() - 1;
  int m = B.size() - 1;
  int i, j;

  p[1] = 0;
  for (j = 1; j <= m - 1; ++j) {
    if (B[j+1] == B[p[j]+1]) //看图5中间一部分
      p[j+1] = p[j] + 1;
    else { //看图5最下面
      int k = j;
      while (k > 0 && B[j+1] != B[p[k]+1])
        k = p[k]; //这里的k最少能够到达0

      if (k != 0) //说明找到使得B[j+1] == B[p[k]+1]的k
        p[j+1] = p[k] + 1;
      else //说明没有找到使得B[j+1] == B[p[k]+1]的k
        p[j+1] = 0;
    }
  }

  i = j = 0;
  while (1) {
    if (B[j+1] == A[i+1]){ //看图2啦
      ++j;++i;
      if (j == m) { //如果B串都结束了，那么显然成功匹配咯
        cout << "匹配成功: " << i - m + 1 << endl;
        j = p[j]; //使得可以继续匹配下去，这个你自己画个图就明白为啥要这么做咯
      }
      if (i == n) break;
    }
    else {
      while (j > 0 && B[j+1] != A[i+1])
        j = p[j];//看图4啦
    }
  }
  return 0;
}
