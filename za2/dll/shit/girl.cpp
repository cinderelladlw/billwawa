#include <iostream>
using namespace std;

void String(char *str)
{
	
	for(int i=1;str[i]!='\0';i=i+1)
	{ 
		if('a'<=str[i]&&str[i]<='z')
		{
			str[i]=str[i]-'a'+'A';
		}
	}
}
	
int main()
{ 
	char str[100];
	cin.getline(str,100,'\n');
	String(str);
	for(int i=0;str[i]!=0;i++)
	{
		cout<<str[i];
	}
	cout<<endl;
  return 0;
}
