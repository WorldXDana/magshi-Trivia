#include "helper.h"


void helper::sendData(const SOCKET sc, const std::string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

const messageInfo helper::reciveInformationFromSocket(const SOCKET currSocket)
{
	messageInfo info;
	std::string m = "Error while validating message length.\n";
	char codeBuff[1];
	char lengthBuff[4];

	
	if (sizeof(currSocket) <= 0) { 
		info.code = 999;
		std::copy(m.begin(), m.end(),info.data.begin());
		info.dataLength = info.data.size();
		return info;
	}
	
	if (recv(currSocket, codeBuff, 1, 0) == SOCKET_ERROR) {
		std::string s = "Error while recieving from socket: " + std::to_string(currSocket);
		throw std::exception(s.c_str());
	}
	int code = static_cast<int>(static_cast<unsigned char>(codeBuff[0]));
	info.code = code;
	recv(currSocket, lengthBuff, 4, 0);
	int dataLength = lengthBuff[3];

	for (int i = 2; i >= 0; i--) {
		dataLength |= lengthBuff[i] << ((3 - i) * 8);
	}
	info.dataLength = dataLength;
	
	char* dataBuff = new char[dataLength];
	recv(currSocket, dataBuff, dataLength, 0);
	dataBuff[dataLength - 1] = 0;
	std::vector<char> temp(dataBuff, dataBuff + info.dataLength);
	//temp.erase(std::remove(temp.begin(), temp.end(), ','), temp.end());
	info.data = temp;
	//SOMETHING IS NOT RIGHT HERE FIX IT.
	delete[] dataBuff;

	return info;
}
