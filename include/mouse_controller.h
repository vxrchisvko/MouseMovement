#ifndef MOUSE_CONTROLLER_H_
#define MOUSE_CONTROLLER_H_

#include <Windows.h>
#include <src/bezier/bezier.h>


namespace mouse_library {

    class r_mouse {
    public:
        r_mouse();
        ~r_mouse();

        void initialize();
        void unitialize();

        void move_mouse(int x, int y);
        void humanize_move(int start_x, int start_y, int end_x, int end_y);
        void jitter(float strength, int steps);

        void click_left();
        void click_right();

        void hold_left();
        void release_left();

        POINT get_current_position();
    private:
        HSYNTHETICPOINTERDEVICE pen_device_;
    };

}  // namespace mouse_library

#endif  // MOUSE_CONTROLLER_H_
