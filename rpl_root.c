#include "contiki.h"
#include "net/routing/routing.h"
#include "net/ipv6/simple-udp.h"
#include "sys/log.h"
#include <inttypes.h>
#include <string.h>

#define LOG_MODULE "RPL-ROOT"
#define LOG_LEVEL LOG_LEVEL_INFO

#define UDP_PORT 5678
#define MAX_CLIENTS 5

static struct simple_udp_connection udp_conn;

/* RX per node */
static uint32_t rx_total = 0;

PROCESS(rpl_root_process, "RPL Root");
AUTOSTART_PROCESSES(&rpl_root_process);

/* Helper: extract SEQ and timestamp */
static void parse_payload(const char *data, uint32_t *seq, uint32_t *time)
{
  sscanf(data, "SEQ=%" PRIu32 ";T=%" PRIu32, seq, time);
}

static void
udp_rx_callback(struct simple_udp_connection *c,
                const uip_ipaddr_t *sender_addr,
                uint16_t sender_port,
                const uip_ipaddr_t *receiver_addr,
                uint16_t receiver_port,
                const uint8_t *data,
                uint16_t datalen)
{
  uint32_t seq, tx_time;
  clock_time_t now = clock_time();

  rx_total++;

  parse_payload((const char *)data, &seq, &tx_time);

  clock_time_t delay = now - tx_time;

  LOG_INFO("RX=%" PRIu32 " SEQ=%" PRIu32
           " Delay=%lu ticks From ",
           rx_total, seq, (unsigned long)delay);
  LOG_INFO_6ADDR(sender_addr);
  LOG_INFO_("\n");
}

PROCESS_THREAD(rpl_root_process, ev, data)
{
  PROCESS_BEGIN();

  NETSTACK_ROUTING.root_start();

  simple_udp_register(&udp_conn,
                      UDP_PORT,
                      NULL,
                      UDP_PORT,
                      udp_rx_callback);

  LOG_INFO("RPL Root started\n");

  PROCESS_END();
}
