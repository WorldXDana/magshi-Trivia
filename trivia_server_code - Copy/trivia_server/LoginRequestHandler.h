#pragma once
#include "IRequestHandler.h"
#include "helper.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	//LoginRequestHandler();
	LoginRequestHandler(LoginManager manager, RequestHandlerFactory* factory);
	~LoginRequestHandler();
	
	virtual bool isRequestRelevant(Request request) override;
	virtual RequestResult handleRequest(Request request) override;
private:
	LoginManager m_loginManager;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult signup(Request r);
	RequestResult login(Request r);
};

