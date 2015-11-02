/*
 * LaserDistanceSensor.hpp
 *
 *  Created on: 15 Oct 2012
 *      Author: jkr
 */

#ifndef LASERDISTANCESENSOR_HPP_
#define LASERDISTANCESENSOR_HPP_

#include "Config.hpp"
#include "Shape2DUtils.hpp"
#include "AbstractSensor.hpp"
#include "Robot.hpp"
#include "RobotWorld.hpp"

class DistanceStimulus : public AbstractStimulus
{
	public:
		DistanceStimulus( unsigned long aDistance, unsigned long aWith) :
						distance( aDistance),
						with(aWith)
		{
		}
		unsigned long distance;
		unsigned long with;
};
// class DistanceStimulus

class DistancePercept : public AbstractPercept
{
	public:
		DistancePercept( const DistanceStimulus& aDistanceStimulus) :
						distance( aDistanceStimulus.distance),
						with(aDistanceStimulus.with),
						triggerd(false)
		{
		}
		DistancePercept( unsigned long aDistance, unsigned long aWith) :
						distance( aDistance),
						with(aWith),
						triggerd(false)
		{
		}
		bool check(Robot *agent);

		unsigned long distance;
		unsigned long with;
		bool triggerd;
};
//	class DistancePercept


class LaserDistanceSensor : public AbstractSensor
{
	public:
		/**
		 *
		 */
		LaserDistanceSensor();
		/**
		 *
		 */
		LaserDistanceSensor( Robot* aRobot, unsigned long aSensorRange, unsigned long aSensorWith);
		/**
		 *
		 */
		virtual ~LaserDistanceSensor();
		/**
		 *
		 */
		virtual std::shared_ptr< AbstractStimulus > getStimulus();
		/**
		 *
		 */
		virtual std::shared_ptr< AbstractPercept > getPerceptFor( std::shared_ptr< AbstractStimulus > anAbstractStimulus);
		/**
		 * @name Debug functions
		 */
		//@{
		/**
		 * Returns a 1-line description of the object
		 */
		virtual std::string asString() const;
		/**
		 * Returns a description of the object with all data of the object usable for debugging
		 */
		virtual std::string asDebugString() const;
		//@}
	protected:
	private:
		unsigned long sensorRange;
		unsigned long sensorWith;

};

#endif /* LASERDISTANCESENSOR_HPP_ */
