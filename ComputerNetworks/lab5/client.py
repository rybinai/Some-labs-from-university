import socket
import sys

# python3 client.py хост_сервера порт_сервера имя_файла
def send_http_get_request(host, port, filename):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, port))

    request = f"GET /{filename} HTTP/1.1\r\nHost: {host}\r\n\r\n"
    client_socket.sendall(request.encode())
    print (request)

    response = b''
    while True:
        response2 = client_socket.recv(1024)
        response += response2
        if b'</html>' in response:
            break

    client_socket.close()

    return response.decode(errors='ignore')

if __name__ == "__main__":
    if len(sys.argv) != 4:
        sys.exit(1)

    host = sys.argv[1]
    port = int(sys.argv[2])
    filename = sys.argv[3]
    page = send_http_get_request(host, port, filename)
    print (page)    