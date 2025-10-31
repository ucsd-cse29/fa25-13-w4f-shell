#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define CMD_LENGTH 1000

// Puts arguments into result using strtok
int parse_args(char* cmd, char** result) {
  // Put return values from strtok into result
  char* current = strtok(cmd, " ");
  int i = 0;
  while(current != NULL) {
    result[i] = current;
    current = strtok(NULL, " ");
    i += 1;
  }
  return i;
}

int main() {
  char cmd[CMD_LENGTH];
  char* args[CMD_LENGTH];

  while(1) {
    printf("THIS IS THE PROMPT TYPE HERE PLS» ");
    char* result = fgets(cmd, CMD_LENGTH, stdin);
    if(result == NULL) { break; }
    cmd[strcspn(cmd, "\n")] = '\0';

    int argc = parse_args(cmd, args);
    args[argc] = NULL;


    int pid = fork();

    if(pid < 0) {
      printf("fork() failed: %d\n", pid);
      break;
    }
    else if(pid == 0) {
      // child process 
      execvp(args[0], args);
    }
    else {
      // parent process (our shell)
      printf("Starting %d\n", pid);
      waitpid(pid, NULL, 0);
      printf("Finished %d\n", pid);
    }

  }
}
