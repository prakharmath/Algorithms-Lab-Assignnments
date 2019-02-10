#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define rep(i,n) for(i=0;i<n;i++)
#define ia(a,n) for(i=0;i<n;i++) cin>>a[i]
#define rep1(i,n) for(i=1;i<=n;i++)
#define ia1(a,n) for(i=1;i<=n;i++) cin>>a[i]
//Created By Prakhar Bindal(17CS10036) On 2/August/2018 at 2:20 pm//
struct tree
{
 tree *right;
 tree *left;
 tree *parent;
 string data;
};
tree *newnode(string data)
{
  tree *node=new tree();
  node->data=data;
  node->right=NULL;
  node->left=NULL;
  node->parent=NULL;
  return node;
}
tree *insert(tree *root,string data)
{
  if(root==NULL)
    return newnode(data);
  else if(root->data>data)
    {
     tree *lchild=insert(root->left,data);
     root->left=lchild;
     lchild->parent=root;
    }
  else
    {
     tree *rchild=insert(root->right,data);
     root->right=rchild;
     rchild->parent=root;
    }
  return root;
}

void preorder(tree *root)
{
  if(root!=NULL)
  {
     cout<<root->data<<" ";
     preorder(root->left); 
     preorder(root->right);
  }
}
void inorder(tree *root)
{
  if(root!=NULL)
   {
      inorder(root->left);
      cout<<root->data<<" ";
      inorder(root->right);
  }
}
void parentinorder(tree *root)
{
  if(root!=NULL)
   {
      parentinorder(root->left);
      cout<<root->data<<" ";
      cout<<"Parent::";
      if(root->parent==NULL)
      cout<<"NULL";
      else
      cout<<root->parent->data;
      cout<<endl;
      parentinorder(root->right);
  }
}
void postorder(tree *root)
{
  if(root!=NULL)
  {
    postorder(root->left); 
    postorder(root->right);
    cout<<root->data<<" ";
  }
}
tree *minima(tree *root)
{
  if(root!=NULL)
  {
  while(root->left!=NULL)
   root=root->left;
  }
  return root;
}
bool recursive_search(tree *root,string data)
{
  if(root!=NULL)
  {
   if(root->data==data)
     return true;
   if(root->data>data)
     return recursive_search(root->left,data);
   if(root->data<data)
     return recursive_search(root->right,data);
  }
return false;
}
tree *deletenode(tree *root,string key)
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
      tree *temp=root->right;
      free(root);
      return temp;
    }
    if(root->right==NULL)
    {
      tree *temp=root->left;
      free(root);
      return temp;
    }
   tree *temp=minima(root->right);
   root->data=temp->data;
   root->right=deletenode(root->right,temp->data);
  }
 return root;
}
void deleteinorder(tree *root,string a[],int n)
{
  if(root!=NULL)
  {
    deleteinorder(root->left,a,n);
    int i;
    for( i=0;i<n;i++)
     if(root->data==a[i])
      break;
    if(i==n)
     cout<<root->data<<" ";
    deleteinorder(root->right,a,n);
}
}
bool check_prefix(string s,string str)
{
  int i;
  if(s.length()<str.length())
    return false;
  for(i=0;i<str.length();i++)
   if(s[i]!=str[i])
     break;
  if(i==str.length())
    return true;
  return false;
}
void find_extensions(tree *root,string str)
{
  tree *current;                    //A node to keep a track of our current node of investigation//
  tree *previous;  
                 // A node to keep a track of the parent//
  if(root==NULL)
    return;                        //if root is empty return//
  current=root;
  string a[100];
  int j=0;
  while(current!=NULL)            
  {
     if(current->left==NULL)         //If the left child of our root of investigation is empty then simply just check current data to satisfy the prefix or not //
     {
      if(check_prefix(current->data,str))
      {
      cout<<current->data<<" ";
      a[j]=current->data;
      j++;
      }           //Then move in the forward direction//
      current=current->right;
     }
    else
    {
      previous=current->left;
      while(previous->right!=NULL&&previous->right!=current) //else find the inorder successor of the given node and backtrack searching for prefixes using parent"
        previous=previous->right;
      if(previous->right==NULL)
       {
          previous->right=current;            //Go for the rightmost child of in the left subtree//
          current=current->left;
       }
      else
      { 
          previous->right=NULL;
          if(check_prefix(current->data,str)) //Check for prefixes using our builtin functions//
          {
           cout<<current->data<<" ";
           a[j]=current->data;
           j++;
           }
          current=current->right;
}
}
}
cout<<endl;
cout<<"The tree after deletion is "<<endl;
deleteinorder(root,a,j);
}                  
int main()
{
  tree *root=NULL;
  int n;
  int i;
  cout<<"Enter the Number of words:"<<endl;
  cin>>n;
  string a[n];
  rep(i,n)
  { 
    cout<<"Enter the word"<<endl; 
    cin>>a[i];
  }
 root=insert(root,a[0]);
 rep1(i,n-1)
  insert(root,a[i]);
 cout<<"The inorder traversal of the given tree is"<<endl;
 inorder(root);
 cout<<endl;
 cout<<"The inorder traversal of the given tree with parent node of each node in the BST is"<<endl;
 parentinorder(root);
 cout<<"Please enter the string prefix you wanna search in the BST"<<endl;
 string str;
 cin>>str;
 cout<<"The strings with given prefix common in our binary search tree are "<<endl;
 find_extensions(root,str);
 cout<<endl;
}
  

      


