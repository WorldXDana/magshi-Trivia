#pragma once
#include <vector>
#include <string>
#include <map>
#include <WinSock2.h>
#include <chrono>
#include <algorithm>
#include <string>

class messageInfo {
public:
	int code;
	int dataLength;
	std::vector<char> data;
};

class helper
{
public:
	static void sendData(const SOCKET sc, const std::string message);
	static const messageInfo reciveInformationFromSocket(const SOCKET currSocket);

};

#ifdef _DEBUG // vs add this define in debug mode
#include <stdio.h>
// Q: why do we need traces ?
// A: traces are a nice and easy way to detect bugs without even debugging
// or to understand what happened in case we miss the bug in the first time
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
// for convenient reasons we did the traces in stdout
// at general we would do this in the error stream like that
// #define TRACE(msg, ...) fprintf(stderr, msg "\n", __VA_ARGS__);

//#else // we want nothing to be printed in release version
//#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
//#define TRACE(msg, ...) // do nothing
#endif