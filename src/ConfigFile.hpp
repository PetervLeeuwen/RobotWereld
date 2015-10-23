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
	ConfigFile();
	ConfigFile(std::string file);
	virtual ~ConfigFile();

	void loadFile();

	const std::string& getIpaddress() const;

	const std::string& getPort() const;

private:
	std::string file;
	std::string ipaddress;
	std::string port;
};

#endif /* SRC_CONFIGFILE_HPP_ */
