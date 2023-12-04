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
    int fd = open(device, O_RDWR | O_NOCTTY | O_SYNC);
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

    // Disable hardware flow control
    tio.c_cflag &= ~CRTSCTS;

    // Set custom baud rate (for example, 6000000)
    tio.c_cflag &= ~CBAUD;
    tio.c_cflag |= BOTHER;
    tio.c_cflag |= CLOCAL;
    tio.c_ispeed = speed;
    tio.c_ospeed = speed;

    tio.c_cc[VMIN] = 0;   // Non-blocking read
    tio.c_cc[VTIME] = 5;  // 0.5 seconds read timeout

    if (ioctl(fd, TCSETS2, &tio) == -1) {
        std::cerr << "Error setting terminal attributes: " << std::strerror(errno) << std::endl;
        close(fd);
        return -1;
    }

    // Set the file descriptor to non-blocking mode
    fcntl(fd, F_SETFL, FNDELAY);

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
    cout << "Before" << endl;
    ssize_t bytesRead = read(fd, buffer, maxBufferSize - 1); // Leave space for null terminator
    cout << "Bytes read" << bytesRead << endl;
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
    int speed = 4800;
    fd = initSerialPort("/dev/ttyCH343USB0", speed);
    if (fd == -1) {
        return -1;
    }
    cout << fd << endl;
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

    int bytes_count = 0;

    std::string receivedData;


    // Example: Continuously receiving data and summing total bytes read
    char buffer[100];
    ssize_t bytesRead;

    auto start_time = std::chrono::high_resolution_clock::now();
    while (bytes_count < 500000)  {
        bytesRead = receiveData(fd, buffer, sizeof(buffer));
        if (bytesRead == -1) {
            std::cerr << "Error receiving data: " << std::strerror(errno) << std::endl;
            // Decide whether to break the loop or handle the error differently
            break;
        } else if (bytesRead > 0) {
            bytes_count += bytesRead;
            std::cout << "Received data: " << buffer << std::endl;
        }

        std::cout << "Total bytes read so far: " << bytes_count << std::endl;

        // Optional: Add a small delay or condition to break the loop if necessary
        // usleep(10000); // Sleep for 10 milliseconds, for example
    }

    // while (bytes_count < 500000) {
    //     cout << "inside" << endl;
    //     if (receiveDataAsString(fd, receivedData, 100) == -1) { // Assuming maximum 100 bytes
    //         std::cerr << "Error receiving data: " << std::strerror(errno) << std::endl;
    //     } else {
    //         cout << "huh" << endl;
    //         std::cout << receivedData << std::endl;
    //         bytes_count += receivedData.size();
    //         // cout << received_data << endl;
    //         receivedData = "";
    //     }
    //     sleep(1);
    // }
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time-start_time);
    cout << "Finished " << duration.count() << " seconds" << endl;

    close(fd);

    return 0;
}
