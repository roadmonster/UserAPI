#include "user.h"

User::User(const std::string& id, const std::string& username, const std::string& password)
    : m_username(username), m_password(password), m_id(id) {}

std::string User::getUsername() const {
    return m_username;
}

std::string User::getPassword() const {
    return m_password;
}

std::string User::getId() const {
    return m_id;
}

void User::setPassword(const std::string& password) {
    m_password = password;
}

void User::setUsername(const std::string& username) {
    m_username = username;
}