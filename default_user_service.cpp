#include "user_service.cpp"
#include "user_repository.cpp"
#include "utility.h"
// User service implementation
class DefaultUserService : public UserService {
public:
    DefaultUserService(UserRepository& userRepository) : userRepository(userRepository) {}

    User createUser(const std::string& username, const std::string& password) override {
        std::string passwordHash = sha256(password);
        const std::string id = generateId();
        User user{id, username, passwordHash};
        return userRepository.create(user);
    }

    User getUser(const std::string& id) override {
        return userRepository.read(id);
    }

    User updateUser(const std::string& id, const std::string& username, const std::string& password) override {
        User user = userRepository.read(id);
        if (!username.empty()) {
            user.setUsername(username);
        }
        if (!password.empty()) {
            std::string pwd = sha256(password);
            user.setPassword(pwd);
        }
        return userRepository.update(user);
    }

    void deleteUser(const std::string& id) override {
        userRepository.remove(id);
    }

    bool authenticate(const std::string& username, const std::string& password) override {
        std::vector<User> users = getAllUsers();
        std::string passwordHash = sha256(password);
        for (const auto& user : users) {
            if (user.getUsername() == username && user.getPassword() == passwordHash) {
                return true;
            }
        }
        return false;
    }

private:
    UserRepository& userRepository;
    int lastId = 0;

    std::string generateId() {
        return std::to_string(++lastId);
    }

    std::vector<User> getAllUsers() {
        return userRepository.getAll();
    }
};
