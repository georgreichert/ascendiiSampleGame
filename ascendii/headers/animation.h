#include "../ascendii.h"

class Animation {
    private:

    public:
        // nextAnim will be called when current animation is finished or next() is called. If duration is set to negative value, animation will play
        // until stop() is called. prevAnim will be deleted after call to nextAnim.
        Animation(Sprite* sprite, int duration = 300, Animation* nextAnim = nullptr, Animation* prevAnim = nullptr);
};
