#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("usage: wait <command> <args>\n");
    exit(1);
  }

  pid_t process_id = fork();

  if (process_id < 0) {
    int err = errno;
    perror("fork failed");
    exit(err);
  }
  if (process_id == 0) {
    // exec the named process
    fprintf(stderr, "child: forking ");
    for (int i = 1; i < argc; i++) {
      fprintf(stderr, " %s", argv[i]);
    }
    fprintf(stderr, "\n");

    if (execvp(argv[1], argv + 1) < 0) {
      int err = errno;
      perror("execv failed");
      exit(err);
    }
  }

  fprintf(stderr, "parent: waiting on %d\n", process_id);
  int status;
  pid_t p = waitpid(process_id, &status, 0);

  // terminated normally
  if (WIFEXITED(status) != 0) {
    exit(WEXITSTATUS(status));
  }

  // killed by a signal
  if (WIFSIGNALED(status) != 0) {
    fprintf(stderr, "child (%d) was killed by signal: %d\n", process_id, WTERMSIG(status));
    exit(255);
  }
}
