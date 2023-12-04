#include <iostream>       // For standard input/output stream objects
#include <fcntl.h>        // For file control options (e.g., open)
#include <unistd.h>       // For POSIX operating system API (e.g., close, read, write)
#include <errno.h>        // For retrieving error codes
#include <cstring>        // For string manipulation functions like strerror
#include <string>         // For std::string class
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <asm/termbits.h>   /* Definition of struct termios,
                               struct termios2, and
                               Bnnn, BOTHER, CBAUD, CLOCAL,
                               TC*{FLUSH,ON,OFF} and other constants */
#include <chrono>

#include <csignal>
using namespace std;
int fd;

// Function to initialize the serial port with custom speed
int initSerialPort(const char* device, int speed) {
    int fd = open(device, O_RDWR | O_NOCTTY);
    if (fd == -1) {
        std::cerr << "Error opening " << device << ": " << std::strerror(errno) << std::endl;
        return -1;
    }

    struct termios2 tio;
    if (ioctl(fd, TCGETS2, &tio) == -1) {
        std::cerr << "Error getting terminal attributes: " << std::strerror(errno) << std::endl;
        close(fd);
        return -1;
    }

    tio.c_cflag &= ~CBAUD;
    tio.c_cflag |= BOTHER;
    tio.c_cflag |= CLOCAL;
    tio.c_ispeed = speed;
    tio.c_ospeed = speed;

    if (ioctl(fd, TCSETS2, &tio) == -1) {
        std::cerr << "Error setting terminal attributes: " << std::strerror(errno) << std::endl;
        close(fd);
        return -1;
    }

    return fd;
}

// Function to send data
ssize_t sendData(int fd, const char* data, size_t length) {
    return write(fd, data, length);
}

// Function to receive data
ssize_t receiveData(int fd, char* buffer, size_t length) {
    return read(fd, buffer, length);
}


// Function to send data using std::string
ssize_t sendDataAsString(int fd, const std::string& data) {
    return write(fd, data.c_str(), data.size());
}


// // Example: Receiving string data
//     std::string receivedData;
//     if (receiveData(fd, receivedData, 100) == -1) { // Assuming maximum 100 bytes
//         std::cerr << "Error receiving data: " << std::strerror(errno) << std::endl;
//     } else {
//         std::cout << "Received data: " << receivedData << std::endl;
//     }
// Function to receive data into a std::string
ssize_t receiveDataAsString(int fd, std::string& outString, size_t maxBufferSize) {
    char buffer[maxBufferSize];
    ssize_t bytesRead = read(fd, buffer, maxBufferSize - 1); // Leave space for null terminator
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the string
        outString = buffer;
    }
    return bytesRead;
}


// Signal handler function
void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";

    // perform cleanup tasks here if necessary
    close(fd);

    // Terminate program
    exit(signum);  
}


int main(int argc, char* argv[]) {
    // if (argc != 3) {
    //     std::cerr << "Usage: " << argv[0] << " <device> <speed>\n";
    //     std::cerr << "Example:\n    " << argv[0] << " /dev/ttyUSB0 6000000\n";
    //     return -1;
    // }

    // int speed = std::atoi(argv[2]);
    int speed = 6000000;
    int fd = initSerialPort("/dev/ttyCH343USB0", speed);
    if (fd == -1) {
        return -1;
    }

    // Register signal handler
    signal(SIGINT, signalHandler);

    // // Example: Sending data
    // const char* dataToSend = "Hello, Serial Port!";
    // if (sendData(fd, dataToSend, strlen(dataToSend)) == -1) {
    //     std::cerr << "Error sending data: " << std::strerror(errno) << std::endl;
    // } else {
    //     std::cout << "Data sent successfully.\n";
    // }

    // Example: Receiving data

    int bytes_count;

    std::string receivedData;
    auto start_time = std::chrono::high_resolution_clock::now();
    while (1) {
        if (receiveDataAsString(fd, receivedData, 100) == -1) { // Assuming maximum 100 bytes
            std::cerr << "Error receiving data: " << std::strerror(errno) << std::endl;
        } else {
            std::cout << "Received data: " << receivedData << std::endl;
            bytes_count += receivedData.size();
            // cout << received_data << endl;
            receivedData = "";
            
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time-start_time);
    cout << "Finished " << duration.count() << " seconds" << endl;

    close(fd);

    return 0;
}
