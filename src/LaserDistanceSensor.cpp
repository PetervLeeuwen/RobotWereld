/*
 * LaserDistanceSensor.cpp
 *
 *  Created on: 15 Oct 2012
 *      Author: jkr
 */

#include "LaserDistanceSensor.hpp"
#include "Robot.hpp"
#include "Logger.hpp"

/**
 *
 */
bool DistancePercept::check(Robot *agent)
{
	triggerd = false;
	std::vector<RobotPtr> robots = RobotWorld::getRobotWorld().getRobots();
	for(auto robot : robots)
	{
		if(robot.get() == agent)
		{
			continue;
		}
		if(Shape2DUtils::getDistanceBetweenPoints(robot.get()->getPosition(),
					agent->getPosition())
				<= distance)
		{
			triggerd = true;
		}
	}
	return triggerd;
}
/**
 *
 */
LaserDistanceSensor::LaserDistanceSensor()
{
}
/**
 *
 */
LaserDistanceSensor::LaserDistanceSensor(Robot* aRobot):
		AbstractSensor(aRobot)
{
}
/**
 *
 */
LaserDistanceSensor::~LaserDistanceSensor()
{
}
/**
 *
 */
std::shared_ptr< AbstractStimulus > LaserDistanceSensor::getStimulus()
{
	std::shared_ptr< AbstractStimulus > distanceStimulus( new DistanceStimulus( 15));
	return distanceStimulus;
}
/**
 *
 */
std::shared_ptr< AbstractPercept > LaserDistanceSensor::getPerceptFor( std::shared_ptr< AbstractStimulus > anAbstractStimulus)
{
	DistanceStimulus* distanceStimulus = dynamic_cast< DistanceStimulus* >( anAbstractStimulus.get());
	return std::shared_ptr< AbstractPercept >( new DistancePercept( distanceStimulus->distance));
}
/**
 *
 */
std::string LaserDistanceSensor::asString() const
{
	return "LaserDistanceSensor";
}
/**
 *
 */
std::string LaserDistanceSensor::asDebugString() const
{
	return asString();
}

