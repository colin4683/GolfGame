
#ifndef GOLFGAME_SETTINGS_H
#define GOLFGAME_SETTINGS_H
#endif //GOLFGAME_SETTINGS_H


class Settings {
public:
    int windowWidth = 1920;
    int windowHeight = 1080;
    bool isDebugMode = true;
    bool isFullscreen = false;
    bool isMusicEnabled = true;
    bool isSoundEnabled = true;
    bool isLaunchFromAnywhereEnabled = false;
    int tileSize = 50;
};

inline Settings &getSettings() {
    static Settings settings;
    return settings;
}
