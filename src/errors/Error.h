//
// Created by ilias on 17/06/2021.
//

#ifndef BOMBERMAN_ERROR_H
#define BOMBERMAN_ERROR_H

#include <string>
#include <exception>
#include <stdexcept>

namespace err {
    class Error : public std::exception {
    public:
        explicit Error(const std::string &message, const std::string &component = "Unknown");
        ~Error() override = default;

    public:
        std::string getComponent() const;
        const char *what() const noexcept override;

    protected:
        std::runtime_error message;
        std::runtime_error component;
        // using std::runtime_error instead of std::string because of this:
        // https://web.archive.org/web/20160730024945/https://www.securecoding.cert.org/confluence/display/cplusplus/ERR60-CPP.+Exception+objects+must+be+nothrow+copy+constructible
    };

    class MapGeneration : public Error {
    public:
        explicit MapGeneration(const std::string &message, const std::string &component = "MapGeneration") : Error(message, component) {}
        ~MapGeneration() override = default;
    };

    class AssetLoading : public Error {
    public:
        explicit AssetLoading(const std::string &message, const std::string &component = "AssetLoading") : Error(message, component) {}
        ~AssetLoading() override = default;
    };

    class Player : public Error {
    public:
        explicit Player(const std::string &message, const std::string &component = "Player") : Error(message, component) {}
        ~Player() override = default;
    };

    class Core: public Error {
    public:
        explicit Core(const std::string &message, const std::string &component = "Core") : Error(message, component) {}
        ~Core() override = default;
    };
}


#endif //BOMBERMAN_ERROR_H
