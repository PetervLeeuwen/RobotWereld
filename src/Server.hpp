#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "Config.hpp"
#include "Message.hpp"
#include "Session.hpp"
#include "CommunicationService.hpp"

namespace MessageASIO
{
	/**
	 *
	 */
	class Server
	{
		public:
			/**
			 * The server will listen on localhost/ip-address on the port
			 */
			Server( boost::asio::io_service& an_io_service,
					short port,
					Robot* aRobot);

			~Server();

			/**
			 *	Handle any incoming connections
			 */
			void handleAccept( 	MessageASIO::ServerSession* aSession,
								const boost::system::error_code& error);

		boost::asio::io_service&& getIOService();

		private:
			// Provides core I/O functionality
			// @see http://www.boost.org/doc/libs/1_40_0/doc/html/boost_asio/reference/io_service.html
			boost::asio::io_service& io_service;

			// Provides the ability to accept new connections
			// @see http://www.boost.org/doc/libs/1_40_0/doc/html/boost_asio/reference/basic_socket_acceptor.html
			boost::asio::ip::tcp::acceptor acceptor;

			/**
			 *
			 */
			Robot* robot;
	};
// class Server
}// namespace MessageASIO

#endif // SERVER_HPP_
