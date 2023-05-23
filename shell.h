#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>


/* constants for the specific command type
 * 		 EXT_CMD - commands e.g. /bin/ls
 *		 INT_CMD - commands e.g. exit, env
 *		 PATH_CMD - commands in the PATH
 *		 INVALID_CMD - invalid commands
 */
#define INVALID_CMD -1
#define EXT_CMD 1
#define INT_CMD 2
#define PATH_CMD 3


#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 *struct map - a struct that maps a command name to a function 
 *
 *@commandName: name of the command
 *@function: the function that executes the command
 */

typedef struct map
{
	char *commandName;
	void (*function)(char **command);
} mapFunction;

extern char **environ;
extern char *cmdLine;
extern char **commands;
extern char *shellName;
extern int exitStatus;

/*Utilities*/
int parseCommand(char *);
char *getEnvironmentVariable(char *);
char *checkPath(char *);
void (*getFunction(char *))(char **);
char **tokenize(char *, char *);
void executeCommand(char **, int);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void ctrlCHandler(int);
extern void initializeCommand(char **current_command, int type_command);
extern void nonInteractiveMode(void);

/*Strings*/
char *_strtok_r(char *, char *, char **);
int _atoi(char *);
void removeComment(char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);
int _strspn(char *, char *);
int _strcspn(char *, char *);
char *_strchr(char *, char);
void print(char *, int);
void removeNewline(char *);
int _strlen(char *);
void _strcpy(char *, char *);

/*Builtin*/
void quit_function(char **);
void env_function(char **);

#endif /*SHELL_H*/
