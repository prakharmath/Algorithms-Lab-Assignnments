#include<iostream>
#include<algorithm>
#include<iterator>
#define rep(i,n) for(i=0;i<n;i++)
#include<stdio.h>
using namespace std;
typedef long long int ll;
//Created by Prakhar Bindal at 4:00 pm on 18/July/2018//
struct Node
{
 ll data;
 struct Node *next;
 struct Node *previous;
};
void add(struct Node **head,ll data_to_be_inserted)
{
  struct Node *new_node=(struct Node*)malloc(sizeof(struct Node));
  new_node->data=data_to_be_inserted;
  new_node->next=*head;
  new_node->previous=NULL;
  if(*head!=NULL)
   (*head)->previous=new_node;
  *head=new_node;
}
void traverse_from_end_to_front(struct Node *head)
{
  cout<<"The linked list traversed in backward direction is "<<endl; 
  while(head!=NULL)
  {
    cout<<head->data<<" ";       //Backward traversal of the doubly linked list
    head=head->previous;
  }
cout<<endl;
}
 
void traverse_from_front_to_end(struct Node *head)
{
  struct Node *last;
  cout<<"The linked list traversed in forward direction is "<<endl;
  while(head!=NULL) //Forward traversal of the doubly linked list
  {
   cout<<head->data<<" ";
   last=head;
   head=head->next;
  }
  cout<<endl;
  traverse_from_end_to_front(last);
}
void reverse(struct Node **head,struct Node **tail)
{
 struct Node *temp=NULL;
 struct Node *current=*head;
 while(current!=NULL)
 {
   temp=current->next;
   current->next=current->previous;
   current->previous=temp;
   current=current->previous;
 }
 if(temp!=NULL)
  *head=temp->previous;
}
void bubblesort(struct Node *start)
{
  int swapped,i;
  struct Node *ptr1;
  struct Node *lptr=NULL;
  if(ptr1==NULL)
    return;
  do
    {
      swapped=0;
      ptr1=start;
      while(ptr1->next!=lptr)
	{
	  if(ptr1->data>ptr1->next->data)
	    {
	    swap(ptr1,ptr1->next);
            swapped=1;                       //Implementing the bubble sort algorithm//
	    }
	  ptr1=ptr1->next;
	}
      lptr=ptr1;
    }while(swapped);
}
void printList(struct Node *start)
{
  struct Node *temp=start;
  printf("\n");
  while(temp!=NULL)                   //Printing the list//
    {
      cout<<temp->data<<" ";
      temp=temp->next;
    }  
}

int main()
{
  ll i,n; 
  srand(time(NULL));
  struct Node *head=NULL;
  cout<<"Please enter the size of data you want to insert in the linked list";
  cin>>n;
  cout<<"The random numbers which we will be inserting in the linked list are "<<endl;
  rep(i,n)
  {
   ll temp=rand()%101;
   cout<<temp<<" ";
   add(&head,temp);
  }
 cout<<endl;
 traverse_from_front_to_end(head);
 reverse(&head,&head);
 cout<<"The traversals of the linked list after reversal are "<<endl;
 printList(head);
 cout<<endl;
 bubblesort(head);
 cout<<"The linked list after sorting is "<<endl;
 printList(head);
}
    
     
