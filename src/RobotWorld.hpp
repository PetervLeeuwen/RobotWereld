#ifndef ROBOTWORLD_HPP_
#define ROBOTWORLD_HPP_

#include "Config.hpp"
#include "Widgets.hpp"
#include "ModelObject.hpp"
#include "Notifier.hpp"
#include <vector>

class Robot;
typedef std::shared_ptr<Robot> RobotPtr;

class WayPoint;
typedef std::shared_ptr<WayPoint> WayPointPtr;

class Goal;
typedef std::shared_ptr<Goal> GoalPtr;

class Wall;
typedef std::shared_ptr<Wall> WallPtr;

class RobotWorld;
typedef std::shared_ptr<RobotWorld> RobotWorldPtr;

class RobotWorld: public ModelObject
{
public:
	/**
	 *
	 */
	static RobotWorld& getRobotWorld();
	/**
	 *
	 */
	RobotPtr newRobot(const std::string& aName,
			const Point& aPosition,
			bool aNotifyObservers,
			bool original,
			long long aId);
	/**
	 *
	 */
	RobotPtr newRobot(const std::string& aName,
			const Point& aPosition,
			bool aNotifyObservers,
			bool original);
	/**
	 *
	 */
	WayPointPtr newWayPoint(const std::string& aName, const Point& aPosition =
			Point(-1, -1), bool aNotifyObservers = true);
	/**
	 *
	 */
	GoalPtr newGoal(const std::string& aName,
			const Point& aPosition = Point(-1, -1),
			const bool original = true,
			bool aNotifyObservers = true);
	/**
	 *
	 */
	WallPtr newWall(const Point& aPoint1, const Point& aPoint2, const bool aOriginal,
			bool aNotifyObservers = true);
	/**
	 *
	 */
	void deleteRobot(RobotPtr aRobot, bool aNotifyObservers = true);
	/**
	 *
	 */
	void deleteRobot(long long aRobotId);
	/**
	 *
	 */
	void deleteWayPoint(WayPointPtr aWayPoint, bool aNotifyObservers = true);
	/**
	 *
	 */
	void deleteGoal(GoalPtr aGoal, bool aNotifyObservers = true);
	/**
	 *
	 */
	void deleteWall(WallPtr aWall, bool aNotifyObservers = true);
	/**
	 *
	 */
	RobotPtr getRobotByName(const std::string& aName) const;
	/**
	 *
	 */
	WayPointPtr getWayPointByName(const std::string& aName) const;
	/**
	 *
	 */
	GoalPtr getGoalByName(const std::string& aName) const;
	/**
	 *
	 */
	GoalPtr getGoal() const;
	/**
	 *
	 */
	RobotPtr getRobot() const;
	/**
	 *
	 */
	const std::vector<RobotPtr>& getRobots() const;
	/**
	 *
	 */
	const std::vector<WayPointPtr>& getWayPoints() const;
	/**
	 *
	 */
	const std::vector<GoalPtr>& getGoals() const;
	/**
	 *
	 */
	const std::vector<WallPtr>& getWalls() const;
	/**
	 *
	 */
	void populatePart1();
	/**
	 *
	 */
	void populatePart2();
	/**
	 *
	 */
	void unpopulate(bool aNotifyObservers = true);
	/**
	 *
	 */
	void startActing();
	/**
	 *
	 */
	void stopActing();
	/**
	 *
	 */
	void receiveRobotData(std::vector<RobotPtr> aRobot,
			std::vector<WayPointPtr> aWayPoint, std::vector<GoalPtr> aGoal,
			std::vector<WallPtr> aWall);
protected:
	/**
	 *
	 */
	RobotWorld();
	/**
	 *
	 */
	virtual ~RobotWorld();
private:
	std::vector<RobotPtr> robots;
	std::vector<WayPointPtr> wayPoints;
	std::vector<GoalPtr> goals;
	std::vector<WallPtr> walls;
};

#endif // ROBOTWORLD_HPP_
