#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/* name of 7 states */
enum DFAState {Start, Character, Space, NewLine, CommentCheck1, Comment, CommentCheck2};
enum DFAState state = Start;
enum ProgramResult {SUCCESS, FAILURE};
enum ProgramResult result = SUCCESS;
/* to know previous state of CommentCheck1 is Character or not */
enum WhereIsCharFrom {NotFromStateCharacter, FromStateCharacter};
enum WhereIsCharFrom from = NotFromStateCharacter;\
/* to verify if text is empty */
enum IsFileEmpty {Empty, NotEmpty};
enum IsFileEmpty file = Empty;

int c;
int nErrorLine; /* number of line where error is occured */
int nLine=1, nWord, nChar;

/* add num1,num2,num3 which are 0 or 1 to nLine,nWord,nChar respectively */
int Add(int num1,int num2,int num3){
  nLine += num1;
  nWord += num2;
  nChar += num3;
  return 0; }

int StartFunc(void){
  if(c == '/'){
    Add(0,0,1);
    file = NotEmpty;
    state = CommentCheck1; }
  else if(!isspace(c) &&  c != EOF){
    Add(0,0,1);
    file= NotEmpty;
    state = Character; }
  else if(isspace(c)){
    if(c == '\n') Add(1,0,1);
    else Add(0,0,1);
    file = NotEmpty; } 
  else if(c == EOF){
    if(file == Empty) nLine = 0; } /* if text has no input at all */
  return 0; }

int CharFunc(void){
  if(c == '/'){
    Add(0,0,1);
    from = FromStateCharacter;
    state = CommentCheck1; }
  else if(!isspace(c) && c != EOF) Add(0,0,1);
  else if(isspace(c)){
    if(c == '\n'){
      Add(1,1,1);
      state = NewLine; }
    else {
      Add(0,1,1);
      state = Space; }}
  else if(c == EOF) Add(0,1,0); /* if text finishes is this state */
  return 0; }

int SpaceFunc(void){
  if(c == '/'){
    Add(0,0,1);
    state = CommentCheck1; }
  else if(!isspace(c) && c != EOF){
    Add(0,0,1);
    state = Character; }
  else if(isspace(c)){
    if (c == '\n'){
      Add(1,0,1);
      state = NewLine; }
    else Add(0,0,1); }
  return 0; }

int NewLineFunc(void){
  if(c == '/'){
    Add(0,0,1);
    state = CommentCheck1; }
  else if(!isspace(c) && c != EOF){
    Add(0,0,1);
    state = Character; }
  else if(isspace(c)){
    if(c == '\n') Add(1,0,1);
    else{
      Add(0,0,1);
      state = Space; }}
  return 0; }

int Check1Func(void){
  if(c == '*'){
    /* if previous state was Character, number of word should be increased by 1.
       if not number of word has increased by 1 already, so it doesn't need to be increased. */
    if(from == NotFromStateCharacter) Add(0,0,1);
    else if(from == FromStateCharacter){
      Add(0,1,1);
      from = NotFromStateCharacter; } /* initialize from */
    state = Comment;
    nErrorLine = nLine; } /* error occured in current line */
  else if(c == '/') Add(0,0,1);
  else if(!isspace(c) && c != EOF){
    Add(0,0,1);
    from = NotFromStateCharacter; /* initialize from */
    state = Character; }
  else if(isspace(c)){
    if(c == '\n'){
      Add(1,1,1);
      state = NewLine; }
    else{
      Add(0,1,1);
      state = Space; }
    from = NotFromStateCharacter; } /* initialize from */
  else if(c == EOF) Add(0,1,0); /* if text finishes in this state  */
  return 0; }

int CommentFunc(void){
  if(c == '*') state = CommentCheck2;
  else if(c == '\n') Add(1,0,1);
  else if(c == EOF) result = FAILURE; /* to go to state Error */
  return 0; }

int Check2Func(void){
  if(c == '/'){
    Add(0,0,-1);
    state = Start; }
  else if(c == '\n'){
    Add(1,0,1);
    state = Comment; }
  else if(c == EOF) result = FAILURE; /* to go to state Error */
  else if(c != '*') state = Comment;
  return 0; }

int ErrorFunc(void){
  fprintf(stderr, "Error: line %d: unterminated comment\n", nErrorLine);
  return 0; }

int main(void){
  do{
    c = getchar();
    switch (state){
    case Start:
      StartFunc();
      break;
    case Character:
      CharFunc();
      break;
    case Space:
      SpaceFunc();
      break;
    case NewLine:
      NewLineFunc();
      break;
    case CommentCheck1:
      Check1Func();
      break;
    case Comment:
      CommentFunc();
      break;
    case CommentCheck2:
      Check2Func();
      break;
    }
  }while(c != EOF);
  
  if(result == FAILURE){
    ErrorFunc();
    return EXIT_FAILURE; }
  fprintf(stdout, "%d %d %d\n", nLine, nWord, nChar);
  return EXIT_SUCCESS;
}
