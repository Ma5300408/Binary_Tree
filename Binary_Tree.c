#include<stdio.h>
#include<stdlib.h>

struct node{
   int data;
   int repeat;
   int size;
   struct node *left;
   struct node *right;
   struct node *next;
};


struct node * head = NULL;
struct node * tail = NULL;

int enqueue(struct node * p){

  struct node * temp = (struct node*)malloc(sizeof(struct node));
   temp =  p;
   if(head == NULL)head = tail = temp;

  else{
     tail->next = temp;
     tail = temp;

   }

   temp->next = NULL;
   return 0;
}


struct node * dequeue(){

  if(head == NULL){

      tail = NULL;
      return NULL;
    }


  else{
      struct node * temp;
     temp = head;
     head = head->next;
     return temp;
   }

}

int IsEmpty(){


   if(head == NULL)return 1;
   else return 0;


}


struct node * root;
struct node * new_root;

struct node * CopyTree(struct node *r){

      if(!r)return NULL;
  
      else{

         struct node * new_node = (struct node*)malloc(sizeof(struct node));
         new_node->left = CopyTree(r->left);
         new_node->right = CopyTree(r->right);
        // memcpy(new_node,r,sizeof(struct node));
          new_node->data = r->data;
          new_node->repeat = r->repeat;
          new_node->size = r->size;
         return new_node;
      }


}


void Insert(struct node * r,int value){

   struct node * pp;
   struct node * p;
   p = r;
   while(p){
     
     pp = p;
     if(p->data > value)p = p->left;
     else if(p->data < value)p = p->right; 
     else{p->repeat++; return;}
   }

   p = (struct node*)malloc(sizeof(struct node));
   p->data = value;
   p->repeat = 0;
   p->left = NULL;
   p->right = NULL;
   p->size = 0;

   if(r){
     if(pp->data > value)pp->left = p;
     else pp->right = p;
     printf("Success!\n");
   }
   else root = p;

}


struct node* find_right_min(struct node* p){

     if(!p)return NULL;
    
     
    
     struct node * pp;
     pp = p;
     p = p->right;

     while(p->left!=NULL){pp = p; p = p->left;}

    if(pp->data > p->data){   
     pp->left = p->right;
     p->right = NULL;
     }
    else{
     pp->right = p->right;
      p->right = NULL;
     }

    return p;
}


void Delete(struct node * r,int value){

   if(!r)return;

   struct node * pp;
   struct node * p;
   pp = NULL;
   p = r;
   while( p!=NULL && p->data != value){

       if(p->data > value){pp = p; p = p->left;}
       else if(p->data < value){pp = p; p = p->right;}
   }


  if(p == NULL){
       printf("The node isn't found.\n");
       return;
    }

  if(p->data == value){
      struct node * replace =(struct node*)malloc(sizeof(struct node)); 
          replace =  find_right_min(p);
             
        if(replace!=NULL){
            replace->left = p->left;
            replace->right = p->right;
          }

        if(pp!=NULL){
              if(pp->data > p->data)pp->left = replace;
              else pp->right = replace;
          }
         else root = replace;
        free(p);
        
      return;
   }

}


int Recursive_Get(struct node * r,int value){

   if(!r)return -1;
   if(r->data > value)Recursive_Get(r->left,value);
   if(r->data < value)Recursive_Get(r->right,value);
   printf("data: %d\n repeat: %d\n",r->data,r->repeat);
   return 0;


}

int Get(struct node * r,int value){

    struct node * current;

    while(current){

      if(current->data < value)current = current->left;
      else if(current->data > value)current = current->right;
      else {
             printf("data: %d\n repeat: %d\n",r->data,r->repeat);
             return 0;
            }

    }

    return -1;

}



int Equivalence(struct node * r1,struct node * r2){

    if( (!r1) && (!r2) )return 1;
   
    else return( r1&&r2
                  && (r1->data == r2->data)
                  && Equivalence(r1->left,r2->left)
                  && Equivalence(r1->right,r2->right) );



}




void Preorder(struct node * r){

    if(r){

     printf("data: %d , repeat: %d, size: %d\n",r->data,r->repeat,r->size);
      Preorder(r->left);
      Preorder(r->right);
    }

}


void Inorder(struct node * r){

    if(r){

      Inorder(r->left);
      printf("data: %d , repeat: %d, size: %d\n",r->data,r->repeat,r->size);
      Inorder(r->right);
    }

}


void Postorder(struct node * r){

    if(r){

      Postorder(r->left);
      Postorder(r->right);
       printf("data: %d , repeat: %d, size: %d\n",r->data,r->repeat,r->size);
    }
}


int Ranknode(struct node * r){

    if(r){

     int leftSize = Ranknode(r->left);
     int rightSize = Ranknode(r->right);
     return r->size = leftSize+rightSize+1;
    }
   
   else return 0;

}


int RankGet(int num,struct node * r){

    struct node * current = r;
    while(current){
       if(num < current->size)current = current->left;
       else if(num > current->size){
          num -= current->size;
           current = current->right;
        }

      else return current->data;


   }
   
  return -1;

}

void Levelorder(struct node * r){

     struct node * current = r; 
  
     while(current){
       printf("data: %d,repeat: %d\n",current->data,current->repeat);
       if(current->left)enqueue(current->left);
       if(current->right)enqueue(current->right);
       if(IsEmpty())return;
        current  = dequeue();
     }


}




int main(){

    //printf("hi!\n");
   Insert(root,5);

   Insert(root,2);
   Insert(root,1);
   Insert(root,3);
   Insert(root,4);

   Insert(root,7);
   Insert(root,6);
   Insert(root,8);
   Insert(root,9);
   Ranknode(root);   

   Preorder(root);
   printf("\n");
   Inorder(root);
   printf("\n");
   Levelorder(root);
   printf("\n");

  new_root = CopyTree(root);

  int w;
  for(w = 0; w < 3; w++){
   int del;  
   scanf("%d",&del); 
   Delete(root,del);
   
    Preorder(root);
   printf("\n");
   Inorder(root);
   printf("\n");
 
  }

  Preorder(new_root);
  printf("\n");
   Inorder(new_root);
   printf("\n");
  // Levelorder(root);
  // printf("\n");

//   printf("#5: %d \n" ,RankGet(5,root));
//   printf("#3: %d \n" ,RankGet(3,root));
 //  printf("#8: %d \n" ,RankGet(8,root));



  printf("Same? : %d \n" ,Equivalence(root,new_root));

 return 0;
}
