#include <iostream>
#include <list>
using namespace std;

int print(int &str)
{
  cout<<str<<endl;
}
int main()
{
  list<int> intlist;
  intlist.push_back(23);
  intlist.push_back(45);
  intlist.push_front(11);
  intlist.push_front(1);
  intlist.push_front(123);
  
  //list<int>::iterator p;
  //for (p = intlist.begin(); p != intlist.end(); p++)
  //  cout<<*p<<endl;
  //
  //intlist.sort();
  //for (p = intlist.begin(); p != intlist.end(); p++)
  //  cout<<*p<<endl;
  for_each(intlist.begin(), intlist.end(), print); 
  return 0;
}
