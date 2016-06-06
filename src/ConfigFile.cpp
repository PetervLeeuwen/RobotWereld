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
//	loadFile();
}

void ConfigFile::loadFile(std::string aFile)
{
	Logger::log("New config file " + aFile);
	file = aFile;
	loadFile();
}

void ConfigFile::loadFile() {
	std::ifstream ifStream(file);
	if (ifStream.is_open()) {
		std::getline(ifStream, ipaddress);
		std::getline(ifStream, localPort);
		std::getline(ifStream, remotePort);
		ifStream.close();
		Logger::log("ConfigFile IPaddress: " + ipaddress);
		Logger::log("ConfigFile Port: " + localPort);
		Logger::log("ConfigFile Port: " + remotePort);
	}
	else
	{
		Logger::log("Unable to open file");
	}
	ifStream.close();
}

ConfigFile& ConfigFile::getInstance(){
	static ConfigFile instance;
	return instance;
}

const std::string ConfigFile::getLocalPort(){
	return localPort;
}

const std::string ConfigFile::getRemotePort(){
	return remotePort;
}

const std::string ConfigFile::getIpaddress(){
	return ipaddress;
}

ConfigFile::~ConfigFile() {
// TODO Auto-generated destructor stub
}

