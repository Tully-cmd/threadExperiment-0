#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>  
#include <sys/stat.h>
#include <fcntl.h>

int main() {
  //fork then exec ps -eT, redirect output to file, parent wait...

  int childPID = fork();

  if( childPID == 0 ) {
    
    printf("Child process..\n");
    close(1);
    open("./psOutput",O_CREAT | O_WRONLY | O_TRUNC , S_IRWXU );
    char * psArgs[3];
    psArgs[0] = "ps";
    psArgs[1] = "-eT";
    psArgs[2] = NULL;  

    execvp(psArgs[0],psArgs);
    
  } else if ( childPID < 0) { 
  //error
    fprintf(STDOUT_FILENO,"fork failed\n");
    exit(2); 
  } else {
    
    printf("Parent waiting for child..\n");
    wait(NULL);

  }

  //fscanf/scanf through file and add valid lines to struct ProcThreads
  struct ProcThreads {
    int PID;
    int occur;
    char * proc;
  };  
  
  //sort ProcThread objs based on occurances 

  //print results
  int * stream = fopen("./psOutput","r"); 
  char * line = NULL;
  size_t len = 0;
  ssize_t nread;

  while ((nread = getline(&line, &len, stream)) != -1) {
    
    fwrite(line, nread, 1, stdout);
  }

  free(line);
  fclose(stream); 

  return 0;
}
