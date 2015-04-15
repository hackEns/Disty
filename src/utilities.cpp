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

    void trim(std::string &s)
    {
        size_t p = s.find_first_not_of(" \t\n");
        s.erase(0, p);

        p = s.find_last_not_of(" \t\n");
        if (std::string::npos != p) {
            s.erase(p + 1);
        }
    }
}  // namespace utilities
