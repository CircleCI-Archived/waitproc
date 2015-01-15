### NAME

waitproc - run a command and print signal information if killed by a signal

### SYNOPSIS
waitproc COMMAND [ARG]...

### DESCRIPTION
Run COMMAND, if it is killed by being sent a signal print the signal number to
stderr.

If COMMAND exits normally waitproc exits with the same exit code.

This is intended for commands run over SSH. SSH exits 255 if an error occurs,
including when the command is terminated due to receiving a signal.

```bash
$ ssh localhost sleep 59
$ echo $?
255
```

```bash
$ ssh localhost waitproc sleep 59
parent: waiting on 106779
child: forking  sleep 59
child (106779) was killed by signal: 9
$ echo $?
255
```
