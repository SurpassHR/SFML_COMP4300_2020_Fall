#ifndef INPUT_H
#define INPUT_H

class Input {
public:
    Input() = default;
    ~Input() = default;
public:
    bool up{ false };
    bool left{ false };
    bool right{ false };
    bool down{ false };
    bool shoot{ false };
    bool specialWeapon{ false };
};

#endif // INPUT_H