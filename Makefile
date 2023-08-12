server:
	g++ m_server.cpp src/server.cpp src/log.cpp src/database.cpp src/client.cpp  src/sha2/sha2.cpp -o server -lsqlite3
	./server 
client:
	g++ m_client.cpp src/server.cpp src/log.cpp src/database.cpp src/client.cpp  src/sha2/sha2.cpp -o client -lsqlite3
	./client 
