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
    if (B[j+1] == B[p[j]+1]) //��ͼ5�м�һ����
      p[j+1] = p[j] + 1;
    else { //��ͼ5������
      int k = j;
      while (k > 0 && B[j+1] != B[p[k]+1])
        k = p[k]; //�����k�����ܹ�����0

      if (k != 0) //˵���ҵ�ʹ��B[j+1] == B[p[k]+1]��k
        p[j+1] = p[k] + 1;
      else //˵��û���ҵ�ʹ��B[j+1] == B[p[k]+1]��k
        p[j+1] = 0;
    }
  }

  i = j = 0;
  while (1) {
    if (B[j+1] == A[i+1]){ //��ͼ2��
      ++j;++i;
      if (j == m) { //���B���������ˣ���ô��Ȼ�ɹ�ƥ�俩
        cout << "ƥ��ɹ�: " << i - m + 1 << endl;
        j = p[j]; //ʹ�ÿ��Լ���ƥ����ȥ��������Լ�����ͼ������ΪɶҪ��ô����
      }
      if (i == n) break;
    }
    else {
      while (j > 0 && B[j+1] != A[i+1])
        j = p[j];//��ͼ4��
    }
  }
  return 0;
}
