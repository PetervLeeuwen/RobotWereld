#include "MainFrameWindow.hpp"
#include "MainApplication.hpp"
#include "RobotWorldCanvas.hpp"
#include "LogTextCtrl.hpp"
#include "WidgetDebugTraceFunction.hpp"
#include "StdOutDebugTraceFunction.hpp"
#include "Button.hpp"
#include "RobotWorld.hpp"
#include "Robot.hpp"
#include "Math.hpp"
#include "Shape2DUtils.hpp"
#include <iostream>
#include <vector>
#include "Message.hpp"
#include "Thread.hpp"
#include "Logger.hpp"
#include "Client.hpp"
#include "ConfigFile.hpp"

#include "Wall.hpp"
#include "Goal.hpp"

/**
 * IDs for the controls and the menu commands
 * If there are (default) wxWidget ID's try to maintain
 * compatibility, especially wxID_ABOUT because on a Mac it is special
 */
enum
{
	ID_QUIT = wxID_EXIT,         	//!< ID_QUIT
	ID_OPTIONS = wxID_PROPERTIES,	//!< ID_OPTIONS
	ID_ABOUT = wxID_ABOUT,        	//!< ID_ABOUT
	ID_WIDGET_DEBUG_TRACE_FUNCTION, //!< ID_WIDGET_DEBUG_TRACE_FUNCTION
	ID_STDCOUT_DEBUG_TRACE_FUNCTION //!< ID_STDCOUT_DEBUG_TRACE_FUNCTION

};
/**
 *
 */
MainFrameWindow::MainFrameWindow( const std::string& aTitle) :
				Frame( NULL, DEFAULT_ID, WXSTRING( aTitle), DefaultPosition, Size( 500, 400)),
				clientPanel( NULL),
				menuBar( NULL),
				splitterWindow( NULL),
				lhsPanel( NULL),
				robotWorldCanvas( NULL),
				rhsPanel( NULL),
				logTextCtrl( NULL),
				buttonPanel( NULL),
				debugTraceFunction( NULL)
{
	initialise();
}
/**
 *
 */
MainFrameWindow::~MainFrameWindow()
{
	if (debugTraceFunction)
	{
		delete debugTraceFunction;
	}
}
/**
 *
 */
DebugTraceFunction* MainFrameWindow::getTraceFunction()
{
	return debugTraceFunction;
}
/**
 *
 */
void MainFrameWindow::initialise()
{
	SetMenuBar( initialiseMenuBar());

	GridBagSizer* sizer = new GridBagSizer( 5, 5);

	sizer->Add( initialiseClientPanel(),
	GBPosition( 0, 0), 	// row ,col
	GBSpan( 1, 1), 		// row ,col
	EXPAND);

	sizer->AddGrowableCol( 0);
	sizer->AddGrowableRow( 0);

	sizer->SetSizeHints( this);
	SetMinSize( wxSize( 500, 350));

	Bind( wxEVT_COMMAND_MENU_SELECTED,
	      [this](CommandEvent& anEvent){ this->OnQuit(anEvent);},
	      ID_QUIT);
	Bind( wxEVT_COMMAND_MENU_SELECTED,
	      [this](CommandEvent& anEvent){ this->OnWidgetDebugTraceFunction(anEvent);},
	      ID_WIDGET_DEBUG_TRACE_FUNCTION);
	Bind( wxEVT_COMMAND_MENU_SELECTED,
	      [this](CommandEvent& anEvent){ this->OnStdOutDebugTraceFunction(anEvent);},
	      ID_STDCOUT_DEBUG_TRACE_FUNCTION);
	Bind( wxEVT_COMMAND_MENU_SELECTED,
	      [this](CommandEvent& anEvent){ this->OnAbout(anEvent);},
	      ID_ABOUT);
}
/**
 *
 */
MenuBar* MainFrameWindow::initialiseMenuBar()
{
	Menu* fileMenu = new Menu;
	fileMenu->Append( ID_QUIT, WXSTRING( "E&xit\tAlt-X"), WXSTRING( "Exit the application"));

	Menu* debugMenu = new Menu;
	debugMenu->AppendRadioItem( ID_WIDGET_DEBUG_TRACE_FUNCTION, WXSTRING( "Widget"), WXSTRING( "Widget"));
	debugMenu->AppendRadioItem( ID_STDCOUT_DEBUG_TRACE_FUNCTION, WXSTRING( "StdOut"), WXSTRING( "StdOut"));

	Menu* helpMenu = new Menu;
	helpMenu->Append( ID_ABOUT, WXSTRING( "&About...\tF1"), WXSTRING( "Show about dialog"));

	menuBar = new wxMenuBar;
	menuBar->Append( fileMenu, WXSTRING( "&File"));
	menuBar->Append( debugMenu, WXSTRING( "&Debug"));
	menuBar->Append( helpMenu, WXSTRING( "&Help"));

	return menuBar;
}
/**
 *
 */
Panel* MainFrameWindow::initialiseClientPanel()
{
	if (!clientPanel)
	{
		clientPanel = new Panel( this, DEFAULT_ID);

		GridBagSizer* sizer = new GridBagSizer();

		sizer->Add( 5, 5,
		GBPosition( 0, 0));

		sizer->Add( initialiseSplitterWindow(),
		GBPosition( 1, 1),
		GBSpan( 1, 1), EXPAND);
		sizer->AddGrowableRow( 1);
		sizer->AddGrowableCol( 1);

		sizer->Add( 5, 5,
		GBPosition( 2, 2));

		clientPanel->SetSizer( sizer);
		sizer->SetSizeHints( clientPanel);
	}
	return clientPanel;

}
/**
 *
 */
SplitterWindow* MainFrameWindow::initialiseSplitterWindow()
{
	if (!splitterWindow)
	{
		GridBagSizer* sizer = new GridBagSizer();

		splitterWindow = new SplitterWindow( clientPanel, DEFAULT_ID);

		splitterWindow->SplitVertically( initialiseLhsPanel(), initialiseRhsPanel());

		sizer->Add( 5, 5,
		GBPosition( 0, 0));

		sizer->Add( splitterWindow,
		GBPosition( 1, 1),
		GBSpan( 1, 1), EXPAND);
		sizer->AddGrowableRow( 1);
		sizer->AddGrowableCol( 1);

		sizer->Add( 5, 5,
		GBPosition( 2, 2));

		splitterWindow->SetSizer( sizer);
		sizer->SetSizeHints( splitterWindow);

	}
	return splitterWindow;

}
/**
 *
 */
Panel* MainFrameWindow::initialiseLhsPanel()
{
	if (!lhsPanel)
	{
		lhsPanel = new Panel( splitterWindow, DEFAULT_ID);

		GridBagSizer* sizer = new GridBagSizer();
		sizer->Add( 5, 5,
		GBPosition( 0, 0),
		GBSpan( 1, 1), EXPAND);

		sizer->Add( robotWorldCanvas = new RobotWorldCanvas( lhsPanel),
		GBPosition( 1, 1),
		GBSpan( 1, 1), EXPAND);
		sizer->AddGrowableCol( 1);
		sizer->AddGrowableRow( 1);

		sizer->Add( 5, 5,
		GBPosition( 2, 2),
		GBSpan( 1, 1), EXPAND);

		lhsPanel->SetSizer( sizer);
		sizer->SetSizeHints( lhsPanel);
	}
	return lhsPanel;
}
/**
 *
 */
Panel* MainFrameWindow::initialiseRhsPanel()
{
	if (!rhsPanel)
	{
		rhsPanel = new Panel( splitterWindow, DEFAULT_ID);

		GridBagSizer* sizer = new GridBagSizer();
		sizer->Add( 5, 5,
		GBPosition( 0, 0),
		GBSpan( 1, 1), EXPAND);

		sizer->Add( logTextCtrl = new LogTextCtrl( rhsPanel, DEFAULT_ID, wxTE_MULTILINE | wxTE_DONTWRAP),
		GBPosition( 1, 1),
		GBSpan( 1, 1), EXPAND);
		sizer->AddGrowableCol( 1);
		sizer->AddGrowableRow( 1);
		logTextCtrl->SetMinSize( Size( 500, 300));

		debugTraceFunction = new WidgetDebugTraceFunction( logTextCtrl);

		sizer->Add( buttonPanel = initialiseButtonPanel(),
		GBPosition( 2, 1),
		GBSpan( 1, 1), SHRINK);
		sizer->AddGrowableRow( 2);

		sizer->Add( 5, 5,
		GBPosition( 2, 2),
		GBSpan( 1, 1), EXPAND);

		rhsPanel->SetSizer( sizer);
		sizer->SetSizeHints( rhsPanel);
	}
	return rhsPanel;
}
/**
 *
 */
Panel* MainFrameWindow::initialiseButtonPanel()
{
	Panel* panel = new Panel( rhsPanel);

	GridBagSizer* sizer = new GridBagSizer();


	sizer->Add( makeButton( panel,
	                        "Start robot",
	                        [this](CommandEvent &anEvent){this->OnStartRobot(anEvent);}),
	            GBPosition( 0, 0),
	            GBSpan( 1, 1), EXPAND);

	sizer->Add( makeButton( panel,
	                        "Stop robot",
	                        [this](CommandEvent &anEvent){this->OnStopRobot(anEvent);}),
	            GBPosition( 0, 1),
	            GBSpan( 1, 1), EXPAND);


	sizer->Add( makeButton( panel,
	                        "Populate part 1",
	                        [this](CommandEvent &anEvent){this->OnPopulatePart1(anEvent);}),
	            GBPosition( 1, 0),
	            GBSpan( 1, 1), EXPAND);
	sizer->Add( makeButton( panel,
	                        "Populate part 2",
	                        [this](CommandEvent &anEvent){this->OnPopulatePart2(anEvent);}),
	            GBPosition( 1, 1),
	            GBSpan( 1, 1), EXPAND);

	sizer->Add( makeButton( panel,
	                        "Unpopulate",
	                        [this](CommandEvent &anEvent){this->OnButton4Clicked(anEvent);}),
	            GBPosition( 1, 2),
	            GBSpan( 1, 1), EXPAND);


	sizer->Add( makeButton( panel,
	                        "Start communicating",
	                        [this](CommandEvent &anEvent){this->OnStartCommunicating(anEvent);}),
	            GBPosition( 2, 0),
	            GBSpan( 1, 1), EXPAND);
	sizer->Add( makeButton( panel,
	                        "Say the words",
	                        [this](CommandEvent &anEvent){this->OnButton6Clicked(anEvent);}),
	            GBPosition( 2, 1),
	            GBSpan( 1, 1), EXPAND);
	sizer->Add( makeButton( panel,
	                        "Stop communicating",
	                        [this](CommandEvent &anEvent){this->OnButton7Clicked(anEvent);}),
	            GBPosition( 2, 2),
	            GBSpan( 1, 1), EXPAND);
	sizer->Add( makeButton( panel,
	                        "Merge Worlds",
	                        [this](CommandEvent &anEvent){this->OnButton8Clicked(anEvent);}),
	            GBPosition( 2, 3),
	            GBSpan( 1, 1), EXPAND);

	panel->SetSizerAndFit( sizer);

	return panel;
}
/**
 *
 */
void MainFrameWindow::OnQuit( CommandEvent& UNUSEDPARAM(anEvent))
{
	Close( true);
}
/**
 *
 */
void MainFrameWindow::OnWidgetDebugTraceFunction( CommandEvent& UNUSEDPARAM(anEvent))
{
	if (debugTraceFunction)
		delete debugTraceFunction;
	debugTraceFunction = new WidgetDebugTraceFunction( logTextCtrl);
}
/**
 *
 */
void MainFrameWindow::OnStdOutDebugTraceFunction( CommandEvent& UNUSEDPARAM(anEvent))
{
	if (debugTraceFunction)
		delete debugTraceFunction;
	debugTraceFunction = new StdOutDebugTraceFunction();

}

/**
 *
 */
void MainFrameWindow::OnAbout( CommandEvent& UNUSEDPARAM(anEvent))
{
	wxMessageBox( WXSTRING( "OOSE/CAR 2014 RobotWorld.\n"), WXSTRING( "About RobotWorld"), wxOK | wxICON_INFORMATION, this);
}
/**
 *
 */
void MainFrameWindow::OnStartRobot( CommandEvent& UNUSEDPARAM(anEvent))//Start Robot
{
	RobotWorld::getRobotWorld().startActing();
}
/**
 *
 */
void MainFrameWindow::OnStopRobot( CommandEvent& UNUSEDPARAM(anEvent))//Stop Robot
{
	RobotWorld::getRobotWorld().stopActing();
}
/**
 *
 */
void MainFrameWindow::OnPopulatePart1( CommandEvent& UNUSEDPARAM(anEvent))//Populate part1
{
	Logger::log( __PRETTY_FUNCTION__);

	robotWorldCanvas->populatePart1();
}
/**
 *
 */
void MainFrameWindow::OnPopulatePart2( CommandEvent& UNUSEDPARAM(anEvent))//Populate part2
{
	Logger::log( __PRETTY_FUNCTION__);

	robotWorldCanvas->populatePart2();
}
/**
 *
 */
void MainFrameWindow::OnButton4Clicked( CommandEvent& UNUSEDPARAM(anEvent))//Unpopulate
{
	Logger::log( __PRETTY_FUNCTION__);

	robotWorldCanvas->unpopulate();
}
/**
 *
 */
void MainFrameWindow::OnStartCommunicating( CommandEvent& UNUSEDPARAM(anEvent))//Start communicating
{
	Logger::log( __PRETTY_FUNCTION__);

	RobotPtr robot = RobotWorld::getRobotWorld().getRobot();
	if (robot)
	{
		if (MainApplication::isArgGiven( "-conf"))
		{
			Logger::log("Config file given");
			ConfigFile::getInstance().loadFile(MainApplication::getArg( "-conf").value);
		}

		robot->startCommunicating();
		Logger::log("IPaddress: " + ConfigFile::getInstance().getIpaddress());
		Logger::log("Local Port: " + ConfigFile::getInstance().getLocalPort());
		Logger::log("Remote Port: " + ConfigFile::getInstance().getRemotePort());
	}
}
/**
 *
 */
void MainFrameWindow::OnButton6Clicked( CommandEvent& UNUSEDPARAM(anEvent))//Say the words
{
	Logger::log( __PRETTY_FUNCTION__);

	RobotPtr robot = RobotWorld::getRobotWorld().getRobot();
	if (robot)
	{

		if (MainApplication::isArgGiven( "-conf"))
		{
			Logger::log("Config file given");
			ConfigFile::getInstance().loadFile(MainApplication::getArg( "-conf").value);
		}

		MessageASIO::Client c1ient( CommunicationService::getCommunicationService().getIOService(), ConfigFile::getInstance().getIpaddress(), ConfigFile::getInstance().getRemotePort(), robot);
		MessageASIO::Message message( 1, "Hello world!");
		Logger::log("hello world");
		c1ient.dispatchMessage( message);
	}
	else
	{
		Logger::log("CANT START CLIENT");
	}
}
/**
 *
 */
void MainFrameWindow::OnButton7Clicked( CommandEvent& UNUSEDPARAM(anEvent))//Stop communicating
{
	Logger::log( __PRETTY_FUNCTION__);

	RobotPtr thijs = RobotWorld::getRobotWorld().getRobot();
	if (thijs)
	{
		thijs->stopCommunicating();
	}
}

void MainFrameWindow::OnButton8Clicked( CommandEvent& UNUSEDPARAM(anEvent))//Merge worlds
{
	Logger::log( __PRETTY_FUNCTION__);

	RobotPtr robot = RobotWorld::getRobotWorld().getRobot();
	if(robot){
		std::string remoteIpAdres = ConfigFile::getInstance().getIpaddress();
		std::string remotePort = ConfigFile::getInstance().getRemotePort();
		Logger::log("Button8 " + remoteIpAdres + " " + remotePort);

		MessageASIO::Client c1ient( CommunicationService::getCommunicationService().getIOService(), remoteIpAdres, remotePort, robot);

		for(RobotPtr robot : RobotWorld::getRobotWorld().getRobots())
		{
			if(robot->original)
			{
				MessageASIO::Message message( 1, "robot");
				c1ient.dispatchMessage( message);
				MessageASIO::Message message2( 1, "Name:" + to_string(robot->getName()));
				c1ient.dispatchMessage( message2);
				MessageASIO::Message message3( 1, "Pos_x:" + std::to_string(robot->getPosition().x));
				c1ient.dispatchMessage( message3);
				MessageASIO::Message message4( 1, "Pos_y:" + std::to_string(robot->getPosition().y));
				c1ient.dispatchMessage( message4);
				MessageASIO::Message message5( 1, "Id:" + std::to_string(robot->getRobotId()));
				c1ient.dispatchMessage( message5);
				MessageASIO::Message message6 (1, "end");
				c1ient.dispatchMessage( message6);
			}
		}
		Logger::log("Sending Robots...");
		for(WallPtr wall : RobotWorld::getRobotWorld().getWalls())
		{
			if(wall->isOriginal())
			{
				MessageASIO::Message message( 1, "wall");
				c1ient.dispatchMessage( message);
				MessageASIO::Message message2( 1, "pos_1x:" + std::to_string(wall->getPoint1().x));
				c1ient.dispatchMessage( message2);
				MessageASIO::Message message3( 1, "pos_1y:" + std::to_string(wall->getPoint1().y));
				c1ient.dispatchMessage( message3);
				MessageASIO::Message message4( 1, "pos_2x:" + std::to_string(wall->getPoint2().x));
				c1ient.dispatchMessage( message4);
				MessageASIO::Message message5( 1, "pos_2y:" + std::to_string(wall->getPoint2().y));
				c1ient.dispatchMessage( message5);
				MessageASIO::Message message6 (1, "end");
				c1ient.dispatchMessage( message6);
			}
		}
		Logger::log("Sending Walls...");
		for(GoalPtr goal : RobotWorld::getRobotWorld().getGoals())
		{
			if(goal->isOriginal())
			{
				MessageASIO::Message message( 1, "goal");
				c1ient.dispatchMessage( message);
				MessageASIO::Message message2( 1, "Name:" + goal->getName());
				c1ient.dispatchMessage( message2);
				MessageASIO::Message message3( 1, "Pos_y:" + std::to_string(goal->getPosition().x));
				c1ient.dispatchMessage( message3);
				MessageASIO::Message message4( 1, "Pos_x:" + std::to_string(goal->getPosition().y));
				c1ient.dispatchMessage( message4);
				MessageASIO::Message message6 (1, "end");
				c1ient.dispatchMessage( message6);
			}
		}
		Logger::log("Sending goals...");
	}
}
