# GL_Server-Client
I wrote a server program and a client program using BOOST Library. The server accepts requests from clients asynchronously.
The server and client code are based on a boost asynchronous echo server and a boost echo client. 

Sever and Client have a Command-Line Interface (used CLI Library). C++14 was used (because of CLI).
I used Makefile to compile on Linux OS.

The server has functions for starting, stoping, and setting the server port.
The client has a function for connecting and sending messages to the server.
 Also, both have "help" and "exit" functions.

**"help" functions you can see on screenshots:**

![image](https://user-images.githubusercontent.com/21126221/118152995-0f153a00-b41e-11eb-9ec2-04dd0df47bc4.png)
![image](https://user-images.githubusercontent.com/21126221/118153081-25bb9100-b41e-11eb-8159-8b27796bac25.png)

**Example work:**

![image](https://user-images.githubusercontent.com/21126221/118153341-7501c180-b41e-11eb-9793-f990094b3010.png)
![image](https://user-images.githubusercontent.com/21126221/118153413-8ea30900-b41e-11eb-9ab7-5b67affb8fd9.png)

## Install for Linux OS
To download files use:
```
git clone git@github.com:elementallyXD/GL_Server-Client.git
```
Change dir:
```
cd GL_Server-Client
```
Run Makefile for build project:
```
make
```
**Now we can use server and client!**

## Usage for Linux OS
For run server use:
```
./server
```
For run client use:
```
./client
```

## Install for Windows
To download files use [Google Drive](https://cutt.ly/XbH4Fdv)
or use [Releases for download files](https://github.com/elementallyXD/GL_Server-Client/releases)

Unpack or move to your directory. Open Windows Terminal(CMD) as an administrator in that directory.

## Usage for Windows OS
**IN TERMINAL**

For run server use:
```
GL_Task_Wind.exe
```
For run client use:
```
GL_Task_Wind_Client.exe
```
