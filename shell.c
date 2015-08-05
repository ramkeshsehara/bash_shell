#include<stdio.h>
#include<sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>
#include<fcntl.h> 
#define FALSE 0
#define TRUE !FALSE
 
extern  int alphasort(); //Inbuilt sorting function
 
char pathname[MAXPATHLEN];
 
void die(char *msg)
{
  perror(msg);
  exit(0);
}
 
int file_select(struct direct *entry)
{
    if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
        return (FALSE);
    else
        return (TRUE);
}
 /* ls function start */
int dir()
{
    int count,i;
    struct direct **files;
 
    if(!getcwd(pathname, sizeof(pathname)))
        die("Error getting pathname\n");
 
    printf("Current Working Directory = %s\n",pathname);
    count = scandir(pathname, &files, file_select, alphasort);
 
    /* If no files found, make a non-selectable menu item */
    if(count <= 0)
      die("No files in this directory\n");
  
    printf("Number of files = %d\n",count);
    for (i=1; i<count+1; ++i)
        printf("%s  ",files[i-1]->d_name);
    printf("\n"); /* flush buffer */
    return 0;
}



/* pipe function start */
void p()
{
int fd[2];
char input[100],*argv[50];
char *opt = "|",*spc = " ",*dir,*dest,*src;
fgets(input, sizeof(input), stdin);
dest = strtok(input, opt);
src = strtok(NULL, opt);
argv[1]=strtok(dest,spc);
argv[2]=strtok(NULL,spc);
argv[3]=strtok(src,spc);
argv[4]=strtok(NULL,spc);

pid_t child;
//pid_t pid
pipe(fd);
child=fork();
printf("Your Input == %s %s|%s %s\n",argv[1],argv[2],argv[3],argv[4]);
    if (child == -1)
    {
        printf("Error");
        exit(1);
    }
    else if (child) 
    {
        wait(&child);       
        close(fd[1]);
        dup2(fd[0],0);
        execlp(argv[3],argv[3],argv[4],NULL);

    }
    else if (child==0) 
    {
        close(fd[0]); 
        dup2(fd[1],1);
        execlp(argv[1],argv[1],argv[2],NULL);
    }

    //return 0;

}

/* pwd function start */

int pwd()
{
    char* cwd;
    char buff[PATH_MAX + 1];

    cwd = getcwd( buff, PATH_MAX + 1 );
    if( cwd != NULL ) {
        printf( "%s.\n", cwd );
    }
    return EXIT_SUCCESS;
}
 /* cd function start */

int change(char* argument)
{
    char* cwd;
    int x;
    char buff[PATH_MAX + 1];
    cwd = getcwd( buff, PATH_MAX + 1 );
    strcat(cwd,"/");
    strcat(cwd,argument);
    x = chdir(cwd);
  if(x==0)
{
printf("working directory is now : %s", cwd);
}
else
{
printf("\n error");
}
}
ope(int argc, char **argv)
{
  char arr[50], sou[30], op[20], des[20];
  int i, j, k, output_fd, input_fd;
  int pipefd[2];
  pid_t pid;
  scanf ("%s", &sou);
  scanf ("%s", &op);
  scanf ("%s", &des);
  if (strcmp (op, ">") == 0)
    {
      if (strcmp (sou, "ls") == 0)
    {
      pid = fork();
      if (pid == 0)
        {

        
          output_fd =
        open (des, O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
          dup2 (output_fd, 1);
          if (execv ("/bin/ls", argv) < 0)
        {
          printf ("%s: Command not found\n", argv[0]);
        }
          close (output_fd);
        }
     
    }
    }
  else if (strcmp (op, ">>") == 0)
    {
      if (strcmp (sou, "ls") == 0)
    {
      pid = fork();
      if (pid == 0)
        {
          output_fd =
        open (des, O_APPEND | O_WRONLY | O_CREAT,
              S_IRUSR | S_IRGRP | S_IROTH);
          dup2 (output_fd, 1);
          if (execv ("/bin/ls", argv) < 0)
        {
          printf ("%s: Command not found\n", argv[0]);
        }
        close(input_fd);
        }
    }
   main(argc,argv);
    }
else if (strcmp(op,"<")==0)
{
    if (strcmp (sou, "cat") == 0)
    {
      pid = fork ();
      if (pid == 0)
        {
          input_fd =
        open (des,O_RDONLY,0);
          dup2 (input_fd, 0);
          if (execv ("/bin/cat", argv) < 0)
        {
          printf ("%s: Command not found\n", argv[0]);
        }
        }
    }
}

else {
printf("operator is not here");
}

  return 0;
}
int main(int argc, char **argv)
{
   char str[80];
   int i=0;
   const char s[2] = " ";
   char *token,*token1;
 while(i=1)
{
   fgets(str, sizeof(str), stdin);
   /* get the first token */
   token = strtok(str, s);
   token1 = strtok(NULL, s);

if(strcmp(token,"mkdir")==0)
{
  mkdir(token1, 0777);
}
else if(strcmp(token,"rmdir")==0)
{
rmdir(token1);
}
else if(strcmp(token,"pwd")==0)
{
pwd();
}
else if(strcmp(token,"cd")==0)
{
change(token1);
}
else if(strcmp(token,"ls")==0)
{
dir();
}
else if(strcmp(token,"pipe")==0)
{
p();
}
else if(strcmp(token,"operator")==0)
{
ope(argc,argv);
}
else if(strcmp(token,"exit")==0)
{
exit(0);
}
else
{
printf("$");
}
}   
   return 0;
}








2.

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
int
main (int argc ,char **argv)
{
  //char *const argv[1000];
  char arr[50], sou[30], op[20], des[20];
  int i, j, k, output_fd, input_fd;
  int pipefd[2];
  pid_t pid;
  scanf ("%s", &sou);
  scanf ("%s", &op);
  scanf ("%s", &des);
  if (strcmp (op, ">") == 0)
    {
      if (strcmp (sou, "ls") == 0)
    {
      pid = fork ();
      if (pid == 0)
        {
          output_fd =
        open (des, O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
          dup2 (output_fd, 1);
          if (execv ("/bin/ls",argv ) < 0)
        {
          printf ("%s: Command not found\n", argv[0]);
        }
          close (output_fd);
        }
    }
    }
  else if (strcmp (op, ">>") == 0)
    {
      if (strcmp (sou, "ls") == 0)
    {
      pid = fork ();
      if (pid == 0)
        {
          output_fd =
        open (des, O_APPEND | O_WRONLY | O_CREAT,
              S_IRUSR | S_IRGRP | S_IROTH);
          dup2 (output_fd, 1);
          if (execv ("/bin/ls", argv) < 0)
        {
          printf ("%s: Command not found\n", argv[0]);
        }
        close(input_fd);
        }
    }
    }
else if (strcmp(op,"<")==0)
{
    if (strcmp (sou, "cat") == 0)
    {
      pid = fork ();
      if (pid == 0)
        {
          input_fd =
        open (des,O_RDONLY,0);
          dup2 (input_fd, 0);
          if (execv ("/bin/cat", argv) < 0)
        {
          printf ("%s: Command not found\n", argv[0]);
        }
        }
    }
}

  return 0;
}




3



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main()
{
int fd[2];
char input[100],*argv[50];
char *opt = "|",*spc = " ",*dir,*dest,*src;
gets(input);
dest = strtok(input, opt);
src = strtok(NULL, opt);
argv[1]=strtok(dest,spc);
argv[2]=strtok(NULL,spc);
argv[3]=strtok(src,spc);
argv[4]=strtok(NULL,spc);

pid_t child;
pipe(fd);
child=fork();
printf("Your Input == %s %s|%s %s\n",argv[1],argv[2],argv[3],argv[4]);
    if (child == -1)
    {
        printf("Error");
exit(1);
    }
    else if (child)  
    {
        wait(&child);        
        close(fd[1]);
        dup2(fd[0],0);
        execlp(argv[3],argv[3],argv[4],NULL);

    }
    else if (child==0)  
    {
        close(fd[0]);  
        dup2(fd[1],1);
        execlp(argv[1],argv[1],argv[2],NULL);
    }
    return 0;

}






4


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#define BUFFER_SIZE 1<<16
#define ARR_SIZE 1<<16

void parse_args(char *buffer, char** args,
                size_t args_size, size_t *nargs)
{
    char *buf_args[args_size]; 
    char **cp;
    char *wbuf;
    size_t i, j;
   
    wbuf=buffer;
    buf_args[0]=buffer;
    args[0] =buffer;
   
    for(cp=buf_args; (*cp=strsep(&wbuf, " \n\t")) != NULL ;){
        if ((*cp != '\0') && (++cp >= &buf_args[args_size]))
            break;
    }
   
    for (j=i=0; buf_args[i]!=NULL; i++){
        if(strlen(buf_args[i])>0)
            args[j++]=buf_args[i];
    }
   
    *nargs=j;
    args[j]=NULL;
}

int main(int argc, char **argv)
{
    char buffer[BUFFER_SIZE];
    char *args[ARR_SIZE];

    int *ret_status;
    size_t nargs,i;
    pid_t pid;
    fgets(buffer, BUFFER_SIZE, stdin);
        parse_args(buffer, args, ARR_SIZE, &nargs);
    if(strcmp(args[0],"ls")==0)
    {
        if(strcmp(args[1],"&")==0)
            {
                pid = fork();
                if(pid == -1)
                    printf("fork failed!");
                else if(pid)   
                    {
                         /*printf("Waiting for child (%d)\n", pid);
                            pid = wait(ret_status);
                            */printf("Child (%d) finished\n", pid);
                    }
                else
                {

                    if( execv("/bin/ls", argv))
                     {
                    puts(strerror(errno));
                    exit(127);
                     }   
                }
            }
    }                 
return 0;

}




5

#include<stdio.h>
#include<sys/types.h>
#define MAX 50
void separate(char *statment, char **words){

    while(*statment != '\0'){
        while(*statment == ' ' || *statment=='\n')
            *statment++ = '\0';
        *words++ = statment;
        while(*statment != ' ' && *statment != '\0' && *statment != '\n')
            statment++;
    }
    *words = '\0';
    return;
}

void execute(char **words){
    pid_t pid;
    int status;
    if((pid=fork())<0){
        printf("fork failed.\n");
    }else if(pid==0){
        if(execvp(*words,words)<0){
            printf( "execvp failed\n");
            exit(1);
        }
        printf("\n");
    }else{
        while(wait(&status) != pid);
    }
    return;
}
int main()
{
int done=1;
while(done)
{
printf("RAMKESHMEENA$ ");
char cmd1[MAX];
 char *words[MAX];
fgets(cmd1,sizeof(cmd1),stdin);
if(strcmp(cmd1,"exit")==0)
break;
separate(cmd1,words);
execute(words);
}
return 0;
}