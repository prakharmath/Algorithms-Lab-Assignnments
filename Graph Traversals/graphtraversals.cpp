#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define endl '\n'
#define MAXN 100
struct node
{
   struct node *next;
   int dtn;
};
struct Graph
{
   struct node *adjlist[MAXN];
};
struct edge
{
  int src;
  int dtn;
};
Graph *creategraph(edge edges[],int n)
{
   int i;
   Graph *graph=(struct Graph *)malloc(sizeof(struct Graph));
   for(int i=0;i<MAXN;i++)
      graph->adjlist[i]=NULL;
   for(int i=0;i<n;i++)
   {
      int src=edges[i].src;
      int dtn=edges[i].dtn;
      node *newnode=(struct node *)malloc(sizeof(struct node));
      newnode->dtn=dtn;
      newnode->next=graph->adjlist[src];
      graph->adjlist[src]=newnode;
   }
   return graph; 
}
void printgraph(Graph *graph)
{
  for(int i=0;i<MAXN;i++)
  {
    node *ptr=graph->adjlist[i];
    bool okay=true;
    if(ptr==NULL)
      okay=false;
    if(ptr!=NULL)
    cout<<"Vertex "<<i<<": ";
    while(ptr!=NULL)
    {
      cout<<ptr->dtn<<" ";
      ptr=ptr->next;
    }
    if(okay)
    cout<<endl;
 }
}
void DFSVisit(int v,bool visited[],int vertex,Graph *graph)
{
  visited[v]=true;
  node *ptr=graph->adjlist[v];
  while(ptr!=NULL)
  {
    int i=ptr->dtn;
    if(i==vertex)
      {
        ptr=ptr->next;
        continue;
      }
    if(!visited[i])
      DFSVisit(i,visited,vertex,graph); 
    ptr=ptr->next;
  } 
}
int DFSComp(int vertex,Graph *graph,int n)
{
   bool *visited=new bool[n];
   for(int i=0;i<n;i++)
     visited[i]=false;
   visited[vertex]=true;
   int count=0;
   for(int i=0;i<n;i++)
   {
      if(i==vertex)
        continue;
      if(visited[i]==false)
     {
        DFSVisit(i,visited,vertex,graph);
        count++;
     }
  }
  return count;
}
void findcritical(Graph *graph,int n)
{
    cout<<"Critical Junction using Simple Algorithm"<<endl;
    for(int i=0;i<n;i++)
    {
      int ans=DFSComp(i,graph,n);
      if(ans>1)
       cout<<"Vertex "<<i<<":"<<ans<<" Components"<<endl;
    }
}
void DFS(int u,bool visited[],int discovery[],int low[],int parent[],bool ans[],Graph *graph)
{
  static int time=0;
  int children=0;  //For counting the number of children in DFS Tree//
  visited[u]=true;
  discovery[u]=low[u]=++time; 
  node *ptr=graph->adjlist[u];
  while(ptr!=NULL)
  {
    int v=ptr->dtn;
    if(visited[v]==false)
    {
       children++;
       parent[v]=u;  //If a vertex is not visited make it the child of current vertex and again do DFS with this vertex//
       DFS(v,visited,discovery,low,parent,ans,graph);
       low[u]=min(low[u],low[v]);
       if(parent[u]==0&&children>1)   //Either it is a root and has more than 1 children//
         ans[u]=true;
       if(parent[u]!=0&&low[v]>=discovery[u]) //It is not a root and low value of its child is greater than discovery time of u//
         ans[u]=true;
    }
    else if(v!=parent[u])   //Update the value of low[u] by taking the discovery time of one of its children so that we always have the minima//
     low[u]=min(low[u],discovery[v]);
    ptr=ptr->next;
  }
}
void findcriticalfaster(Graph *graph,int n)
{
  cout<<"Critical Junctions using faster algorithm"<<endl;
  bool *visited=new bool[n]; //We create a visited array for keeping a track of visited vertices//
  int *parent=new int[n];  //We keep a parent array for each node in the DFS Tree//
  int *low=new int[n];     //We keep a low array for keeping the earliest visited vertex that can be reached from the subtree rooted at a particular vertex//
  int *discovery=new int[n]; //We keep a discovery array for storing the earliest time a vertex was visited//
  bool *ans=new bool[n];
  for(int i=0;i<n;i++)
  {
     parent[i]=0;
     visited[i]=false;
     ans[i]=false;
  }
  for(int i=0;i<n;i++)
  {
     if(visited[i]==false)
     {
       DFS(i,visited,discovery,low,parent,ans,graph);
     }
  }
  for(int i=0;i<n;i++)
    if(ans[i])
       cout<<"Vertex "<<i<<" is a critical junction"<<endl;
}
signed main()
{
   cout<<"Please enter the number of vertices and the number of edges in the graph"<<endl;
   int n,e;
   cin>>n>>e;
   edge edges[MAXN];
   int k=0;
   for(int i=0;i<n;i++)
   {
     int degree;
     cout<<"Please enter the degree of vertex "<<i<<endl;
     cin>>degree;
     cout<<"Please enter the neighbours of the vertex"<<endl;
     for(int j=0;j<degree;j++) 
     {
        int x;
        cin>>x;
        edges[k].dtn=x;
        edges[k].src=i;
        k++;
     }
   }
   Graph *graph=creategraph(edges,k);
   cout<<"The adjaceny list of the given graph is"<<endl;
   printgraph(graph);
   findcritical(graph,n);
   findcriticalfaster(graph,n);
}

