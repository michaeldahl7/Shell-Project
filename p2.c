#include "p2.h" /* Not sure what else ill need*/
//#define statements /*such as flags , */
//declarations;
int c;
char s[STORAGE*MAXITEM];
char * ptr;
int wordCount = 0;
#define TRUE 1
#define FALSE 0
char *newargv[MAXITEM];
int wordLength;
int leftCarrotFound = FALSE;
int rightCarrotFound = FALSE;
int ampersandFound = FALSE;
char * nullptr = NULL;

int main()
{

//Declaration of locals
//any necessary setup, including signal catcher??
	for(;;){
		printf("p2: ");
		/*setup redirections*/
		parse();
		if(wordCount == 0)
			continue;
		if(wordLength == -1){
			break;
		}
		//else if()
		/*if(fork() == 0){
			redirect I/O as requested

			use execvp() to start requested process
			If execvp() vails {
				print error message
			exit(9);
			}
		}
		//This is where i handle if ampersand true on not.
		//
		If approprioate, wait for child to complete;
		Else print the childs pid, and in this case, the child should redirect its stdin to /dev/null*/
	}
	//killpg(getpid(), SIGTERM); //Terminate any children that are still running. WARNING: bad args to killpg can kill auto grader,

	printf("p2 terminated. \n");

	exit(0);
}

void parse(){
	ptr = s;
	wordLength = getword(s);
	while(wordLength != 0 && wordLength != -1){
		if(leftCarrotFound == TRUE){
			newargv[wordCount] = *ptr;	//this is the input file argument where to verify input..
			leftCarrotFound = FALSE;
		}
		if(rightCarrotFound == TRUE){
			newargv[wordCount] = *ptr;	//this is the output file argument
			rightCarrotFound = FALSE;
		}
		if(*ptr == '<'){
			leftCarrotFound = TRUE;
			printf("word found is <. \n");
		}2
		if(*ptr == '>'){
			rightCarrotFound = TRUE;
			printf("word found is >. \n");
			//handle outputfile
		}
		if(*ptr == '&'){
			ampersandFound = TRUE;
			printf("word found is &. \n");
			newargv[wordCount] = nullptr;
			break;
			//set up background
			//null pointer in newargv array
			//end line break, or goto?
		}
		//newargv[wordCount] = ptr;
		printf("n=%d, s=[%s]\n", wordLength, ptr);
		ptr = (ptr+(wordLength + 1));
		wordLength = getword(ptr);
	}
}
