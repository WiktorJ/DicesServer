//
// Created by Wojciech Grabis on 08.12.15.
//

#include "Sender.h"

using boost::asio::ip::tcp;

class tcp_connection
        : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_service& io_service)
    {
        return pointer(new tcp_connection(io_service));
    }

    tcp::socket& Socket()
    {
        return Socket_;
    }


    void start()
    {
        m_message = make_daytime_string();


        boost::asio::async_write(Socket_, boost::asio::buffer(m_message),
                                 boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }

private:
    tcp_connection(boost::asio::io_service& io_service)
            : Socket_(io_service)
    {
    }
    void handle_write(const boost::system::error_code& /*error*/,
                      size_t /*bytes_transferred*/)
    {
    }

    tcp::socket Socket_;
    std::string m_message;
};

class Sender
{
public:

    tcp::socket& Socket()
    {
        return Socket_;
    }

    Sender(boost::asio::io_service& io_service)
            : acceptor_(io_service, tcp::endpoint(tcp::v4(), 13))
    {
        accept();
    }


    void send(std::string data)
    {

     m_message = data;

        boost::asio::async_write(Socket_, boost::asio::buffer(m_message),
                                 boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));

    }




private:
    void accept()
    {
        tcp_connection::pointer new_connection =
                tcp_connection::create(acceptor_.get_io_service());

        acceptor_.async_accept(new_connection->socket(),
                               boost::bind(&Sender::handle_accept, this, new_connection,
                                           boost::asio::placeholders::error));
    }
    void handle_accept(tcp_connection::pointer new_connection,
                       const boost::system::error_code& error)
    {
        if (!error)
        {
            new_connection->start();
        }

        accept();
    }

    tcp::acceptor acceptor_;
};

int main()
{
    try
    {
        boost::asio::io_service io_service;

        Sender sender(io_service);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
