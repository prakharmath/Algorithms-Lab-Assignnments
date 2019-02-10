#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;
/*Created By Prakhar Bindal (17CS10036) on 6th Septemnber at 2:10 pm*/
typedef struct scores
{
  int mscore;
  int escore;
}score,*scorelist;
double distancebetween(score p1,score p2)
{
  return abs(p1.mscore-p2.mscore)+abs(p1.escore-p2.escore);
}
void mergebymscore(score a[],int left,int middle,int right)
{
  int i,j,k,n1,n2;
  n1=middle-left+1;
  n2=right-middle;
  score L[n1],R[n2];
  for(i=0;i<n1;i++)
  {
   L[i]=a[left+i];
  }
  for(i=0;i<n2;i++)
   R[i]=a[middle+i+1];
  i=0;
  j=0;
  k=left;
  while(i<n1&&j<n2)
  {
     if(L[i].mscore<=R[j].mscore)
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
}
void mergesortbymscore(score T[],int left,int right)
{
  if(left<right)
  {
    int middle=left+(right-left)/2;
    mergesortbymscore(T,left,middle);
    mergesortbymscore(T,middle+1,right);
    mergebymscore(T,left,middle,right);
  }
}
void mergebyescore(score a[],int left,int middle,int right)
{
  int i,j,k,n1,n2;
  n1=middle-left+1;
  n2=right-middle;
  score L[n1],R[n2];
  for(i=0;i<n1;i++)
  {
   L[i]=a[left+i];
  }
  for(i=0;i<n2;i++)
   R[i]=a[middle+i+1];
  i=0;
  j=0;
  k=left;
  while(i<n1&&j<n2)
  {
     if(L[i].escore<=R[j].escore)
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
}
void mergesortbyescore(score T[],int left,int right)
{
  if(left<right)
  {
    int middle=left+(right-left)/2;
    mergesortbyescore(T,left,middle);
    mergesortbyescore(T,middle+1,right);
    mergebyescore(T,left,middle,right);
  }

}
double calmindistance(score withinrange[],int size,double min,score *score1,score *score2)
{
  mergesortbyescore(withinrange,0,size-1);
  for(int i=0;i<size;i++)
  {
    for(int j=i+1;j<size&&withinrange[j].escore-withinrange[i].escore<min;j++)
    {
       if(distancebetween(withinrange[i],withinrange[j])<min)
          {
          min=distancebetween(withinrange[i],withinrange[j]);
          *score1=withinrange[i];
          *score2=withinrange[j];
         }
    }
  }
  return min;
}
int direct(score T[],int n,score *score1,score *score2)
{
  double min=100000000000;
  for(int i=0;i<n;i++)
   for(int j=i+1;j<n;j++)
    if(distancebetween(T[i],T[j])<min)
     {
      min=distancebetween(T[i],T[j]); 
      *score1=T[i];
      *score2=T[j]; 
     }
   return min;
}
int Nearestprofiles(score T[],int n,score *score1,score *score2)
{
   if(n<=3)
     return direct(T,n,score1,score2);
   mergesortbymscore(T,0,n-1);
   int middlepoint=n/2;
   score mid=T[middlepoint];
   double leftmindistance=Nearestprofiles(T,middlepoint,score1,score2);
   score temp11=*score1;
   score temp12=*score2;
   double rightmindistance=Nearestprofiles(T+middlepoint,n-middlepoint,score1,score2);
   score temp21=*score1;
   score temp22=*score2;
   double mindistance=min(leftmindistance,rightmindistance);
   if(mindistance==leftmindistance)
   {
     *score1=temp11;
     *score2=temp12;
   }
   else
   {
     *score1=temp21;
     *score2=temp22;
   }
   score withinrange[n];
   int j=0;
   for(int i=0;i<n;i++)
    if(abs(T[i].mscore-mid.mscore)<mindistance)
       {
        withinrange[j]=T[i];
        ++j;  
      }
   return min(mindistance,calmindistance(withinrange,j,mindistance,score1,score2));
}
int Clusterdistance1(score T[],int n,score U[],int m,score *score1,score *score2)
{
  double min=10000000000;
  for(int i=0;i<n;i++)
   {
     for(int j=0;j<m;j++)
     {
       if(distancebetween(T[i],U[j])<min)
       {
         min=distancebetween(T[i],U[j]);
         *score1=T[i];
         *score2=U[j];
       }
    }
  }
return min;
}
int main()
{
  int n; 
  cout<<"Please enter the number of students for which you want to compare the closest pair of marks"<<endl;
  cin>>n;
  score T[n];
  cout<<"Please enter the maths and english marks of the above students respectively one by one"<<endl;
  for(int i=0;i<n;i++)
  {
    cin>>T[i].mscore>>T[i].escore;
  }
  if(n==1)
  {
    cout<<"Invalid input";
    return 0;
  }
  else if(n==2)
  {
    cout<<"The only one pair of student exists in the input"<<endl;
    cout<<"The distance between their scores is "<<distancebetween(T[0],T[1])<<endl;  
  }
  else
  {
   score score1=T[0];
   score score2=T[1];
   cout<<"The minimum distance between scores of two students in the provided list is "<<endl;
   cout<<Nearestprofiles(T,n,&score1,&score2)<<endl;
   cout<<"The pair of students having this minimum distance between their scores is"<<endl;
   cout<<"("<<score1.mscore<<","<<score1.escore<<")"<<" ";
   cout<<"("<<score2.mscore<<","<<score2.escore<<")"<<endl;
 }
  int m;
  cout<<"Please enter the number of students in the second section"<<endl;
  cin>>m;
  score U[m];
  cout<<"Please enter the maths and english marks of the above students respectively one by one"<<endl;
  for(int i=0;i<m;i++)
  {
   cin>>U[i].mscore>>U[i].escore;
  }
  score score1=T[0];
  score score2=U[0];
  cout<<"The minimum distance between scores of two students in the provided list of different sections is "<<endl;
  cout<<Clusterdistance1(T,n,U,m,&score1,&score2)<<endl;
  cout<<"The pair of students having this minimum distance between their scores is"<<endl;
   cout<<"("<<score1.mscore<<","<<score1.escore<<")"<<" ";
   cout<<"("<<score2.mscore<<","<<score2.escore<<")"<<endl;
 
}
