# ex4
The 4th exercise in Advanced Programming 1

### way of implementation

I used Thread Pool in order to implement the task. I divided the server tasks into 3 categories : Reading, Algoritmic Operation and Writing. Each time the task ends, it adds the next task into the thread pool's queue, and another thread takes it and does it.

### Error Codes:
1. unable to find a path.
2. Falied reading the user's message.
3. there are less than one space or more than 2 spaces in the first user message.
4. the user did not send "solve" in the beginning of his first message.
5. the user did not have 2 \r\n at the end of his massege.
6. the server failed writing to the user.
7. the user sent unknown operation to do.
8. the server failed creating the graph.
9. the user sent invalid graph.
