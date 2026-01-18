#include "contiki.h"
#include "net/routing/routing.h"
#include "net/ipv6/simple-udp.h"
#include "random.h"
#include "sys/log.h"
#include <inttypes.h>

#define LOG_MODULE "RPL-CLIENT"
#define LOG_LEVEL LOG_LEVEL_INFO

#define UDP_PORT 5678
#define SEND_INTERVAL (10 * CLOCK_SECOND)

static struct simple_udp_connection udp_conn;
PROCESS(rpl_client_process, "RPL Client");
AUTOSTART_PROCESSES(&rpl_client_process);

PROCESS_THREAD(rpl_client_process, ev, data)
{
    static struct etimer timer;
    static uint32_t seq = 0;
    static uint32_t tx_count = 0;

    static uip_ipaddr_t root_ip;

    PROCESS_BEGIN();

    simple_udp_register(&udp_conn,
                        UDP_PORT,
                        NULL,
                        UDP_PORT,
                        NULL);

    etimer_set(&timer, random_rand() % SEND_INTERVAL);

    while (1)
    {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

        if (NETSTACK_ROUTING.node_is_reachable() &&
            NETSTACK_ROUTING.get_root_ipaddr(&root_ip))
        {

            char msg[32];
            clock_time_t now = clock_time();
            snprintf(msg, sizeof(msg),
                     "SEQ=%" PRIu32 ";T=%lu", seq, (unsigned long)now);

            simple_udp_sendto(&udp_conn, msg, strlen(msg), &root_ip);

            tx_count++;
            seq++;

            LOG_INFO("TX=%" PRIu32 " Sent %s\n", tx_count, msg);
        }
        else
        {
            LOG_INFO("RPL not ready\n");
        }

        etimer_set(&timer, SEND_INTERVAL);
    }

    PROCESS_END();
}
