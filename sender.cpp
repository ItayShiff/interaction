#include <iostream>
#include <vector> 
#include <thread>
#include <filesystem>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <SerialStream.h>

using namespace LibSerial;
using namespace cv;
using namespace std;

int main() {
    // Mat frame;
    // cv::VideoCapture vid_capture1("./Test1.mp4");   

    // Specify the serial port (change this to your port)
    SerialStream my_serial_stream("/dev/ttyCH343USB0", BaudRate::BAUD_4000000);

    //    std::string input_buffer = "HellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdas";
    char input_buffer[1000] = "fasHefsafasdfdasHellodsafsasdfsdfafasdfasdfadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdas";



    // Check if the serial port is open
    if (my_serial_stream.IsOpen()) {
        // Message to send
        std::string message = "Hellodsafsadfsafasdfdas test";



        while (true) {
            // Write the message to the serial port
            // my_serial_stream << message << std::endl;
            my_serial_stream << input_buffer << std::endl;

        }

        my_serial_stream.Close();


            // if (!vid_capture1.read(frame)) {
            //     break;
            // }

            // cout << frame << endl;

            // while (true) {
            // vid_capture1.read(frame);
            // cout << frame.size() << endl;
            // }

            //frame.col
            // Mat firstRow = frame.row(0);
            // for (int i = 0; i < frame.rows; i++) {
            //     // cout << frame.row(i).cols << endl;

            //     stringstream ss;
            //     ss << frame;
            //     cout << "Frame " << i + 1  << " size: " << ss.str().size() << endl;

            // }
            
            

            // frame
            // stringstream ss;
            // ss << frame;
            // // cout << ss.str().size() << endl;
            // std::cout << ss.str();
            // my_serial_stream.write(ss.str().c_str(), ss.str().size());
            


        // Optionally, you can also send individual characters
        // for (char ch : message) {
        //     my_serial_stream.put(ch);
        // }

        // Close the serial port
    } else {
        std::cerr << "Error: Unable to open serial port." << std::endl;
    }

    return 0;
}
