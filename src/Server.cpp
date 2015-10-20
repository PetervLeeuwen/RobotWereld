/*
 * Server.cpp
 *
 *  Created on: 20 okt. 2015
 *      Author: Peter
 */

#include "Config.hpp"
#include "Message.hpp"
#include "Session.hpp"
#include "CommunicationService.hpp"

namespace MessageASIO
{

	Server::Server( boost::asio::io_service& an_io_service,
						short port,
						Robot* aRobot) :
								io_service( an_io_service),
								acceptor( io_service, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), port)),
								robot( aRobot)
				{
					// start handling incomming connections
					handleAccept( NULL, boost::system::error_code());
				}

	Server::~Server()
	{
	}


/**
 *	Handle any incoming connections
 */
	void Server::handleAccept( 	MessageASIO::ServerSession* aSession,
						const boost::system::error_code& error)
	{
		if (!error)
		{
			// Create the session that will handle the next incomming connection
			MessageASIO::ServerSession* session = new MessageASIO::ServerSession( io_service, robot);
			// Let the acceptor wait for any new incoming connections
			// and let it call server::handle_accept on the happy occasion
			acceptor.async_accept( session->getSocket(), boost::bind( &Server::handleAccept, this, session, boost::asio::placeholders::error));
			// If there is a session, start it up....
			if (aSession)
			{
				aSession->start();
			}
		} else
		{
			delete aSession;
			throw std::runtime_error( __PRETTY_FUNCTION__ + std::string( ": ") + error.message());
		}
	}

	boost::asio::io_service&& getIOService(){
		return io_service;
	}
}
