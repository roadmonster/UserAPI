#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(const std::string& id, const std::string& username, const std::string& password);

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getId() const;
    void setPassword(const std::string& password);
    void setUsername(const std::string& username);
private:
    std::string m_username;
    std::string m_password;
    std::string m_id;

};

#endif // USER_H
