#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#define SIZE 1024
#define OFFSET 72


int mygetch ( void ) 
{
  int ch;
  struct termios oldt, newt;
  
  tcgetattr ( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );
  
  return ch;
}





typedef struct pilots

{

        char Lname[24];

        char Fname[24];

        char Phone[15];

        char Genter;

        unsigned short int BirthDay;

        unsigned short int BirthMonth;

        unsigned short int BirthYear;

        unsigned short int Hours;

}pilots;


struct node
{
    int addr;
    int hours; //node will store an integer
    struct node *right_child; // right child
    struct node *left_child; // left child
};

struct node* new_node(int addr,int hours) 
{
    struct node *p;
    p = malloc(sizeof(struct node));
    p->addr = addr;
    p->hours = hours;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}


struct node* insert(struct node *root, int addr,int hours)
{
    //searching for the place to insert
    if(root==NULL)
        return new_node(addr,hours);
    else if(hours>root->hours) // x is greater. Should be inserted to right
        root->right_child = insert(root->right_child, addr,hours);
    else // x is smaller should be inserted to left
        root->left_child = insert(root->left_child,addr,hours);
    return root;
}





void inorder(struct node *root)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left_child); // visiting left child
        printf("hours:%d addr:%d \n", root->hours,root->addr); // printing data at root
        
        inorder(root->right_child);// visiting right child
    }
}

bool compare_dates (pilots root)
{
    if (root.BirthYear < 1980)
       return false;

    else if (root.BirthYear > 1980)
       return true;

    if (root.BirthYear == 1980)
    {
         if (root.BirthMonth < 1)
              return false;
         else if (root.BirthMonth >1)
              return true;
         else if (root.BirthDay < 1)
              return false;
         else if(root.BirthDay >1)
              return true;
         else
              return false;
    }
    return false;
}



void Find_number(struct node *root,char * phone,FILE *fp)
{
  if(root!=NULL) // checking if the root is not null
    {
        Find_number(root->left_child,phone,fp); // visiting left child
        //printf("hours:%d addr:%d \n", root->hours,root->addr); // printing data at root
        pilots temp;
        fseek(fp,root->addr - OFFSET,SEEK_SET);
        fread(&temp,OFFSET,1,fp);
        if(strcmp(temp.Phone,phone) == 0) 
        {
           printf("hours:%d yy/mm/dd:%d/%d/%d sex:%c Lname:%.24s Fname:%.24s Phone:%.15s\n",temp.Hours,temp.BirthYear,temp.BirthMonth,temp.BirthDay,temp.Genter,temp.Lname,temp.Fname,temp.Phone);
        }
        Find_number(root->right_child,phone,fp);// visiting right child
    }
}






void Find_above_and_below(struct node *root, int k1, int k2,FILE * fp)
{
   /* base case */
   if ( NULL == root )
      return;
 
   /* Since the desired o/p is sorted, recurse for left subtree first
      If root->data is greater than k1, then only we can get o/p keys
      in left subtree */
   if ( k1 < root->hours )
     Find_above_and_below(root->left_child, k1, k2,fp);
 
   /* if root's data lies in range, then prints root's data */
   if ( k1 <= root->hours && k2 >= root->hours )
   {
     //printf("%d ", root->data.Hours );
      pilots temp;
      fseek(fp,root->addr - OFFSET,SEEK_SET);
      fread(&temp,OFFSET,1,fp);
      printf("hours:%d yy/mm/dd:%d/%d/%d sex:%c Lname:%.24s Fname:%.24s Phone:%.15s\n",temp.Hours,temp.BirthYear,temp.BirthMonth,temp.BirthDay,temp.Genter,temp.Lname,temp.Fname,temp.Phone);
   }   
  /* recursively call the right subtree */
   Find_above_and_below(root->right_child, k1, k2,fp);
}

void Find_above_and_below_woman(struct node *root, int k1, int k2,FILE * fp)
{
   /* base case */
   if ( NULL == root )
      return;
 
   /* Since the desired o/p is sorted, recurse for left subtree first
      If root->data is greater than k1, then only we can get o/p keys
      in left subtree */
   if ( k1 < root->hours )
     Find_above_and_below_woman(root->left_child, k1, k2,fp);
 
   /* if root's data lies in range, then prints root's data */
   if ( k1 <= root->hours && k2 >= root->hours )
   {
     //printf("%d ", root->data.Hours );
      pilots temp;
      fseek(fp,root->addr - OFFSET,SEEK_SET);
      fread(&temp,OFFSET,1,fp);
      if(temp.Genter == 'F')
      {
        printf("hours:%d yy/mm/dd:%d/%d/%d sex:%c Lname:%.24s Fname:%.24s Phone:%.15s\n",temp.Hours,temp.BirthYear,temp.BirthMonth,temp.BirthDay,temp.Genter,temp.Lname,temp.Fname,temp.Phone);
      }
   }   
  /* recursively call the right subtree */
   Find_above_and_below_woman(root->right_child, k1, k2,fp);
}


void Find_above_and_below_men_date(struct node *root, int k1, int k2,FILE * fp)
{
   /* base case */
   if ( NULL == root )
      return;
 
   /* Since the desired o/p is sorted, recurse for left subtree first
      If root->data is greater than k1, then only we can get o/p keys
      in left subtree */
   if ( k1 < root->hours )
     Find_above_and_below_men_date(root->left_child, k1, k2,fp);
 
   /* if root's data lies in range, then prints root's data */
   if ( k1 <= root->hours && k2 >= root->hours )
   {
     //printf("%d ", root->data.Hours );
      pilots temp;
      fseek(fp,root->addr - OFFSET,SEEK_SET);
      fread(&temp,OFFSET,1,fp);
      if(temp.Genter == 'M' && compare_dates(temp))
        printf("hours:%d yy/mm/dd:%d/%d/%d sex:%c Lname:%.24s Fname:%.24s Phone:%.15s\n",temp.Hours,temp.BirthYear,temp.BirthMonth,temp.BirthDay,temp.Genter,temp.Lname,temp.Fname,temp.Phone);
   }   
  /* recursively call the right subtree */
   Find_above_and_below_men_date(root->right_child, k1, k2,fp);
}





int main()
{
   struct node *root;
   FILE *fp;
 
   if((fp = fopen("pilots.txt","rb")) == NULL) //Open the file for reading
   {
       printf("Error!");
       return 1;
   }
   
   pilots temp;
   fread(&temp,sizeof(pilots),1,fp);
   root = new_node(OFFSET,temp.Hours);


   int addr[SIZE];
   addr[0] = -1; 
    
   for(int i=2; i<=SIZE; i++) //Mapping hours to addrs
   {
      //addr[i] = sizeof(pilots) * i;
      //printf(" i:%d %d\n",i,addr[i]);
      fread(&temp,sizeof(pilots),1,fp);
      insert(root,i*OFFSET,temp.Hours);
   }
   //inorder(root); DEBUG
   //Find_above_and_below(root,9500,12000,fp); 
     //Find_above_and_below_woman(root,4500,9500,fp);
     //Find_above_and_below_men_date(root,9500,12000,fp);
   //Find_number(root,"6934012084",fp);
    
  Find_above_and_below(root,9500,12000,fp); //Answer 2 
  printf("~~~~~~~~~~~~~~~~~~~~Press Any Key to Continue~~~~~~~~~~~~~~~~\n");
  mygetch();
  Find_above_and_below_men_date(root,9500,12000,fp); //Answer 3 
  printf("~~~~~~~~~~~~~~~~~~~~Press Any Key to Continue~~~~~~~~~~~~~~~~\n");
  mygetch();
  Find_above_and_below_woman(root,4500,9500,fp); //Answer 4
  printf("~~~~~~~~~~~~~~~~~~~~Press Any Key to Continue~~~~~~~~~~~~~~~~\n");
  mygetch();
  Find_number(root,"6934012084",fp);

  fclose(fp);

}