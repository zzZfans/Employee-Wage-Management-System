#include<iostream>

using namespace std;

int  main(){
	int nums[10000];
	int flag=0;
	for(int i=0;i<10000;){
		flag++;
		for(int j=0;j<flag;){
			nums[i++]=j++ +1;
		}
	}
	int result[10000];
	result[0]=1;
	for(int i=1;i<10000;i++)
		result[i]=result[i-1]+nums[i];
	
	int K,N;
	cin>>K;
	for(int i=0;i<K;i++)
		{cin>>N;
cout<<result[N-1]<<endl;
	}
	return 0;
}
