#include<iostream>
#include<stdio.h>
#include<math.h>
#define endl '\n'
using namespace std;
int findMinimumDaysFaster(int n,int t)
{
    int **dp=new int*[n+1];
  for(int i=0;i<n+1;i++)
    dp[i]=new int[t+1];
  int temp1=0;
  int temp2=10000000;
  for(int i=0;i<=n;i++)
   dp[i][0]=0;
  for(int l=0;l<=t;l++)
   dp[1][l]=l;
  for(int i=2;i<=n;i++)
   {
     for(int l=1;l<=t;l++)
      {
        int low=0;
        int high=l-1;
       while(low<=high)
       {
       int mid=low+(high-low)/2;
         if(dp[i-1][mid]<=dp[i][l-mid-1])
          {
           temp2=mid;
           low=mid+1;
           }
         else
           high=mid-1;
        }
        dp[i][l]=1+max(dp[i-1][temp2],dp[i][l-temp2-1]);
        temp2=10000000;
      }
   }
   temp1=dp[n][t];
   for(int i=0;i<=n;i++)
   {
     delete []dp[i];
   }
   delete []dp;
   return temp1;
}     
int findMinimumDays(int n,int t)
{
    int **dp=new int*[n+1];
  for(int i=0;i<n+1;i++)
    dp[i]=new int[t+1];
  int temp1=0;
  int temp2=10000000;
  for(int i=0;i<=n;i++)
   dp[i][0]=0;
  for(int l=0;l<=t;l++)
   dp[1][l]=l;
  for(int i=2;i<=n;i++)
   {
     for(int l=1;l<=t;l++)
      {
        for(int x=1;x<=l;x++)
        {
          temp1=max(dp[i-1][x-1],dp[i][l-x]);
          if(temp1<temp2)
            temp2=temp1;
        }
        dp[i][l]=1+temp2;
        temp2=10000000;
      }
   }
   temp1=dp[n][t];
   for(int i=0;i<=n;i++)
   {
     delete []dp[i];
   }
   delete []dp;
   return temp1;
}         
int main()
{
  int n,t;
  cout<<"Please enter the value of n"<<endl;
  cin>>n;
  cout<<"Please enter the value of t"<<endl;
  cin>>t;
  cout<<"The Minimum number of days required for knowing the capacity of all the trucks via nt^2 algorithm is ";
  cout<<findMinimumDays(n,t)<<endl;
  cout<<"The Minimum number of days required for knowing the capacity of all trucks via ntlogt algorithm is ";
  cout<<findMinimumDaysFaster(n,t)<<endl;
}
