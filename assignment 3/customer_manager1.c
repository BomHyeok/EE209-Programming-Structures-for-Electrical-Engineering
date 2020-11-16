/*
임범혁
20140475

assignment3

customer_manager1.c
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "customer_manager.h"

/*----------------------------------------------------------------------*/

#define UNIT_ARRAY_SIZE 64

struct UserInfo {
  char *name;                // customer name
  char *id;                  // customer id
  int purchase;              // purchase amount (> 0)
};

struct DB {
  struct UserInfo *pArray;   // pointer to the array
  int curArrSize;            // current array size (max # of elements)
  int numItems;              // # of stored items, needed to determine
			     // # whether the array should be expanded
			     // # or not
};

/*----------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
DB_T
CreateCustomerDB(void)
{
  // struct database d which points to CustomerInfo
  DB_T d;

  // allocate memory into d and if it is failed, return null
  d = (DB_T) calloc(1, sizeof(struct DB));
  if (d == NULL) {
    fprintf(stderr, "Can't allocate a memory for DB_T\n");
    return NULL;
  }

  // initialize array size into 64, number of items into 0
  d->curArrSize = UNIT_ARRAY_SIZE; // start with 64 elements
  d->numItems = 0;

  // allocate array which i will store info of customer
  // if it is failed return -1
  d->pArray = (struct UserInfo *)calloc(d->curArrSize, sizeof(struct UserInfo));
  if (d->pArray == NULL) {
    fprintf(stderr, "Can't allocate a memory for array of size %d\n",
	    d->curArrSize);
    return NULL;
  }

  // create database succecfully, return database d
  return d;
}
/*--------------------------------------------------------------------*/
void
DestroyCustomerDB(DB_T d)
{
  // check if d is null
  if (d == NULL) return;

  /* free name and id in the every array one by one */
  for (int num=0 ; num < d->curArrSize ; num++){
    if ((d->pArray+num)->name && (d->pArray+num)->id){
      free((d->pArray+num)->name);
      free((d->pArray+num)->id);
    }
  }
  
  /* free pArray which I allocated in RegisterCustomer */
  free(d->pArray);
  free(d);
  return;
}
/*--------------------------------------------------------------------*/
int
RegisterCustomer(DB_T d, const char *id,
		 const char *name, const int purchase)
{
  /* check if d, id, name, purchase is null */
  if (d == NULL) return (-1);
  if (id == NULL || name == NULL || purchase<=0) return (-1);

  /* check if recived name or id are already in the array */
  for (int num=0 ; num < d->curArrSize ; num++){
    if ((d->pArray+num)->name && (d->pArray+num)->id)
      // name and id in array should not be null pointers */
      if (strcmp((d->pArray+num)->name, name) == 0 || strcmp((d->pArray+num)->id, id) == 0)
	return (-1);
  }

  // if number of  items is same as array size
  // we need more space in array to store more customer info
  if (d->numItems == d->curArrSize){
    d->curArrSize += UNIT_ARRAY_SIZE; // expand as unit array size, 64
    d->pArray = (struct UserInfo *) realloc (d->pArray, (sizeof(struct UserInfo)) * (d->curArrSize));                                    
    if (d->pArray == NULL){ // if realloc failed, return -1
      fprintf(stderr, "Can't allocate a memory for array of size %d\n", d->curArrSize);
      return -1;
    }

    // realloc doesn't initialize a memory, thus I initialized a new memory into null
    for (int num=(d->curArrSize) - UNIT_ARRAY_SIZE ; num < d->curArrSize ; num++){
      (d->pArray+num)->name = NULL;
      (d->pArray+num)->id = NULL;
      (d->pArray+num)->purchase = 0;
    }
    
  }

  // find a closest empty userinfo in the array
  // copying into array with strdup and increase number of items
  for (int num=0 ; num < d->curArrSize ; num++){
    if((d->pArray+num)->name == NULL){
      // if it is failed to copy, return -1
      if(((d->pArray+num)->name = strdup(name)) == NULL)
	return (-1);
      if(((d->pArray+num)->id = strdup(id)) == NULL)
	return (-1);
      (d->pArray+num)->purchase = purchase;
      d->numItems++;
      // register successfully and return 0
      return 0;
    }
  }

  // register failed and return -1
  return (-1);
}
/*--------------------------------------------------------------------*/
int
UnregisterCustomerByID(DB_T d, const char *id)
{
  // chaeck if d and id are null
  if (d == NULL) return -1;
  if (id == NULL) return -1;
  
  // find a customer whose id is same as typed id
  for (int num=0 ; num < d->curArrSize ; num++){
    if ((d->pArray+num)->name && (d->pArray+num)->id){
      // if we find it, free name, id, and put null into name, id pointer
      if (strcmp((d->pArray+num)->id, id) == 0){
	free((d->pArray+num)->name);
	free((d->pArray+num)->id);
	(d->pArray+num)->name = NULL;
	(d->pArray+num)->id = NULL;
	(d->pArray+num)->purchase = 0;
	d->numItems--;
	// unregister successfully and return 0
	return 0;
      }
    }
  }

  // if we couldn't find, return -1
  return (-1);
}

/*--------------------------------------------------------------------*/
// same as UnregisterCustomerByID
int
UnregisterCustomerByName(DB_T d, const char *name)
{
  if (d == NULL) return -1;
  if (name == NULL) return -1;
  
  for (int num=0 ; num < d->curArrSize ; num++){
    if ((d->pArray+num)->name && (d->pArray+num)->id){
      if (strcmp((d->pArray+num)->name, name) == 0){
	free((d->pArray+num)->name);
	free((d->pArray+num)->id);
	(d->pArray+num)->name = NULL;
	(d->pArray+num)->id = NULL;
	(d->pArray+num)->purchase = 0;
	d->numItems--;
	return 0;
      }
    }
  }
  return (-1);
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByID(DB_T d, const char* id)
{
  // check if d, id are null
  if (d == NULL) return -1;
  if (id == NULL) return -1;

  for (int num=0 ; num < d->curArrSize ; num++){
    if ((d->pArray+num)->name && (d->pArray+num)->id)
      // if we find typed id, return purchase of that customer
      if (strcmp((d->pArray+num)->id, id) == 0)
	return (d->pArray+num)->purchase;
  }

  // if we couldn't find, return -1
  return (-1);
}
/*--------------------------------------------------------------------*/
// same as GetPutchaseByID
int
GetPurchaseByName(DB_T d, const char* name)
{
  if (d == NULL) return -1;
  if (name == NULL) return -1;

  for (int num=0 ; num < d->curArrSize ; num++){
    if ((d->pArray+num)->name && (d->pArray+num)->id)
      if (strcmp((d->pArray+num)->name, name) == 0)
	return (d->pArray+num)->purchase;
  }
  
  return (-1);
}
/*--------------------------------------------------------------------*/
int
GetSumCustomerPurchase(DB_T d, FUNCPTR_T fp)
{
  // check if d, fp are null
  if (d == NULL || fp == NULL) return (-1);
  // sum that customer purchase from fp
  int sum=0;

  // sum all the purchase that are returned from fp
  for (int num=0 ; num < d->curArrSize ; num++)
    if ((d->pArray+num)->name && (d->pArray+num)->id)
      sum += fp((d->pArray+num)->id, (d->pArray+num)->name, (d->pArray+num)->purchase);
  
  return sum;
}
