/*Synopsis  -

Michael Dahl
John Carroll
CS 570
Due: 2/10/2016
 */
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

int main()
{

int max;
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

		int kidpid;

		/* do the fork, remember the value returned by fork(), and test it */
		if (-1 == (kidpid = fork())) {
			/* -1 indicates the fork was unsuccessful */
			perror("Cannot fork");
			exit(1);
		} else if (0 == kidpid) {
			/* fork() returns 0 to the newly-created child process */
			sleep(1);
			/* block for 1 second, to ensure a context switch for this example */
			printf("child says: my pid = %d, parent pid = %d\n", getpid(), getppid());
			exit(0);
		} else {
/* fork() returns a positive number to the process that issued the fork()
 * The number it returns is the PID of the child process that was just created */
			sleep(1);
			/* block for 1 second, to ensure a context switch for this example */
			printf("parent says: child pid = %d, my pid = %d\n", kidpid, getpid());
			exit(0);
		}
		//else if()
		/*if(fork() == 0){
			redirect I/O as requested*/
   		//CHK(execvp(newargv[0], newargv));
		execvp(newargv[0], newargv);
		/*	use execvp() to start requested process
			If execvp() fails {
				print error message
			exit(9);
			}
		}
		//This is where i handle if ampersand true on not.
		If approprioate, wait for child to complete;
		Else print the childs pid, and in this case, the child should redirect its stdin to /dev/null  */
	}
	//killpg(getpid(), SIGTERM); //Terminate any children that are still running. WARNING: bad args to killpg can kill auto grader,

	printf("p2 terminated. \n");

	exit(0);
}

void parse(){
	ptr = s;
	wordLength = getword(s);
	while(wordLength != 0 && wordLength != -1) {
		if (leftCarrotFound == TRUE) {
			newargv[wordCount] = ptr;    //this is the input file argument where to verify input..
			leftCarrotFound = FALSE;
		}
		else if (rightCarrotFound == TRUE) {
			newargv[wordCount] = ptr;    //this is the output file argument
			rightCarrotFound = FALSE;
		}
		else if (*ptr == '<') {
			leftCarrotFound = TRUE;
			printf("word found is <. \n");
		}
		else if (*ptr == '>') {
			rightCarrotFound = TRUE;
			printf("word found is >. \n");
			//handle outputfile
		}
		else if (*ptr == '&') {
			ampersandFound = TRUE;
			printf("word found is &. \n");
			newargv[wordCount] = NULL;
			break;
			//set up background
			//null pointer in newargv array
			//end line break, or goto?
		}
		else {
		//newargv[wordCount] = ptr;
		printf("n=%d, s=[%s]\n", wordLength, ptr);
		ptr = (ptr + (wordLength + 1));
		wordLength = getword(ptr);
		}
	}

}
