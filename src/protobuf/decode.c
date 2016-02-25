#include <stdio.h>
#include <stdlib.h>
#include "cache.pb-c.h"
#define MAX_MSG_SIZE 1024

static size_t
read_buffer (unsigned max_length, uint8_t *out)
{
  size_t cur_len = 0;
  size_t nread;
  while ((nread=fread(out + cur_len, 1, max_length - cur_len, stdin)) != 0)
  {
    cur_len += nread;
    if (cur_len == max_length)
    {
      fprintf(stderr, "max message length exceeded\n");
      exit(1);
    }
  }
  return cur_len;
}


int main (int argc, const char * argv[])
{
  SQLStmt *stmt;

  // Read packed message from standard-input.
  uint8_t buf[MAX_MSG_SIZE];
  size_t stmt_len = read_buffer (MAX_MSG_SIZE, buf);

  // Unpack the message using protobuf-c.
  stmt = sqlstmt__unpack(NULL, stmt_len, buf);
  if (stmt == NULL)
  {
    fprintf(stderr, "error unpacking incoming message\n");
    exit(1);
  }

  // display the message's fields.
  printf("Received command %d\n", stmt->type);  // required field
  if (stmt->type == SQL__REGISTER) {                   // handle optional field
    printf("Service: %s\n",stmt->aregister->service);
    printf("Automaton: %s\n",stmt->aregister->automaton);
    printf("IP addr: %s\n",stmt->aregister->ipaddr);
    printf("Port: %d\n",stmt->aregister->port);
  }

  // Free the unpacked message
  sqlstmt__free_unpacked(stmt, NULL);
  return 0;
}
