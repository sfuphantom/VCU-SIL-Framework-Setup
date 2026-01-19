#include "IPC.h"
#include "ansi_colors.h"
#ifndef _WIN32
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#endif

Pipe SimulationPipe;

// Function to connect to the named pipe
//IMPORTANT: Executing program must run with administrator permissions in order to connect to pipe
Pipe connect_to_pipe(const char* pipe_path) {
    Pipe pipe;
#ifdef OS_Windows
    pipe.handle = CreateFile(
        pipe_path,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );
    if (pipe.handle == INVALID_HANDLE_VALUE) {
        printf("%sError opening pipe: %d%s\n", RED, GetLastError(), CRESET);
        pipe.handle = NULL; /* Mark as invalid */
        SimulationPipe = pipe;
        return pipe;
    }
#else
    /* On Mac/Linux, try to create the FIFO if it doesn't exist */
    struct stat st;
    if (stat(pipe_path, &st) != 0) {
        /* FIFO doesn't exist, try to create it */
        if (mkfifo(pipe_path, 0666) != 0) {
            printf("%sWarning: Could not create pipe '%s': %s%s\n", YEL, pipe_path, strerror(errno), CRESET);
            printf("%sApplication will continue without pipe connection.%s\n", YEL, CRESET);
            pipe.fd = -1; /* Mark as invalid */
            SimulationPipe = pipe;
            return pipe;
        }
    }
    
    /* Open FIFO in write-only, non-blocking mode */
    /* This allows the app to continue even if no reader is connected */
    pipe.fd = open(pipe_path, O_WRONLY | O_NONBLOCK);
    if (pipe.fd == -1) {
        if (errno == ENXIO) {
            /* No reader connected yet - this is okay, we'll try again on write */
            printf("%sWarning: No reader connected to pipe '%s' yet.%s\n", YEL, pipe_path, CRESET);
            printf("%sApplication will continue. Pipe will be used when a reader connects.%s\n", YEL, CRESET);
        } else {
            printf("%sWarning: Could not open pipe '%s': %s%s\n", YEL, pipe_path, strerror(errno), CRESET);
            printf("%sApplication will continue without pipe connection.%s\n", YEL, CRESET);
        }
        pipe.fd = -1; /* Mark as invalid for now */
    } else {
        printf("%sSuccessfully connected to pipe '%s'.%s\n", GRN, pipe_path, CRESET);
    }
#endif
    SimulationPipe = pipe;
    return pipe;
}

Pipe create_pipe(const char* pipe_path)
{
    Pipe pipe;
#ifdef OS_Windows
    pipe.handle = CreateFile(
        pipe_path,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        CREATE_NEW,
        0,
        NULL
    );
    if (pipe.handle == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error opening pipe: %d\n", GetLastError());
        //exit(EXIT_FAILURE);
    }
#else
    pipe.fd = open(pipe_path, O_RDWR | O_CREAT, 0666);
    if (pipe.fd == -1) {
        perror("Error creating pipe");
        //exit(EXIT_FAILURE);
    }
#endif
    return pipe;
}

// Function to read from the named pipe
int read_from_pipe(Pipe pipe, char* buffer, int buffer_size) {
#ifdef OS_Windows
    DWORD bytes_read;
    BOOL success = ReadFile(pipe.handle, buffer, buffer_size, &bytes_read, NULL);
    if (!success || bytes_read == 0) {
        fprintf(stderr, "Error reading from pipe: %d\n", GetLastError());
        return -1;
    }
    return bytes_read;
#else
    if (pipe.fd == -1) {
        return -1; /* Pipe not connected */
    }
    int bytes_read = read(pipe.fd, buffer, buffer_size);
    if (bytes_read == -1) {
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            perror("Error reading from pipe");
        }
        return -1;
    }
    return bytes_read;
#endif
}

// Function to write to the named pipe
int write_to_pipe(Pipe pipe, const char* data, int data_size) {
#ifdef OS_Windows
    DWORD bytes_written;
    if (!WriteFile(pipe.handle, data, data_size, &bytes_written, NULL)) {
        fprintf(stderr, "Error writing to pipe: %d\n", GetLastError());
        return -1;
    }
    return bytes_written;
#else
    if (pipe.fd == -1) {
        return -1; /* Pipe not connected */
    }
    int bytes_written = write(pipe.fd, data, data_size);
    if (bytes_written == -1) {
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            perror("Error writing to pipe");
        }
        return -1;
    }
    return bytes_written;
#endif
}

// Function to close the named pipe
void close_pipe(Pipe pipe) {
#ifdef OS_Windows
    CloseHandle(pipe.handle);
#else
    if (pipe.fd != -1) {
        close(pipe.fd);
    }
#endif
}

void initializeSimulationPipe()
{
    fflush(stdout);
    const char* pipe_path =
#ifdef OS_Windows
        "\\\\.\\pipe\\my_pipe";
#else
        //Linux Development
        "my_pipe";
#endif
    printf("%sConnecting to pipe\n%s", GRN, CRESET);

    connect_to_pipe(pipe_path);
}

int Test_Pipe_Main() {
    fflush(stdout);
    const char* pipe_path =
#ifdef OS_Windows
        "\\\\.\\pipe\\my_pipe";
#else
        "my_pipe";
#endif
    printf("About to connect my pipe");

    Pipe pipe = connect_to_pipe(pipe_path);

    // Read data from the pipe
    char buffer[BUFFFER_SIZE];
    int bytes_read = read_from_pipe(pipe, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        close_pipe(pipe);
        exit(EXIT_FAILURE);
    }
    if (bytes_read > BUFFFER_SIZE)
    {
        buffer[BUFFFER_SIZE - 1] = '\0';
    }
    else
    {
        buffer[bytes_read - 1] = '\0';
    }
    // Print the received message
    printf("Received message: %s\n", buffer);

    // Write acknowledgment message to the pipe
    const char* ack_message = "Data from C";
    int bytes_written = write_to_pipe(pipe, ack_message, strlen(ack_message));
    if (bytes_written == -1) {
        close_pipe(pipe);
        exit(EXIT_FAILURE);
    }

    // Write back the received message
    bytes_written = write_to_pipe(pipe, buffer, bytes_read);
    if (bytes_written == -1) {
        close_pipe(pipe);
        exit(EXIT_FAILURE);
    }

    // Close the pipe handle
    //close_pipe(pipe);

    return 0;
}
