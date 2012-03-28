/**@file client.c
 *
 * @brief A sample client program to demonstrate datagram service
 *
 * This client simply loads datagram service and sends one datagram to
 * remote server
 *
 * @author Shrikant Mether (smether)
 */

#include "datagram.h"

int main(int argc, char *argv[])
{
    int port, srvport, retval;
    datagram_t datagram;

    // Check command line arguments
    if (argc != 3) {
        fprintf(stderr, "usage: %s <localport> <serverport>\n", argv[0]);
        exit(-1);
    }
    port = atoi(argv[1]);
    srvport = atoi(argv[2]);

    init_datagram_service(port, DEBUG_ALL);

    // Prepare datagram
    bzero(&datagram, sizeof(datagram));
    strcpy(datagram.srcaddr, "128.2.13.139"); // These should be command line inputs
    strcpy(datagram.dstaddr, "128.2.13.139"); // I am just being lazy here :-).
                                           // replace with your ip values before running
    datagram.srcport = port;
    datagram.dstport = srvport;
    strcpy(datagram.data, "Hello World!");
    datagram.size = 12;

    // Send datagram
    retval = send_datagram(&datagram);
    if (retval < 0) {
        perror("Send error");
    }
    printf("Sent %d bytes\n", retval);

    return 0;
}


