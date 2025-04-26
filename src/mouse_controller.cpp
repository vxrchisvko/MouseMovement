#ifndef MOUSE_CONTROLLER_C_
#define MOUSE_CONTROLLER_C_

#include <include/mouse_controller.h>
#include <random>

namespace mouse_library {

    r_mouse::r_mouse() : pen_device_(nullptr) { 
    }

    r_mouse::~r_mouse() {
        //clean up
        if (pen_device_) {
            DestroySyntheticPointerDevice(pen_device_);
        }
    }

    void r_mouse::initialize() {
        pen_device_ = CreateSyntheticPointerDevice(PT_PEN, 1, POINTER_FEEDBACK_DEFAULT);

        if (pen_device_ == nullptr) {
            MessageBox(
                NULL,
                L"Something failed inside the library",
                L"Rest",
                MB_ICONERROR
            );
        }
    }

    void r_mouse::unitialize() {
        if (pen_device_) {
            DestroySyntheticPointerDevice(pen_device_);
            pen_device_ = nullptr;
        }
    }

    void r_mouse::move_mouse(int x, int y) {
        POINTER_TYPE_INFO pointer_info = {};
        pointer_info.type = PT_PEN;

        POINTER_PEN_INFO& pen_info = pointer_info.penInfo;
        pen_info.pointerInfo.pointerType = PT_PEN;
        pen_info.pointerInfo.pointerId = 0;
        pen_info.pointerInfo.ptPixelLocation.x = x;
        pen_info.pointerInfo.ptPixelLocation.y = y;

        pen_info.pointerInfo.pointerFlags =
            POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE;

        pen_info.penFlags = PEN_FLAG_NONE;
        pen_info.penMask = PEN_MASK_PRESSURE;
        pen_info.pressure = 512;

        InjectSyntheticPointerInput(pen_device_, &pointer_info, 1);
    }

    void r_mouse::humanize_move(int start_x, int start_y, int end_x, int end_y) {
        //bezier probably

        POINT start = { start_x, start_y };
        POINT end = { end_x, end_y };

        float control_x = (start.x + end.x) / 2.0f;
        float control_y = (start.y + end.y) / 2.0f;

        std::vector<POINT> bezier_points = calculate_bezier_curve(start, end, control_x, control_y);

        for (const auto& point : bezier_points) {
            move_mouse(point.x, point.y);
        }
    }


    void r_mouse::jitter(float strength, int steps) {
        POINT pt;
        GetCursorPos(&pt);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(-static_cast<int>(strength), static_cast<int>(strength));

        for (int i = 0; i < steps; ++i) {
            int jitter_x = pt.x + dis(gen);
            int jitter_y = pt.y + dis(gen);

            move_mouse(jitter_x, jitter_y);
        }
    }

    void r_mouse::click_left() {
        POINTER_TYPE_INFO pointer_info = {};
        pointer_info.type = PT_PEN;

        POINTER_PEN_INFO& pen_info = pointer_info.penInfo;
        pen_info.pointerInfo.pointerType = PT_PEN;
        pen_info.pointerInfo.pointerId = 0;

        POINT cursor_pos;
        GetCursorPos(&cursor_pos);
        pen_info.pointerInfo.ptPixelLocation = cursor_pos;
        pen_info.pointerInfo.pointerFlags =
            POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;

        pen_info.penFlags = PEN_FLAG_NONE;
        pen_info.penMask = PEN_MASK_PRESSURE;
        pen_info.pressure = 1024;

        InjectSyntheticPointerInput(pen_device_, &pointer_info, 1);

        pen_info.pointerInfo.pointerFlags = POINTER_FLAG_UP;
        InjectSyntheticPointerInput(pen_device_, &pointer_info, 1);
    }

    void r_mouse::click_right() {
        POINTER_TYPE_INFO pointer_info = {};
        pointer_info.type = PT_PEN;

        POINTER_PEN_INFO& pen_info = pointer_info.penInfo;
        pen_info.pointerInfo.pointerType = PT_PEN;
        pen_info.pointerInfo.pointerId = 0;

        POINT cursor_pos;
        GetCursorPos(&cursor_pos);
        pen_info.pointerInfo.ptPixelLocation = cursor_pos;
        pen_info.pointerInfo.pointerFlags =
            POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;

        pen_info.penFlags = PEN_FLAG_NONE;
        pen_info.penMask = PEN_MASK_PRESSURE;
        pen_info.pressure = 1024;

        InjectSyntheticPointerInput(pen_device_, &pointer_info, 1);

        pen_info.pointerInfo.pointerFlags = POINTER_FLAG_UP;
        InjectSyntheticPointerInput(pen_device_, &pointer_info, 1);
    }

    void r_mouse::hold_left() {
        POINTER_TYPE_INFO pointer_info = {};
        pointer_info.type = PT_PEN;

        POINTER_PEN_INFO& pen_info = pointer_info.penInfo;
        pen_info.pointerInfo.pointerType = PT_PEN;
        pen_info.pointerInfo.pointerId = 0;

        POINT cursor_pos;
        GetCursorPos(&cursor_pos);
        pen_info.pointerInfo.ptPixelLocation = cursor_pos;
        pen_info.pointerInfo.pointerFlags =
            POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;

        pen_info.penFlags = PEN_FLAG_NONE;
        pen_info.penMask = PEN_MASK_PRESSURE;
        pen_info.pressure = 1024;

        InjectSyntheticPointerInput(pen_device_, &pointer_info, 1);
    }

    void r_mouse::release_left() {
        POINTER_TYPE_INFO pointer_info = {};
        pointer_info.type = PT_PEN;

        POINTER_PEN_INFO& pen_info = pointer_info.penInfo;
        pen_info.pointerInfo.pointerType = PT_PEN;
        pen_info.pointerInfo.pointerId = 0;

        POINT cursor_pos;
        GetCursorPos(&cursor_pos);
        pen_info.pointerInfo.ptPixelLocation = cursor_pos;
        pen_info.pointerInfo.pointerFlags = POINTER_FLAG_UP;

        pen_info.penFlags = PEN_FLAG_NONE;
        pen_info.penMask = PEN_MASK_PRESSURE;
        pen_info.pressure = 1024;

        InjectSyntheticPointerInput(pen_device_, &pointer_info, 1);
    }


    POINT r_mouse::get_current_position() {
        POINT pt;
        GetCursorPos(&pt);
        return pt;
    }

}  // namespace mouse_library

#endif
