#pragma once
#include <iostream>
#include "helper.h"
#include "requestAndRespond.h"

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(Request request) = 0;
	virtual RequestResult handleRequest(Request request) = 0;
};

