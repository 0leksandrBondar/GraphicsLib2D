#pragma once

#include "GraphicsLib/OpenGL.h"

namespace gfx2d
{

    enum Mouse
    {
        LeftButton = 0,
        RightButton = 1,
        MiddleButton = 2,
    };

    enum Keyboard
    {
        KeyNone = -1,
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,
        Esc = GLFW_KEY_ESCAPE,
        Space = GLFW_KEY_SPACE,
        End = GLFW_KEY_END,
        Home = GLFW_KEY_HOME,
        Left = GLFW_KEY_LEFT,
        Up = GLFW_KEY_UP,
        Right = GLFW_KEY_RIGHT,
        Down = GLFW_KEY_DOWN,
        Print = GLFW_KEY_PRINT_SCREEN,
        Enter = GLFW_KEY_ENTER,
        Insert = GLFW_KEY_INSERT,
        Delete = GLFW_KEY_DELETE,
        Multiply = GLFW_KEY_KP_MULTIPLY,
        Add = GLFW_KEY_KP_ADD,
        Decimal = GLFW_KEY_KP_DECIMAL,
        Divide = GLFW_KEY_KP_DIVIDE,
        NP_Enter = GLFW_KEY_KP_ENTER,
        NP_Equal = GLFW_KEY_KP_EQUAL,
        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,
        LShift = GLFW_KEY_LEFT_SHIFT,
        RShift = GLFW_KEY_RIGHT_SHIFT,
        LControl = GLFW_KEY_LEFT_CONTROL,
        RControl = GLFW_KEY_RIGHT_CONTROL,
        LMenu = GLFW_KEY_LEFT_ALT,
        RMenu = GLFW_KEY_RIGHT_ALT,
        Back = GLFW_KEY_BACKSPACE,
        Tab = GLFW_KEY_TAB,
    };

} // namespace gfx2d