#include <iostream>
#include <vector> 
#include <thread>
#include <filesystem>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sstream>
#include <SerialStream.h>

using namespace LibSerial;
using namespace cv;
using namespace std;

// std::string encodeImageToString(const cv::Mat &image) {
//     vector<uchar> buffer;
//     cv::imencode(".jpg", image, buffer);
//     // string encoded = base64_encode()
//     return base64_encode(buffer.data(), buffer.size());
// }

// cv::Mat decodeStringToImage(const string &encodedImage) {
//     string decodedData = base64_decode(encodedImage);
//     vector<uchar> buffer(decodedData.begin(), decodedData.end());
//     return cv::imdecode(buffer, cv::IMREAD_UNCHANGED);
// }

int main() {
    // Mat frame;
    // cv::VideoCapture vid_capture1("./Test1.mp4");   

    // Specify the serial port (change this to your port)
    SerialStream my_serial_stream("/dev/ttyCH343USB0", BaudRate::BAUD_4800);

    // cv::Mat image = cv::imread("./0.jpg");

    // if (image.empty()) {
    //     cerr << "Error: Could not read the image" << endl;
    //     return 1;
    // }

    // string encodedImageString = encodeImageToString(image);

    // cv::Mat reconstructedImage = decodeStringToImage(encodedImageString);

    // cv::imshow("Reconstructed image", reconstructedImage);




    


    //    std::string input_buffer = "HellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdas";
    // char input_buffer[1000] = "fasHefsafasdfdasHellodsafsasdfsdfafasdfasdfadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdasHellodsafsadfsafasdfdas";
    char input_buffer[1000] = "Hi_this_is_DroneX_-_Laser_-_Beware\0";



    // Check if the serial port is open
    if (my_serial_stream.IsOpen()) {
        // Message to send
        std::string message = "Hellodsafsadfsafasdfdas test";



        while (true) {
            // Write the message to the serial port
            // my_serial_stream << message << std::endl;
            my_serial_stream << input_buffer << endl;
            // my_serial_stream.write(input_buffer, 1000);

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
