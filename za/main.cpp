#include <iostream>
#include <vector>
using namespace std;

int main()
{
  vector<int> int_vector;
  vector<double> double_vector;
  int_vector.push_back(99);
  int_vector.push_back(9900);
  double_vector.push_back(99.99);
  double_vector.push_back(9900.9900);
  int size;
  size = int_vector.size();
  int i;
  for(i = 0; i < size; i++) {
    cout<<int_vector[i]<<endl;
  }
  size = double_vector.size();
  int j;
  for(j = 0; j < size; j++) {
    cout<<double_vector[j]<<endl;
  }
  return 0;
}
 
