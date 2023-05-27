#include "http_server.cpp"
#include "default_user_service.cpp"
#include <iostream>

int main() {
    InMemoryUserRepository userRepository;
    DefaultUserService userService(userRepository);
    UserHttpServer httpServer(userService, "http://localhost:8080/users");
    httpServer.start();
    std::cout << "Server started" << std::endl;
    std::cin.get();
    httpServer.stop();
    std::cout << "Server stopped" << std::endl;
    return 0;
}