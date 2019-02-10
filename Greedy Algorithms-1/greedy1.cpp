#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define endl '\n'
using namespace std;
typedef struct _rwd
{
  int start_time;
  int service_time;
  int jobid;
}reqWD;
typedef struct _rsd
{
  int service_time; 
  int target_time;
  int jobid;
}reqSD;
void merge1(reqWD jobs[],int low,int mid,int high)
{
    int i,j,k;
    int n1=mid-low+1;
    int n2=high-mid;
    reqWD left[n1];
    reqWD right[n2];
    for(int i=0;i<n1;i++)
      left[i]=jobs[i+low];
    for(int j=0;j<n2;j++)
      right[j]=jobs[mid+1+j];
    i=0;
    j=0;
    k=low;
    while(i<n1&&j<n2)
    {
      if(left[i].start_time<=right[j].start_time)
      {
        jobs[k]=left[i];
        i++;
      }
      else
       {
         jobs[k]=right[j];
         j++;
       }
      k++;
     }
    while(i<n1)
    {
      jobs[k]=left[i];
      i++;
      k++;
    }
   while(j<n2)
   {
     jobs[k]=right[j];
     j++;
     k++;
   }
}   
void mergesort1(reqWD jobs[],int low,int high)
{
  if(low<high)
  {
     int mid=low+(high-low)/2;
     mergesort1(jobs,low,mid);
     mergesort1(jobs,mid+1,high); 
     merge1(jobs,low,mid,high);
  }
}
void schedule1(reqWD jobs[],int n)
{
    mergesort1(jobs,0,n-1); //Sorting by start times//
    bool jobdone[n];
    for(int i=0;i<n;i++)
      jobdone[i]=false;
    reqWD counter[n];
    int counters_count=0;
    int ans=0;
    for(int i=0;i<n;i++)    
    {
      if(!jobdone[i]) 
      {
         counter[counters_count].start_time=jobs[i].start_time;
         counter[counters_count].service_time=jobs[i].service_time;
         counter[counters_count].jobid=jobs[i].jobid;
         counters_count++;
         jobdone[i]=true;
         int temp=i;  //Greedily choosing the next job with least start time that has not been scheduled yet//
         for(int j=temp+1;j<n;j++)
         {
            if(jobs[j].start_time>=jobs[temp].start_time+jobs[temp].service_time&&!jobdone[j])
            {
               counter[counters_count].start_time=jobs[j].start_time;
              counter[counters_count].service_time=jobs[j].service_time;
              counter[counters_count].jobid=jobs[j].jobid;
              counters_count++;
              jobdone[j]=true;
              temp=j;
            }
        }
      }
     if(counters_count!=0)
     cout<<"Counter No "<<ans<<" "<<endl;
      for(int k=0;k<counters_count;k++)
      {
         cout<<counter[k].jobid<<" "<<counter[k].start_time<<" "<<counter[k].service_time+counter[k].start_time<<endl;
      }
      if(counters_count!=0)
        ans++;
      counters_count=0;
    }          
}
void merge2(reqSD jobs[],int low,int mid,int high)
{
    int i,j,k;
    int n1=mid-low+1;
    int n2=high-mid;
    reqSD left[n1];
    reqSD right[n2];
    for(int i=0;i<n1;i++)
      left[i]=jobs[i+low];
    for(int j=0;j<n2;j++)
      right[j]=jobs[mid+1+j];
    i=0;
    j=0;
    k=low;
    while(i<n1&&j<n2)
    {
      if(left[i].target_time<=right[j].target_time)  //Sorting by target time//
      {
        jobs[k]=left[i];
        i++;
      }
      else
       {
         jobs[k]=right[j];
         j++;
       }
      k++;
     }
    while(i<n1)
    {
      jobs[k]=left[i];
      i++;
      k++;
    }
   while(j<n2)
   {
     jobs[k]=right[j];
     j++;
     k++;
   }
}   
void mergesort2(reqSD jobs[],int low,int high)
{
  if(low<high)
  {
     int mid=low+(high-low)/2;
     mergesort2(jobs,low,mid);
     mergesort2(jobs,mid+1,high); 
     merge2(jobs,low,mid,high);
  }
}
void schedule2(reqSD jobs[],int m)
{
   mergesort2(jobs,0,m-1);
   int time=0;    //Sorting by target time//
   for(int i=0;i<m;i++)
   {
      cout<<jobs[i].jobid<<" "<<time<<" "<<time+jobs[i].service_time<<endl;
      time+=jobs[i].service_time;
   }
}
signed main()
{
  int n;
  cout<<"Please enter the number of jobs you must schedule"<<endl;
  cin>>n;
  cout<<"Please enter the start and service time of the above jobs"<<endl;
  reqWD jobs[n];
  for(int i=0;i<n;i++)
  {
     cin>>jobs[i].start_time>>jobs[i].service_time;
     jobs[i].jobid=i;
  }
  schedule1(jobs,n);
  int m;
  cout<<"Please enter the number of jobs you wanna schedule on Saturday"<<endl;
  cin>>m;
  cout<<"Please enter the service time and the target time of the jobs you wanna schedule on saturday"<<endl;
  reqSD jobs_saturday[m];
  for(int i=0;i<m;i++)
  {
    cin>>jobs_saturday[i].service_time>>jobs_saturday[i].target_time;
    jobs_saturday[i].jobid=i;
  }
 schedule2(jobs_saturday,m); 
}
