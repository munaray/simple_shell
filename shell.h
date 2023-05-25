#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3


/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;


/* prototype for aliases.c */
int handleAliasCmd(char **args, char __attribute__((__unused__)) **argStart);
void updateAlias(char *name, char *value);
void printAlias(alias_t *alias);
char **printAliasValue(char **args);

/* START BuiltinHelp Prototype*/
/* envbuiltinhelp */
void displayEnvHelp(void);
void displaySetenvHelp(void);
void displayUnsetenvHelp(void);
/* otherbuiltinhelp.c */
void displayAllHelp(void);
void displayAliasHelp(void);
void displayCdHelp(void);
void displayExitHelp(void);
void displayHelpMessage(void);
/* END */

/* builtinHandler.c */
int (*handleBuiltin(char *command))(char **args, char **argStart);
int exitShell(char **args, char **argStart);
int cdShell(char **args, char __attribute__((__unused__)) **argStart);
int helpShell(char **args, char __attribute__((__unused__)) **argStart);

/* Envirometal variable builtinHandler.c */
int envShell(char **args, char __attribute__((__unused__)) **argStart);
int setenvShell(char **args, char __attribute__((__unused__)) **argStart);
int unsetenvShell(char **args, char __attribute__((__unused__)) **argStart);

/* environ.c */
char **_copyenv(void);
void freeEnv(void);
char **_getenv(const char *var);
char *envValueHandler(char *beginning, int len);
extern char **environ;

/* errorsHandler.c */
int numLen(int num);
char *_itoa(int num);
int createError(char **args, int err);

/* errormessages.c */
char *errorEnv(char **args);
char *error1(char **args);
char *errorToExit(char **args);
char *errorToCd(char **args);
char *syntaxError(char **args);

/* errormessages1.c */
char *error126(char **args);
char *error127(char **args);

/* getline.c */
void *_realloc(void *ptr, unsigned int oldSize, unsigned int newSize);
void allocateLineptr(char **lineptr, size_t *lineptrSize, char *buffer, size_t bufferSize);
ssize_t _getline(char **lineptr, size_t *lineptrSize, FILE *file);

/* variableHandler.c */
void replaceVariable(char **args, int *retLastExeCmd);

/* getpid.c */
char *getPid(void);
int execute(char **args, char **argStart);

/* logicalOperator.c */
void handleLogicalOperator(char *line, ssize_t *newLen);

/* lineHandler.c */
void lineHandler(char **line, ssize_t read);
ssize_t grabNewLen(char *line);

/* arguments.c */
int callArgs(char **args, char **argStart, int *retLastExeCmd);
char *getArgs(char *line, int *retLastExeCmd);
int checkArgs(char **args);
int executeArgs(char **args, char **argStart, int *retLastExeCmd);
int argsHandler(int *retLastExeCmd);

/* stringfunctions.c */
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/* stringfunctions1.c */
char *_strchr(char *str, char c);
int _strspn(char *str, char *accept);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);

/* tokenizers.c */
int tokenLength(char *str, char *delim);
int tokensCounter(char *str, char *delim);
char **_strtok(char *line, char *delim);

/* otherfunctions.c */
void handleSignal(int sig);
void freeArgs(char **args, char **argStart);

/* linkedlist.c */
alias_t *addAliasEnd(alias_t **head, char *name, char *value);
void freeAliasList(alias_t *head);
list_t *addNodeEnd(list_t **head, char *dir);
void freeList(list_t *head);

/* cmdByPath.c */
char *fillDirByPath(char *path);
list_t *getDirByPath(char *path);
char *handleCmdByPath(char *cmd);

/* fileascmdarg.c */
int failToOpen(char *filePath);
int processCmdFromFile(char *filePath, int *retLastExeCmd);

#endif
