/**@file datagram.h
 *
 * @brief Contains datastructures and constants used by datagram service
 */
#ifndef __DATAGRAM_H__
#define __DATAGRAM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/**@brief Maximum datagram size (MTU) */
#define DATAGRAM_LEN_MAX    1500
/**@brief IP address section lengh */
#define IPADDR_BUF_SIZE     16
/**@brief Total size of header fields */
#define DATAGRAM_HEADER_SIZE 40
/**@brief Max length of data that can be sent in one datagram */
#define DATAGRAM_DATA_SIZE  (DATAGRAM_LEN_MAX - DATAGRAM_HEADER_SIZE)

/**@name Debug Options
 * @brief Options for controlling amount of debug output generated by datagram
 * service. Use these constants as verbose parameter of init_datagram_service()
 */
/*@{ */
#define DEBUG_ALL   10
#define DEBUG_NONE  0
/*@}*/

/**@brief Format of datagram packet
 */
typedef struct datagram {
    /**@brief Source IP address */
    char srcaddr[IPADDR_BUF_SIZE];
    /**@brief Destination IP address */
    char dstaddr[IPADDR_BUF_SIZE];
    /**@brief Source port number */
    unsigned short srcport;
    /**@brief Destination port number */
    unsigned short dstport;
    /**@brief Actual length of data section */
    unsigned short size;
    /**@brief Checksum */
    unsigned short checksum;
    /**@brief Actual data */
    char    data[DATAGRAM_DATA_SIZE];
} datagram_t;

int init_datagram_service(int port, int verbose);
int send_datagram(datagram_t *datagram);
int receive_datagram(datagram_t *datagram);

void debug(int level, char *fmt, ...);
#endif