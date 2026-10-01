#pragma once

#include <unordered_map>

enum class Action {
    TOGGLE_FULLSCREEN
};

struct Binding {
    int key = 0;
    bool mouseButton = false;
};

class InputMap {
public:
    InputMap() = default;

    InputMap(std::initializer_list<std::pair<const Action, Binding>> init)
        : bindings(init) {}

    bool IsActionPressed(Action a) const;
    bool IsActionDown(Action a) const;

    void SetBinding(Action a, Binding b);
    Binding GetBinding(Action a) const;

private:
    std::unordered_map<Action, Binding> bindings;
};
