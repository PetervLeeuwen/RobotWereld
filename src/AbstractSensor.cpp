#include "AbstractSensor.hpp"
#include "AbstractAgent.hpp"
#include "Logger.hpp"

/**
 *
 */
AbstractSensor::AbstractSensor() :
				agent( NULL),
				running( false)
{
}
/**
 *
 */
AbstractSensor::AbstractSensor( AbstractAgent* anAgent) :
				agent( anAgent),
				running( false)
{

}
/**
 *
 */
AbstractSensor::~AbstractSensor()
{
}
/**
 *
 */
void AbstractSensor::setOn( unsigned long aSleepTime /*= 100*/)
{
	std::unique_lock< std::recursive_mutex > lock( sensorMutex);

	Logger::log( __PRETTY_FUNCTION__);

	if (running == false)
	{
		running = true;
		std::thread sensorThread( [this, aSleepTime]
		{	run(aSleepTime); });
		std::thread consumeThread( [this, aSleepTime]
		{	consume(); });
		sensorThread.swap( sensorThread);
	}
}
/**
 *
 */
void AbstractSensor::setOff()
{
	std::unique_lock< std::recursive_mutex > lock( sensorMutex);

	running = false;
	sensorThread.interrupt();
	sensorThread.join();
	consumeThread.join();
}
/**
 *
 */
void AbstractSensor::sendPercept( std::shared_ptr< AbstractPercept > anAbstractPercept)
{
	Logger::log("Added a percept");
	agent->addPercept( anAbstractPercept);
}
/**
 *
 */
std::shared_ptr< AbstractPercept > AbstractSensor::removePercept()
{
	return agent->removePercept();
}
/**
 *
 */
void AbstractSensor::run( unsigned long aSleepTime)
{
	try
	{
		while (running == true)
		{
			std::shared_ptr< AbstractStimulus > currentStimulus = getStimulus();
			std::shared_ptr< AbstractPercept > currentPercept = getPerceptFor(currentStimulus);
			sendPercept( currentPercept);
			std::this_thread::sleep_for( std::chrono::milliseconds( aSleepTime));

			// this should be either the last call in the loop or
			// part of the while.
			if (sensorThread.interruption_requested() || running == false)
			{
				break;
			}
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
}
/**
 *
 */
void AbstractSensor::consume()
{
	while (running)
	{
		std::shared_ptr< AbstractPercept > percept = removePercept();
		Logger::log("Consumed a percept");
	}
	Logger::log("stopped with comsuming sensors");
}

void AbstractSensor::attachAgent( AbstractAgent* anAgent)
{
	agent = anAgent;
}
/**
 *
 */
void AbstractSensor::detachAgent()
{
	agent = NULL;
}
/**
 *
 */
std::string AbstractSensor::asString() const
{
	return "AbstractSensor";
}
/**
 *
 */
std::string AbstractSensor::asDebugString() const
{
	return asString();
}
