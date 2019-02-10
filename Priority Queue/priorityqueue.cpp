#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;
//Created By Prakhar Bindal(17CS10036) On 2nd September 2018 at 3:45 am//
#define MAX_SIZE 100
typedef struct _job  //Structure corresponding to job//
{
  int jobId;
  int startTime;
  int jobLength;
  int remLength;
}job;
typedef struct _heap //Structure corresponding to min heap//
{
 job list[MAX_SIZE];
 int numJobs;
}heap;
typedef struct _jobPair  //Structure corresponding to conditional jobpair(part 3)//
{
  int jobid_from;
  int jobid_to;
}jobPair;
int leftchild(int i)
{
 return 2*i+1;
}
int rightchild(int i)
{
  return 2*i+2;
}
int parent(int i)
{
  return (i-1)/2;
}
void initHeap(heap *H)
{
  H->numJobs=0;
}
void insertjob(heap *H,job j)  //Insertion in minheap//
{
  H->numJobs++;
  int i=H->numJobs-1;
  H->list[i]=j;
  while(i!=0&&H->list[parent(i)].remLength>H->list[i].remLength)
  {
   if(H->list[parent(i)].remLength==H->list[i].remLength&&H->list[parent(i)].jobId>H->list[i].jobId)
    {
         swap(H->list[parent(i)],H->list[i]);
         i=parent(i);
     }
    if(H->list[parent(i)].remLength>H->list[i].remLength)
    {
     swap(H->list[parent(i)],H->list[i]);
     i=parent(i);
    }
    cout<<i<<endl;  
  }
}
void min_heapify(heap *H,int i) //Making the heap//
{
  int l=leftchild(i);
  int r=rightchild(i);
  int smallest=i;
  if(l<H->numJobs&&H->list[l].remLength<H->list[i].remLength)
   smallest=l;
  if(r<H->numJobs&&H->list[r].remLength<H->list[i].remLength)
   smallest=r; 
  if(smallest!=i)
  {
    swap(H->list[i],H->list[smallest]);
    min_heapify(H,smallest);
  }
}   
int extractMinJob(heap *H,job *j) //Extracting minimum out of a heap//
{
  if(H->numJobs==0)
   return -1;
  if(H->numJobs==1)
  {
    H->numJobs--;
    return H->list[0].remLength;
  }
  H->list[0]=H->list[H->numJobs-1];
  H->numJobs--;
  min_heapify(H,0);
  return 0;
}

void printheap(heap *H)
{
  cout<<"The min heap after insertion of the jobs enetered is"<<endl;
  for(int i=0;i<H->numJobs;++i)
   {
     cout<<H->list[i].jobId<<" "<<H->list[i].startTime<<" "<<H->list[i].jobLength<<" "<<H->list[i].remLength<<endl;
  }
}
int partition(heap *H,int low,int high) //Partition for quick sort//
{
  int pivot=H->list[high].startTime;
  int i=low-1;
  for(int j=low;j<high;j++)
  {
    if(H->list[j].startTime<pivot)
    {
      i++;
      swap(H->list[j],H->list[i]);
     }
  }
  swap(H->list[i+1],H->list[high]);
  return i+1;
}
void quicksort(heap *H,int low,int high) //The quick sort algorithm//
{
  if(low<high)
  {
    int pi=partition(H,low,high);
    quicksort(H,low,pi-1);
    quicksort(H,pi+1,high);
  }
}
int binarysearch(heap *H,int low,int high,int key) //Binary search//
{
  while(low<=high)
  {
    int mid=low+(high-low)/2;
    if(H->list[mid].startTime==key)
      return mid;
    else if(H->list[mid].startTime>key)
       high=mid-1; 
     else
       low=mid+1;
  }
 return -1;
}
void decreasekey(heap *H,int index)
{
    H->list[index].remLength/=2;
    while(index!=0&&H->list[parent(index)].remLength>H->list[index].remLength)
    {
       swap(H->list[parent(index)],H->list[index]);
       index=parent(index);
    }
}
int count(heap *H,int n)
{
   int temp=0;
   for(int i=0;i<n;i++)
    if(H->list[i].remLength==0)
      ++temp;
    return temp;
}
void newScheduler(heap *H,int n,jobPair pairList[],int m)
{
  int start=H->list[0].startTime;
  int currentjob=0;
  bool check[n];
  for(int i=0;i<n;i++)
    check[i]=false;
  bool check1[n];
  bool check2[n];
  for(int i=0;i<n;i++)
    check2[i]=false;
  for(int i=0;i<n;i++)
   check1[i]=false;
  int sum=0;
  int temp=-1;
  bool okay=false;
  int ans=H->list[0].remLength;
  for(int i=0;H->list[i].startTime==H->list[0].startTime;i++) //If many of jobs have same start time//
  {
      if(H->list[i].remLength<=ans)
      {
         if(H->list[i].remLength==ans)
         {
            if(H->list[i].jobId<H->list[0].jobId)
            {
               currentjob=i;
            }
         }
         else
         {
           currentjob=i;
           ans=H->list[i].remLength;
         }
      }     
  }
  bool x=false;
  for(int i=0;i<start;i++)
    cout<<0<<" ";
  bool check3[n];
  for(int i=0;i<n;i++)
    check3[i]=false;
  if(start==0)
    cout<<H->list[currentjob].jobId<<" ";
  for(int i=start;count(H,n)!=n;i++)
  {   
    if(x)
      cout<<0<<" ";
    else if(i!=start)
    cout<<H->list[currentjob].jobId<<" ";  
    x=false;
    if(H->list[currentjob].remLength>0)
    H->list[currentjob].remLength--;
    int minimaindex;
    if(H->list[currentjob].remLength==0)  //If remaining length becomes 0//
    {
        if(currentjob==0)
        cout<<H->list[0].jobId<<" ";
       if(count(H,n)==n&&currentjob==0)
        okay=true;
       int j;
       int a[n];
       int k=0;
       for(j=0;j<m;j++)     
       {
         if(pairList[j].jobid_from==H->list[currentjob].jobId)
         {
           a[k]=j;
           k++;
        }
        }
        for(int j=0;j<k;j++)
        {
        for(int i=0;i<n;i++)
        {
           if(i==currentjob)
            continue;
           if(H->list[i].jobId==pairList[a[j]].jobid_to&&!check[i])
           {
              H->list[i].remLength/=2;
              if(H->list[i].remLength==0)
              {
                  check3[i]=true;
              }
              break;
           }
        }
      }
     check3[currentjob]=true;
       check[currentjob]=true;
       int minima=10000000;
       minimaindex=-1;
       for(int j=0;j<n;j++) 
       {
         if(j==currentjob) 
           continue;
         if(H->list[j].startTime>i+1)
          continue;
         else if(H->list[j].remLength<=minima&&H->list[j].remLength!=0)
        {
           if(H->list[j].remLength==minima)
           {
             if(H->list[j].jobId<H->list[minimaindex].jobId)
             {
               minima=H->list[j].remLength;
               minimaindex=j;
             }
           }
           else
           {
           minima=H->list[j].remLength;
           minimaindex=j;
          }
        }
       }
     if(minimaindex!=-1)
     {
     if(H->list[minimaindex].startTime<=i+1)
      {
      currentjob=minimaindex;
      x=false;
      check[currentjob]=true;
      }
      else
        minimaindex=-1;
    }
    }
    int index=binarysearch(H,0,n-1,i+1); //For nlogn complexity we use binary search for searching as our array is sorted by start time*/
    if(index!=-1&&H->list[index].startTime<=i+1)
    {
      int temp1=index;
      while(H->list[index].startTime==i+1&&index<=n)
      {
      if(H->list[index].jobLength<H->list[currentjob].remLength&&H->list[index].remLength!=0)
      {
        currentjob=index;
      }
      ++index;
      }
      index=temp1;
      while(H->list[index].startTime==i+1&&index>=1)
       {
        if(H->list[index].jobLength<H->list[currentjob].remLength&&H->list[index].remLength!=0)
        {
        currentjob=index;
        }
       --index;
       }
      check1[i+1]=true;
      check[currentjob]=true;
    }
    else if(minimaindex==-1)
      x=true;
    if(!x)
    {
         if(!check2[H->list[currentjob].jobId])
         {
           sum+=i+1-H->list[currentjob].startTime;
            check2[H->list[currentjob].jobId]=true;
            if(currentjob==0&&start==0)
              sum-=i;
         }
    }
  }
 cout<<endl;
 sum--;
 cout<<"The average turnout time is "<<endl;
 cout<<double(sum*1.0)/n<<endl;
}
int main()
{
 int n;
 cout<<"Please enter the number of jobs you wanna schedule using the priority queue"<<endl;
 cin>>n;
 heap H;
 cout<<"Please enter the jobid,startTime and jobLength for each job"<<endl;
 initHeap(&H);
 job heap[n+1];
 for(int i=1;i<=n;i++)
 {
   cout<<i<<endl;
   cin>>heap[i].jobId>>heap[i].startTime>>heap[i].jobLength;
   heap[i].remLength=heap[i].jobLength;
   insertjob(&H,heap[i]);
   printheap(&H);
 }
cout<<"Please enter the number of dependancy pairs of the jobs"<<endl;
 int m;
 cin>>m;
 jobPair pairList[m];
 cout<<"Please enter the dependancy pairs"<<endl;
 for(int i=0;i<m;i++)
 {
    cin>>pairList[i].jobid_from>>pairList[i].jobid_to;
 }
 quicksort(&H,0,n-1);
 cout<<"Your heap after sorting using quick sort algorithm is "<<endl;
 printheap(&H);
 newScheduler(&H,n,pairList,m);
}