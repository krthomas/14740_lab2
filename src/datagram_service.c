/**@file datagram_service.c
 *
 * @brief A Stub that provides datagram send and receive functionality.
 *
 * Feel free to modify this file to simulate network errors such as packet
 * drops, duplication, corruption etc. But for grading purposes we will
 * replace this file with out own version. So DO NOT make any changes to the
 * function prototypes
 *
 * @author Shrikant Mether (smether)
 */
#include "datagram.h"
#include <stdarg.h>

/**@brief listening socket */
static int listenfd = 0;
static socklen_t  addrlen = sizeof(struct sockaddr_in);
/**@brief verbose level */
static int v = 0;

/**@brief Function for initializing datagram service
 * @param port port number to listen on for incoming packets
 * @param verbose verbose level for datagram service debug output [0 to 10]
 * @return -1 on error, 0 on success
 */
int init_datagram_service(int port, int verbose)
{
    struct sockaddr_in localsock;

    v = verbose;
    debug(DEBUG_ALL, "init_datagram_service(%d, %d)\n", port, v);

    // Initialize listening socket
    if ((listenfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Could not create socket");
        return -1;
    }

    // Bind
    bzero((char *)&localsock, sizeof(localsock));
    localsock.sin_family = AF_INET;
    localsock.sin_addr.s_addr = INADDR_ANY;
    localsock.sin_port = htons(port);
    if (bind(listenfd, (struct sockaddr *)&localsock, sizeof(localsock)) < 0) {
        perror("Bind failed");
        return -1;
    }

    return 0;
}

/**@brief Send a datagram packet to another node
 * @param datagram datagram to be sent
 * @return number of bytes sent on success, -ve value on error
 */
int send_datagram(datagram_t *datagram)
{
    int retval = 0;
    int len = 0;
    struct sockaddr_in dest;

    debug(DEBUG_ALL, "send_datagram(From %s:%d To %s:%d)\n", datagram->srcaddr,
                      datagram->srcport, datagram->dstaddr, datagram->dstport);

    len = datagram->size + DATAGRAM_HEADER_SIZE;

    // Prepare destination info
    memset((char *)&dest, 0, sizeof(struct sockaddr_in));
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr(datagram->dstaddr);
    dest.sin_port = htons(datagram->dstport);

    // Send datagram
    retval = sendto(listenfd, (char *)datagram, len, 0, (struct sockaddr *)&dest, addrlen);

    return retval;
}

/**@brief Function for receiving a datagram
 * @param datagram received packet will be returned via this parameter
 * @return number of bytes received on success, -ve value on error
 */
int receive_datagram(datagram_t *datagram)
{
    int retval = 0;
    struct sockaddr from;

    debug(DEBUG_ALL, "receive_datagram()\n");

    retval = recvfrom(listenfd, (char *)datagram, DATAGRAM_LEN_MAX, 0, &from, &addrlen);

    return retval;
}

/**@brief Function for printing debug output
 */
void debug(int level, char *fmt, ...)
{
    va_list argptr;
    char msg[1024];

    if (v >= level) {
        va_start(argptr,fmt);
        vsnprintf(msg, sizeof msg, fmt, argptr);
        va_end(argptr);
        printf("%s", msg);
    }
}
