#include <iostream>
#include <vector> 
#include <thread>
#include <filesystem>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <SerialStream.h>
#include <fstream>
#include <chrono>

using namespace LibSerial;
using namespace cv;
using namespace std;

int main() {
    // Define the serial port
    SerialStream my_serial_stream("/dev/ttyCH343USB1", BaudRate::BAUD_4000000);

    std::ifstream inFile("serialized_data.txt");
    vector<char> buffer;

    // char input_buffer[1000];
    char input_buffer[1000];

    // Check if the serial port is open
    if (my_serial_stream.IsOpen()) {
        // // Write data to the serial port
        // my_serial_stream << "Hello, Arduino!" << std::endl;
        std::string received_data;
        int bytes_count;


        auto start_time = std::chrono::high_resolution_clock::now();
        while (bytes_count < 500000) {
            my_serial_stream >> received_data;
            bytes_count += received_data.size();
            // cout << received_data << endl;
            received_data = "";
            

            // my_serial_stream.read(input_buffer, sizeof(input_buffer));
            // cout << input_buffer << endl;
            
            // std::string str(input_buffer);
            // str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
            // std::cout << "Received data: " << str.size() << std::endl;

            cout << "Counter" << bytes_count << endl;
        }
        auto end_time = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time-start_time);
        cout << "Finished " << duration.count() << " seconds" << endl;
        //cout << received_data.size() << endl;






        //     // // Read data from the serial port
        //     // 
        //     // my_serial_stream.getline();
        //     // // Display the received data


        // Close the serial port
        my_serial_stream.Close();
    } else {
        std::cerr << "Error: Unable to open serial port." << std::endl;
    }

    return 0;
}