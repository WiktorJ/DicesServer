//
// Created by Wojciech Grabis on 08.12.15.
//

#ifndef DICESSERVER_SENDER_H
#define DICESSERVER_SENDER_H
#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class tcp_connection{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;
    static pointer create(boost::asio::io_service& io_service);
    void start();

private:
    tcp_connection(boost::asio::io_service& io_service);
    void handle_write(const boost::system::error_code& /*error*/,
                      size_t /*bytes_transferred*/);
    tcp::socket Socket_;
    std::string m_message;
};



class Sender {
public:

    tcp::socket& Socket();
    void send(std::string data);

private:
    void accept();
    int main();

};


#endif //DICESSERVER_SENDER_H
