# Readers and writers problem

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

This script simulates concurrent processes in C, where multiple readers and writers access a shared resource in a controlled manner. Multiple reader processes can access the resource simultaneously, while writers require exclusive access. Synchronization is achieved using semaphores and shared memory, ensuring proper coordination and data consistency. Created as part of a learning project to explore process synchronization in C.

## Features

- **Readers**: Can read the shared resource simultaneously.
- **Writers**: Modify the resource with exclusive access.
- **Synchronization**: Utilizes POSIX semaphores (`sem_open`, `sem_wait`, `sem_post`) to prevent conflicts between processes.
- **Shared memory**: 
  - `data`: Shared variable that is read and written.
  - `reader_count`: Counter for the number of active readers.

## Configurable parameters

- `ITERATION`: Number of iterations for each reader/writer.
- `MAX_READERS`: Maximum number of readers.
- `MAX_WRITERS`: Maximum number of writers.

## How to run

1. Compile the program:

```bash
gcc -o readers-writers-problem readers-writers-problem.c -lpthread
```

2. Run the generated binary:

```bash
./readers-writers-problem
```
