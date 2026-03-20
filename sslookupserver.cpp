/***************************************************************************
 * sslookupserver.cpp  -  Program to serve Shakespeare search results
 *
 * copyright : (C) 2009 by Jim Skon
 ***************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "fifo.h"

using namespace std;

string receive_pipe = "request";
string send_pipe = "reply";

/* Server main line,create name MAP, wait for and serve requests */
int main()
{

   /* Create the communication fifos */
   Fifo recfifo(receive_pipe);
   Fifo sendfifo(send_pipe);

   recfifo.openread(); // only open once

   // "infinite loop" for server: repeat each time a request is received
   while (true)
   {

      /* Get a message from a client */
      string searchVerse = recfifo.recv();

      sendfifo.openwrite();
      string reply;
      /* Send back the search term message */
      reply = "YO YO YO I got the message";
      sendfifo.send(reply);
      cout << "Message received, sending reply..." << endl;

      reply = "$end";
      sendfifo.send(reply);
      sendfifo.fifoclose();
      //recfifo.fifoclose();
   }
}
