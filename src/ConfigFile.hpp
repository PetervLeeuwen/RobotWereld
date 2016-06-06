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
	virtual ~ConfigFile();


	static ConfigFile& getInstance();

	const std::string getIpaddress();

	const std::string getRemotePort();

	const std::string getLocalPort();

	void loadFile(std::string aFile);
private:
	ConfigFile();

	void loadFile();


	std::string file = "config.txt";
	std::string ipaddress;
	std::string localPort;
	std::string remotePort;

	static ConfigFile instance;
};

#endif /* SRC_CONFIGFILE_HPP_ */
