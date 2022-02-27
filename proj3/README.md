# Lab 3: Networking
Run the server in one terminal, then run the client in another terminal to check the output.

You can also try to run the server and client in a different lab machines (machines that are connected on the same LAN. Replace localhost or 127.0.0.1 with the IP address of the machine in the code to get it working.

## Requirements
1. In the current version there is only one client. But you must create two different 
clients.
2. Currently the messages are hardcoded in the program. But your code must read 
the client messages from the user.
3. Currently the server is accepting a client message (request) and sending a
response message to the same client. In your new version, the server should 
forward the accepted message from one client to the other client. 
4. The server should work properly only when two clients are up and connecting to 
it. If there is only one client connecting to the server then, the server will send a 
message complaining “only one client is up”
5. The process should not end only after one pass of message between server and 
client as it is now. Server will only stop if one of the clients sends ‘BYE’ message
6. The server process should be designed in such a way so that it cannot be 
aborted by hitting ctrl-c on that terminal
7. For the sake of simplicity, assume that both your client and servers are on the 
same machine i.e. localhost (127.0.0.1)
8. You may need to send the client process pids to the server to establish the 
connection