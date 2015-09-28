#include <string>

namespace udpserver {
    const int BUFFER_LENGTH = 1024;

    class UDPServer {
    public:
        UDPServer(const int port);

        ~UDPServer(void);

        /** Poll for new packets. Return a char* if data is found, NULL otherwise. */
        std::string poll(void);
    private:
        int port_;
        int sock_;
    };
}
