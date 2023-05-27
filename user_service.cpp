// User service interface
 #pragma once
 #include "user.h"
class UserService {
public:
    virtual User createUser(const std::string& username, const std::string& password) = 0;
    virtual User getUser(const std::string& id) = 0;
    virtual User updateUser(const std::string& id, const std::string& username, const std::string& password) = 0;
    virtual void deleteUser(const std::string& id) = 0;
    virtual bool authenticate(const std::string& username, const std::string& password) = 0;
};