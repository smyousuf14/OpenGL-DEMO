#pragma once

#include<string>
#include<fstream>

static const char* extract_version(const char* full) {
	
	std::string p1 = full;
	static std::string p2;
	p2.clear();
	p2 = p1.substr(
		p1.find_last_of("/\\") + 1,          // from after the slash
		(p1.length() - p1.find_last_of("/\\")) - (p1.length() - (p1.find_last_of(".")) + 1)  // up to last dot
	);
	
	return p2.c_str();
}

static void loginfo(const char* msg) {
	std::ofstream logs;
	logs.open("logsINFO.txt", std::ofstream::app | std::ofstream::out);
	logs << msg;
	logs.close();
}
