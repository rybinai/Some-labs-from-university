import socket
import ssl
import base64

# Сообщения
header = "\r\n Beautiful volcano"
msg = "\r\n Check out the beautiful volcano "
endmsg = "\r\n.\r\n"

# Выбираем почтовый сервер
mailserver = 'smtp.gmail.com'

# SSL подключение 
sslconnect = ssl.create_default_context()
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSocket = sslconnect.wrap_socket(clientSocket, server_hostname=mailserver)
clientSocket.connect((mailserver, 465))

# Ответ от сервера
recv = clientSocket.recv(1024)
if recv[:3] != b'220':
    print ('Код 220 от сервера не получен.')
    print (recv)
    exit() 

# Отправляем команду HELO и выводим ответ сервера.
heloCommand = 'HELO \r\n'
clientSocket.send(heloCommand.encode())
recv1 = clientSocket.recv(1024)
print (recv1)
if recv1[:3] != b'250':
    print ('Код 250 от сервера не получен.')
    exit()

# Авторизация
adrec = ''
password = ''
base64_str = ("\x00" + adrec + "\x00" + password).encode()

base64_str = base64.b64encode(base64_str)

# Отправляем команду AUTH и выводим ответ сервера.
authCommand = "AUTH PLAIN ".encode() + base64_str + "\r\n".encode()
clientSocket.send(authCommand)
recv7 = clientSocket.recv(1024)
if recv7[:3] != b'235':
    print (('Код 235 от сервера не получен.'))
    print (recv7)
    exit()

# Отправляем команду MAIL FROM и выводим ответ сервера.
mailfromCommand = 'MAIL FROM: <>\r\n'
clientSocket.send(mailfromCommand.encode())
recv2 = clientSocket.recv(1024)
print (recv2)
if recv2[:3] != b'250':
    print ('Код 250 от сервера не получен.')
    exit()

# Отправляем команду RCPT TO и выводим ответ сервера.
rcpttoCommand = 'RCPT TO: <>\r\n'
clientSocket.send(rcpttoCommand.encode())
recv3 = clientSocket.recv(1024)
print (recv3)
if recv3[:3] != b'250':
    print ('Код 250 от сервера не получен.')
    exit()

# Отправляем команду DATA и выводим ответ сервера.
dataCommand = 'DATA\r\n'    
clientSocket.send(dataCommand.encode())
recv4 = clientSocket.recv(1024)
print (recv4)
if recv4[:3] != b'354':
    print ('Код 354 от сервера не получен.')
    exit()
    
# Отправляем тему/адрес отправителя/адрес получателя
clientSocket.send(("Content-Type: multipart/mixed; boundary=frontier\r\n").encode())
email_message_1 = f"From: \r\nTo: \r\nSubject: {header}\r\n\r\n"
clientSocket.send(email_message_1.encode())
clientSocket.send(("--frontier\r\n").encode())
clientSocket.send(("Content-Type: text/plain;\r\n").encode())
email_message = f"{msg}\r\n"
clientSocket.send(email_message.encode())
clientSocket.send(("--frontier\r\n").encode())
clientSocket.send(("Content-Disposition: attachment; filename=vulkan.png\r\n").encode()) 
clientSocket.send(("Content-Transfer-Encoding: base64\r\n").encode())
clientSocket.send(("Content-Type: image/png\r\n\r\n").encode())
with open("vulkan.png", "rb") as image:
         clientSocket.send(base64.b64encode(image.read() + '\r\n'.encode()))
         image.close()
clientSocket.send(("--frontier--\r\n").encode())
clientSocket.send(endmsg.encode())

recv5 = clientSocket.recv(1024)
print(recv5)
if recv5[:3] != b'250':
    print('Код 250 от сервера не получен.')
    exit()

# Отправляем команду QUIT, получаем ответ сервера
quitCommand = 'QUIT\r\n'
clientSocket.send(quitCommand.encode())
recv6 = clientSocket.recv(1024)
print(recv6)
if recv6[:3] != b'221':
    print ('Код 221 от сервера не получен.')
    print(recv6)
    exit()

# Закрываем соединение.
clientSocket.close()
