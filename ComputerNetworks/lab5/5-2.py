import socket
import threading
def client(connectionSocket, addr):
	try:
		message = connectionSocket.recv(1024).decode()
		print (message)
		if message != '':
			filename = message.split()[1]
		print (filename)

		f =  open(''+filename[1:]) 
		#Отправляем в сокет одну строку HTTP-заголовка
		outputdata = f.read()

		#Отправляем содержимое запрошенного файла клиенту for
		connectionSocket.send("HTTP/1.1 200 OK\r\n\r\n".encode())

		for i in range(0, len(outputdata)):
			connectionSocket.send(outputdata[i].encode())
		connectionSocket.send("\r\n".encode()) 
		connectionSocket.close()
	except IOError:
		#Отправляем ответ об отсутствии файла на сервере
		connectionSocket.send("HTTP/1.1 404 Not Found\r\n\r\n".encode())
		connectionSocket.send("<html><head></head><body><h1>404 Not Found</h1></body></html>".encode())
		connectionSocket.close()

#Подготавливаем сокет сервера
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverport = 8080
serverSocket.bind(('', serverport))
serverSocket.listen()
print(serverSocket)

while True:
    #Устанавливаем соединение
    connectionSocket, addr = serverSocket.accept()
    print('Установлено соединение с', addr)
    client_handler = threading.Thread(target=client, args=(connectionSocket, addr))
    client_handler.start()

serverSocket.close()
