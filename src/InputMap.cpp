#include "InputMap.hpp"
#include "raylib-cpp.hpp"

bool InputMap::IsActionPressed(Action a) const {
    const auto& [key, mouseButton] = bindings.at(a);

    if (key && IsKeyPressed(key)) return true;
    if (mouseButton && IsMouseButtonPressed(mouseButton)) return true;

    return false;
}

bool InputMap::IsActionDown(Action a) const {
    const auto& [key, mouseButton] = bindings.at(a);

    if (key && IsKeyDown(key)) return true;
    if (mouseButton && IsMouseButtonDown(mouseButton)) return true;

    return false;
}

void InputMap::SetBinding(Action a, Binding b) {
    bindings[a] = b;
}

Binding InputMap::GetBinding(Action a) const {
    return bindings.at(a);
}
