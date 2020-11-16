#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for skeleton code */
#include <unistd.h> /* for getopt */
#include "str.h"

#define FIND_STR        "-f"
#define REPLACE_STR     "-r"
#define DIFF_STR        "-d"

#define MAX_STR_LEN 1023

#define FALSE 0
#define TRUE  1

typedef enum {
  INVALID,
  FIND,
  REPLACE,
  DIFF
} CommandType;

/*
 * Fill out your functions here (If you need) 
 */

/*--------------------------------------------------------------------*/
/* PrintUsage()
   print out the usage of the Simple Grep Program                     */
/*--------------------------------------------------------------------*/
void 
PrintUsage(const char* argv0) 
{
  const static char *fmt = 
    "Simple Grep (sgrep) Usage:\n"
    "%s [COMMAND] [OPTIONS]...\n"
    "\nCOMMNAD\n"
    "\tFind: -f [search-string]\n"
    "\tReplace: -r [string1] [string2]\n"
    "\tDiff: -d [file1] [file2]\n";

  printf(fmt, argv0);
}
/*-------------------------------------------------------------------*/
/* DoFind()
   Your task:
   1. Do argument validation 
   - String or file argument length is no more than 1023
   - If you encounter a command-line argument that's too long, 
   print out "Error: argument is too long"
   
   2. Read the each line from standard input (stdin)
   - If you encounter a line larger than 1023 bytes, 
   print out "Error: input line is too long" 
   - Error message should be printed out to standard error (stderr)
   
   3. Check & print out the line contains a given string (search-string)
      
   Tips:
   - fgets() is an useful function to read characters from file. Note 
   that the fget() reads until newline or the end-of-file is reached. 
   - fprintf(sderr, ...) should be useful for printing out error
   message to standard error

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoFind(const char *pcSearch)
{
  char buf[MAX_STR_LEN + 2]; 
  int lenStr, lenLine;

  /* error if input line is long */
  if ((lenStr = StrGetLength(pcSearch)) > MAX_STR_LEN) {
    fprintf(stderr, "Error: input line is too long\n");
    return FALSE;
  }
   
  /* Read the line by line from stdin, Note that this is an example */
  while (fgets(buf, sizeof(buf), stdin)) {
    /* check input line length */
    if ((lenLine = StrGetLength(buf)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line is too long\n");
      return FALSE;
    }
    /* if pcSearch is found, print the line of it */
    if (StrSearch((const char*) buf, pcSearch))
      printf("%s", buf);
  }
   
  return TRUE;
}
/*-------------------------------------------------------------------*/
/* DoReplace()
   Your task:
   1. Do argument validation 
      - String length is no more than 1023
      - If you encounter a command-line argument that's too long, 
        print out "Error: argument is too long"
      - If word1 is an empty string,
        print out "Error: Can't replace an empty substring"
      
   2. Read the each line from standard input (stdin)
      - If you encounter a line larger than 1023 bytes, 
        print out "Error: input line is too long" 
      - Error message should be printed out to standard error (stderr)

   3. Replace the string and print out the replaced string

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoReplace(const char *pcString1, const char *pcString2)
{
  /* buf always points to the first memory of buf */
  char buf[MAX_STR_LEN + 2];
  char *bufCpy = buf;
  char *StrOccur = buf;
  int lenLine;
  
  /* length of pcstrinf1 and pcstring2 */
  int lenStr1 = StrGetLength(pcString1);
  int lenStr2 = StrGetLength(pcString2);
  /* check if input line is long */
  if (lenStr1 > MAX_STR_LEN || lenStr2 > MAX_STR_LEN){
    fprintf(stderr, "Error: input line is too long\n");
    return FALSE;
  }
  /* check if input line string1 is empty */
  if (*pcString1 == EOF){
     fprintf(stderr, "Error: Can't replace an empty substring");
     return FALSE;
  }

  while (fgets(buf, sizeof(buf), stdin)) {
    /* check if a line is long */
    if ((lenLine = StrGetLength(buf)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line is too long\n");
      return FALSE;
    }

    /* NewLine always points to the first memory of NewLine */
    char NewLine[MAX_STR_LEN + 2]="";
    char *NewLineCpy = NewLine;
    
    while((StrOccur = StrSearch((const char*)bufCpy, pcString1))){
      /* copy buf to NewLine until pcString1 is occured */
      while (bufCpy != StrOccur){
	*NewLineCpy = *bufCpy;
	bufCpy++;
	NewLineCpy++;
      }
      /* copy pcstring2 after the result of previous while loop */
      StrConcat(NewLineCpy, pcString2);
      /* bufCpy points to end of pcstring1 which was found in buf
	 and NewLineCpy points to end of pcstrinf2 which I just added to NewLine */
      bufCpy += lenStr1;
      NewLineCpy += lenStr2;
    }
    /* copy buf after pcstring2 into NewLine */
    StrCopy(NewLineCpy, bufCpy);
    /* initialize bufCpy to point to the first memory of buf */
    bufCpy = buf;

    printf("%s", NewLine);
  }

  return TRUE;
}
/*-------------------------------------------------------------------*/
/* DoDiff()
   Your task:
   1. Do argument validation 
     - file name length is no more than 1023
     - If a command-line argument is too long, 
       print out "Error: argument is too long" to stderr

   2. Open the two files
      - The name of files are given by two parameters
      - If you fail to open either file, print out error messsage
      - Error message: "Error: failed to open file [filename]\n"
      - Error message should be printed out to stderr

   3. Read the each line from each file
      - If you encounter a line larger than 1023 bytes, 
        print out "Error: input line [filename] is too long" 
      - Error message should be printed out to stderr

   4. Compare the two files (file1, file2) line by line 

   5. Print out any different line with the following format
      file1@linenumber:file1's line
      file2@linenumber:file2's line

   6. If one of the files ends earlier than the other, print out an
      error message "Error: [filename] ends early at line XX", where
      XX is the final line number of [filename].

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoDiff(const char *file1, const char *file2)
{
  char buf1[MAX_STR_LEN + 2], buf2[MAX_STR_LEN + 2];
  FILE *OpenFile1, *OpenFile2;
  int lenOfFile1 = StrGetLength(file1);
  int lenOfFile2 = StrGetLength(file2);
  int lenOfLineFile1, lenOfLineFile2;
  int DiffLine = 1;
  int numOfLineFile1 = 0, numOfLineFile2 = 0;

  /* error if argument is long */
  if (lenOfFile1 > MAX_STR_LEN || lenOfFile2 > MAX_STR_LEN) {
    fprintf(stderr,"Error: arugment is too long");
    return FALSE;
  }

  /* error if failed to open file */
  OpenFile1 = fopen (file1,"r");
  if (!OpenFile1) {
    fprintf(stderr,"Error: failed to open file [%s]\n",file1);
    return FALSE;
  }
  OpenFile2 = fopen (file2,"r");
  if (!OpenFile2) {
    fprintf(stderr,"Error: failed to open file [%s]\n",file2);
    return FALSE;
  }

  while (fgets(buf1, sizeof(buf1), OpenFile1) && fgets(buf2, sizeof(buf2),OpenFile2)) {
    /* error if a line is long */
    lenOfLineFile1 = StrGetLength(buf1);
    if (lenOfLineFile1>MAX_STR_LEN){
      fprintf(stderr, "Error: input line [%s] is too long", file1 );
      return FALSE;
    }
    lenOfLineFile2 = StrGetLength(buf2);
    if (lenOfLineFile2>MAX_STR_LEN){
      fprintf(stderr, "Error: input line [%s] is too long", file2 );
      return FALSE;
    }
    /* if buf1 which is a line of file1 is same as
       buf2 which is a line of file2 */
    if (StrCompare((const char*)buf1, (const char*)buf2) == 0){
      DiffLine++;
    }
    /* if buf1 is same as buf2 */
    else{
      printf("%s@%d:%s",file1,DiffLine,buf1);
      printf("%s@%d:%s",file2,DiffLine,buf2);
      DiffLine++;
    }
  }

  /* close and open again to get lines from the front */
  fclose (OpenFile1);
  fclose (OpenFile2);
  OpenFile1 = fopen (file1,"r");
  OpenFile2 = fopen (file2,"r");

  /* count number of lines of file1 and file2 to know which finishes early */
  while (fgets(buf1, sizeof(buf1), OpenFile1))
    numOfLineFile1++;
  while (fgets(buf2, sizeof(buf1), OpenFile2))
    numOfLineFile2++;
  if (numOfLineFile1<numOfLineFile2)
    printf ("Error: [%s] ends early at line %d\n",file1,numOfLineFile1);
  if (numOfLineFile1>numOfLineFile2)
    printf ("Error: [%s] ends early at line %d\n",file1,numOfLineFile2);

  return TRUE;
}
/*-------------------------------------------------------------------*/
/* CommandCheck() 
   - Parse the command and check number of argument. 
   - It returns the command type number
   - This function only checks number of argument. 
   - If the unknown function is given or the number of argument is 
   different from required number, this function returns FALSE.
   
   Note: You SHOULD check the argument rule later                    */
/*-------------------------------------------------------------------*/ 
int
CommandCheck(const int argc, const char *argv1)
{
  int cmdtype = INVALID;
   
  /* check minimum number of argument */
  if (argc < 3)
    return cmdtype;
   
  /* check command type */ 
  if (strcmp(argv1, FIND_STR) == 0) {
    if (argc != 3)
      return FALSE;    
    cmdtype = FIND;       
  }
  else if (strcmp(argv1, REPLACE_STR) == 0) {
    if (argc != 4)
      return FALSE;
    cmdtype = REPLACE;
  }
  else if (strcmp(argv1, DIFF_STR) == 0) {
    if (argc != 4)
      return FALSE;
    cmdtype = DIFF;
  }
   
  return cmdtype;
}
/*-------------------------------------------------------------------*/
int 
main(const int argc, const char *argv[]) 
{
  int type, ret;
   
  /* Do argument check and parsing */
  if (!(type = CommandCheck(argc, argv[1]))) {
    fprintf(stderr, "Error: argument parsing error\n");
    PrintUsage(argv[0]);
    return (EXIT_FAILURE);
  }
   
  /* Do appropriate job */
  switch (type) {
  case FIND:
    ret = DoFind(argv[2]);
    break;
  case REPLACE:
    ret = DoReplace(argv[2], argv[3]);
    break;
  case DIFF:
    ret = DoDiff(argv[2], argv[3]);
    break;
  } 

  return (ret)? EXIT_SUCCESS : EXIT_FAILURE;
}
