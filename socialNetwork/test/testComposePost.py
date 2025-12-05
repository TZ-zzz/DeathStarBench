import sys
sys.path.append('../gen-py')

import random
from social_network import ComposePostService
from social_network.ttypes import Media
from social_network.ttypes import PostType
from social_network.ttypes import Creator
from social_network.ttypes import Url
from social_network.ttypes import UserMention


from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

def main():
  socket = TSocket.TSocket("localhost", 10001)
  transport = TTransport.TFramedTransport(socket)
  protocol = TBinaryProtocol.TBinaryProtocol(transport)
  client = ComposePostService.Client(protocol)

  transport.open()
  req_id = random.getrandbits(63)
  text = "TCoch8ij3Pgli6LlPcpoySmH9EDQB5klJmG7vCdhxQIEvjC6S5tKURvY796X4dePDKU0ELgBpVhYrqWG6YvW0Z77K2KStZsJQKH4Q5JPJ6yZ7Un2eCzwTh9diHBsn92MJIZuWmHocC3lkkpzeEcULzLM9UwbY3fsQ7k2v8qKL30qppxsDJLxqWa98svRtAGTI7v45vSFgAGnX9AvHlKHZ2GKewaiSMSoC8wJxDzPf9888OxD1wkA47l68EeOkGJr+@username_916+@username_338+@username_67+@username_505 http://PeTI0e2S444RVMCLVgCxUmwAeXx0unYHWqfQete796QXCdEIQg37F5UJH2HVhsEJ http://sHigXpaLySE2B6nfakaNdKT3OpGNcuYUCFCYV6g3UKZxFoIBQLSFQyY0hpBAjzue http://72OZBVSxRcGuRd456TIcAexMdomRWUYnnris1ZUztsQOnzEzN0Hne0ghoFLPpf9I http://kyZiNjQ3W2W1a4p04Mn6MDa8j3IQuY9bSLYm97lQBZj9DQ9UjvWy0DejTAJSuH0K http://bTuvQmVfordCTakXUZMUc3V1RRWPoQjU5b3cVHP6ZCKf609ELB0rJC4phcZnCq5J"
  post_id = random.getrandbits(63)
  post_type = PostType.POST
  # creator = Creator(username="user_0", user_id=0)
  # url_0 = Url(shortened_url="shortened_url_0", expanded_url="expanded_url_0")
  # url_1 = Url(shortened_url="shortened_url_1", expanded_url="expanded_url_1")
  # urls = [url_0, url_1]
  # user_mention_0 = UserMention(user_id=1, username="user_1")
  # user_mention_1 = UserMention(user_id=2, username="user_2")

  username = "username_1"
  user_id = 0

  # user_mentions = [user_mention_0 ,user_mention_1]
  # print(client._ComposeTextHelper(req_id,text,{}))
  print(client.ComposePost(req_id, username, user_id, text, None, None, post_type, {}))
  transport.close()

if __name__ == '__main__':
  try:
    main()
  except Thrift.TException as tx:
    print('%s' % tx.message)