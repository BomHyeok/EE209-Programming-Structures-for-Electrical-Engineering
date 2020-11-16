/*
임범혁
20140475

assignment3

customer_manager2.c
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "customer_manager.h"

/*----------------------------------------------------------------------*/

struct UserInfo {
  char *name;                // customer name
  char *id;                  // customer id
  int purchase;              // purchase amount (> 0)
  struct UserInfo *NextCustomer;
};

struct DB {
  struct UserInfo *NextCustomer;   // pointer to the info of customer
};

/*----------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
DB_T
CreateCustomerDB(void){
  // make database head that is pointing to the info of customer
  DB_T head;
  
  // allocate for head and if it failed, return -1
  head = (DB_T) calloc(1, sizeof(struct DB));
  if (head == NULL) {
    fprintf(stderr, "Can't allocate a memory for DB_T\n");
    return NULL;
  }
  
  // initialize a pointer NextCustomer
  head->NextCustomer = NULL;

  // if creating database successfully return the database head
  return head;
}
/*--------------------------------------------------------------------*/
void
DestroyCustomerDB(DB_T d)
{
  // check if d is null
  if (d == NULL) return;
  
  struct UserInfo *p;
  struct UserInfo *nextp;
  
  // p points to customer which I want to modify
  // nextp porints to next customer which is p points to
  for (p = d->NextCustomer ; p != NULL ; p = nextp){
    // at first loop, p can be null, and if it is, do nothing
    if(p){
      nextp = p->NextCustomer;
      // free name, id pointer and entire info of customer
      free(p->name);
      free(p->id);
      free(p);
    }
  }
  // free database
  free(d);
  
  return;
}
/*--------------------------------------------------------------------*/
int
RegisterCustomer(DB_T d, const char *id,
		 const char *name, const int purchase)
{
  // check if d, id, name is null and purchase is smaller or equal to 0
  if (d == NULL) return (-1);
  if (id == NULL || name == NULL || purchase<=0) return (-1);

  struct UserInfo *p;

  // check if same id, name are already exist in the database
  // if it is, return -1
  for (p = d->NextCustomer ; p != NULL ; p = p->NextCustomer){
    // p points to customer which I want to modify
    // at first loop, p can be null, and if it is, do nothing{
    if(p){
      if (strcmp(p->id, id) == 0 || strcmp(p->name, name) == 0)
        return (-1);
    }
  }

  // allocate memory for new customer to store
  // if it is failed, return -1
  struct UserInfo *NewCustomer = (struct UserInfo *)calloc(1, sizeof(struct UserInfo));
  if (NewCustomer == NULL){
    fprintf(stderr, "Can't allocate a memory for UserInfo");   
    return (-1);
  }

  // update id, name, purchase and pointer to next customer
  // copying into array with strdup and increase number of items
  // if it is failed, return -1
  if ((NewCustomer->name = strdup(name)) == NULL)
    return (-1);
  if ((NewCustomer->id = strdup(id)) == NULL)
    return (-1);
  NewCustomer->purchase = purchase;
  NewCustomer->NextCustomer = d->NextCustomer;
  d->NextCustomer = NewCustomer;

  // register succesfully, return 0
  return 0;
}
/*--------------------------------------------------------------------*/
int
UnregisterCustomerByID(DB_T d, const char *id)
{
  // check if d, id is null
  if (d == NULL) return -1;
  if (id == NULL) return -1;
  
  struct UserInfo *p;
  struct UserInfo *pointing_p;
  int num=0;

  // find customer whose id is input id
  for (p = d->NextCustomer ; p != NULL ; p = p->NextCustomer){
    // p points to the customer info which I want to modify
    // pointg_p points to the previous customer info which is pointinf p
    // at first loop, p can be null, and if it is, do nothing
    if (p){
      if (strcmp(p->id, id) == 0){
	// if found customer is stored as first or not
	// update previous pointer of p points to next customer to the p
	if (num == 0)
          d->NextCustomer = p->NextCustomer;
        else
          pointing_p->NextCustomer = p->NextCustomer;
	// free name, id of p and free p
	// freed successfully, return 0
	free(p->name);
	free(p->id);
	free(p);
	return 0;
      }
      pointing_p = p;
      num++;
    }
  }

  // if we couldn't find customer whose id is input id, return -1
  return (-1);
}

/*--------------------------------------------------------------------*/
// same as UnregisterCustomerByName
int
UnregisterCustomerByName(DB_T d, const char *name)
{
  if (d == NULL) return -1;
  if (name == NULL) return -1;

  struct UserInfo *p;
  struct UserInfo *pointing_p;
  int num=0;

  for (p = d->NextCustomer ; p != NULL ; p = p->NextCustomer){
    // p points to customer which I want to modify
    // at first loop, p can be null, and if it is, do nothing
   if (p){
      if (strcmp(p->name, name) == 0){
	if (num == 0)
	  d->NextCustomer = p->NextCustomer;
        else
          pointing_p->NextCustomer = p->NextCustomer;
	free(p->name);
        free(p->id);
	free(p);
	return 0;
      }
      pointing_p = p;
      num++;
    }
  }

  return (-1);
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByID(DB_T d, const char* id)
{
  // check id d, id is null
  if (d == NULL) return -1;
  if (id == NULL) return -1;
  
  struct UserInfo *p;

  for (p = d->NextCustomer ; p != NULL ; p = p->NextCustomer){
    // p points to customer which I want to modify
    // at first loop, p can be null, and if it is, do nothing
    if (p)
      if (!strcmp(p->id, id))
	// if we find customer has same id, return purchase of that customer
	return p->purchase;
  }

  //if we couldn't find, return -1
  return (-1);
}
/*--------------------------------------------------------------------*/
// same as GetPurchaseByName
int
GetPurchaseByName(DB_T d, const char* name)
{
  if (d == NULL) return -1;
  if (name == NULL) return -1;

  struct UserInfo *p;

  for (p = d->NextCustomer ; p != NULL ; p = p->NextCustomer){
    // p points to customer which I want to modify
    // at first loop, p can be null, and if it is, do nothing
    if (p)
      if (!strcmp(p->name, name))
	return p->purchase;
  }

  return (-1);
}
/*--------------------------------------------------------------------*/
int
GetSumCustomerPurchase(DB_T d, FUNCPTR_T fp)
{
  // check if d and fp is null
  if (d == NULL || fp == NULL) return (-1);

  // sum of customer purchase from fp
  int sum=0;
  struct UserInfo *p;

  // sum all the purchase that are returned from fp
  for (p = d->NextCustomer ; p != NULL ; p = p->NextCustomer)
    if(p)
      // p points to customer which I want to modify 
      sum += fp(p->id, p->name, p->purchase);
  
  return sum;  
}
