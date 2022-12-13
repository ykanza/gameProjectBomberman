#include "graphics.hpp"
#include "../events/event.h"

#define PL_MPEG_IMPLEMENTATION
#include "../../../include/pl_mpeg.h"

RL::Graphics::Graphics()
{
}

const Vector3 &RL::Graphics::getPosition() const {
    return this->cam.position;
}

const Vector3 &RL::Graphics::getTarget() const {
    return this->cam.target;
}

const Vector3 &RL::Graphics::getUp() const {
    return this->cam.up;
}

void RL::Graphics::setImage(std::string name, std::string path)
{
    this->image[name] = LoadImage(path.c_str());
    //throw if Load Image is bad
    this->texture2D[name] = LoadTextureFromImage(this->image[name]);
    //throw if error
}

std::map<std::string, Image> &RL::Graphics::getImage()
{
    return this->image;
}

std::map<std::string, Texture2D> &RL::Graphics::getTexture()
{
    return this->texture2D;
}

void RL::Graphics::beginDrawing()
{
    BeginDrawing();
}

void RL::Graphics::drawImage(std::string name, int x, int y)
{
    DrawTexture(this->texture2D[name], x, y, WHITE);
}

void RL::Graphics::endDrawing()
{
    EndDrawing();
}

void RL::Graphics::clear()
{
    ClearBackground(RAYWHITE);
}

/**********************
 *       CAMERA       *
 * *******************/

void RL::Graphics::createCamera(pos_t position, pos_t target, pos_t up)
{
    this->cam.position = { position.x, position.y, position.z};
    this->cam.target = { target.x, target.y, target.z };
    this->cam.up = { up.x, up.y, up.z };
    this->cam.fovy = 60.0f;
    this->cam.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(this->cam, CAMERA_THIRD_PERSON);
}

void RL::Graphics::start3Dscene()
{
    // BeginDrawing();
        BeginMode3D(this->cam);
            // UpdateCamera(&this->cam);
}

void RL::Graphics::stop3Dscene()
{
        EndMode3D();
    // EndDrawing();
}

void RL::Graphics::moveCamera(pos_t position)
{
    this->cam.position = { position.x, position.y + 2, position.z + 1 };
    this->cam.target = { position.x, static_cast<float>(position.y + 1.5), position.z + 2 };
    // this->cam.up = (Vector3){ position.x, position.y, position.z };
}

bool RL::Graphics::isThereACollision(Vector3 playerPosition, Vector3 playerSize,
Vector3 enemyBoxPos, Vector3 enemyBoxSize)
{
    return CheckCollisionBoxes(
        {{ playerPosition.x - playerSize.x/2,
                                 playerPosition.y - playerSize.y/2,
                                 playerPosition.z - playerSize.z/2 },
                      { playerPosition.x + playerSize.x/2,
                                 playerPosition.y + playerSize.y/2,
                                 playerPosition.z + playerSize.z/2 }},
        {{ enemyBoxPos.x - enemyBoxSize.x/2,
                                 enemyBoxPos.y - enemyBoxSize.y/2,
                                 enemyBoxPos.z - enemyBoxSize.z/2 },
                      { enemyBoxPos.x + enemyBoxSize.x/2,
                                 enemyBoxPos.y + enemyBoxSize.y/2,
                                 enemyBoxPos.z + enemyBoxSize.z/2 }});
}

void RL::Graphics::playVideo(std::string path, int nbFrames)
{
    plm_t *plm = plm_create_with_filename(path.c_str());
    if (!plm)
        return;
    double framerate = plm_get_framerate(plm);
    plm_frame_t *frame = nullptr;
    Image imFrame = { nullptr };
    imFrame.width = plm_get_width(plm);
    imFrame.height = plm_get_height(plm);
    imFrame.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
    imFrame.mipmaps = 1;
    imFrame.data = (unsigned char *)malloc(imFrame.width * imFrame.height *3);
    Texture texture = LoadTextureFromImage(imFrame);
    plm_set_audio_enabled(plm, FALSE);
    double baseTime = GetTime();
    int i = 0;

    while (i < nbFrames) {
        i++;
        if (Event::isKeyPressed(KEY_SPACE))
            break;
        double time = (GetTime() - baseTime);
        if (time >= (0.5 / framerate)) {
            baseTime = GetTime();
            frame = plm_decode_video(plm);
            plm_frame_to_rgb(frame, (uint8_t *) imFrame.data, imFrame.width * 3);
            UpdateTexture(texture, imFrame.data);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(texture, GetScreenWidth()/2 - texture.width/2, GetScreenHeight()/2 - texture.height/2, WHITE);
        EndDrawing();
    }
    UnloadTexture(texture);
    UnloadImage(imFrame);
    plm_destroy(plm);
}