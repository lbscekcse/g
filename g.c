//readme.txt 
para.l ---IMPLEMENTATION OF LEXICAL ANALYZER USING LEX

word.l ---LEX PROGRAM TO DISPLAY NUMBER OF WORDS,LINES AND 
CHARACTERS

abc.l ---CONVERT SUBSTRING abc TO ABC

vowel.l ---LEX PROGRAM TO FIND NO OF VOWELS AND CONSONANTS




arith.l ---YACC SPECIFICATION TO RECOGNIZE VALID ARITHMETIC 
EXPRESSION

arith.y ---YACC SPECIFICATION TO RECOGNIZE VALID ARITHMETIC 
EXPRESSION



ident.l ---YACC SPECIFICATION TO RECOGNIZE VALID IDENTIFIER

ident.y ---YACC SPECIFICATION TO RECOGNIZE VALID IDENTIFIER



calc.l ---IMPLEMENTATION OF CALCULATOR USING LEX AND YACC

calc.y ---IMPLEMENTATION OF CALCULATOR USING LEX AND YACC



first.c ---FIND FIRST OF ANY GRAMMAR

follow.c ---FIND FOLLOW OF ANY GRAMMAR


rdp.c ---RECURSIVE DESCENT PARSER


run.txt


// abc.l

%{
#include<stdio.h>
int i;
%}

%%
[a-z|A-Z|" "]* {
	for(i=0;i<yyleng;i++)
		{
			if((yytext[i]=='a')&&(yytext[i+1]=='b')&&(yytext[i+2]=='c'))
				{
					yytext[i]='A';
					yytext[i+1]='B';
					yytext[i+2]='C';
				}
			
		}
		printf("%s",yytext);
}
[\n] { printf("%s\n",yytext);}
%%
int main()
	{
		yylex();
	}
		
//arith.l

%{
#include "y.tab.h"
%}

%%
[0-9]+ {return NUMBER;}
[a-zA-Z][a-zA-Z0-9]* {return ID;}
\n {return 0;}
. {return yytext[0];}

%%
// arith.y
%{
#include<stdio.h>
#include<stdlib.h>
%}
%token NUMBER ID
%left '+''-''*''/'

%%
exp: exp'+'exp
| exp'-'exp
| exp'*'exp
| exp'/'exp
| '('exp')'
| NUMBER
| ID;
%%

int main(){
printf("Enter the expression:");
yyparse();
printf("Valid Expression!\n");
}
int yyerror(){
printf("Invalid Expression!\n");
exit(1);
}

//calc.l
%{
#include<stdio.h>
#include"y.tab.h"
extern int yylval;
%}

%%
[0-9]+ {yylval=atoi(yytext); return NUMBER;}
[\t] {}
[\n] return 0;
. return yytext[0];
%%

int yywrap()
{
return 1;
}

//calc.y 
%{
#include<stdio.h>
int flag=0;
%}
%token NUMBER
%left '+''-'
%left '*''/''%'
%left '('')'

%%
ArithmeticExpression:E {printf("\nRESULT=%d\n",$$); return 0;};
E:E'+'E {$$=$1+$3;}
| E'-'E {$$=$1-$3;}
| E'*'E {$$=$1*$3;}
| E'/'E {$$=$1/$3;}
| E'%'E {$$=$1%$3;}
| '('E')' {$$=$2;}
| NUMBER {$$=$1;}
;
%%

void main()
{
printf("Enter any arithmetic expression:");
yyparse();
if(flag==0)
printf("\nVALID EXPRESSION\n");
}
void yyerror()
{
printf("\nInvalid expression\n");
flag=1;
}

//first.c 
#include<stdio.h>
#include<ctype.h>
void FIRST(char);
int count,n=0;
char prodn[10][10],first[10];
void main()
{
 int i,choice;
 char c,ch;
 printf("How many productions?:");
 scanf("%d",&count);
 printf("Enter %d production epsilon=$:\n\n",count);
 for(i=0;i<count;i++)
  scanf("%s%c",prodn[i],&ch);
 do
 {
  n=0;
  printf("Element:");
  scanf("%c",&c);
  FIRST(c);
  printf("\nFIRST(%c)={",c);
  for(i=0;i<n;i++)
   printf("%c",first[i]);
  printf("}\n");
  printf("press 1 to continue:");
  scanf("%d%c",&choice,&ch);
 }
 while(choice==1);
}
void FIRST(char c)
{
 int j;
 if(!isupper(c))
  first[n++]=c;
 for(j=0;j<count;j++)
 {
  if(prodn[j][0]==c)
  {
   if(prodn[j][2]=='$')
    first[n++]='$';
   else if(islower(prodn[j][2]))
    first[n++]=prodn[j][2];
   else
    FIRST(prodn[j][2]);
  }
 }
}


//follow.c 
#include<stdio.h>
#include<string.h>
#include<ctype.h>
int n,m=0,p,i=0,j=0;
char a[10][10],f[10];
void follow(char c);
void first(char c);
int main()
{
 int i,z;
 char c,ch;
 printf("Enter the no of productions:");
 scanf("%d",&n);
 printf("Enter the productions(epsilon=$):\n");
 for(i=0;i<n;i++)
  scanf("%s%c",a[i],&ch);
 do
 {
  m=0;
  printf("Enter the element whose FOLLLoW is to be found:");
  scanf("%c",&c);
  follow(c);
  printf("FOLLOW(%c)={",c);
  for(i=0;i<m;i++)
   printf("%c",f[i]);
  printf("}\n");
  printf("Do you want to continue(0/1)?");
  scanf("%d%c",&z,&ch);
 }
 while(z==1);
}
void follow(char c)
{
 if(a[0][0]==c)
  f[m++]='$';
 for(i=0;i<n;i++)
 {
  for(j=2;j<strlen(a[i]);j++)
  {
   if(a[i][j]==c)
   {
    if(a[i][j+1]!='\0')
     first(a[i][j+1]);
    if(a[i][j+1]=='\0'&&c!=a[i][0])
     follow(a[i][0]);
   }
  }
 }
}
void first(char c)
{
 int k;
 if(!(isupper(c)))
  f[m++]=c;
 for(k=0;k<n;k++)
 {
  if(a[k][0]==c)
  {
   if(a[k][2]=='$')
    follow(a[i][0]);
   else if(islower(a[k][2]))
    f[m++]=a[k][2];
   else
    first(a[k][2]);
  }
 }
}
//ident.l 
%{
#include "y.tab.h"
%}

%%
[0-9] {return DIGIT;}
[a-zA-Z] {return ALPHA;}
\n {return 0;}
. {return yytext [0];}
%%


//ident.y 
%{
#include<stdio.h>
#include<stdlib.h>
%}
%token DIGIT ALPHA

%%
var:ALPHA
| var DIGIT
| var ALPHA;
%%

int main(int argc,char *argv[]){
printf("Enter a variable name:");
yyparse();
printf("Valid Variable!\n");
return 0;
}
int yyerror(){
printf("Invalid Variable!\n");
exit(1);
}

//para.l 
%{
#include<stdio.h>
%}
%%
if|else|while|for|switch|break|continue|do {printf("%s is a keyword\n",yytext);}
"||"|"&&"|"!" {printf("%s is a Logical operator\n",yytext);}
[A-Z|a-z][A-Z|a-z|0-9]* {printf("%s is a Identifier\n",yytext);}
[0-9]* {printf("%s is a Numbers\n",yytext);}
[0-9]+"."[0-9]+ {printf("%s is a Numbers\n",yytext);}
"<"|">"|"<="|">="|"!="|"==" {printf("%s is a Relation operator\n",yytext);}
"+"|"-"|"*"|"/"|"%" {printf("%s is a Arithmetic operator\n",yytext);}
"=" {printf("%s is a Assignment operator\n",yytext);}
"++" {printf("%s is a Increment operator\n",yytext);}
"--" {printf("%s is a Decrement operator\n",yytext);}
. {printf("%s is a Invalid\n",yytext);}
%%
int main(int argc,char *argv[])
{
yyin=fopen(argv[1],"r");
yylex();
}
//rdp.c 

#include<stdio.h>
#include<string.h>
#include<ctype.h>
char input[100];
int i=0,error=0;
void E();
void T();
void Eprime();
void Tprime();
void F();
void main()
{
	printf("Enter an arithmetic expression:\n");
	gets(input);
	E();
	if(strlen(input)==i && error==0)
		printf("Accepted...!!!\n");
	else
		printf("Rejected...!!!\n");
}

void E()
{
	T();
	Eprime();
}

void Eprime()
{
	if(input[i]=='+')
	{
		i++;
		T();
		Eprime();
	}
}

void T()
{
	F();
	Tprime();
}

void Tprime()
{
	if(input[i]=='*')
	{
		i++;
		F();
		Tprime();
	}
}

void F()
{
	if(input[i]== '(' )
	{
		i++;
		E();
		if (input [i]==')')
			i++;
	}
	else if(isalpha(input[i]) || (isalnum(input[i])))
	{
		i++;
		while ((isalnum(input[i])) || (input[i]=='-'))
		i++;
	}
	else
		error=1;
}
		
		
//vowel.l 
%{
#include<stdio.h>
int w=0,c=0;
%}

%%
[aeiouAEIOU] {w++;}
[a-z|A-Z] {c++;}
EOF {printf("No of VOWELS: = %d\n No of consonants=%d\n",w,c);
return 0;}
. {}
%%

int main(int argc,char *argv[])
{
yyin=fopen(argv[1],"r");
yylex();

}
//word.l 
/*Count the letters in a strings*/
%{
#include<stdio.h>
int words=0,ch=0,line=0;
%}
%%
[A-Z|a-z]" " {words++;ch++;}
[A-Z|a-z]"\n" {words++;ch++;line++;}
[A-Z|a-z] {ch++;}

EOF {printf("No of words:%d\nNo of characters:%d\nNo of lines:%d\n",words,ch,line);}
. {}

%%
int main(int argc,char *argv[])
{
yyin=fopen(argv[1],"r");
yylex();
}

//run.txt 

for lex programgcc

lex filename
gcc lex.yy.c -lfl
./a.out


for yacc

lex filename.l
yacc -d filename.y
gcc lex.yy.c y.tab.c -lfl
./a.out


//dfamin.c 

#include<stdio.h>
struct nfa{
char from;
char symbol;
char to;
}n[20];
void main(){
int t,fstate,i,j,states,v1,v2,flag=0,k,visit[10];
char table[10][10];
char f[10],state[10],state1,state2;
printf("Enter the no. of states:");
scanf("%d",&states);
printf("State final/nonfinal(f/n)\n");
for(i=0;i<states;i++){
scanf(" %c %c",&state[i],&f[i]);
visit[i]=0;
}
printf("Enter no. of transitions:");
scanf("%d",&t);
printf("Enter transitions:\nfrom symbol to\n");
for(i=0;i<t;i++)
scanf(" %c %c %c",&n[i].from,&n[i].symbol,&n[i].to);
for(i=0;i<states-1;i++){
for(j=0;j<states-i-1;j++){
if((f[states-i-1]=='n' && f[j]=='f') || (f[states-i-1]=='f' && f[j]=='n'))
table[i][j]='X';
else
table[i][j]=' ';
}
}
for(i=0;i<states-1;i++){
for(j=0;j<states-i-1;j++){
if(table[i][j]==' '){
flag=0;
for(k=0;k<2;k++){
v1=j*2 + k;
v2=(states-i-1)*2+k;
state1=n[v1].to;
state2=n[v2].to;
if((f[(int)state1-48]=='n' && f[(int)state2-48]=='f')||
(f[(int)state1-48]=='f' && f[(int)state2-48]=='n')){
table[i][j]='X';
flag=1;
break;
}
}
if(flag==0)
printf("%c and %c are indistinguishable\n",state[states-i-1],state[j]);
}
}
}
for(i=0;i<states-1;i++)
printf(" %c",state[i]);
printf("\n");
for(i=0;i<states-1;i++){
printf("%c ",state[states-i-1]);
for(j=0;j<states-i-1;j++)
printf("%c ",table[i][j]);
printf("\n");
}
printf("The states of minimized dfa are:\n");
for(i=0;i<states-2;i++){
if(visit[states-i-1]==0){
printf("{%c",state[states-i-1]);
visit[states-i-1]=1;
for(j=0;j<states-i-1;j++){
if(table[i][j]==' ' && visit[j]==0){
printf(",%c",state[j]);
visit[j]=1;
}
}
printf("},");
}
}
for(i=0;i<states;i++){
if(visit[i]==0)
printf("{%c}\n",state[i]);
}
}
//nfatodfa.c 
#include<stdio.h>
#include<stdlib.h>
struct node
{
 int st;
 struct node *link;
};
struct node1
{
 int nst[20];
};
//Functions
void insert(int ,char, int);
int findalpha(char);
void findfinalstate(void);
int insertdfastate(struct node1);
int compare(struct node1,struct node1);
void printnewstate(struct node1);
static int set[20],nostate,noalpha,s,notransition,nofinal,start,finalstate[20],r,buffer[20];
int complete=-1;
char alphabet[20],c;
static int eclosure[20][20]={0};
struct node1 hash[20];
struct node * transition[20][20]={NULL};
void main()
{
int i,j,k,m,t,n,l;
struct node *temp;
struct node1 newstate={0},tmpstate={0};
printf("Enter the number of alphabets?\n");
printf("NOTE:- [ use letter e as epsilon]\n");
printf("NOTE:- [e must be last character ,if it is present]\n");
printf("\nEnter No of alphabets and alphabets?\n");
scanf("%d",&noalpha);
getchar();
for(i=0;i<noalpha;i++){
alphabet[i]=getchar();
getchar();
}
printf("Enter the number of states?\n");
scanf("%d",&nostate);
printf("Enter the start state?\n");
scanf("%d",&start);
printf("Enter the number of final states?\n");
scanf("%d",&nofinal);
printf("Enter the final states?\n");
for(i=0;i<nofinal;i++)
scanf("%d",&finalstate[i]);
printf("Enter no of transition?\n");
scanf("%d",&notransition);
printf("NOTE:- [Transition is in the form–> qno alphabet qno]\n");
printf("NOTE:- [States number must be greater than zero]\n");
printf("\nEnter transition?\n");
for(i=0;i<notransition;i++){
scanf("%d %c %d",&r,&c,&s);
insert(r,c,s);
}
for(i=0;i<20;i++){
for(j=0;j<20;j++)
hash[i].nst[j]=0;
}
complete=-1;
i=-1;
printf("\nEquivalent DFA.....\n");
printf("Trnsitions of DFA\n");
newstate.nst[start]=start;
insertdfastate(newstate);
while(i!=complete){
i++;
newstate=hash[i];
for(k=0;k<noalpha;k++){
 c=0;
 for(j=1;j<=nostate;j++)
 set[j]=0;
 
 for(j=1;j<=nostate;j++){
 l=newstate.nst[j];
 if(l!=0){
 temp=transition[l][k];
 while(temp!=NULL){
 if(set[temp->st]==0){
 c++;
 set[temp->st]=temp->st;
 }
 temp=temp->link;
 }
 }
 }
 printf("\n");
 if(c!=0){
 for(m=1;m<=nostate;m++)
 tmpstate.nst[m]=set[m];
 insertdfastate(tmpstate);
 printnewstate(newstate);
 printf("%c\t",alphabet[k]);
 printnewstate(tmpstate);
 printf("\n");
 }
 else{
 printnewstate(newstate);
 printf("%c\t", alphabet[k]);
 printf("NULL\n");
 }
 }
 }
printf("\nStates of DFA:\n");
for(i=0;i<=complete;i++)
printnewstate(hash[i]); 
printf("\n Alphabets:\n");
for(i=0;i<noalpha;i++)
printf("%c\t",alphabet[i]);
printf("\n Start State:\n");
printf("q%d",start);
printf("\nFinal states:\n");
findfinalstate();
}
int insertdfastate(struct node1 newstate){
int i;
for(i=0;i<=complete;i++){
 if(compare(hash[i],newstate))
 return 0;
}
complete++;
hash[complete]=newstate;
return 1;
}
int compare(struct node1 a,struct node1 b){
int i;
 for(i=1;i<=nostate;i++){
 if(a.nst[i]!=b.nst[i])
 return 0;
 }
 return 1;
}
void insert(int r,char c,int s){
 int j;
 struct node *temp;
 j=findalpha(c);
 if(j==999)
 {
 printf("error\n");
 exit(0);
 }
 temp=(struct node *) malloc(sizeof(struct node));
 temp->st=s;
 temp->link=transition[r][j];
 transition[r][j]=temp;
}
int findalpha(char c){
int i;
for(i=0;i<noalpha;i++)
if(alphabet[i]==c)
 return i;
 return(999);
}
void findfinalstate(){
int i,j,k,t;
for(i=0;i<=complete;i++){
 for(j=1;j<=nostate;j++){
 for(k=0;k<nofinal;k++){
 if(hash[i].nst[j]==finalstate[k]){
 printnewstate(hash[i]);
 printf("\t");
 j=nostate;
 break;
 }
 }
 }
 }
}
void printnewstate(struct node1 state){
int j;
printf("{");
 for(j=1;j<=nostate;j++){
 if(state.nst[j]!=0)
 printf("q%d,",state.nst[j]);
 }
 printf("}\t");
}
//epsilonnfatonfa.c 
#include<stdio.h>
#include<stdlib.h>
struct node{
 int st;
 struct node *link;
};
void findclosure(int,int);
void insert_trantbl(int ,char, int);
int findalpha(char);
void findfinalstate(void);
void unionclosure(int);
void print_e_closure(int);
static int set[20],nostate,noalpha,s,notransition,nofinal,start,finalstate[20],c,r,buffer[20];
char alphabet[20];
static int e_closure[20][20]={0};
struct node * transition[20][20]={NULL};
void main()
{
 int i,j,k,m,t,n;
 struct node *temp;
 printf("enter the number of alphabets?\n");
 scanf("%d",&noalpha);
 getchar();
 printf("NOTE:- [ use letter e as epsilon]\n");
 printf("NOTE:- [e must be last character ,if it is present]\n");
 printf("\nEnter alphabets?\n");
 for(i=0;i<noalpha;i++) {
 alphabet[i]=getchar();
 getchar();
 }
 printf("Enter the number of states?\n");
 scanf("%d",&nostate);
 printf("Enter the start state?\n");
 scanf("%d",&start);
 printf("Enter the number of final states?\n");
 scanf("%d",&nofinal);
 printf("Enter the final states?\n");
 for(i=0;i<nofinal;i++)
 scanf("%d",&finalstate[i]);
 printf("Enter no of transition?\n");
 scanf("%d",&notransition);
 printf("NOTE:- [Transition is in the form--> qno alphabet qno]\n",notransition);
 printf("NOTE:- [States number must be greater than zero]\n");
 printf("\nEnter transition?\n");
 for(i=0;i<notransition;i++){
 scanf("%d %c%d",&r,&c,&s);
 insert_trantbl(r,c,s);
 }
 printf("\n");
 for(i=1;i<=nostate;i++) {
 c=0;
 for(j=0;j<20;j++) {
 buffer[j]=0;
 e_closure[i][j]=0;
 }
 findclosure(i,i);
 }
 printf("Equivalent NFA without epsilon\n");
 printf("-----------------------------------\n");
 printf("start state:");
 print_e_closure(start);
 printf("\nAlphabets:");
 for(i=0;i<noalpha;i++)
 printf("%c ",alphabet[i]);
 printf("\nStates :" );
 for(i=1;i<=nostate;i++)
 print_e_closure(i);
 printf("\nTransitions are...:\n");
 for(i=1;i<=nostate;i++) {
 for(j=0;j<noalpha-1;j++) {
 for(m=1;m<=nostate;m++)
 set[m]=0;
 for(k=0;e_closure[i][k]!=0;k++){
 t=e_closure[i][k];
 temp=transition[t][j];
 while(temp!=NULL){
 unionclosure(temp->st);
 temp=temp->link;
 }
 }
 printf("\n");
 print_e_closure(i);
 printf("%c\t",alphabet[j] );
 printf("{");
 for(n=1;n<=nostate;n++) {
 if(set[n]!=0)
 printf("q%d,",n);
 }
 printf("}");
 }
 }
 printf("\nFinal states:");
 findfinalstate();
}
void findclosure(int x,int sta){
 struct node *temp;
 int i;
 if(buffer[x])
 return;
 e_closure[sta][c++]=x;
 buffer[x]=1;
 if(alphabet[noalpha-1]=='e' && transition[x][noalpha-1]!=NULL){
 temp=transition[x][noalpha-1];
 while(temp!=NULL){
 findclosure(temp->st,sta);
 temp=temp->link;
 }
 }
 }
void insert_trantbl(int r,char c,int s){
 int j;
 struct node *temp;
 j=findalpha(c);
 if(j==999){
 printf("error\n");
 exit(0);
 }
 temp=(struct node *) malloc(sizeof(struct node));
 temp->st=s;
 temp->link=transition[r][j];
 transition[r][j]=temp;
}
int findalpha(char c){
 int i;
 for(i=0;i<noalpha;i++)
 if(alphabet[i]==c)
 return i;
 return(999);
}
void unionclosure(int i){
 int j=0,k;
 while(e_closure[i][j]!=0){
 k=e_closure[i][j];
 set[k]=1;
 j++;
 }
}
void findfinalstate(){
 int i,j,k,t;
 for(i=0;i<nofinal;i++){
 for(j=1;j<=nostate;j++){
 for(k=0;e_closure[j][k]!=0;k++){
 if(e_closure[j][k]==finalstate[i]){
print_e_closure(j);
 }
 }
 }
 }
 }
void print_e_closure(int i)
{
 int j=0;
 printf("{");
 if(e_closure[i][j]!=0)
 printf("q%d,",e_closure[i][0]);
 printf("}\t");
}
//epsilon-closure.c 
#include<stdio.h>
#include<stdlib.h>
struct transition{
 char sym;
 int next;
 struct transition *link1;
};
struct state{
 int st;
 struct state *next;
 struct transition *link2;
}*s=NULL,*ptr,*ptr1;
int stack[10],top=-1;
void push(int val)
{
 top++;
 stack[top]=val;
}
int pop()
{
 int val;
 val=stack[top];
 top--;
 return val;
}
int isVisit(int visit[10],int val)
{
 int i;
 for(i=0;i<10;i++)
 {
 if(visit[i]==val)
 return 1;
 }
 return 0;
}
void findEpselon(struct transition *temp,int visit[10],int k)
{
 while(temp!=NULL)
 {
 if(temp->sym=='e'){
 if(isVisit(visit,temp->next)==0){
 push(temp->next);
 printf(",%d",temp->next);
 visit[k++]=temp->next;
 }
 }
 temp=temp->link1;
 }
}
void main()
{
 int numStates,numTrans,i,from,to,visit[10],k;
 char symbol;
 struct transition *temp,*new;
 printf("Enter number of states : ");
 scanf("%d",&numStates);
 for(i=1;i<=numStates;i++)
 {
 ptr=malloc(sizeof(struct state));
 ptr->st=i;
 if(s==NULL){
 s=ptr;
 }
 else{
 ptr1=s;
 while(ptr1->next!=NULL)
 ptr1=ptr1->next;
 ptr1->next=ptr;
 }
 ptr->next=NULL;
 ptr->link2=NULL;
 }
 printf("Enter number of transitions : ");
 scanf("%d",&numTrans);
 printf("Enter transitions\nfrom symbol to\n");
 for(i=0;i<numTrans;i++)
 {
 scanf("%d %c %d",&from,&symbol,&to);
 new=malloc(sizeof(struct transition));
 new->sym=symbol;
 new->next=to;
 new->link1=NULL;
 ptr=s;
 while(ptr->st!=from)
 ptr=ptr->next;
 temp=ptr->link2;
 if(temp==NULL){
 temp=new;
 ptr->link2=temp;
 } 
 else{
 while(temp->link1!=NULL)
 temp=temp->link1;
 temp->link1=new;
 }
 }
 printf("\nEpsilon closures\n");
 ptr=s;
 while(ptr!=NULL){
 k=0;
 for(i=0;i<10;i++)
 visit[i]=0;
 printf("State %d : {%d",ptr->st,ptr->st);
 visit[k++]=ptr->st;
 temp=ptr->link2;
 findEpselon(temp,visit,k);
 while(top!=-1)
 {
 from=pop();
 ptr1=s;
 while(ptr1->st!=from)
 ptr1=ptr1->next;
 temp=ptr1->link2;
 findEpselon(temp,visit,k);
 }
 ptr=ptr->next;
 printf("}\n");
 }
}
 //lexanalyzer.c
 #include<stdio.h>
#include<ctype.h>
#include<string.h>
int main()
{
FILE *input, *output;
int l=1; int t=0; int j=0; int i,flag; char ch,str[20];
input = fopen("sum.c","r");
output = fopen("output.txt","w+");
char keyword[32][32] = {"auto", "break", "case", "char", 
 "const","continue","default","do","double",
 "else","enum","extern","float", "for","goto", "if", 
 "int","long","register", "return","short",
 "signed","sizeof","static","struct", "switch","typedef","union", 
 "unsigned","void","volatile","while"
 };
fprintf(output,"Line no. \t Token no. \t \t Token \t\t Lexeme\n\n");
printf("Line no. \t Token no. \t \t Token \t\t Lexeme\n\n");
while(!feof(input))
{
i=0;
flag=0;
ch=fgetc(input);
if(ch=='+' || ch== '-' || ch=='*' || ch=='/')
{
fprintf(output,"%7d\t\t %7d\t\t Operator\t %7c\n",l,t,ch);
printf("%7d\t\t %7d\t\t Operator\t %7c\n",l,t,ch);
t++;
}
else if( ch==';' || ch=='{' || ch=='}' || ch=='(' || ch==')'|| ch=='?' || ch=='@' || ch=='!' || 
ch=='%')
{
fprintf(output,"%7d\t\t %7d\t\t Special symbol\t %7c\n",l,t,ch);
printf("%7d\t\t %7d\t\t Special symbol\t %7c\n",l,t,ch);
t++;
}
else if(isdigit(ch))
{
 fprintf(output,"%7d\t\t %7d\t\t Digit\t\t %7c\n",l,t,ch);
 printf("%7d\t\t %7d\t\t Digit\t\t %7c\n",l,t,ch);
t++;
}
else if(isalpha(ch))
{
str[i]=ch;
i++;
ch=fgetc(input);
while(isalnum(ch) && ch!=' ')
{
str[i]=ch; i++; 
ch=fgetc(input);
 }
str[i]='\0';
for(j=0;j<=32;j++)
{
if(strcmp(str,keyword[j])==0)
{
flag=1;
break;
}
 }
 if(flag==1)
{
 fprintf(output,"%7d\t\t %7d\t\t Keyword\t %7s\n",l,t,str);
 printf("%7d\t\t %7d\t\t Keyword\t %7s\n",l,t,str);
t++;
}
 else
{
fprintf(output,"%7d\t\t %7d\t\t Identifier\t %7s\n",l,t,str);
printf("%7d\t\t %7d\t\t Identifier\t %7s\n",l,t,str);
t++;
}
}
else if(ch=='\n')
{
l++;
}
}
fclose(input);
fclose(output);
return 0;
}
sum.c
#include <stdio.h>
int main() {
 int n, i, sum = 0;
 printf("Enter a positive integer: ");
 scanf("%d", &n);
 for (i = 1; i <= n; ++i) {
 sum += i;
 }
 printf("Sum = %d", sum);
 return 0;
}
