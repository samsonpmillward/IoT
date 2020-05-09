--make sure you are online first - Dalin
cl = net.createConnection(net.TCP, 0)
--create a TCP based not encryped client
cl:on("connection",function(conn, s)
conn:send("Now in connection, hello Dalin\n")
end)
cl:on("disconnection",function(conn, s)
print("Now we are disconnected\n")
end)
cl:on("sent",function(conn, s)
print("Message has been sent out\n")
end)
cl:on("receive", function(conn, s)
print("What we receive from the server\n" .. s .. "\n")
end)
--on(event, function())
--event can be "connection", "reconnection", "disconnection", "receive" or "sent"
--function(net.socket[, para]) is the callback function.
--The first parameter of callback is the socket.
--If event is "receive", the second parameter is the received data as string.
--If event is "disconnection" or "reconnection", the second parameter is error code.
cl:connect(1990,"192.168.8.139")
--the local IP of your test server