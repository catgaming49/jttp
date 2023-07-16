cd "\julsvor text transfer protocol/jttp"
gcc .\src\server.c .\src\utils.c -I.\include  -lws2_32 -o .\bin\jttpd.exe
gcc .\src\client.c .\src\utils.c -I.\include  -lws2_32 -o .\bin\jttp.exe 