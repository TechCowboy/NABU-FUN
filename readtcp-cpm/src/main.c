// ************************************************************************
// Skeleton Project
// DJ Sures (c)2023
//
// This is the progress of a game I'm making for the NABU computer.
// There are bugs, and I know about them. So you don't need to tell me :)
// I'm enjoying making it myself, so hope you understand keeping comments to yourself xD
// I shared the code so others can build their own games and use this as a starting point.
// If you make something, please let me know! We're a small NABU community and need to stick together.
//
// Have fun!
// - DJ
// ************************************************************************

#define BIN_TYPE BIN_CPM

#pragma output nofileio
#pragma output noprotectmsdos

#define DISABLE_VDP

#define DISABLE_CURSOR

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "NABU-LIB.h"
#include "RetroNET-FileStore.h"

#define IN_BUF_LEN 32
uint8_t _inBuf[IN_BUF_LEN] = { 0 };

#define OUT_BUF_LEN 1
uint8_t _outBuf[OUT_BUF_LEN] = { 0 };


void main() 
{
  uint8_t result;
  bool    ImHosting = false;
  uint8_t chars_read;
  int     i;


  initNABULib();  

  puts("");
  puts("This proof on concept application that");
  puts("tests the connection with the RetroNET");
  puts("Internet Adapter as a TCP Server");
  puts("Insure you have the server enabled");
  puts("in the settings under the menu ");
  puts("RetroNET");
  puts("Take note of the port assigned to it");
  puts("");
  puts("");
  puts("- CTRL-C to exit");
  puts("- CTRL-D display client count");
  puts("");

  result = rn_TCPServerAvailable();

  printf("Available: %d\n", result);

  if (ImHosting)
  while (true)
  {
    // uint8_t rn_TCPServerRead(uint8_t* buffer, uint16_t bufferOffset, uint8_t readLength)
    // void    rn_TCPServerWrite(uint16_t dataOffset, uint8_t dataLen, uint8_t* data)
    // uint8_t rn_TCPServerClientCnt()
    // int32_t rn_TCPHandleWrite(uint8_t tcpHandle, uint16_t dataOffset, uint16_t dataLen, uint8_t* data)
    // int32_t rn_TCPHandleRead(uint8_t tcpHandle, uint8_t* buffer, uint16_t bufferOffset, uint16_t readLength)
    // int32_t rn_TCPHandleSize(uint8_t fileHandle)
    // void    rn_TCPHandleClose(uint8_t fileHandle)
    // uint8_t rn_TCPOpen(uint8_t hostnameLen, uint8_t* hostname, uint16_t port, uint8_t fileHandle)
    //

    chars_read = (rn_TCPServerRead(_inBuf, 0, IN_BUF_LEN) & 0xFF);

    for (i = 0; i < (int)chars_read; i++)
      putchar((int) (_inBuf[i] & 0xFF));

    for (i = 0; i < (int)chars_read; i++)
      rn_TCPServerWrite(i, OUT_BUF_LEN, _inBuf);
  }
  else
  {
    char url[] = {"192.168.2.100"};
    uint16_t port = 6502;
    uint8_t filehandle = 0xff;
    uint8_t tcpHandle;
    char temp[32];
    uint8_t buffer[1024];
    int counter = 0;

    // uint8_t rn_TCPOpen(uint8_t hostnameLen, uint8_t* hostname, uint16_t port, uint8_t fileHandle)

    tcpHandle = rn_TCPOpen(strlen(url), url, port, filehandle);

    // connect to host
    while (true)
    {
      chars_read = rn_TCPHandleRead(tcpHandle, buffer, 0, sizeof(buffer));

      if (chars_read > 0)
      {
        printf("read %d characters\n", chars_read);

        for (i = 0; i < (chars_read & 0xFF); i++)
          putchar((int)(buffer[i] & 0xFF));
        printf("\n");
      }

      for(i = 0; i< 2000; i++)
        ;

      sprintf(temp, "%04d%c", counter, 155);

      // int32_t rn_TCPHandleWrite(uint8_t tcpHandle, uint16_t dataOffset, uint16_t dataLen, uint8_t* data)
      rn_TCPHandleWrite(tcpHandle, 0, strlen(temp), temp);
      counter++;
      
    }
  }

}
