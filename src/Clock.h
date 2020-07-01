//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef Clock_H
#define Clock_H

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Clock {
public:
    static Clock* getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Clock();
    }

    void tick();
    inline float getDeltaTime() const { return deltaTime; }

private:
    Clock() = default;
    static Clock *s_Instance;
    float deltaTime;
    float lastTime;
};


#endif //Clock_H
