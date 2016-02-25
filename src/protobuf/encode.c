#include <stdio.h>
#include <stdlib.h>
#include "cache.pb-c.h"

int main (int argc, const char * argv[])
{
  SQLStmt stmt = SQLSTMT__INIT; // AMessage
  Register reg = REGISTER__INIT;
  void *buf;                     // Buffer to store serialized data
  unsigned len;                  // Length of serialized data
  stmt.type = SQL__REGISTER;
  stmt.aregister = &reg;
  reg.automaton = "asdsadasd";
  reg.ipaddr = "asdsadasd";
  reg.port = 2020;
  reg.service = "sdasdsad";

  len = sqlstmt__get_packed_size(&stmt);

  buf = malloc(len);
  sqlstmt__pack(&stmt, buf);

  fprintf(stderr,"Writing %d serialized bytes\n",len); // See the length of message
  fwrite(buf, len, 1, stdout); // Write to stdout to allow direct command line piping

  free(buf); // Free the allocated serialized buffer
  return 0;
}