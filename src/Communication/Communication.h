#pragma once

namespace Communication
{
    /**
     * @brief creates the socket and and calls for the queue to start
     *  doing operations.
     * 
     * @param argc number of arguments
     * @param argv the arguments
     */
    void connect(const int argc, const char *const argv[]);

    constexpr static int SERVER_BACKLOG = 20;
}