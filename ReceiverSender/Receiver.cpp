//
// Created by Marcin Sendera on 15.12.2015.
//

#include "Receiver.h"
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/write.hpp>
#include <boost/bind.hpp>
#include <iostream>

using boost::asio::deadline_timer;
using boost::asio::ip::tcp;

class Receiver
{
public:
    Receiver(boost::asio::io_service& io_service)
            : stopped_(false),
              socket_(io_service),
              deadline_(io_service),
              heartbeat_timer_(io_service)
    {
    }

    void start(tcp::resolver::iterator endpoint_iter)
    {
        start_connect(endpoint_iter);

        deadline_.async_wait(boost::bind(&client::check_deadline, this));
    }

    void stop()
    {
        stopped_ = true;
        socket_.close();
        deadline_.cancel();
        heartbeat_timer_.cancel();
    }

private:
    void start_connect(tcp::resolver::iterator endpoint_iter)
    {
        if (endpoint_iter != tcp::resolver::iterator())
        {
            std::cout << "Trying " << endpoint_iter->endpoint() << "...\n";

            deadline_.expires_from_now(boost::posix_time::seconds(60));

            socket_.async_connect(endpoint_iter->endpoint(),
                                  boost::bind(&client::handle_connect,
                                              this, _1, endpoint_iter));
        }
        else
        {
            stop();
        }
    }

    void handle_connect(const boost::system::error_code& ec,
                        tcp::resolver::iterator endpoint_iter)
    {
        if (stopped_)
            return;

        if (!socket_.is_open())
        {
            std::cout << "Connect timed out\n";

            start_connect(++endpoint_iter);
        }

        else if (ec)
        {
            std::cout << "Connect error: " << ec.message() << "\n";

            socket_.close();

            start_connect(++endpoint_iter);
        }
        else
        {
            std::cout << "Connected to " << endpoint_iter->endpoint() << "\n";

            start_read();

            start_write();
        }
    }

    void start_read()
    {
        // Set a deadline for the read operation.
        deadline_.expires_from_now(boost::posix_time::seconds(1));

        boost::asio::async_read_until(socket_, input_buffer_, '\n',
                                      boost::bind(&client::handle_read, this, _1));
    }

    void handle_read(const boost::system::error_code& ec)
    {
        if (stopped_)
            return;

        if (!ec)
        {
            std::string line;
            std::istream is(&input_buffer_);
            std::getline(is, line);

            if (!line.empty())
            {
                std::cout << "Received: " << line << "\n";
            }

            start_read();
        }
        else
        {
            std::cout << "Error on receive: " << ec.message() << "\n";

            stop();
        }
    }

    void start_write()
    {
        if (stopped_)
            return;
        boost::asio::async_write(socket_, boost::asio::buffer("\n", 1),
                                 boost::bind(&client::handle_write, this, _1));
    }

    void handle_write(const boost::system::error_code& ec)
    {
        if (stopped_)
            return;

        if (!ec)
        {
            heartbeat_timer_.expires_from_now(boost::posix_time::seconds(10));
            heartbeat_timer_.async_wait(boost::bind(&client::start_write, this));
        }
        else
        {
            std::cout << "Error on heartbeat: " << ec.message() << "\n";

            stop();
        }
    }

    void check_deadline()
    {
        if (stopped_)
            return;

        if (deadline_.expires_at() <= deadline_timer::traits_type::now())
        {
            socket_.close();
            deadline_.expires_at(boost::posix_time::pos_infin);
        }

        deadline_.async_wait(boost::bind(&client::check_deadline, this));
    }

private:
    bool stopped_;
    tcp::socket socket_;
    boost::asio::streambuf input_buffer_;
    deadline_timer deadline_;
    deadline_timer heartbeat_timer_;
};

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: client <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;
        tcp::resolver r(io_service);
        client c(io_service);

        c.start(r.resolve(tcp::resolver::query(argv[1], argv[2])));

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
