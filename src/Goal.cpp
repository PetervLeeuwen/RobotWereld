#include "Goal.hpp"
#include <sstream>
#include "Logger.hpp"
#include "Shape2DUtils.hpp"

/**
 *
 */
Goal::Goal( const std::string& aName) :
				WayPoint( aName),
				original(true)
{
}
/**
 *
 */
Goal::Goal( const std::string& aName,
			const Point& aPosition) :
				WayPoint( aName, aPosition),
				original(true)
{
}
/**
 *
 */
Goal::~Goal()
{
}
/**
 *
 */
std::string Goal::asString() const
{
	std::ostringstream os;

	os << "Goal " << getName() << " at (" << getPosition().x << "," << getPosition().y << ")";

	return os.str();
}
/**
 *
 */
std::string Goal::asDebugString() const
{
	std::ostringstream os;

	os << "Goal:\n";
	os << WayPoint::asDebugString();

	return os.str();
}
