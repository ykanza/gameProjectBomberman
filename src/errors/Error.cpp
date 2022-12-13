//
// Created by ilias on 17/06/2021.
//

#include "Error.h"

err::Error::Error(const std::string &message, const std::string &component)
: message(message), component(component){}

std::string err::Error::getComponent() const {
    return this->component.what();
}

const char *err::Error::what() const noexcept {
    return this->message.what();
}