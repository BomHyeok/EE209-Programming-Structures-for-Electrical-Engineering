#include <assert.h> /* to use assert() */
#include <stdio.h>
#include "str.h"

/* Your task is: 
   1. Rewrite the body of "Part 1" functions - remove the current
      body that simply calls the corresponding C standard library
      function.
   2. Write appropriate comment per each function
*/

/* Part 1 */
/*------------------------------------------------------------------------*/
size_t StrGetLength(const char* pcSrc)
{
  const char *pcEnd;
  assert(pcSrc); /* NULL address, 0, and FALSE are identical. */
  pcEnd = pcSrc;
	
  while (*pcEnd) /* null character and FALSE are identical. */
    pcEnd++;

  return (size_t)(pcEnd - pcSrc);
}

/*------------------------------------------------------------------------*/
char *StrCopy(char *pcDest, const char* pcSrc)
{
  assert(pcDest && pcSrc);
  /* pcDest always points to the first memory of pcDest */
  char *pcDestCpy = pcDest;
  /* pcSrc always points to the first memory of pcSrc */
  const char*pcSrcCpy = pcSrc;

  /* copying one by one */
  while (*pcSrcCpy){
    *pcDestCpy = *pcSrcCpy;
    pcDestCpy++;
    pcSrcCpy++;
  }
  /* while loop doesn't copy '\0' which is the end of pcSrc */
  *pcDestCpy = '\0';
  
  return pcDest;
}

/*------------------------------------------------------------------------*/
int StrCompare(const char* pcS1, const char* pcS2)
{
  assert(pcS1 && pcS2);
  /* pcS1, pcS2 always points to the first memory of pcS1, pcS2 respectively */
  const char *pcS1Cpy = pcS1, *pcS2Cpy = pcS2;

  int result=0;

  while (*pcS1Cpy){
    if (*pcS1Cpy != *pcS2Cpy){
      result = *pcS1Cpy - *pcS2Cpy;
      /* if characters are different, stop the funtion and return difference of characters */
      return result;
    }
    pcS1Cpy++;
    pcS2Cpy++;
  }
  /* if pcS1 ends first, return minus of character of pcS2 */
  if (*pcS2Cpy) result=-*pcS2Cpy;

  return result;
}
/*------------------------------------------------------------------------*/
char *StrSearch(const char* pcHaystack, const char *pcNeedle)
{
  assert(pcHaystack && pcNeedle);

  const char *FirstOccur = pcHaystack;
  /* pcHaystack, pcNeedle always points to the first memory of pcHatstack, pcNeedle respectively */
  const char *pcHCpy = pcHaystack, *pcNCpy = pcNeedle;

  int state = 1;
  
  while (*pcHCpy){
    switch(state){
    case 1: /* if characters are different */
      if (!*pcNCpy)
	return (char *) FirstOccur;
      if (*pcHCpy == *pcNCpy){
	/* if first charater of pcNeedle is found, go to state2 
	   and store address of it in FirstOccur */
        state = 2;
        FirstOccur = pcHCpy;
        pcNCpy++;
      }
      pcHCpy++;
      break;
    case 2:
      if (!*pcNCpy){
	/* if pcNeedle is in pcHaystack, return pcHaystack 
	   from word which is same as pcNeedel */
        return (char *) FirstOccur;
      }
      else if (*pcHCpy != *pcNCpy){
	/* if pcNeedle isn't in pcHaystack, go to state1 
	   and initialize pcNCpy, FirstOccur */
        state = 1;
        pcNCpy = pcNeedle;
	FirstOccur = pcHaystack;
      }
      else pcNCpy++;
      pcHCpy++;
      break;
    }
  }
  /* if pcHaystack ends during checking pcNeedle characters one by one
     and pcNeedle doesn't end */
  if (state == 2 && !*pcNCpy)
    return (char *) FirstOccur;

  return NULL;
}
/*-------------------------------------------------------------------------*/
char *StrConcat(char *pcDest, const char* pcSrc)
{
  assert(pcDest && pcSrc);
  /* pcDest, pcSrc always points to the first memory of pcDest, pcSrc respectively */
  char* pcDestCpy;
  const char* pcSrcCpy;
  pcDestCpy = pcDest;
  pcSrcCpy = pcSrc;

  /* pcDestCpy points to the end of pcDest */
  while (*pcDestCpy)
    pcDestCpy++;
  /* Add pcSrc at the end of pcDest */
  while (*pcSrcCpy){
    *pcDestCpy = *pcSrcCpy;
    pcDestCpy++;
    pcSrcCpy++;
  }
  *pcDestCpy = '\0';

  return pcDest;
}
