#include "socket.hh"
#include "util.hh"

#include <cstdlib>
#include <iostream>

using namespace std;

//find void get_URL(const string &host, const string &path).


void get_URL_server(const string &host, const string &path) {
    // Your code here.
    // there will be 10 rows code

    // const string *service;
    // const Address a_dns_server("host", 53);

    // create TCPSocket structure
    TCPSocket tcps;

    // Bind and listen
    // generate a random port
    // const uint16_t port_num = ((std::random_device()()) % 50000) + 1025;
    //tcps.bind(Address(host, port_num));// service/host unknown Error
    //tcps.bind(a_dns_server(host, port_num));  // unknown a_dns_server
    tcps.bind(Address(host, "http")); // work fine
    tcps.listen(1);

    // Accept connection
    //std::cout << "start accept\r\n";
    auto tcps3 = tcps.accept();
    while(1)
    {
        // Write response string
        // std::cout << "start write data\r\n";
        tcps3.write("hello world\r\n");

        //std::cout << "while\r\n";
        // tcps.accept();

        // Print received string
        // std::cout << "start read data\r\n";
        //
        auto recvd2 = tcps3.read();
        std::cout << recvd2 << "\r\n";

        // telnet \r\n input
        if (recvd2 == "\r\n") {
             tcps.close();
             tcps3.shutdown(SHUT_RDWR);
             break;
        }
        // wget curl ctrl-c input
        if (tcps3.eof()) {
             tcps.close();
             tcps3.shutdown(SHUT_RDWR);
             break;
        }
   }
    
    // You will need to connect to the "http" service on
    // the computer whose name is in the "host" string,
    // then request the URL path given in the "path" string.

    // Then you'll need to print out everything the server sends back,
    // (not just one call to read() -- everything) until you reach
    // the "eof" (end of file).

    cerr << "Function called: get_URL(" << host << ", " << path << ").\n";
    cerr << "Warning: get_URL() has not been implemented yet.\n";
}

void get_URL(const string &host, const string &path) {
    // Your code here.

    // You will need to connect to the "http" service on
    // the computer whose name is in the "host" string,
    // then request the URL path given in the "path" string.

    // reference: https://cs144.github.io/doc/lab0/class_t_c_p_socket.html
    TCPSocket tcps; 
    tcps.connect(Address(host, "http"));
    string input("GET " + path + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n");
    tcps.write(input);

    // Then you'll need to print out everything the server sends back,
    // (not just one call to read() -- everything) until you reach
    // the "eof" (end of file).

    // eof reference: https://cs144.github.io/doc/lab0/class_file_descriptor.html
    while (!tcps.eof()) {
        // waiting the eof in here
    } 
    tcps.close();

    // cerr << "Function called: get_URL(" << host << ", " << path << ").\n";
    // cerr << "Warning: get_URL() has not been implemented yet.\n";
}

int main(int argc, char *argv[]) {
    try {
        if (argc <= 0) {
            abort();  // For sticklers: don't try to access argv[0] if argc <= 0.
        }

        // The program takes two command-line arguments: the hostname and "path" part of the URL.
        // Print the usage message unless there are these two arguments (plus the program name
        // itself, so arg count = 3 in total).
        if (argc != 3) {
            cerr << "Usage: " << argv[0] << " HOST PATH\n";
            cerr << "\tExample: " << argv[0] << " stanford.edu /class/cs144\n";
            return EXIT_FAILURE;
        }

        // Get the command-line arguments.
        const string host = argv[1];
        const string path = argv[2];

        // Call the student-written function.
        get_URL(host, path);
    } catch (const exception &e) {
        cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
