#include "RobotWorld.hpp"
#include "Logger.hpp"
#include "Robot.hpp"
#include "WayPoint.hpp"
#include "Goal.hpp"
#include "Wall.hpp"
#include <algorithm>

/**
 *
 */
/* static */RobotWorld& RobotWorld::RobotWorld::getRobotWorld()
{
	static RobotWorld robotWorld;
	return robotWorld;
}
/**
 *
 */
RobotPtr RobotWorld::newRobot(	const std::string& aName,
								const Point& aPosition /*= Point(-1,-1)*/,
								bool aNotifyObservers /*= true*/)
{
	RobotPtr robot( new Robot( aName, aPosition));
	robots.push_back( robot);
	if (aNotifyObservers == true)
	{
		notifyObservers();
	}
	return robot;

}
/**
 *
 */
WayPointPtr RobotWorld::newWayPoint(	const std::string& aName,
									const Point& aPosition /*= Point(-1,-1)*/,
									bool aNotifyObservers /*= true*/)
{
	WayPointPtr wayPoint(new WayPoint( aName, aPosition));
	wayPoints.push_back( wayPoint);
	if (aNotifyObservers == true)
	{
		notifyObservers();
	}
	return wayPoint;

}
/**
 *
 */
GoalPtr RobotWorld::newGoal(	const std::string& aName,
							const Point& aPosition /*= Point(-1,-1)*/,
							bool aNotifyObservers /*= true*/)
{
	GoalPtr goal( new Goal( aName, aPosition));
	goals.push_back( goal);
	if (aNotifyObservers == true)
	{
		notifyObservers();
	}
	return goal;
}
/**
 *
 */
WallPtr RobotWorld::newWall(const Point& aPoint1,
							const Point& aPoint2,
							bool aNotifyObservers /*= true*/)
{
	WallPtr wall( new Wall( aPoint1, aPoint2));
	walls.push_back( wall);
	if (aNotifyObservers == true)
	{
		notifyObservers();
	}
	return wall;
}
/**
 *
 */
void RobotWorld::deleteRobot( 	RobotPtr aRobot,
								bool aNotifyObservers /*= true*/)
{
	auto i = std::find_if( robots.begin(), robots.end(), [aRobot](RobotPtr r)
	{
		return aRobot->getName() == r->getName();
	});
	if (i != robots.end())
	{
		robots.erase( i);
		if (aNotifyObservers == true)
		{
			notifyObservers();
		}
	}
}
/**
 *
 */
void RobotWorld::deleteWayPoint( 	WayPointPtr aWayPoint,
									bool aNotifyObservers /*= true*/)
{
	auto i = std::find_if( wayPoints.begin(), wayPoints.end(), [aWayPoint]( WayPointPtr w)
	{
		return aWayPoint->getName() == w->getName();
	});
	if (i != wayPoints.end())
	{
		wayPoints.erase( i);
		if (aNotifyObservers == true)
		{
			notifyObservers();
		}
	}
}
/**
 *
 */
void RobotWorld::deleteGoal( 	GoalPtr aGoal,
								bool aNotifyObservers /*= true*/)
{
	auto i = std::find_if( goals.begin(), goals.end(), [aGoal]( GoalPtr g)
	{
		return aGoal->getName() == g->getName();
	});
	if (i != goals.end())
	{
		goals.erase( i);

		if (aNotifyObservers == true)
		{
			notifyObservers();
		}
	}
}
/**
 *
 */
void RobotWorld::deleteWall( 	WallPtr aWall,
								bool aNotifyObservers /*= true*/)
{
	auto i = std::find_if( walls.begin(), walls.end(), [aWall]( WallPtr w)
	{
		return
		aWall->getPoint1() == w->getPoint1() &&
		aWall->getPoint2() == w->getPoint2();
	});
	if (i != walls.end())
	{
		walls.erase( i);

		if (aNotifyObservers == true)
		{
			notifyObservers();
		}
	}
}
/**
 *
 */
RobotPtr RobotWorld::getRobotByName( const std::string& aName) const
{
	for (RobotPtr robot : robots)
	{
		if (robot->getName() == aName)
		{
			return robot;
		}
	}
	return NULL;
}
/**
 *
 */
WayPointPtr RobotWorld::getWayPointByName( const std::string& aName) const
{
	for (WayPointPtr wayPoint : wayPoints)
	{
		if (wayPoint->getName() == aName)
		{
			return wayPoint;
		}
	}
	return NULL;
}
/**
 *
 */
GoalPtr RobotWorld::getGoalByName( const std::string& aName) const
{
	for (GoalPtr goal : goals)
	{
		if (goal->getName() == aName)
		{
			return goal;
		}
	}
	return NULL;
}

/**
 *
 */
const std::vector< RobotPtr >& RobotWorld::getRobots() const
{
	return robots;
}
/**
 *
 */
const std::vector< WayPointPtr >& RobotWorld::getWayPoints() const
{
	return wayPoints;
}
/**
 *
 */
const std::vector< GoalPtr >& RobotWorld::getGoals() const
{
	return goals;
}
/**
 *
 */
const std::vector< WallPtr >& RobotWorld::getWalls() const
{
	return walls;
}
/**
 *
 */
void RobotWorld::populate( int aNumberOfWalls /*= 2*/)
{
	RobotWorld::getRobotWorld().newRobot( "Peter", Point( 75, 75),false);
	RobotWorld::getRobotWorld().newRobot( "Thomas", Point( 450, 75),false);

	static Point coordinates[] = { Point( 100, 240), Point( 400, 240),
	Point( 0, 340),Point( 180, 320),
	Point( 310, 340),Point( 500, 340)};

	for (int i = 0; i < 2 * aNumberOfWalls; i += 2)
	{
		RobotWorld::getRobotWorld().newWall( coordinates[i], coordinates[i + 1],false);
	}

	RobotWorld::getRobotWorld().newGoal( "Leon", Point( 250, 450),false);

	notifyObservers();
}
/**
 *
 */
void RobotWorld::unpopulate( bool aNotifyObservers /*= true*/)
{
	robots.clear();
	wayPoints.clear();
	goals.clear();
	walls.clear();

	if (aNotifyObservers)
	{
		notifyObservers();
	}
}
/**
 *
 */
void RobotWorld::startActing()
{
	for(auto robot : robots)
	{
		if(robot.get()->original)
		{
			Logger::log( "Calculate path for: " + robot.get()->getName());
			robot->startActing();
			robot->calculatePath();
		}
	}
	for(auto robot : robots)
	{
		if(robot.get()->original)
		{
			Logger::log( "Starting robot: " + robot.get()->getName());
			robot->startMoving();
		}
	}
}
/**
 *
 */
void RobotWorld::stopActing()
{
	for(auto robot : robots)
	{
		if(robot.get()->original)
		{
			Logger::log( "Attempting to stop " + robot.get()->getName());
			robot->stopActing();
		}
	}
}
/**
 *
 */
RobotWorld::RobotWorld()
{
}
/**
 *
 */
RobotWorld::~RobotWorld()
{
	// No notification while I am in the destruction mode!
	disableNotification();
	unpopulate();
}

void RobotWorld::sendRobotData()
{

}

void RobotWorld::receiveRobotData(std::vector<RobotPtr> aRobot,
		std::vector<WayPointPtr> aWayPoint, std::vector<GoalPtr> aGoal,
		std::vector<WallPtr> aWall)
{
	for(auto robot : aRobot)
	{
		robot.get()->original = false;
		robots.push_back(robot);
	}
	for(auto wayPoint : aWayPoint)
	{
		wayPoints.push_back(wayPoint);
	}
	for(auto goal : aGoal)
	{
		goal.get()->original = false;
		goals.push_back(goal);
	}
	for(auto wall : aWall)
	{
		walls.push_back(wall);
	}
}

GoalPtr RobotWorld::getGoal() const
{
	for(GoalPtr goal : goals)
	{
		if(goal.get()->original){
			return goal;
		}
	}
	return nullptr;
}

RobotPtr RobotWorld::getRobot() const
{
	for(RobotPtr robot : robots)
	{
		if(robot.get()->original){
			return robot;
		}
	}
	return nullptr;
}

void RobotWorld::updateRobotPosition(ObjectId id,Point location)
{
	for(RobotPtr robot : robots)
	{
		if(robot.get()->getRobotId() == id){
			robot.get()->setPosition(location,true);
		}
	}
}

void RobotWorld::sendUpdateRobotPosition()
{
	for(RobotPtr robot : robots)
	{
		if(robot.get()->original){
			//updateRobotPosition(robot.get()->getRobotId(),robot.get()->getPosition());
		}
	}
}
