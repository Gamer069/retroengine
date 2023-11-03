#pragma once

#include "inp.h"

namespace RetroEngine {
    class WindowsControls : public Controls {
    protected:
        virtual bool IsKeyPressedImpl(int key) override;
        virtual bool IsMousePressedImpl(int btn) override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
        virtual MousePos GetMousePosImpl() override;
    };
}
