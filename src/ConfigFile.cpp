/*
 * ConfigFile.cpp
 *
 *  Created on: 22 okt. 2015
 *      Author: Peter
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

#include"Logger.hpp"
#include "ConfigFile.hpp"


ConfigFile::ConfigFile(){
}

ConfigFile::ConfigFile(std::string aFile):
	file(aFile)
{
}

void ConfigFile::loadFile() {
	std::ifstream ifStream(file);
	if (ifStream.is_open()) {
		std::getline(ifStream, ipaddress);
		std::getline(ifStream, port);
		ifStream.close();
		Logger::log("IPaddress: " + ipaddress);
		Logger::log("Port: " + port);
	}

	else
		Logger::log("Unable to open file");

	ifStream.close();
}

const std::string& ConfigFile::getPort() const {
	return port;
}

const std::string& ConfigFile::getIpaddress() const {
	return ipaddress;
}

ConfigFile::~ConfigFile() {
// TODO Auto-generated destructor stub
}

