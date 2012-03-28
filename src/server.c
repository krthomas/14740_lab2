/**@file server.c
 * @brief A simple server program to demonstrate datagram service
 *
 * This server simply initializes datagram service and receives datagrams
 * infinitely
 *
 * @author Shrikant Mether (smether)
 */

#include "datagram.h"

// Function prototypes
void run();

int main(int argc, char *argv[])
{
    int port;

    // Check command line arguments
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(-1);
    }
    port = atoi(argv[1]);

    init_datagram_service(port, DEBUG_ALL);

    // Start server
    run();

    return 0;
}

/**@brief Keeps receiving datagrams and prints them
 */
void run()
{
    int retval;
    char buf[DATAGRAM_DATA_SIZE];
    datagram_t datagram;

    while (1) {
        retval = receive_datagram(&datagram);
        if (retval < 0) {
            perror("receive failed");
            continue;
        }

        bzero(buf, DATAGRAM_DATA_SIZE);
        strncpy(buf, datagram.data, datagram.size);
        printf("Received Datagram From %s:%d Data:%s\n", datagram.srcaddr,
                datagram.srcport, buf);
    }
}

