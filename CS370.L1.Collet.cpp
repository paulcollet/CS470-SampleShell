/* 
 * Author: Paul Collet
 * Date: 01/16/19
 * Class: CS370
 * Assignment: Lab 1
 * File: CS370.L1.Collet.cpp
 * 
 * All of the functions are built into exec() system :)
 */

#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


/* Function: command                                               
 *   This function receives a command line argument and then 
 *   uses fork() and execvp().   
 *   return: void
 *   par:    char **argv                                 
*/  

void command(char **argv)
{
    // I got 'pid' from online. It was originally a pid_t type. 
    int  pid, status;                                                                      
     
    if ((pid = fork()) < 0)                     // fork a child process
    {        
        printf("ERROR: forking failed\n");
        
        // apparently, there's a failing exit and a successful exit 
        exit(0);                                                                              
    }
     
     //for the child process: execute the command 
    else if (pid == 0 && execvp(*argv, argv) < 0) 
    {         
        printf("ERROR: exec failed\n");
        exit(0);
    }
     
     //for the parent: wait for completion
    else 
    {                                           
        /* Here's another one I found online. 
         * I had to find the include for it, though.*/
        while (wait(&status) != pid);                                                                                                   
    }
}


/* Function: parse                                                  
 *   This function takes an input line and parse it into tokens. 
 *   return: void
 *   par:    char *line, char **argv
 *   Personal Note: I originally had a a different parsing function, but I
 *   switched to this after I stopped using a string type as my command line.  
 */

void parse(char *line, char **argv)
{
    while (*line != '\0')                       // if not the end of line 
    {                    
        while (*line == ' ' || *line == '\t' 
                              || *line == '\n')
            *line++ = '\0';                     // replace white spaces with 0
          
        *argv++ = line;                         // save argument position
          
        while (*line != '\0' && *line != ' ' && 
            *line != '\t' && *line != '\n') 
            line++;                             // skip the argument until
    }
     
    *argv = '\0';                               // end of argument
}


/* Function: main                                                  
 *   return: int (because it won't take void...)
 *   par:    int argc, char* argv[64]   
 *   Personal Note:
 *      I got the numbers 10124 and 64 from online examples. 
 *      I thought about using vectors instead, but this works fine.                           
*/     
int main(int argc, char* argv[64])              // doesn't like a default argc?
{
    char  line[1024];                           // input 'string'
     
    while (true)                                // repeats until exits
    {                             
        printf("cwushell> ");                   // display a prompt
          
        // reads command line* Isn't there another getline?
        std::cin.getline(line, 1024, '\n');                                                 
          
        parse(line, argv);                      // parse the line
          
        if (strcmp(argv[0], "exit") == 0)       // checks for exit
            exit(1);                            // successful exit!
          
        command(argv);                          // otherwise, execute something
    }
     
    return 1;
}

//end

                

