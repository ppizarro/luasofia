%{

#include <sofia-sip/su.h>

%}

/* Protocol families.  */
#define SU_PF_UNSPEC       0       /* Unspecified.  */
#define SU_PF_LOCAL        1       /* Local to host (pipes and file-domain).  */
#define SU_PF_UNIX         PF_LOCAL /* POSIX name for PF_LOCAL.  */
#define SU_PF_FILE         PF_LOCAL /* Another non-standard name for PF_LOCAL.  */
#define SU_PF_INET         2       /* IP protocol family.  */
#define SU_PF_AX25         3       /* Amateur Radio AX.25.  */
#define SU_PF_IPX          4       /* Novell Internet Protocol.  */
#define SU_PF_APPLETALK    5       /* Appletalk DDP.  */
#define SU_PF_NETROM       6       /* Amateur radio NetROM.  */
#define SU_PF_BRIDGE       7       /* Multiprotocol bridge.  */
#define SU_PF_ATMPVC       8       /* ATM PVCs.  */
#define SU_PF_X25          9       /* Reserved for X.25 project.  */
#define SU_PF_INET6        10      /* IP version 6.  */
#define SU_PF_ROSE         11      /* Amateur Radio X.25 PLP.  */
#define SU_PF_DECnet       12      /* Reserved for DECnet project.  */
#define SU_PF_NETBEUI      13      /* Reserved for 802.2LLC project.  */
#define SU_PF_SECURITY     14      /* Security callback pseudo AF.  */
#define SU_PF_KEY          15      /* PF_KEY key management API.  */
#define SU_PF_NETLINK      16
#define SU_PF_ROUTE        PF_NETLINK /* Alias to emulate 4.4BSD.  */
#define SU_PF_PACKET       17      /* Packet family.  */
#define SU_PF_ASH          18      /* Ash.  */
#define SU_PF_ECONET       19      /* Acorn Econet.  */
#define SU_PF_ATMSVC       20      /* ATM SVCs.  */
#define SU_PF_SNA          22      /* Linux SNA Project */
#define SU_PF_IRDA         23      /* IRDA sockets.  */
#define SU_PF_PPPOX        24      /* PPPoX sockets.  */
#define SU_PF_WANPIPE      25      /* Wanpipe API sockets.  */
#define SU_PF_BLUETOOTH    31      /* Bluetooth sockets.  */
#define SU_PF_IUCV         32      /* IUCV sockets.  */
#define SU_PF_RXRPC        33      /* RxRPC sockets.  */
#define SU_PF_ISDN         34      /* mISDN sockets.  */
#define SU_PF_MAX          35      /* For now..  */

/* Types of sockets.  */
#define SU_SOCK_STREAM     1        /* Sequenced, reliable, connection-based
                                       byte streams.  */
#define SU_SOCK_DGRAM      2        /* Connectionless, unreliable datagrams
                                       of fixed maximum length.  */
#define SU_SOCK_RAW        3        /* Raw protocol interface.  */
#define SU_SOCK_RDM        4        /* Reliably-delivered messages.  */
#define SU_SOCK_SEQPACKET  5        /* Sequenced, reliable, connection-based,
                                       datagrams of fixed maximum length.  */
#define SU_SOCK_DCCP       6        /* Datagram Congestion Control Protocol.  */
#define SU_SOCK_PACKET     10       /* Linux specific way of getting packets
                                       at the dev level.  For writing rarp and
                                       other similar things on the user level. */
#define SU_SOCK_CLOEXEC    02000000 /* Atomically set close-on-exec flag for the
                                       new descriptor(s).  */
#define SU_SOCK_NONBLOCK   04000    /* Atomically mark descriptor(s) as
                                       non-blocking.  */

%include <sofia-sip/su.h>

