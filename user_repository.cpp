#include <unordered_map>
#include <vector>
#include "user.h"

// User repository interface
class UserRepository {
public:
    virtual User create(const User& user) = 0;
    virtual User read(const std::string& id) = 0;
    virtual User update(const User& user) = 0;
    virtual void remove(const std::string& id) = 0;
    virtual std::vector<User> getAll() = 0;
};

// User repository implementation using an unordered_map
class InMemoryUserRepository : public UserRepository {
public:
    User create(const User& user) override {
        users.emplace(user.getId(), user);
        return user;
    }


    User read(const std::string& id) override {
        return users.at(id);
    }

    User update(const User& user) override {
        users.emplace(user.getId(), user);
        return user;
    }

    void remove(const std::string& id) override {
        users.erase(id);
    }

    std::vector<User> getAll() override {
        std::vector<User> myUsers;
        for (const auto& kv: users) {
            myUsers.push_back(kv.second);
        }
        return myUsers;
    }


private:
    std::unordered_map<std::string, User> users;
};
