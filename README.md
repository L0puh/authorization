`client-server` implementation of authorization proccess.

## stack: 
- unix sockets 
- sqlite3 as a database 
- async cryptography with a secret key (in future)
- hashing a password (in future)

## compiling 
- *server*
    - `make server`
	- `g++ m_server.cpp src/* -o server -lsqlite3 && ./server` 
- *client*
   - `make client`
   - `g++ m_client.cpp src/* -o client -lsqlite3 && ./client`
