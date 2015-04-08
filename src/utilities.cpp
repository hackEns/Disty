#include "utilities.hpp"


namespace utilities {
    float clamp(const float value, float b1, float b2) {
        if (b2 < b1) {
            float tmp = b1;
            b2 = b1;
            b1 = tmp;
        }

        if (value < b1) {
            return b1;
        }
        else if (value > b2) {
            return b2;
        }
        else {
            return value;
        }
    }
}  // namespace utilities
