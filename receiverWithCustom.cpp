#include <CppLinuxSerial/SerialPort.hpp>
#include <chrono>

using namespace mn::CppLinuxSerial;
using namespace std;

int main() {
	// Create serial port object and open serial port at 57600 baud, 8 data bits, no parity bit, one stop bit (8n1),
	// and no flow control
	// SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_57600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	SerialPort serialPort("/dev/ttyACM0", 115200); // instead if you want to provide a custom baud rate
	serialPort.SetTimeout(100); // Block for up to 100ms to receive data
	serialPort.Open();

	// WARNING: If using the Arduino Uno or similar, you may want to delay here, as opening the serial port causes
	// the micro to reset!

	// Read some data back (will block for up to 100ms due to the SetTimeout(100) call above)
	std::string readData;

    int bytes_count = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    while (bytes_count < 500000) {
	    serialPort.Read(readData);
	    std::cout << "Read data = \"" << readData << "\"" << std::endl;
        bytes_count += readData.size();
        readData = "";
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time-start_time);
    cout << "Finished " << duration.count() << " seconds" << endl;

	// Close the serial port
	serialPort.Close();
}