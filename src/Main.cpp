#include "Config.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include "MainApplication.hpp"
#include "Server.hpp"
#include "RobotWorld.hpp"

int main( 	int argc,
			char* argv[])
{

		RobotWorld RW;
		try
		{
			if(argc == "client" ||argc == 'Client' ||argc == "Cliënt" ||argc == "cliënt"){
				// Call the wxWidgets main variant
				// This will actually call Application
				int result = runGUI( argc, argv);
				return result;
			}
			if(argc == "server"){
				// Create the server object. This must be alive while the program runs
				MessageASIO::Server server(server.getIOService(), 12345, RW.getRobotWorld().getRobots());

				// Run the service until further notice
				server.getIOService().run();
			}

		}
		catch (std::exception& e)
		{
			std::cerr << __PRETTY_FUNCTION__ << ": " << e.what() << std::endl;
		}
		catch (...)
		{
			std::cerr << __PRETTY_FUNCTION__ << ": unknown exception" << std::endl;
		}
		return 0;
}
