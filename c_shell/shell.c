#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
// so we need to define what delimits our tokens.
// In this case  white space
// will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size
#define MAX_NUM_HISTORY 15      // history only supports up to 15 items
#define MAX_NUM_PID 20          // PID history only supports up to 15 items
#define MAX_NUM_ARGUMENTS 20    // Mav shell only supports five arguments

void history_print(char *history_array[]);
void pid_history_print(int *pid_history_array);

int main(int argc, char *argv[])
{

    //variables
    char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );
    char * historyArray[MAX_NUM_HISTORY];
    int pidHistoryArray[MAX_NUM_PID] = {0};
    int historyCount = 0;
    int pidHistoryCount = 0;

    //allocate memory for history array
    for (int i = 0; i< MAX_NUM_HISTORY; i++)
    {
        historyArray[i] = (char *) malloc (1024);
        memset(historyArray[i], 0, 1024);
    }

    while( 1 )
    {
        // Print out the msh prompt
        printf ("msh> ");

        // Read the command from the commandline.  The
        // maximum command that will be read is MAX_COMMAND_SIZE
        // This while command will wait here until the user
        // inputs something since fgets returns NULL when there
        // is no input
        while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );

        strncpy(historyArray[historyCount++], cmd_str, strlen(cmd_str));

        //resets history so it only tracks most recent commands
        if (historyCount == 15)
            historyCount = 0;

        if (pidHistoryCount == 15)
            pidHistoryCount = 0;

        //if input starts with '!' this will remove the '!' then extract
        //the integer from the given string and will then use that int to 
        //reuse the command from history 
        if (cmd_str[0] == '!')
        {

            char * strToExtractInt = malloc(1024);
            //copy over string except for the '!' 
            memcpy(strToExtractInt, &cmd_str[1], strlen(cmd_str));

            //convert string into an int
            int extractedInt = atoi(strToExtractInt);

            //extracted int is used to pick which element out of history then copy
            //the history element into cmd_str
            if (extractedInt >= 0 && extractedInt <= MAX_NUM_HISTORY)
            {
                strncpy(cmd_str, historyArray[extractedInt], strlen(historyArray[extractedInt]));
            }
        }

        /* Parse input */
        char *token[MAX_NUM_ARGUMENTS];

        int   token_count = 0;

        // Pointer to point to the token
        // parsed by strsep
        char *arg_ptr;

        char *working_str  = strdup( cmd_str );

        // we are going to move the working_str pointer so
        // keep track of its original value so we can deallocate
        // the correct amount at the end
        char *working_root = working_str;

        // Tokenize the input strings with whitespace used as the delimiter
        while ( ( (arg_ptr = strsep(&working_str, WHITESPACE) ) != NULL) && (token_count<MAX_NUM_ARGUMENTS))
        {
            token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );

            if (strlen( token[token_count] ) == 0)
                token[token_count] = NULL;

            token_count++;
        }

        //Shell
        if (token[0] != NULL) //if blank line entered continue to print prompt
        {
            if (strcmp(token[0], "quit") == 0 || strcmp(token[0], "exit") == 0)
                goto Exit;
                //exit(0);
            else
            {
                //cd command
                if (strcmp(token[0], "cd") == 0)
                    chdir(token[1]);

                //If a command still contains a ! then that means it failed to pull from history.
                //if command contains ! still then this will throw and error and print contents
                //of the history array
                else if (strchr(token[0], '!'))
                {
                    printf("Command not in history.\n");
                    history_print(historyArray);
                }

                //history command
                else if (strcmp(token[0], "history") == 0)
                    history_print(historyArray);  

                //showpids command
                else if (strcmp(token[0], "showpids") == 0)
                    pid_history_print(pidHistoryArray);
                
                else
                {
                    //fork creation
                    pid_t pid = fork();

                    //add pid created to pidHistoryArray
                    pidHistoryArray[pidHistoryCount++] = pid;

                    //check if fork failed
                    if (pid < 0)
                        perror("Fork Failed");

                    //on fork success
                    if (pid == 0)
                    {
                        //return value for exec failure is -1
                        //if command to execvp fails then print error
                        if (execvp(token[0], token) == -1)
                            printf("%s: Command not found.\n", token[0]); //print error
                    }
                    else 
                        wait(NULL);

                    free( working_root );
                }
            }
        }
    }

Exit:
    return 0;
}

void history_print(char *history_array[])
{
    for (int k = 0; k < MAX_NUM_HISTORY; k++)
    {
        if (strlen(history_array[k]) > 0 )
            printf("%d: %s", k, history_array[k]);
    }
}

void pid_history_print(int *pid_history_array)
{
    for (int k = 0; k < MAX_NUM_PID; k++)
    {
        if (pid_history_array[k] > 0) //unused elements set to 0
            printf("%d: %d\n", k, pid_history_array[k]);
    }
}
