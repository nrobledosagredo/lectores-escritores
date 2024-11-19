# Readers and writers problem

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

This script implements a simulation of concurrent processes in C, where multiple readers and writers access a shared resource in a controlled manner.

The program allows multiple reader processes to access the shared resource simultaneously, while writers require exclusive access. Coordination between readers and writers is achieved using semaphores and shared memory, ensuring proper synchronization and data consistency.

## Details

- **Involved processes:**
  - Readers: Can read the resource simultaneously.
  - Writers: Modify the resource with exclusive access.
- **Synchronization:**
  - POSIX semaphores (`sem_open`, `sem_wait`, `sem_post`) are used to prevent conflicts between processes.
- **Shared memory:**
  - `data`: Shared variable that is read and written.
  - `reader_count`: Counter for the number of active readers.

## Configurable parameters

- `ITERATION`: Number of iterations for each reader/writer.
- `MAX_READERS`: Maximum number of readers.
- `MAX_WRITERS`: Maximum number of writers.

## Compilation and execution

1. Compile the program:  
   ```bash
   gcc -o readers_writers readers_writers.c -lpthread
   ```

2. Run the generated binary:
   ```bash
   ./readers_writers
   ```