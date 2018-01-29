

#include <iostream>
#include <boost/asio.hpp>
#include "server.hpp"

void start_server();



int main(int argc, char *argv[]) {
    start_server();
    return 0;
}


void start_server() {
        try {
            // Check command line arguments.
            /*if (argc != 4) {
                std::cerr << "Usage: http_server <address> <port> <doc_root>\n";
                std::cerr << "  For IPv4, try:\n";
                std::cerr << "    receiver 0.0.0.0 80 .\n";
                std::cerr << "  For IPv6, try:\n";
                std::cerr << "    receiver 0::0 80 .\n";
                return 1;
            }*/

            std::string address = "192.168.0.15";
            std::string port = "5001";
            std::string folder = "/Users/santa/CLionProjects/Boosting/templates";

            std::cout << "Address is " << address << std::endl;
            std::cout << "Port is " << port << std::endl;
            std::cout << "Folder is " << folder << std::endl;

            // Initialise the server.
            http::server::server s(address, port, folder);

            // Add route get cars
            const std::string getCarsRequest = "/get_cars";
            http::server::route routeGetCars(getCarsRequest, []() -> std::string {
                return "Hello world";
            });
            s.add_route(routeGetCars);

            // Run the server until stopped.
            s.run();
        }
        catch (std::exception &e) {
            std::cerr << "exception: " << e.what() << "\n";
        }
};