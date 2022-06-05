#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//~~~~~~~~~~~~~~~Code for linked List~~~~~~~~~~~~~~~~~~~~~~~~~~~



struct node {
   int data;
   int key;
   int pre_key;
   struct node *next;
};

struct node *head = NULL;
struct node *head2 = NULL; //for copy
struct node *current = NULL;

//display the list
void printList() {
   struct node *ptr = head;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(des:%d,id:%d,origin:%d) ",ptr->key,ptr->data,ptr->pre_key);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

void printListCopy() { //for copy
   struct node *ptr = head2;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(des:%d,id:%d,origin:%d) ",ptr->key,ptr->data,ptr->pre_key);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

//insert link at the first location
void insertFirst(int key, int data , int pre_key) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
  
   link->pre_key = pre_key;
   link->key = key;
   link->data = data;
	
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}

void insertFirstCopy(int key, int data , int pre_key) { //for copy
   //create a link
   struct node *link2 = (struct node*) malloc(sizeof(struct node));
	
  
   link2->pre_key = pre_key;
   link2->key = key;
   link2->data = data;
	
   //point it to old first node
   link2->next = head2;
	
   //point first to new first node
   head2 = link2;
}


int length() {
   int length = 0;
   struct node *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}


int search()
{
   struct node *ptr = head2;
	int counter=0;
   //start from the beginning
   while(ptr != NULL) {
      //printf("(des:%d,id:%d,origin:%d) ",ptr->key,ptr->data,ptr->pre_key);
      counter += ptr->key - ptr->pre_key;
      ptr = ptr->next;
   }
	return counter;  
}


//delete a link with given key
int delete(int key) {

   //start from the first link
   struct node* current = head;
   struct node* previous = NULL;
	
   //if list is empty
   /*if(head == NULL) {
      return NULL;
   }*/

   //navigate through list
   while(current->key != key) {

      //if it is last node
      if(current->next == NULL) {
         return 0;
         //break;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
	
   return 1;
}

//~~~~~~~~~~~~~~~~~End of Code for Linked List~~~~~~~~~~~~~~~~~~~


int id_initialization()
{
   static int id= 0;
   id++;
   return id ;
}


int bus_stop_initialization(int current)
{
  current++;
  return (rand() % (30 - (current) + 1) + (current));
  //(rand() % (max - min +1)) + min)
}


struct best_stop
{
   int stop;
   int capacity;
};

void bsortDesc(struct best_stop list[30], int s)
{
    int i, j;
    struct best_stop temp;
    
    for (i = 0; i < s - 1; i++)
    {
        for (j = 0; j < (s - 1-i); j++)
        {
            if (list[j].capacity < list[j + 1].capacity)
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            } 
        }
    }
}



int main()
{
    //srand(4043);
    struct best_stop bstop[30],nstop[30];
    int starting_pass = rand() % 16;
    int bus_stop_pass = rand() % 8; 
    int pp = 0;
    int pp2 =0;
    int max = 0;
    //struct node *pass_node;
    //int bus_capacity = 0; //Up to 85 
    int total_served= starting_pass;
    int total_not_served = 0; 
    bstop[0].stop = 1 ;
    bstop[0].capacity = starting_pass;
    nstop[0].stop = 1 ;
    nstop[0].capacity = 0;
    for(int i=0; i<starting_pass; i++)
    {
       pp=bus_stop_initialization(1);
       pp2 =id_initialization();
       insertFirst(pp,pp2,1);
       insertFirstCopy(pp,pp2,1);
    }
    //struct node *found;
   // printf("Starting pass:%d",starting_pass); debug
    for(int i=2; i<=29; i++)
    {
       bstop[i-1].stop = i;
       nstop[i-1].stop = i;
       //printf("stop:%d i:%d\n",bstop[i].stop,i); debug
       
       for(int x=0; x<length(); x++) //Deletes the passengers 
       {
          max+=delete(i);
       }
       
       nstop[i-1].capacity = max;
       max =0;

       bus_stop_pass = rand() % 8; // it is 8
       //printf("\n bus_stop_pass:%d ",bus_stop_pass); debug
       if(length() + bus_stop_pass > 85) //Overcrowded 
       {
          total_not_served += ((length() + bus_stop_pass) - 85 ) ;
          bus_stop_pass = bus_stop_pass-((length() + bus_stop_pass) - 85 );
       }
       
       for(int g=0; g<bus_stop_pass; g++) //Adds the passengers
       {
          pp=bus_stop_initialization(i);
          pp2 = id_initialization();
          insertFirst(pp,pp2,i);
          insertFirstCopy(pp,pp2,i);
          //insertFirst(bus_stop_initialization(i),id_initialization(),i);
       }
       
       bstop[i-1].capacity = length();
       //printList(); debug
       total_served+=bus_stop_pass;
       //printf("bus_stop_bass:%d ",bus_stop_pass); debug
       //printf("stop:%d capacity:%d total_not_served:%d  total_served:%d\n ",i,length(),total_not_served,total_served);   debug    
    }
    bstop[29].stop =30;
    bstop[29].capacity = length();
    nstop[29].stop =30;
    nstop[29].capacity = length();
    /*while(length() != 0) //Release the last passengers
       {
          //printf("%d\n",length()); debug
          delete(30);
       }*/   
    //printList(); debug
    bsortDesc(bstop,30); //sorting for best stop
    bsortDesc(nstop,30);

    /*for(int i=0; i<30; i++)
    {
       printf(" bstop stop:%d capacity:%d \n",bstop[i].stop,bstop[i].capacity);
    }

    for(int i=0; i<30; i++)
    {
       printf("nstop stop:%d capacity:%d \n",nstop[i].stop,nstop[i].capacity);
    }
    
    printListCopy();
    

    */ //debug

    printf("1:Total number of passengers:%d\n",total_served);
    printf("2:Total number of people not served:%d\n",total_not_served);
    printf("3:Most popular stop:%d\n",bstop[0].stop);
    printf("4:Most popular destination:%d\n",nstop[0].stop);
    printf("5:Average distance:%d\n",search()/total_served);
    return 0 ;
}
