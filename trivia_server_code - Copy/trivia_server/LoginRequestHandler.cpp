#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(LoginManager manager, RequestHandlerFactory* factory) : m_loginManager(manager), m_handlerFactory(factory)
{

}

LoginRequestHandler::~LoginRequestHandler()
{
}


bool LoginRequestHandler::isRequestRelevant(Request request)
{
    return request.id == LOGIN_REQUEST || request.id == SIGNUP_REQUEST;
}

RequestResult LoginRequestHandler::handleRequest(Request request)
{
    try {
        SignupResponse resSignUp;
        LoginResponse resLogin;
        bool factor;
        if (request.id == LOGIN_REQUEST) {
            LoginRequest req = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer.data(), request.buffer.size() + 5);
            factor = m_loginManager.login(req.username, req.password);
            if (factor) {
                resLogin = { LOGIN_SUCCESS };
            }            
            else
                resLogin = { REQUEST_ERROR };
            return { JsonResponsePacketSerializer::serializeResponse(resLogin), nullptr };
        }
        if (request.id == SIGNUP_REQUEST) {
            SignupRequest req = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer.data(), request.buffer.size());
            factor = m_loginManager.signup(req.username, req.password, req.email);
            if (factor)
                resSignUp = { SIGNUP_SUCCESS };
            else
                resSignUp = { REQUEST_ERROR };
            return { JsonResponsePacketSerializer::serializeResponse(resSignUp), nullptr };

        }
    }
    
    catch (nlohmann::json::exception& e)
    {
        ErrorResponse res = { "Invalid json in request" };
        return { JsonResponsePacketSerializer::serializeResponse(res), m_handlerFactory->createLoginRequestHandler() };
    }
    catch (std::exception& e)
    {
        ErrorResponse res = { e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
    }
    
    ErrorResponse res = { "Invalid request" };
    return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
}

RequestResult LoginRequestHandler::signup(Request r)
{
    return RequestResult();
}

RequestResult LoginRequestHandler::login(Request r)
{
    return RequestResult();
}

