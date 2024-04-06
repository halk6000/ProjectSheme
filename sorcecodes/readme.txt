Hello This server use to:
1. add ip Local or custom ip
2. S React command name like ,,dom"
3. if get ,,dom" back client True.
4. client send version after True.
5. server run lib to SynhV.dll and send version server and version Client


Description of the SynhV.dll library:

1.The SynhV library receives variables from the server.
2.It uses them to calculate the version difference between the client and the server.
3.The second stage of calculations involves shifting the difference by 0.01 as many times as there were iterations in order to equalize the client and server versions.
4.During operation, it collects cases that are also version numbers.
5.During implementation:

The server receives information from the library, which it uses to launch the library responsible for searching for files. 
The server then returns information to the client and the file replacement process begins.