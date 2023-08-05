server:
	g++ m_server.cpp src/* -o server -lsqlite3
	./server 
client:
	g++ m_client.cpp src/* -o client -lsqlite3
	./client 
