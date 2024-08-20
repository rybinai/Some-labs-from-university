#импортируем модуль для работы с сокетами
from socket import *
serverSocket = socket(AF_INET, SOCK_STREAM)
#Подготавливаем сокет сервера
serverport = 8080
serverSocket.bind((gethostname(), serverport))
print (serverSocket)
serverSocket.listen()
while True:
	#Устанавливаем соединение print 'Готов к обслуживанию...'
	connectionSocket, addr = serverSocket.accept()
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

connectionSocket.close()
