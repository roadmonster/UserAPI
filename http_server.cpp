#include "user_service.cpp"
#include "user_controller.cpp"
class UserHttpServer {
public:
    UserHttpServer(UserService& userService, const std::string& url) : userService(userService), listener(url) {
        listener.support(methods::POST, std::bind(&UserHttpServer::handleUserRequest, this, std::placeholders::_1));
        listener.support(methods::GET, std::bind(&UserHttpServer::handleRead, this, std::placeholders::_1));
        listener.support(methods::PUT, std::bind(&UserHttpServer::handleUpdate, this, std::placeholders::_1));
        listener.support(methods::DEL, std::bind(&UserHttpServer::handleDelete, this, std::placeholders::_1));
        
    }

    void start() {
    listener.open().wait();
}

    void stop() {
        listener.close().wait();
    }
private:
    void handleUserRequest(http_request request) {
        auto relativePath = uri::decode(request.relative_uri().path());

        if (relativePath == "/users") {
            if (request.headers().content_type() == "application/json") {
                userController.handleCreate(request);
            } else {
                request.reply(status_codes::UnsupportedMediaType, "Unsupported content type");
            }
        } else if (relativePath == "/users/authenticate") {
            if (request.headers().content_type() == "application/json") {
                userController.handleAuthenticate(request);
            } else {
                request.reply(status_codes::UnsupportedMediaType, "Unsupported content type");
            }
        } else {
            request.reply(status_codes::NotFound, "Invalid endpoint");
        }
    }

    void handleRead(http_request request) {
        userController.handleRead(request);
    }

    void handleUpdate(http_request request) {
        userController.handleUpdate(request);
    }

    void handleDelete(http_request request) {
        userController.handleDelete(request);
    }

    UserService& userService;
    UserController userController{userService};
    http_listener listener;
};



