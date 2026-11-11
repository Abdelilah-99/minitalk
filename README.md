# minitalk: client-server messaging with UNIX signals

A project from **1337** (42 network): a small data-exchange program written in C: the **client** sends a string to the **server** using
only two UNIX signals, `SIGUSR1` and `SIGUSR2`.

## How it works
- Each character is sent **bit by bit**: `SIGUSR2` = 1, `SIGUSR1` = 0
- The server rebuilds each byte with `sigaction` (`SA_SIGINFO`) and prints it when 8 bits arrive
- The server **acknowledges every bit** back to the client (`kill(client_pid, SIGUSR1)`), so no
  signal is lost even for long messages
- `'\0'` marks the end of a message

## Build and run
```bash
make
./server                 # prints its PID
./client <PID> "hello"   # in another terminal
```

**Stack:** C · UNIX signals · Makefile
