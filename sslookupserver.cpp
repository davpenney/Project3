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
#include "Bible.h"
#include "Verse.h"
#include "Ref.h"

using namespace std;

string receive_pipe = "request";
string send_pipe = "reply";

/* Server main line,create name MAP, wait for and serve requests */
int main()
{

   /* Create the communication fifos */
   Fifo recfifo(receive_pipe);
   Fifo sendfifo(send_pipe);

   //Create the Bible for the client to search
   Bible webBible("/home/class/csc3004/Bibles/web-complete");
   LookupResult result;
   string reply;

   recfifo.openread(); // only open once

   // "infinite loop" for server: repeat each time a request is received
   while (true)
   {
      //sendfifo.send("Enter a ReF YO!");
      /* Get a message from a client */
      Ref searchVerse = recfifo.recv();


      sendfifo.openwrite();
      cout << "Requested Verse: ";
      Verse verse = webBible.lookup(searchVerse, 1, result);
      reply = verse.getVerse();

      /* Send back the search term message */
      sendfifo.send(reply);
      cout << "\nSending results...\n" << endl;

      string reply = "$end";
      sendfifo.send(reply);
      sendfifo.fifoclose();
      //recfifo.fifoclose();
   }
}
