typedef struct Controller_Profile {
    bool start, back;
    Vec2 left_stick, right_stick;

    struct {
        bool left, right;
    } shoulder, trigger;
    
    struct {
        bool a, b, x, y;
    } button;
    
    struct {
        bool up, down, left, right;
    } dpad;
} Controller_Profile;

typedef struct Input_Profile {
    bool keys[256];
    bool keys_old[256];

    Controller_Profile controller;
    Controller_Profile controller_old;
} Input_Profile;