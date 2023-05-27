#include <iostream>
#include <sstream>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "user_service.cpp"
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class UserController {
public:
    UserController(UserService& userService) : userService(userService) {}

    void handleCreate(http_request request) {
        json::value response;
        try {
            auto body = request.extract_json().get();
            auto username = body.at("username").as_string();
            auto password = body.at("password").as_string();
            auto user = userService.createUser(username, password);
            response["id"] = json::value::string(user.getId());
            response["username"] = json::value::string(user.getUsername());
            request.reply(status_codes::Created, response);
        } catch (const json::json_exception& e) {
            response["error"] = json::value::string(e.what());
            request.reply(status_codes::BadRequest, response);
        }
    }

    void handleRead(http_request request) {
        json::value response;
        try {
            auto id = request.relative_uri().path();
            id.erase(0, 1);
            auto user = userService.getUser(id);
            response["id"] = json::value::string(user.getId());
            response["username"] = json::value::string(user.getUsername());
            request.reply(status_codes::OK, response);
        } catch (const std::out_of_range& e) {
            response["error"] = json::value::string(e.what());
            request.reply(status_codes::NotFound, response);
        }
    }

    void handleUpdate(http_request request) {
        json::value response;
        try {
            auto id = request.relative_uri().path();
            id.erase(0, 1);
            auto body = request.extract_json().get();
            auto username = body.at("username").as_string();
            auto password = body.at("password").as_string();
            auto user = userService.updateUser(id, username, password);
            response["id"] = json::value::string(user.getId());
            response["username"] = json::value::string(user.getUsername());
            request.reply(status_codes::OK, response);
        } catch (const std::out_of_range& e) {
            response["error"] = json::value::string(e.what());
            request.reply(status_codes::NotFound, response);
        } catch (const json::json_exception& e) {
            response["error"] = json::value::string(e.what());
            request.reply(status_codes::BadRequest, response);
        }
    }

    void handleDelete(http_request request) {
        json::value response;
        try {
            auto id = request.relative_uri().path();
            id.erase(0, 1);
            userService.deleteUser(id);
            request.reply(status_codes::NoContent);
        } catch (const std::out_of_range& e) {
            response["error"] = json::value::string(e.what());
            request.reply(status_codes::NotFound, response);
        }
    }

    void handleAuthenticate(http_request request) {
        json::value response;
        try {
            auto body = request.extract_json().get();
            auto username = body.at("username").as_string();
            auto password = body.at("password").as_string();
            bool authenticated = userService.authenticate(username, password);
            response["authenticated"] = json::value::boolean(authenticated);
            request.reply(status_codes::OK, response);
        } catch (const json::json_exception& e) {
            response["error"] = json::value::string(e.what());
            request.reply(status_codes::BadRequest, response);
        }
    }
private:
    UserService& userService;
};