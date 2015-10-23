/*
 * ConfigFile.hpp
 *
 *  Created on: 22 okt. 2015
 *      Author: Peter
 */

#include <vector>
#include <iostream>
#include <algorithm>

#ifndef SRC_CONFIGFILE_HPP_
#define SRC_CONFIGFILE_HPP_

class ConfigFile {

public:
	const std::string& getIpaddress();

	const std::string& getPort();

	static ConfigFile& getInstance();

private:
	ConfigFile();
	virtual ~ConfigFile();

	void loadFile();

	std::string file = "config.txt";
	std::string ipaddress;
	std::string port;

	static ConfigFile instance;
};

#endif /* SRC_CONFIGFILE_HPP_ */
