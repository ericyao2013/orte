#ifndef __NETWORKCONFIG_H__
#define __NETWORKCONFIG_H__

#include <rtems/rtems_bsdnet.h>
#include <bsp.h>

static char ethernet_address[6] = {0x00, 0x04, 0x9F, 0x00, 0x27, 0x50 };

#ifdef RTEMS_USE_LOOPBACK

int
rtems_bsdnet_loopattach(struct rtems_bsdnet_ifconfig *, int);

#ifdef RTEMS_USE_LOOPBACK_ONLY
static struct rtems_bsdnet_ifconfig netdriver_config = {
#else
static struct rtems_bsdnet_ifconfig loopback_config = {
#endif
  .name = "lo0",
  .attach = rtems_bsdnet_loopattach,
  .next = NULL,
  .ip_address = "127.0.0.1",
  .ip_netmask = "255.0.0.0",
};

#endif /*RTEMS_USE_LOOPBACK*/

#ifndef RTEMS_USE_LOOPBACK_ONLY
static struct rtems_bsdnet_ifconfig netdriver_config = {
  .name = RTEMS_BSP_NETWORK_DRIVER_NAME,
  .attach = RTEMS_BSP_NETWORK_DRIVER_ATTACH,
#ifdef RTEMS_USE_LOOPBACK
  .next = &loopback_config,
#else /*RTEMS_USE_LOOPBACK*/
  .next = NULL,
#endif /*RTEMS_USE_LOOPBACK*/
  .ip_address = "192.168.2.3",
  .ip_netmask = "255.255.255.0",
  .hardware_address = ethernet_address,
  .ignore_broadcast = 0,
  .mtu = 0,
  .rbuf_count = 0,
  .xbuf_count = 0,
  .port = 0,
  .irno = 0,
  .bpar = 0,
  .drv_ctrl = NULL
};
#endif /*RTEMS_USE_LOOPBACK_ONLY*/

struct rtems_bsdnet_config rtems_bsdnet_config = {
  .ifconfig = &netdriver_config,
  .bootp = NULL,
  .network_task_priority = 0,                   /* 100        */
  .mbuf_bytecount = 256 * 1024,                 /* 64 kbytes  */
  .mbuf_cluster_bytecount = 256 * 1024,         /* 128 kbytes */
  .hostname = NULL,
  .domainname = NULL,
  .gateway = NULL,
  .log_host = NULL,
  .name_server = { "NULL" },
  .ntp_server = { "NULL" },
  .sb_efficiency = 0,
  .udp_tx_buf_size = 0,                         /* UDP TX: 9216 bytes */
  .udp_rx_buf_size = 0,                         /* UDP RX: 40 * (1024 + sizeof(struct sockaddr_in)) */
  .tcp_tx_buf_size = 0,                         /* TCP TX: 16 * 1024 bytes */
  .tcp_rx_buf_size = 0,                         /* TCP TX: 16 * 1024 bytes */
};

#endif /* ifndef __NETWORKCONFIG_H__ */
