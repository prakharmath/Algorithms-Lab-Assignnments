#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
#define rep(i,n) for(i=0;i<n;i++)
#define rep1(i,n) for(i=1;i<=n;i++)
#define nrep(i,n) for(i=n-1;i>=0;i--)
#define nrep1(i,n) for(i=n;i>=1;i--)
#define ia(a,n) for(i=0;i<n;i++) cin>>a[i]
#define ia1(a,n) for(i=1;i<=n;i++) cin>>a[i]
#define mod 1000000007
//Created By Prakhar Bindal(17CS10036) on 9/August/2018 at 2:05 pm//
struct node
{
  node *right;
  node *left;
  node *parent;          //Declaring the binary search tree//
  int data;
}NODE,*NODEPTR;
node *newnode(int data)
{
  node *temp=new node();     //Creating a newnode for the binary search tree//
  temp->data=data;
  temp->parent=NULL;
  temp->right=NULL;
  temp->left=NULL;
  return temp;
}
node *makeroot(node *&root,node *&n)  //makeroot function for making the current node of the binary search tree as the parent root//
{
  if(n->parent==root)
    {
    node *temp=n->left;
    n->left=temp->right;
    if (temp->right!=NULL)
        temp->right->parent=n;
    temp->parent=n->parent;
    if (n->parent==NULL)
        root=temp;
    else
    {
        if (n==n->parent->left)
            n->parent->left=temp;
        else
            n->parent->right=temp;
    }
    temp->right=n;
    n->parent=temp;
   }
}

node *oppositeorientation(node *&root,node *&n)  //Opposite Orientation function for Rotation along opposite orientation//
{
    node *temp=n->right;
    n->right=temp->left;
    if (temp->left!=NULL)
        temp->left->parent=n;
    temp->parent=n->parent;
    if (n->parent==NULL)
        root=temp;
    else
    {
        if (n==n->parent->left)
            n->parent->left=temp;
        else
            n->parent->right=temp;
    }
    temp->left=n;
    n->parent=temp;
}
node *sameorientation(node *&root,node *&n) //Same orientation function for rotation along the same direction//
{
   node *temp=n->left;
    n->left=temp->right;
    if (temp->right!=NULL)
        temp->right->parent=n;
    temp->parent=n->parent;
    if (n->parent==NULL)
        root=temp;
    else
    {
        if (n==n->parent->left)
            n->parent->left=temp;
        else
            n->parent->right=temp;
    }
    temp->right=n;
    n->parent=temp;
}
node *minima(node *root)  //Function for calculating the minima of the binary search tree for deletion function//
{
  if(root!=NULL)
  {
  while(root->left!=NULL)
   root=root->left;
  }
  return root;
}
node *recursive_search(node *root,int data) //A recursive function to search for a particular value in the binary search tree//
{
 if(root!=NULL)
 {
   if(root->data==data)
     return root;
   if(root->data>data)
     return recursive_search(root->left,data);
   if(root->data<data)
      return recursive_search(root->right,data);
 }
}
node *insert(node *root,int data)  //A recursive insertion function for inserting keys in the binary search tree//
{
   node *temp=newnode(data);
   if(root==NULL)
   return temp;
  if(root->data>data)
  {
    root->left=insert(root->left,data);
    root->left->parent=root;
  }
  else if(root->data<data)
   {
     root->right=insert(root->right,data);
     root->right->parent=root;
   }
  makeroot(root,temp);
  return root;
  
}
void inorder(node *root) //A recursive function for doing the inorder traversal of the binary search tree//
{
 if(root!=NULL)
 {
    inorder(root->left);
    cout<<root->data<<endl;
    inorder(root->right);
 }
}
void preorder(node *root) //A recursive function for doing the preorder traversal of the binary search tree//
{
  if(root!=NULL)
  {
   cout<<root->data<<endl;
   preorder(root->left);
   preorder(root->right);
  }
}
void postorder(node *root) //A recursive function for doing the postorder traversal of the binary seaarch tree//
{
 if(root!=NULL)
 {
  postorder(root->left);
  postorder(root->right);
  cout<<root->data<<endl;
 }
}
node *deletenode(node *root,int key)  //A recursive function for deleting a node of the binary search tree//
{
  if(root==NULL)
   return root;
  if(root->data>key)
   root->left=deletenode(root->left,key);
  else if(root->data<key)
   root->right=deletenode(root->right,key);
  else
  {
    if(root->left==NULL)
    {
      node *temp=root->right;
      free(root);
      return temp;
    }
    if(root->right==NULL)
    { 
      node *temp=root->left;
      free(root);
      return temp;
    }
   node *temp=minima(root->right);
   root->data=temp->data;
   root->right=deletenode(root->right,temp->data);
  }
 return root;
}

int main()
{
   cout<<"Please enter the number of numbers that you want to insert in the superb binary search node"<<endl;
   int n;
   cin>>n;
   int a[n];
   cout<<"Please enter numbers you want to insert in the superb binary search node"<<endl;
   int i;
   node *root=NULL;
   int x;
    cin>>x;
   root=insert(root,x);
   rep(i,n-1)
     {
        cin>>x;
       insert(root,x);
     }
  cout<<"The inorder traversal of the  binary search node before deletion is"<<endl;
  inorder(root);
  cout<<"The preorder traversal of the binary search node before deletion is"<<endl;
  preorder(root);
  cout<<"The postorder traversal of the binary search node before deletion is"<<endl;
  postorder(root);
  cout<<"Please enter the number of values you wanna delete from the binary search node"<<endl;
  int temp;
  cin>>temp;
  rep(i,temp)
  {
    cout<<"Please enter the key to delete:"<<endl;
    cin>>x;
    deletenode(root,x);
    cout<<"The inorder traversal of the binary search tree after deletion is"<<endl;
    inorder(root);
    cout<<"The preorder traversal of the binary search tree after deletion is"<<endl;
    preorder(root);
 }
}
