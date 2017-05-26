/*
 * File: utils.h
 * Author: Vladislav Tananaev
 *
 */

#ifndef MRPT_BRIDGE_UTILS_H
#define MRPT_BRIDGE_UTILS_H

#include <ros/console.h>
#include <mrpt/system/datetime.h>
#include <mrpt/version.h>
#if MRPT_VERSION>=0x150
#	include <mrpt/utils/COutputLogger.h>
#endif
#include <log4cxx/logger.h>

namespace mrpt_bridge {

#if MRPT_VERSION>=0x150
	/**
   * @brief function that converts ROS verbosity level log4cxx::Level to MRPT equivalent mrpt::utils::VerbosityLevel
   */
	inline mrpt::utils::VerbosityLevel rosLoggerLvlToMRPTLoggerLvl(log4cxx::LevelPtr lvl){
		using namespace mrpt::utils;
		using namespace log4cxx;

		// determine on the corresponding VerbosityLevel
		VerbosityLevel mrpt_lvl;

		if (lvl == Level::getFatal() ||
				lvl == Level::getError())
	  {
	    mrpt_lvl = LVL_ERROR;
	  }
	  else if (lvl == Level::getWarn())
	  {
	    mrpt_lvl = LVL_WARN;
	  }
	  else if (lvl == Level::getInfo())
	  {
	    mrpt_lvl = LVL_INFO;
	  }
	  else if (lvl == Level::getDebug())
	  {
	    mrpt_lvl = LVL_DEBUG;
	  }
	  else
	  {
			THROW_EXCEPTION("Unknown log4cxx::Level is given.");
		}

		return mrpt_lvl;

	} // end of rosLoggerLvlToMRPTLoggerLvl

	/**
   * @brief callback that is called by MRPT mrpt::utils::COuputLogger to redirect log messages to ROS logger.
   * 	This function has to be inline, otherwise option log4j.logger.ros.package_name will be taken from mrpt_bridge
   *  instead of the package from which macro is actually called.
   */
	inline void mrptToROSLoggerCallback(const std::string &msg, const mrpt::utils::VerbosityLevel level, const std::string &loggerName, const mrpt::system::TTimeStamp timestamp, void *userParam) {

		// Remove trailing \n if present
		std::string tmsg = msg;
		if (!tmsg.empty() && tmsg.compare(tmsg.length()-1, tmsg.length(), "\n")==0){
			tmsg.erase(tmsg.end()-1);
		}

		if (level == mrpt::utils::LVL_DEBUG){
	    ROS_DEBUG("%s", tmsg.c_str());
	  } else if (level == mrpt::utils::LVL_INFO) {
	    ROS_INFO("%s", tmsg.c_str());
	  } else if (level == mrpt::utils::LVL_WARN) {
	    ROS_WARN("%s", tmsg.c_str());
	  } else if (level == mrpt::utils::LVL_ERROR) {
	    ROS_ERROR("%s", tmsg.c_str());
	  }
	}

#endif

} //namespace mrpt_bridge

#endif //MRPT_BRIDGE_UTILS_H
