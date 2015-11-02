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

		double angle = Shape2DUtils::getAngle( agent->getFront()) + 0.5 * PI;
		Point agentPos = agent->getPosition();

		if(Shape2DUtils::isPointInRangeOfLine(
					agentPos,
					Point(agentPos.x + std::cos( angle - 0.5 * PI) * distance, agentPos.y + std::sin( angle - 0.5 * PI) * distance),
					robot.get()->getPosition(),
					distance,
					with) && robot.get()->getSpeed() == 10){
			triggerd = true;
		}
	}
	return triggerd;
}
/**
 *
 */
LaserDistanceSensor::LaserDistanceSensor():
		sensorRange(0),
		sensorWith(0)
{
}
/**
 *
 */
LaserDistanceSensor::LaserDistanceSensor(Robot* aRobot, unsigned long aSensorRange,unsigned long aSensorWith):
		AbstractSensor(aRobot),
		sensorRange(aSensorRange),
		sensorWith(aSensorWith)
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
	std::shared_ptr< AbstractStimulus > distanceStimulus( new DistanceStimulus(sensorRange, sensorWith));
	return distanceStimulus;
}
/**
 *
 */
std::shared_ptr< AbstractPercept > LaserDistanceSensor::getPerceptFor( std::shared_ptr< AbstractStimulus > anAbstractStimulus)
{
	DistanceStimulus* distanceStimulus = dynamic_cast< DistanceStimulus* >( anAbstractStimulus.get());
	return std::shared_ptr< AbstractPercept >( new DistancePercept( distanceStimulus->distance, distanceStimulus->with));
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

