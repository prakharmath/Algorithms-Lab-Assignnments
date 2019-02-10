#include<iostream>
#include<stdio.h>
using namespace std;
#define endl '\n'
#define MAXN 1000
typedef int **graph;
struct node
{
  int key;
  struct node *next;
};
struct queue
{
  struct node *front,*rear;
};
struct node *newnode(int key)
{
   struct node *temp=new node();
   temp->key=key;
   temp->next=NULL;
   return temp;
}
struct queue *createqueue()
{
   struct queue *q=new queue(); 
   q->front=q->rear=NULL;
   return q;
}
struct edge
{
  int src;
  int dtn;
};
void push(struct queue *q,int key)
{
  struct node *temp=newnode(key);
  if(q->rear==NULL)
  {
     q->front=q->rear=temp;
     return;
  }
  q->rear->next=temp;
  q->rear=temp;
}
struct node *pop(struct queue *q)
{
    if(q->front==NULL)
      return NULL;
    struct node *temp=q->front;
    q->front=q->front->next;
    if(q->front==NULL)
      q->rear=NULL;
    return temp;
}
bool isempty(struct queue *q)
{
    if(q->front==NULL)
      return true;
    return false;
} 
int isConnectedUsingBFS(graph G,int n)
{
   bool *visited=new bool[MAXN+1];   //Dynamically allocating our visited array for bfs//
   struct queue *q=createqueue();
   push(q,0);
   while(!isempty(q))
   {
      struct node *temp=pop(q);
      int element=temp->key;
      for(int i=0;i<n;i++)
      {
          if(G[element][i]!=0&&!visited[i])
          {
              push(q,i);
              visited[i]=true;
          }
     }
   }
   bool answer=false;
   for(int i=0;i<n;i++)
    {
       if(!visited[i])
         return false;
    }
    return true; 
}
void merge(edge edges[],int low,int mid,int high,graph G,int n)
{
    int i,j,k;
    int n1=mid-low+1;
    int n2=high-mid;
    edge left[n1];
    edge right[n2];
    for(int i=0;i<n1;i++)
      left[i]=edges[i+low];
    for(int j=0;j<n2;j++)
      right[j]=edges[mid+1+j];
    i=0;
    j=0;
    k=low;
    while(i<n1&&j<n2)
    {
      if(G[left[i].src][left[i].dtn]<G[right[j].src][right[j].dtn])  //Sorting by target time//
      {
        edges[k]=left[i];
        i++;
      }
      else
       {
         edges[k]=right[j];
         j++;
       }
      k++;
     }
    while(i<n1)
    {
      edges[k]=left[i];
      i++;
      k++;
    }
   while(j<n2)
   {
     edges[k]=right[j];
     j++;
     k++;
   }
}   
void mergesort(edge edges[],int low,int high,graph G,int n)
{
  if(low<high)
  {
     int mid=low+(high-low)/2;
     mergesort(edges,low,mid,G,n);
     mergesort(edges,mid+1,high,G,n); 
     merge(edges,low,mid,high,G,n);
  }
}
void findMST(graph G,int n,edge edges[],int k)
{
    mergesort(edges,0,k-1,G,n);  //sorting edges by weight//
    bool mark[MAXN][MAXN];
    for(int i=0;i<k;i++)
        mark[edges[i].src][edges[i].dtn]=false;
    for(int i=k-1;i>=0;i--)
    {
      if(!mark[edges[i].src][edges[i].dtn])
      {
         int temp1=G[edges[i].src][edges[i].dtn];
         int temp2=G[edges[i].dtn][edges[i].src];
         G[edges[i].src][edges[i].dtn]=0;
         G[edges[i].dtn][edges[i].src]=0;
         if(!isConnectedUsingBFS(G,n))
         {
            mark[edges[i].src][edges[i].dtn]=true;
            G[edges[i].dtn][edges[i].src]=temp2;
            G[edges[i].src][edges[i].dtn]=temp1;
         }
      }
    }
   cout<<"The MST of the graph is"<<endl;
    for(int i=0;i<n;i++)
   { 
     cout<<"Vertex "<<i<<": ";
     for(int j=0;j<n;j++)
     { 
          if(G[i][j]!=0)
          {
             cout<<j<<" "<<G[i][j]<<" ";
          }
     }
      cout<<endl;
   }
   
}
signed main()
{
   cout<<"Please enter the number of the nodes and the number of edges"<<endl;
   int n,e;
   cin>>n>>e;
   int **A=new int*[MAXN]; //Allocating a dynamic 2D array which will act as our adjacency matrix for storing weights of the edges//
   for(int i=0;i<MAXN;i++)
      A[i]=new int[MAXN];
   for(int i=0;i<MAXN;i++)
   {
     for(int j=0;j<MAXN;j++)
        A[i][j]=0;
   }
   edge *edges=new edge[MAXN];  //Dynamically allocating an array for storing the edges//
   int k=0;
   for(int i=0;i<n;i++)
   {
      cout<<"Please enter the degree of the vertex"<<endl;
      int degree;
      cin>>degree;
      cout<<"Please enter the vertex and weight of the corresponding edge connecting them one by one in pairs"<<endl;
      for(int j=0;j<degree;j++)
      {
         int v,w;
         cin>>v>>w;
         A[i][v]=w;
         edges[k].src=i;
         edges[k].dtn=v;
         k++;
      }
   }
   cout<<"The neighbours of each node in the input graph and their corresponding weight are"<<endl;
   for(int i=0;i<n;i++)
   { 
     cout<<"Vertex "<<i<<": ";
     for(int j=0;j<n;j++)
     { 
          if(A[i][j]!=0)
          {
             cout<<j<<" "<<A[i][j]<<" ";
          }
     }
      cout<<endl;
   }
   findMST(A,n,edges,k);
   for(int i=0;i<n;i++)
     delete[]A[i];          //Freeing/Deleting our dynamically allocated 2D Array//
   delete[]A;    
}
