#include <string>
#include <vector>

namespace utilities {
    /**
     * Clamp a value between bounds b1 and b2.
     */
    float clamp(float value, float b1, float b2);

    /**
     * Remove trailing whitespaces from the string s.
     */
    void trim(std::string &s);

    /**
     * Split the string on delimiter, returning a vector of tokens.
     *
     * Does not pass empty tokens.
     */
    std::vector<std::string> split(const std::string &s, char delimiter);


    /**
     * Sleep for the given amount of milliseconds.
     */
    void millisleep(int milliseconds);
}  // namespace utilities
