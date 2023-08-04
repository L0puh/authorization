server:
	g++ m_server.cpp src/* -o server -lsqlite3
client:
	g++ m_client.cpp src/* -o client -lsqlite3
