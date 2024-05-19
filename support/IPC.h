#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define OS_Windows
#else
#include <unistd.h>
#include <fcntl.h>
#define OS_Linux
#endif

#define BUFFFER_SIZE 100

// Structure to hold platform-specific pipe data
typedef struct {
#ifdef OS_Windows
    HANDLE handle;
#else
    int fd;
#endif
} Pipe;

Pipe SimulationPipe;

// Function to connect to the named pipe
//IMPORTANT: Executing program must run with administrator permissions in order to connect to pipe
Pipe connect_to_pipe(const char* pipe_path);

// Function to read from the named pipe
int read_from_pipe(Pipe pipe, char* buffer, int buffer_size);

// Function to write to the named pipe
int write_to_pipe(Pipe pipe, const char* data, int data_size);

// Function to close the named pipe
void close_pipe(Pipe pipe);

int Test_Pipe_Main();

void initializeSimulationPipe();

