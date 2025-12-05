import sys
sys.path.append('../gen-py')

import uuid
from social_network import TextService

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

def main():
  socket = TSocket.TSocket("localhost", 10007)
  transport = TTransport.TFramedTransport(socket)
  protocol = TBinaryProtocol.TBinaryProtocol(transport)
  client = TextService.Client(protocol)


  transport.open()
  for i in range(1):
    req_id = uuid.uuid4().int & 0x7FFFFFFFFFFFFFFF

    text = "TCoch8ij3Pgli6LlPcpoySmH9EDQB5klJmG7vCdhxQIEvjC6S5tKURvY796X4dePDKU0ELgBpVhYrqWG6YvW0Z77K2KStZsJQKH4Q5JPJ6yZ7Un2eCzwTh9diHBsn92MJIZuWmHocC3lkkpzeEcULzLM9UwbY3fsQ7k2v8qKL30qppxsDJLxqWa98svRtAGTI7v45vSFgAGnX9AvHlKHZ2GKewaiSMSoC8wJxDzPf9888OxD1wkA47l68EeOkGJr+@username_916+@username_338+@username_67+@username_505 http://PeTI0e2S444RVMCLVgCxUmwAeXx0unYHWqfQete796QXCdEIQg37F5UJH2HVhsEJ http://sHigXpaLySE2B6nfakaNdKT3OpGNcuYUCFCYV6g3UKZxFoIBQLSFQyY0hpBAjzue http://72OZBVSxRcGuRd456TIcAexMdomRWUYnnris1ZUztsQOnzEzN0Hne0ghoFLPpf9I http://kyZiNjQ3W2W1a4p04Mn6MDa8j3IQuY9bSLYm97lQBZj9DQ9UjvWy0DejTAJSuH0K http://bTuvQmVfordCTakXUZMUc3V1RRWPoQjU5b3cVHP6ZCKf609ELB0rJC4phcZnCq5J"
    print(client.ComposeText(req_id, text, {}))
  transport.close()

if __name__ == '__main__':
  try:
    main()
  except Thrift.TException as tx:
    print('%s' % tx.message)