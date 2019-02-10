#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;
//Created By Prakhar Bindal(17CS10036) On 16th August 2018 at 2:50 pm//
typedef struct _wordR      
{
  string str;
  double x,y;
}wordR;
typedef struct _node
{
  wordR newnode;
  _node *next;
}node,*nodePointer;
typedef nodePointer **hashtable;
int hashfunction(double x,int m)
{
  return floor(m*x*1.0);
}
void insertH(hashtable H,int m,wordR W)
{
  int hash1=hashfunction(W.x,m);
  int hash2=hashfunction(W.y,m);
  _node *temp=new _node();
   (temp->newnode).str=W.str;
   (temp->newnode).x=W.x;
   (temp->newnode).y=W.y;
   temp->next=NULL;
  if(H[hash1][hash2]==NULL)
  {
    H[hash1][hash2]=temp;
  }
 else
 {
   temp->next=H[hash1][hash2];
   H[hash1][hash2]=temp;
  }
}
void printH(hashtable H,int m)
{
  for(int i=0;i<m;i++)
   {
     for(int j=0;j<m;j++)
     {
      if(H[i][j]==NULL)
      cout<<"["<<i<<","<<j<<"]"<<"::"<<"()";
      else
      {
       _node *temp=H[i][j];
        if(temp->next==NULL)
        {
          cout<<"["<<i<<","<<j<<"]"<<"::"<<temp->newnode.str<<" ";
        }
       else if(H[i][j]!=NULL)
       {
        int count=0;
        while(temp->next!=NULL)
        {
          if(count==0)
          cout<<"["<<i<<","<<j<<"]"<<"::"<<temp->newnode.str<<" ";
          else
           cout<<temp->newnode.str<<" ";
          temp=temp->next;
          count++;
        }
        cout<<temp->newnode.str;
     }
  }
cout<<endl;
}
}
}
double caldistance(double x1,double y1,double x2,double y2)
{
 return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
void findNN(hashtable H,int m,wordR W)
{
  int hash1=hashfunction(W.x,m);
  int hash2=hashfunction(W.y,m);
  double x=W.x;
  double y=W.y;
  string ans;
  double ansx=0;
  double ansy=0;
  double max=1000000000000000;
  int i,j;
  for(i=0;i<m;i++)
    for(j=0;j<m;j++)
     {
       if(H[i][j]!=NULL)
       { 
            _node *temp=H[i][j];
            while(temp->next!=NULL)
            {
              if(caldistance(temp->newnode.x,temp->newnode.y,x,y)<max)
               {
                    max=caldistance(temp->newnode.x,temp->newnode.y,x,y);
                    ansx=temp->newnode.x;
                    ansy=temp->newnode.y;
                    ans=temp->newnode.str;
               }
             temp=temp->next;
            }
          if(caldistance(temp->newnode.x,temp->newnode.y,x,y)<max)
               {
                    max=caldistance(temp->newnode.x,temp->newnode.y,x,y);
                    ansx=temp->newnode.x;
                    ansy=temp->newnode.y;
                    ans=temp->newnode.str;
               }
         }
  }
 cout<<"The word at minimum distance along with its x and y coordinates are"<<endl;
 cout<<ansx<<" "<<ansy<<" "<<ans<<endl;           
}
int main()
{
 int n;
 cout<<"Please enter the number of words you want to insert in the hash table"<<endl;
 cin>>n;
 int m=ceil(sqrt(n*1.0));
 hashtable H=(nodePointer **)malloc(m*sizeof(nodePointer *));
 int i,j;
 for(i=0;i<m;i++)
  {
    H[i]=(nodePointer *)malloc(m*sizeof(nodePointer));
    for(j=0;j<m;j++)
     H[i][j]=NULL;
  }
   cout<<"Please enter the string and their corresponding x-y vector representation"<<endl;
 for(i=0;i<n;i++)
 {
   string str;
   cin>>str;
   double x,y;
   cin>>x>>y;
   wordR W;
   W.str=str;
   W.x=x;
   W.y=y;
   insertH(H,m,W);
 }
 printH(H,m);
 cout<<"Please enter the number of words you want to search for their minimum distance neighbours in the hash table"<<endl;
 int temp;
 cin>>temp;
 cout<<"Please enter the string and its corresponding x and y coordinates you wanna search for minimum distance neightbours for"<<endl;
 for(i=0;i<temp;i++)
 {
   string str;
   cin>>str;
   double x,y;
   cin>>x>>y;
   wordR W;
   W.str=str;
   W.x=x;
   W.y=y;
   findNN(H,m,W);
}
}
