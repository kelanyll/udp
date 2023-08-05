#include <boost/asio.hpp>
#include <iostream>

int main() {
  std::cout << "udp" << std::endl;

  try {
    // Create an I/O context
    boost::asio::io_context io_context;

    // Create a UDP socket
    boost::asio::ip::udp::socket socket(
        io_context,
        boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8080));

    // Buffer for receiving data
    char recv_buffer[1024];

    for (;;) {
      // Endpoint to store the client's address
      boost::asio::ip::udp::endpoint remote_endpoint;

      // Receive a message
      size_t len = socket.receive_from(boost::asio::buffer(recv_buffer),
                                       remote_endpoint);

      // Print the received message
      std::cout << "Received: " << std::string(recv_buffer, recv_buffer + len)
                << std::endl;

      // Send a reply
      std::string reply_message = "Hello, client!";
      socket.send_to(boost::asio::buffer(reply_message), remote_endpoint);
    }
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}