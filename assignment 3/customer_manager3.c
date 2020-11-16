/* 
임범혁
20140475

assignment3

customer_manager3.c
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "customer_manager.h"

#define UNIT_ARRAY_SIZE 1024
enum {HASH_MULTIPLIER = 65599};

struct UserInfo {
  char *name;                // customer name
  char *id;                  // customer id
  int purchase;              // purchase amount (> 0)
  // pointer to the next customer by name
  struct UserInfo *NextCusByName;
  // pointer to the next customer by id
  struct UserInfo *NextCusByID;
};

struct DB {
  // pointer to the hash table by id
  struct UserInfo *HT_ID[UNIT_ARRAY_SIZE];
  // pointer to the hash table by name
  struct UserInfo *HT_NAME[UNIT_ARRAY_SIZE];
};

/*----------------------------------------------------------------------*/

 /*--------------------------------------------------------------------*/

static int hash_function(const char *pcKey, int iBucketCount)
{
   int i;
   unsigned int uiHash = 0U;
   for (i = 0; pcKey[i] != '\0'; i++)
      uiHash = uiHash * (unsigned int)HASH_MULTIPLIER
               + (unsigned int)pcKey[i];
   return (int)(uiHash % (unsigned int)iBucketCount);
}

DB_T CreateCustomerDB(void)
{
  // make database d that is pointing to the info of customer
  DB_T d;

  // allocate for d and if it failed, return -1    
  d = (DB_T) calloc(1, sizeof(struct DB));
  if (d == NULL) {
    fprintf(stderr, "Can't allocate a memory for DB_T\n");
    return NULL;
  }

  // initialize every element of array hash table of id, name into null
  for (int num=0 ; num < UNIT_ARRAY_SIZE ; num++){
    d->HT_ID[num] = NULL;
    d->HT_NAME[num] = NULL;
  }

  // if creating database successfully return the database head 
  return d;
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
  for (int num=0 ; num < UNIT_ARRAY_SIZE ; num++)
    for (p = d->HT_ID[num] ; p != NULL ; p = nextp)
      if(p){
	nextp = p->NextCusByID;
	// free name, id pointer and entire info of customer
	free(p->name);
	free(p->id);
	free(p);
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
  
  // hash code of recieved id, name
  int ID_num = hash_function(id, UNIT_ARRAY_SIZE);
  int NAME_num = hash_function(name, UNIT_ARRAY_SIZE);
  struct UserInfo *p;

  // check if same id, name are already exist in the database
  // if it is, return -1
  for (p = d -> HT_ID[ID_num] ; p != NULL ; p = p->NextCusByID){
    // p points to customer which I want to modify
    // at first loop, p can be null, and if it is, do nothing
    if(p)
      if (strcmp(p->id, id) == 0 || strcmp(p->name, name) == 0)
        return (-1);
  }
  for (p = d -> HT_NAME[NAME_num] ; p != NULL ; p = p->NextCusByName\
){
    if(p)
      if (strcmp(p->id, id) == 0 || strcmp(p->name, name) == 0)
        return (-1);
  }

  // allocate memory for new customer to store
  // if it is failed, return -1
  struct UserInfo *NewCustomer = (struct UserInfo *)calloc(1, sizeof(struct UserInfo));
  if (NewCustomer == NULL){
    fprintf(stderr, "Can't allocate a memory for UserInfo");
    free(d);
    return (-1);
  }

  // update id, name, purchase
  // copying into array with strdup and increase number of items
  // if it is failed, return -1 
  if((NewCustomer->name = strdup(name)) == NULL)
    return -1;
  if((NewCustomer->id = strdup(id)) == NULL)
    return -1;
  NewCustomer->purchase = purchase;

  // update pointer to next customer by id, name repectively
  NewCustomer->NextCusByName = d->HT_NAME[NAME_num];
  d->HT_NAME[NAME_num] = NewCustomer;

  NewCustomer->NextCusByID = d->HT_ID[ID_num];
  d->HT_ID[ID_num] = NewCustomer;
  
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

  // hash code of recieved id
  int ID_num = hash_function(id, UNIT_ARRAY_SIZE);
  int num=0;

  // p points to the customer info which I want to modify
  // pointg_p points to the previous customer info which is pointing p   
  for (p = d->HT_ID[ID_num] ; p != NULL ; p = p->NextCusByID){
    // at first loop, p can be null, and if it is, do nothing 
    if (p){
      if (strcmp(p->id, id) == 0){
	// if found customer is stored as first or not
	// update previous pointer of p points to next customer to the p
        if (num == 0)
          d->HT_ID[ID_num] = p->NextCusByID;
        else
          pointing_p->NextCusByID = p->NextCusByID;
	break;
      }
      pointing_p = p;
      num++;
    }
  }
  // if we couldn't find customer that has same id, p will be null
  // and check if p is null, return -1
  if (p == NULL) return (-1);

  // hash code of recieved name
  int NAME_num = hash_function(p->name, UNIT_ARRAY_SIZE);
  struct UserInfo *q;
  struct UserInfo *pointing_q;
  num = 0;

  // this loop is to free the connection between hash table by name
  // and customer info that has same id
  for (q = d->HT_NAME[NAME_num] ; q != NULL ; q = q->NextCusByName){
    if (q){
      if (strcmp(p->name, q->name) == 0){
        if (num == 0)
          d->HT_NAME[NAME_num] = q->NextCusByName;
        else
          pointing_q->NextCusByName = q->NextCusByName;
	// free name, id of p and free p
	// freed successfully, return 0
	free(q->name);                                                                                                                                      
        free(q->id);                                                                                                                                        
        free(q);
	return 0;
      }
      pointing_q = q;
      num++;
    }
  }

  // if unregister is not successful, return -1
  return (-1);
}

/*--------------------------------------------------------------------*/
//same as UnregisterCustomerByID
int
UnregisterCustomerByName(DB_T d, const char *name)
{
  if (d == NULL) return -1;
  if (name == NULL) return -1;

  struct UserInfo *p;
  struct UserInfo *pointing_p;

  int NAME_num = hash_function(name, UNIT_ARRAY_SIZE);
  int num=0;

  for (p = d->HT_NAME[NAME_num] ; p != NULL ; p = p->NextCusByName){
    if (p){
      if (strcmp(p->name, name) == 0){
        if (num == 0)
          d->HT_NAME[NAME_num] = p->NextCusByName;
        else
          pointing_p->NextCusByName = p->NextCusByName;
	break;
      }
      pointing_p = p;
      num++;
    }
  }
  if (p == NULL) return (-1);

  int ID_num = hash_function(p->id, UNIT_ARRAY_SIZE);
  struct UserInfo *q;
  struct UserInfo *pointing_q;
  num = 0;

  for (q = d->HT_ID[ID_num] ; q != NULL ; q = q->NextCusByID){
    if (q){
      if (strcmp(p->id, q->id) == 0){
        if (num == 0)
          d->HT_ID[ID_num] = q->NextCusByID;
        else
          pointing_q->NextCusByID = q->NextCusByID;
        free(q->name);
        free(q->id);
        free(q);
        return 0;
      }
      pointing_q = q;
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

  // p points to customer which I want to modify  
  struct UserInfo *p;
  // hash code of recieved name
  int ID_num = hash_function(id, UNIT_ARRAY_SIZE);
  
  for (p = d->HT_ID[ID_num] ; p != NULL ; p = p->NextCusByID){
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
// same as GetPurchaseByID
int
GetPurchaseByName(DB_T d, const char* name)
{
  if (d == NULL) return -1;
  if (name == NULL) return -1;

  struct UserInfo *p;
  
  int NAME_num = hash_function(name, UNIT_ARRAY_SIZE);

  for (p = d->HT_NAME[NAME_num] ; p != NULL ; p = p->NextCusByName){
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
  for (int num=0 ; num < UNIT_ARRAY_SIZE ; num++)
    for (p = d->HT_ID[num] ; p != NULL ; p = p->NextCusByID)
      // p points to customer which I want to modify
      if (p)
	sum += fp(p->id, p->name, p->purchase);

  return sum;
}
