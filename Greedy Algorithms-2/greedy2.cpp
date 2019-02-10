#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define endl '\n'
/*Created by Prakhar Bindal(17CS10036) at 2:05 pm*/
typedef struct
{  
  int subpartID;
  int cost_per_day;
  int duration;
}subpart_data;
typedef struct
{
  int predecessor;
  int successor;
}dependency_info;
void merge(subpart_data data[],int low,int mid,int high)
{
    int i,j,k;
    int n1=mid-low+1;
    int n2=high-mid;
    subpart_data left[n1];
    subpart_data right[n2];
    for(int i=0;i<n1;i++)
      left[i]=data[i+low];
    for(int j=0;j<n2;j++)
      right[j]=data[mid+1+j];
    i=0;
    j=0;
    k=low;
    while(i<n1&&j<n2)
    {
      if(left[i].cost_per_day<right[j].cost_per_day)
      {
        data[k]=left[i];
        i++;
      }
      else if(left[i].cost_per_day==right[j].cost_per_day)
      {
         if(left[i].duration<right[j].duration)
          {
            data[k]=right[j];
            j++;
          }
         else
          {
             data[k]=left[i];
             i++;
          }
      }
      else
       {
         data[k]=right[j];
         j++;
       }
      k++;
     }
    while(i<n1)
    {
      data[k]=left[i];
      i++;
      k++;
    }
   while(j<n2)
   {
     data[k]=right[j];
     j++;
     k++;
   }
}   
void mergesort(subpart_data data[],int low,int high)
{
  if(low<high)
  {
     int mid=low+(high-low)/2;
     mergesort(data,low,mid);
     mergesort(data,mid+1,high); 
     merge(data,low,mid,high);
  }
}
void print_schedule(int k,subpart_data data[])
{
   mergesort(data,1,k);  //Sorting by cost_per_day//
   long long total_cost=0;
   long long current_time=0;
   for(int i=k;i>=1;i--)
   {
      current_time+=data[i].duration;
      total_cost+=current_time*data[i].cost_per_day;
   }
   cout<<"The minimum total cost required for doing the project is ";
   cout<<total_cost<<endl; 
}
void merge1(dependency_info relation[],int low,int mid,int high,int jobid[],subpart_data data[])
{
    int i,j,k;
    int n1=mid-low+1;
    int n2=high-mid;
    dependency_info left[n1];
    dependency_info right[n2];
    for(int i=0;i<n1;i++)
      left[i]=relation[i+low];
    for(int j=0;j<n2;j++)
      right[j]=relation[mid+1+j];
    i=0;
    j=0;
    k=low;
    while(i<n1&&j<n2)
    {
      int x1=jobid[left[i].predecessor];
      int y1=jobid[left[i].successor];
      int x2=jobid[right[i].predecessor];
      int y2=jobid[right[i].successor];
      double ratio1=1.0*(data[x1].cost_per_day+data[y1].cost_per_day)/(data[x1].duration+data[y1].duration);
      double ratio2=1.0*(data[x2].cost_per_day+data[y2].cost_per_day)/(data[x2].duration+data[y2].duration);
      if(ratio1<=ratio2)
      {
        relation[k]=left[i];
        i++;
      }
      else
       {
         relation[k]=right[j];
         j++;
       }
      k++;
     }
    while(i<n1)
    {
      relation[k]=left[i];
      i++;
      k++;
    }
   while(j<n2)
   {
     relation[k]=right[j];
     j++;
     k++;
   }
}   
void mergesort1(dependency_info relation[],int low,int high,int jobid[],subpart_data data[])
{
  if(low<high)
  {
     int mid=low+(high-low)/2;
     mergesort1(relation,low,mid,jobid,data);
     mergesort1(relation,mid+1,high,jobid,data); 
     merge1(relation,low,mid,high,jobid,data);
  }
}
void print_schedule1(int k,subpart_data data[],int l,dependency_info relation[])
{
     long long total_cost=0;
     long long current_time=0;
     mergesort(data,1,k);  //Sorting by cost_per_day//
     int jobid[k+1];
     for(int i=1;i<=k;i++)
       jobid[data[i].subpartID]=i;
     mergesort1(relation,0,l-1,jobid,data);  //Sorting the chains by division of sum of cost_per_day and sum of durations of single sized chains//
     bool jobdone[k+1];
     for(int i=1;i<=k;i++)
       jobdone[i]=false;
     for(int i=l-1;i>=0;i--)
     {
        if(jobdone[jobid[relation[i].predecessor]]&&jobdone[jobid[relation[i].successor]])
           continue;
        else if(!jobdone[jobid[relation[i].predecessor]]&&!jobdone[jobid[relation[i].successor]])
        {
           jobdone[jobid[relation[i].predecessor]]=true;
           jobdone[jobid[relation[i].successor]]=true;
           current_time+=data[jobid[relation[i].predecessor]].duration;
           total_cost+=current_time*data[jobid[relation[i].predecessor]].cost_per_day;
           current_time+=data[jobid[relation[i].successor]].duration; 
           total_cost+=data[jobid[relation[i].successor]].cost_per_day*current_time;
           continue;
        }
       else
       {
         current_time+=data[jobid[relation[i].successor]].duration; 
           total_cost+=data[jobid[relation[i].successor]].cost_per_day*current_time; 
          jobdone[jobid[relation[i].successor]]=true;
       } 
    }
   for(int i=k;i>=1;i--)
   {
       if(jobdone[data[i].subpartID])
         continue;
        jobdone[data[i].subpartID]=true;
              current_time+=data[i].duration;
              total_cost+=current_time*data[i].cost_per_day;
   }
   cout<<"The minimal total cost for doing the project is ";
   cout<<total_cost;
}
signed main()
{
  cout<<"Please enter the number of subparts of the project"<<endl;
  int k;
  cin>>k;
  cout<<"Please enter the duration of each subpart"<<endl;
  subpart_data data[k+1];
  for(int i=1;i<=k;i++)
   {
    cin>>data[i].duration;
    data[i].subpartID=i;
   }
  cout<<"Please enter the cost per day for each subpart"<<endl;
  for(int i=1;i<=k;i++)
    cin>>data[i].cost_per_day;
  print_schedule(k,data);
  cout<<"Please enter the number of depedencies"<<endl;
  int l;
  cin>>l;
  cout<<"Please enter the projectid's of the projects which depend on each other"<<endl;
  dependency_info relation[l];
  for(int i=0;i<l;i++)
   cin>>relation[i].predecessor>>relation[i].successor;
  print_schedule1(k,data,l,relation);
}
