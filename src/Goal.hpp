#ifndef GOAL_HPP_
#define GOAL_HPP_

#include "Config.hpp"
#include "Widgets.hpp"
#include "WayPoint.hpp"

class Goal;
typedef std::shared_ptr<Goal> GoalPtr;

class Goal : public WayPoint
{
	public:
		/**
		 *
		 */
		Goal( const std::string& aName);
		/**
		 *
		 */
		Goal(	const std::string& aName,
				const Point& aPosition,
				const bool& aOriginal = true);
		/**
		 *
		 */
		virtual ~Goal();
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
		/**
		 *
		 */
		bool isOriginal(){return original;};
		//@}
	protected:

	private:
		bool original;

};

#endif // GOAL_HPP_
