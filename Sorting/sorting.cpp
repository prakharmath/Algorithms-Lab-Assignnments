#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;
//Created By Prakhar Bindal 17CS10036//
int compare2(int a[],int m,int x,int y,int map[])
{
   if(map[x]<=map[y])
    return 1;
   else
     return -1;   
}
void combine2(int a[],int left,int middle,int right,int B[],int m,int map[])
{
  int i,j,k,n1,n2,*L,*R;
  n1=middle-left+1;
  n2=right-middle;
  L=(int *)malloc(n1*(sizeof(int)));
  R=(int *)malloc(n2*(sizeof(int)));
  for(i=0;i<n1;i++)
   L[i]=a[left+i];
  for(i=0;i<n2;i++)
   R[i]=a[middle+i+1];
  i=0;
  j=0;
  k=left;
  while(i<n1&&j<n2)
  {
     if(compare2(B,m,L[i],R[j],map)==1)
     {
       a[k]=L[i];
       ++i;
     }
     else
     {
        a[k]=R[j];
        ++j;
     }
    ++k;
  }
  while(i<n1)
  {
    a[k]=L[i];
    i++;
    k++;
  }
  while(j<n2)
  {
    a[k]=R[j];
    j++;
    k++;
  }
 free(L);
 free(R);
}
void superbsorting2(int a[],int n,int b[],int m,int map[])
{
  int i,left;
  for(i=1;i<=n-1;i*=2)
  { 
    for(left=0;left<n-1;left+=2*i)
    {
      int middle=i+left-1;
      int right=min(left+2*i-1,n-1);
      combine2(a,left,middle,right,b,m,map);
     }
  }  
}
int compare1(int a[],int m,int x,int y)
{
   int i;   
   for (i=0;i<m;i++)
   {
     if(a[i]==x||a[i]==y)
     break;
   }
  if(a[i]==x)
   return 1;
  else
   return -1;        
}
void combine1(int a[],int left,int middle,int right,int B[],int m)
{
  int i,j,k,n1,n2,*L,*R;
  n1=middle-left+1;
  n2=right-middle;
  L=(int *)malloc(n1*(sizeof(int)));
  R=(int *)malloc(n2*(sizeof(int)));
  for(i=0;i<n1;i++)
   L[i]=a[left+i];
  for(i=0;i<n2;i++)
   R[i]=a[middle+i+1];
  i=0;
  j=0;
  k=left;
  while(i<n1&&j<n2)
  {
     if(compare1(B,m,L[i],R[j])==1)
     {
       a[k]=L[i];
       ++i;
     }
     else
     {
        a[k]=R[j];
        ++j;
     }
    ++k;
  }
  while(i<n1)
  {
    a[k]=L[i];
    i++;
    k++;
  }
  while(j<n2)
  {
    a[k]=R[j];
    j++;
    k++;
  }
 free(L);
 free(R);
}
void superbsorting1(int a[],int n,int b[],int m)
{
  int i,left;
  for(i=1;i<=n-1;i*=2)
  { 
    for(left=0;left<n-1;left+=2*i)
    {
      int middle=i+left-1;
      int right=min(left+2*i-1,n-1);
      combine1(a,left,middle,right,b,m);
     }
  }  
}
void combine(int a[],int left,int middle,int right)
{
  int i,j,k,n1,n2,*L,*R;
  n1=middle-left+1;
  n2=right-middle;
  L=(int *)malloc(n1*(sizeof(int)));
  R=(int *)malloc(n2*(sizeof(int)));
  for(i=0;i<n1;i++)
   L[i]=a[left+i];
  for(i=0;i<n2;i++)
   R[i]=a[middle+i+1];
  i=0;
  j=0;
  k=left;
  while(i<n1&&j<n2)
  {
     if(L[i]<=R[j])
     {
       a[k]=L[i];
       ++i;
     }
     else
     {
        a[k]=R[j];
        ++j;
     }
    ++k;
  }
  while(i<n1)
  {
    a[k]=L[i];
    i++;
    k++;
  }
  while(j<n2)
  {
    a[k]=R[j];
    j++;
    k++;
  }
 free(L);
 free(R);
}
void superbsorting(int a[],int n)
{
  int i,left;
  for(i=1;i<=n-1;i*=2)
  { 
    for(left=0;left<n-1;left+=2*i)
    {
      int middle=i+left-1;
      int right=min(left+2*i-1,n-1);
      combine(a,left,middle,right);  //Combining the subarrays of size 2^i//
     }
  }  
}
int main()
{
  int n;
  cout<<"Please enter the number of entries in your array A"<<endl;
  cin>>n;
  int a[n];
  cout<<"Please enter the elements of the array"<<endl;
  for(int i=0;i<n;i++)
    cin>>a[i];
   superbsorting(a,n);
  cout<<"Your Array after sorting using iterative nlogn algorithm is"<<endl;
  for(int i=0;i<n;i++)
   cout<<a[i]<<endl;
  cout<<"Please enter the array you wanna sort"<<endl;
  for(int i=0;i<n;i++)
   cin>>a[i];
  cout<<"Please enter the size of array according to which you wanna sort the original array"<<endl;
  int m;
  cin>>m;
  int b[m];
  cout<<"Please enter the elements of the array"<<endl;
  for(int i=0;i<m;i++)
    cin>>b[i];
  superbsorting1(a,n,b,m);
  cout<<"Your array after sorting using iterative nlogn algorithm according to the provided array is"<<endl;
  for(int i=0;i<n;i++)
   cout<<a[i]<<endl;
  cout<<"Please enter the array you wanna sort"<<endl;
  for(int i=0;i<n;i++)
   cin>>a[i];
  cout<<"Please enter the size of array according to which you wanna sort the original array"<<endl;
  cin>>m;
  int c[m];
  cout<<"Please enter the elements of the array"<<endl;
  int map[10*m+1];
  for(int i=0;i<=10*m;i++)
   map[i]=0;
  for(int i=0;i<m;i++)
  {
    cin>>c[i];
    map[c[i]]=i;  //We precompute the indexes of all numbers and use it later for doing in O(1) time//
  }
  superbsorting2(a,n,c,m,map);
  cout<<"Your array after sorting using iterative nlogn algorithm according to the provided array is"<<endl;
  for(int i=0;i<n;i++)
   cout<<a[i]<<endl;
}

