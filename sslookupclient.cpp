/* sslookupclient.cpp
 * Shakespeare full-text search client:
 * receives an Ajax request from web client
 * extracts search string, and sends request to sslookupserver
 */
#include <iostream>
#include <fstream>
#include <string>

//Stuff for pipes
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "fifo.h"
using namespace std;

// Pipes for communication
string receive_pipe = "reply";
string send_pipe = "request";

int main()
{
   // prepare the response output,
   // send required header before any other output
   cout << "Content-Type: text/plain\n\n" << endl;

   Fifo recfifo(receive_pipe);
   Fifo sendfifo(send_pipe);

   sendfifo.openwrite();

   string lookup = "25:3:1";
   // Call server to get results
   sendfifo.send(lookup);

   recfifo.openread();

   // output the response to the web page
   string results = "";
   int times = 0; // Counter for header lines
   while (results != "$end")
   {
      results = recfifo.recv();
      if (results != "$end")
      {
         cout << results << endl;
         if (times++ > 2)
         {
            cout << "<br>";
         }
      }
   }
   cout << endl; // flush output when done

   recfifo.fifoclose();

   sendfifo.fifoclose();

   return 0;
}
