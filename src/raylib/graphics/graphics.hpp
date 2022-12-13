#ifndef BOMBERMAN_GRAPHICS_H
#define BOMBERMAN_GRAPHICS_H

#include <map>
#include <list>
#include "raylib.h"
#include <string>
#include "../../../include/game.h"
namespace RL {
    class Graphics {
    private:
        std::map<std::string, Image> image; //Contient une image en fonction d'un nom
        std::map<std::string, Texture2D> texture2D; //Contient une texture 2D en fonction d'un nom
        Camera cam;

    public:
        Graphics();

        ~Graphics() = default;

    public:
        const Vector3 &getPosition() const;

        const Vector3 &getTarget() const;

        const Vector3 &getUp() const;

        std::map<std::string, Image> &getImage();
        std::map<std::string, Texture2D> &getTexture();
    public:

        /**************************
         *         Image          *
         * ***********************/
        void setImage(std::string name,
                      std::string path); //// Créer une image et la set en fonction du nom dans la map image
        void beginDrawing();

        void endDrawing();

        void drawImage(std::string name, int x, int y);

        void clear();

        /**************************
         *         Core           *
         * ***********************/
        void createCamera(pos_t position, pos_t target, pos_t up);

        void start3Dscene();

        void stop3Dscene();

        void moveCamera(pos_t position);

        static bool
        isThereACollision(Vector3 playerPosition, Vector3 playerSize,
                          Vector3 enemyBoxPos, Vector3 enemyBoxSize);

        void static playVideo(std::string path, int nbFrames);
    };
}
#endif //BOMBERMAN_GRAPHICS_H
