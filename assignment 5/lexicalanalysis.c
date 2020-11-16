/*--------------------------------------------------------------------*/
/* dfa.c                                                              */
/* Original Author: Bob Dondero                                       */
/* Illustrate lexical analysis using a deterministic finite state     */
/* automaton (DFA)                                                    */
/*--------------------------------------------------------------------*/

#include "dynarray.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

enum {MAX_LINE_SIZE = 1024};

enum {FALSE, TRUE};

enum TokenType {TOKEN_NUMBER, TOKEN_WORD};

/*--------------------------------------------------------------------*/

/* A Token is either a number or a word, expressed as a string. */

struct Token
{
   enum TokenType eType;
   /* The type of the token. */

   char *pcValue;
   /* The string which is the token's value. */
};

/*--------------------------------------------------------------------*/

static void freeToken(void *pvItem, void *pvExtra)

/* Free token pvItem.  pvExtra is unused. */

{
   struct Token *psToken = (struct Token*)pvItem;
   free(psToken->pcValue);
   free(psToken);
}

/*--------------------------------------------------------------------*/
/*
static void printNumberToken(void *pvItem, void *pvExtra)

Print token pvItem to stdout iff it is a number.  pvExtra is
   unused. 

{
   struct Token *psToken = (struct Token*)pvItem;
   if (psToken->eType == TOKEN_NUMBER)
      printf("%s ", psToken->pcValue);
}
*/
/*--------------------------------------------------------------------*/

static void printWordToken(void *pvItem, void *pvExtra)

/* Print token pvItem to stdout iff it is a word.  pvExtra is
   unused. */

{
   struct Token *psToken = (struct Token*)pvItem;
   if (psToken->eType == TOKEN_WORD)
     printf("%s ", psToken->pcValue);
}

/*--------------------------------------------------------------------*/

static struct Token *makeToken(enum TokenType eTokenType,
   char *pcValue)

/* Create and return a Token whose type is eTokenType and whose
   value consists of string pcValue.  Return NULL if insufficient
   memory is available.  The caller owns the Token. */

{
   struct Token *psToken;

   psToken = (struct Token*)malloc(sizeof(struct Token));
   if (psToken == NULL)
      return NULL;

   psToken->eType = eTokenType;

   psToken->pcValue = (char*)malloc(strlen(pcValue) + 1);
   if (psToken->pcValue == NULL)
   {
      free(psToken);
      return NULL;
   }

   strcpy(psToken->pcValue, pcValue);

   return psToken;
}

/*--------------------------------------------------------------------*/

static int lexLine(const char *pcLine, DynArray_T oTokens)
  
/* Lexically analyze string pcLine.  Populate oTokens with the
   tokens that pcLine contains.  Return 1 (TRUE) if successful, or
   0 (FALSE) otherwise.  In the latter case, oTokens may contain
   tokens that were discovered before the error. The caller owns the
   tokens placed in oTokens. */

/* lexLine() uses a DFA approach.  It "reads" its characters from
   pcLine. */

{
  //  enum Command {E, C, H, O, END};

  //enum Command cState = E;
  
  enum LexState {STATE_START, STATE_IN_WORD, STATE_IN_QUOTE, STATE_UNQUOTE, STATE_SPECIAL_CHAR};
  
  enum LexState eState = STATE_START;
  
  int iLineIndex = 0;
  int iValueIndex = 0;
  //int COMM = 0;
  char c;
  char acValue[MAX_LINE_SIZE];
  struct Token *psToken;
  
  assert(pcLine != NULL);
  assert(oTokens != NULL);
  /*
  for (int i=0 ; i<5 ; i++)
    {
      c = pcLine[iLineIndex++];
      
      switch (cState)
        {
	case E:
	  if (c == 'e')
	    cState = C;
	  break;
	  
	case C:
	  if (c == 'c')
            cState = H;
	  break;

	case H:
	  if (c == 'h')
	    cState = O;
	  break;
	  
	case O:
	  if (c == 'o')
            cState = END;
	  break;
	  
	case END:
	  if (isspace(c))
	    COMM = 1;
	  break;

	default:
	  assert(FALSE);
	}
	}*/
  
  while (1)
    {
      /* "Read" the next character from pcLine. */
      c = pcLine[iLineIndex++];
      
      switch (eState)
	{
	case STATE_START:
	  if ((c == '\n') || (c == '\0'))
	    return TRUE;
	  else if (isspace(c))
	    eState = STATE_START;
	  else if (c == '"')
	    eState = STATE_IN_QUOTE;
	  else if (c == '|' || c == '>' || c == '<')
	    {
	      acValue[iValueIndex++] = c;
	      eState = STATE_SPECIAL_CHAR;
	    }
	  else
	    {
	      acValue[iValueIndex++] = c;
	      eState = STATE_IN_WORD;
	    }
	  break;
	  
	case STATE_IN_WORD:
	  if ((c == '\n') || (c == '\0'))
            {
               /* Create a WORD token. */
	      acValue[iValueIndex] = '\0';
	      psToken = makeToken(TOKEN_WORD, acValue);
	      if (psToken == NULL)
		{
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
		}
	      if (! DynArray_add(oTokens, psToken))
		{
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
		}
	      iValueIndex = 0;
	      
	      return TRUE;
            }
	  else if (isspace(c))
            {
	      /* Create a WORD token. */
	      acValue[iValueIndex] = '\0';
	      psToken = makeToken(TOKEN_WORD, acValue);
	      if (psToken == NULL)
		{
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
		}
               if (! DynArray_add(oTokens, psToken))
		 {
		   fprintf(stderr, "Cannot allocate memory\n");
		   return FALSE;
		 }
               iValueIndex = 0;

               eState = STATE_START;
            }
	  else if (c == '|' || c == '>' || c == '<')
	    {
              /* Create a WORD token. */
              acValue[iValueIndex] = '\0';
              psToken = makeToken(TOKEN_WORD, acValue);
              if (psToken == NULL)
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
               if (! DynArray_add(oTokens, psToken))
                 {
                   fprintf(stderr, "Cannot allocate memory\n");
                   return FALSE;
                 }
               iValueIndex = 0;

	       acValue[iValueIndex++] = c;

               eState = STATE_SPECIAL_CHAR;
            }
	  else if (c == '"')
	    {
	      eState = STATE_IN_QUOTE;
	    }
	  else
	    {
	      acValue[iValueIndex++] = c;
	      eState = STATE_IN_WORD;
	    }
	  break;

	case STATE_IN_QUOTE:
	  if (c == '\n'|| c == '\0')
	    {
	      fprintf (stderr, "ERROR-unmatched quote\n");
	      return FALSE;
	    }
	  else if (c == '"')
	    {
	      eState = STATE_UNQUOTE;
	    }
	  else
	    {
	      acValue[iValueIndex++] = c;
	      eState = STATE_IN_QUOTE;
	    }
	  break;
	
	case STATE_UNQUOTE:
	  if ((c == '\n') || (c == '\0'))
            {
	      /* Create a WORD token. */
              acValue[iValueIndex] = '\0';
              psToken = makeToken(TOKEN_WORD, acValue);
              if (psToken == NULL)
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
              if (! DynArray_add(oTokens, psToken))
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
              iValueIndex = 0;
	      
              return TRUE;
            }
	  else if (isspace(c))
	    {
              /* Create a WORD token. */
              acValue[iValueIndex] = '\0';
              psToken = makeToken(TOKEN_WORD, acValue);
              if (psToken == NULL)
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
	      if (! DynArray_add(oTokens, psToken))
		{
		  fprintf(stderr, "Cannot allocate memory\n");
		  return FALSE;
		}
	      iValueIndex = 0;
	      
	      eState = STATE_START;
            }
	  else if (c == '|' || c == '>' || c == '<')
            {
              /* Create a WORD token. */
              acValue[iValueIndex] = '\0';
              psToken = makeToken(TOKEN_WORD, acValue);
              if (psToken == NULL)
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
               if (! DynArray_add(oTokens, psToken))
                 {
                   fprintf(stderr, "Cannot allocate memory\n");
                   return FALSE;
                 }
               iValueIndex = 0;

	       acValue[iValueIndex++] = c;

               eState = STATE_SPECIAL_CHAR;
            }
	  else if (c == '"')
            {
              eState = STATE_IN_QUOTE;
            }
          else
            {
              acValue[iValueIndex++] = c;
              eState = STATE_IN_WORD;
            }
	  break;

	case STATE_SPECIAL_CHAR:
	  if ((c == '\n') || (c == '\0'))
            {
              /* Create a WORD token. */
              acValue[iValueIndex] = '\0';
              psToken = makeToken(TOKEN_WORD, acValue);
              if (psToken == NULL)
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
              if (! DynArray_add(oTokens, psToken))
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
              iValueIndex = 0;

              return TRUE;
            }
	  else if (isspace(c))
            {
              /* Create a WORD token. */
              acValue[iValueIndex] = '\0';
              psToken = makeToken(TOKEN_WORD, acValue);
              if (psToken == NULL)
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
              if (! DynArray_add(oTokens, psToken))
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
              iValueIndex = 0;

              eState = STATE_START;
            }
	  else if (c == '|' || c == '>' || c == '<')
            {
              acValue[iValueIndex++] = c;
              eState = STATE_SPECIAL_CHAR;
            }
	  else if (c == '"')
	    {
              /* Create a WORD token. */
              acValue[iValueIndex] = '\0';
              psToken = makeToken(TOKEN_WORD, acValue);
              if (psToken == NULL)
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
              if (! DynArray_add(oTokens, psToken))
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
              iValueIndex = 0;

              eState = STATE_IN_QUOTE;
            }
	  else
	    {
              /* Create a WORD token. */
              acValue[iValueIndex] = '\0';
              psToken = makeToken(TOKEN_WORD, acValue);
              if (psToken == NULL)
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
              if (! DynArray_add(oTokens, psToken))
                {
                  fprintf(stderr, "Cannot allocate memory\n");
                  return FALSE;
                }
              iValueIndex = 0;

	      acValue[iValueIndex++] = c;

              eState = STATE_IN_WORD;
            }
	  break;

	default:
	  assert(FALSE);
	}
    }
}

/*--------------------------------------------------------------------*/

int main(void)

/* Read a line from stdin, and write to stdout each number and word
   that it contains.  Repeat until EOF.  Return 0 iff successful. */

{
   char acLine[MAX_LINE_SIZE];
   DynArray_T oTokens;
   int iSuccessful;

   printf("%c ", '%');
   while (fgets(acLine, MAX_LINE_SIZE, stdin) != NULL)
   {
      oTokens = DynArray_new(0);
      if (oTokens == NULL)
      {
         fprintf(stderr, "Cannot allocate memory\n");
         exit(EXIT_FAILURE);
      }

      iSuccessful = lexLine(acLine, oTokens);
      if (iSuccessful)
      {
	printf("%c ", '%');
	DynArray_map(oTokens, printWordToken, NULL);
	printf("\n");
      }
      printf("%c ", '%');

      DynArray_map(oTokens, freeToken, NULL);
      DynArray_free(oTokens);
   }

   return 0;
}
