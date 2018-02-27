/*
 * test_ethernet.c
 *
 *  Created on: 2017. 10. 18.
 *      Author: opus
 */

#include "test_def.h"

#if _TEST_ENABLE_ETHERNET

#include "test_ethernet.h"

#ifdef _USE_HW_RTOS

#define ETH_TASK_PRIO  ( tskIDLE_PRIORITY + 5 )

static void threadEthernet(void const * argument);
static void threadServerLoopback(void);
static void taskServerLoopback(void *arg);
static void threadClientLoopback(void);
static void taskClientLoopback(void *arg);
static void threadUDPLoopback(void);
static void taskUDPLoopback(void *arg);
static void threadDnsClient(void);
static void taskDnsClient(void *arg);

void testEthernetMain(void)
{
  osThreadId ret;

  osThreadDef(TEST_ETHERNET, threadEthernet, osPriorityNormal, 0, configMINIMAL_STACK_SIZE * 5);
  ret = osThreadCreate(osThread(TEST_ETHERNET), NULL);
  if (ret == NULL)
  {
    cmdifPrintf("osThreadCreate : threadEthernet(%X) fail\n", ret);
  }
}

static void threadEthernet(void const * argument)
{
  uint8_t mac_addr[6] = { 0x00, 0x08, 0xDC, 0x50, 0xF4, 0xF5 };

  ip_addr_t ip_addr, subnet, gateway, dns_server;
  IP4_ADDR(&ip_addr, 192, 168, 0, 4);
  IP4_ADDR(&subnet, 255, 255, 255, 0);
  IP4_ADDR(&gateway, 192, 168, 0, 1);
  IP4_ADDR(&dns_server, 8, 8, 8, 8);

  ethernetIfBegin(IP_DHCP, mac_addr, &ip_addr, &subnet, &gateway, &dns_server);

  threadServerLoopback();
  threadClientLoopback();
  threadUDPLoopback();
  threadDnsClient();

  for (;;)
  {
    osThreadTerminate(NULL);
  }
}

/* TCP Server */
static void threadServerLoopback(void)
{
  sys_thread_new("ServerLoopback", taskServerLoopback, NULL,
  DEFAULT_THREAD_STACKSIZE, ETH_TASK_PRIO);
}

static void taskServerLoopback(void *arg)
{
  err_t err;
  socket_t server;
  int conn_sockfd;
  int32_t recv_len;
  uint8_t shared_buf[256];
  u16_t server_port = 5000;

  err = ethernetOpenSocket(&server, server_port, TCP_SERVER);
  if (err == ERR_OK)
  {
    for (;;)
    {
      conn_sockfd = ethernetAccept(&server);
      if (conn_sockfd >= 0)
      {
        ethernetEnableKeepAlive(conn_sockfd);
        recv_len = ethernetRecvTCP(conn_sockfd, shared_buf, sizeof(shared_buf));
        while (recv_len > 0)
        {
          ethernetSendTCP(conn_sockfd, shared_buf, recv_len);
          recv_len = ethernetRecvTCP(conn_sockfd, shared_buf, sizeof(shared_buf));
        }
        ethernetCloseSocket(conn_sockfd); //for passive close (Close wait)
      }
    }
    ethernetCloseSocket(server.sockfd);
  }

  USBD_UsrLog("Server task over!\r\n");

  for (;;)
  {
    osThreadTerminate(NULL);
  }
}

/* TCP Client */
static void threadClientLoopback(void)
{
  sys_thread_new("ClientLoopback", taskClientLoopback, NULL,
  DEFAULT_THREAD_STACKSIZE, ETH_TASK_PRIO);
}

static void taskClientLoopback(void *arg)
{
  err_t err;
  socket_t client;
  int32_t recv_len = 0;
  uint8_t shared_buf[256];
  u16_t remote_port = 50000;
  ip_addr_t remote_server;
  IP4_ADDR(&remote_server, 192, 168, 11, 16);

  for (;;)
  {
    err = ethernetOpenSocket(&client, CLIENT_LOCAL_PORT, TCP_CLIENT);
    if (err == ERR_OK)
    {
      err = ethernetConnect(&client, &remote_server, remote_port);
      if (err == 0)
      {
        recv_len = ethernetRecvTCP(client.sockfd, shared_buf, sizeof(shared_buf));
        while (recv_len > 0)
        {
          ethernetSendTCP(client.sockfd, shared_buf, recv_len);
          recv_len = ethernetRecvTCP(client.sockfd, shared_buf, sizeof(shared_buf));
        }
      } else
      {
        USBD_UsrLog("[Client] connection socket err : %d", err);
        delay(5000);
      }
      ethernetCloseSocket(client.sockfd);
    }
  }

  USBD_UsrLog("client task over!\r\n");

  for (;;)
  {
    osThreadTerminate(NULL);
  }
}

/* UDP */
static void threadUDPLoopback(void)
{
  sys_thread_new("UDPLoopback", taskUDPLoopback, NULL,
  DEFAULT_THREAD_STACKSIZE, ETH_TASK_PRIO);
}

static void taskUDPLoopback(void *arg)
{
  err_t err;
  socket_t udp_peer;
  int32_t recv_len;
  uint8_t shared_buf[256];
  u16_t local_port = 8080;
  ip_addr_t remote_ip_addr;
  u16_t remote_port;
  //IP4_ADDR(&remote_peer_addr, 192, 168, 0, 10); //if you want specific remote peer

  err = ethernetOpenSocket(&udp_peer, local_port, UDP_PEER);
  if (err == ERR_OK)
  {
    for (;;)
    {
      recv_len = ethernetRecvUDP(&udp_peer, shared_buf, sizeof(shared_buf));
      while (recv_len > 0)
      {
        remote_ip_addr.addr = (u32_t) udp_peer.remote_addr.sin_addr.s_addr;
        remote_port = (u16_t) udp_peer.remote_addr.sin_port;
        ethernetSendUDP(&udp_peer, shared_buf, recv_len, &remote_ip_addr, remote_port);
        recv_len = ethernetRecvUDP(&udp_peer, shared_buf, sizeof(shared_buf));
      }
    }
    ethernetCloseSocket(udp_peer.sockfd);
  }

  USBD_UsrLog("UDP task over!\r\n");

  for (;;)
  {
    osThreadTerminate(NULL);
  }
}

/* DNS */
static void threadDnsClient(void)
{
  sys_thread_new("testDnsClient", taskDnsClient, NULL,
  DEFAULT_THREAD_STACKSIZE, ETH_TASK_PRIO);
}

static void taskDnsClient(void *arg)
{
  err_t err;
  socket_t client;
  int32_t recv_len = 0;
  uint8_t shared_buf[256];
  ip_addr_t remote_server;
  u16_t remote_port = 80;
  char* req_http_msg = "GET /asciilogo.txt HTTP/1.1\r\nHost: arduino.cc\r\n\r\n";

  delay(5000);

  ethernetGetIpByDNS("arduino.cc", &remote_server);

  err = ethernetOpenSocket(&client, CLIENT_LOCAL_PORT, TCP_CLIENT);
  if (err == ERR_OK)
  {
    err = ethernetConnect(&client, &remote_server, remote_port);
    if (err == 0)
    {
      ethernetSendTCP(client.sockfd, (uint8_t*) req_http_msg, strlen(req_http_msg));

      recv_len = ethernetRecvTCP(client.sockfd, shared_buf, sizeof(shared_buf));
      while (recv_len > 0)
      {
        vcpWrite(shared_buf, recv_len);
        recv_len = ethernetRecvTCP(client.sockfd, shared_buf, sizeof(shared_buf));
      }
    } else
    {
      USBD_UsrLog("[Client] connection socket err : %d", err);
    }
    ethernetCloseSocket(client.sockfd);
  }

  USBD_UsrLog("DNS Client task over!\r\n");

  for (;;)
  {
    osThreadTerminate(NULL);
  }

}

#endif /*_USE_HW_RTOS*/
#endif /*_TEST_ENABLE_ETHERNET*/
