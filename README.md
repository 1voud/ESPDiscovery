# ESPDiscovery
Discover ESP8266 in local network using UDP

Python code to discover ESP8266 in your network:
```
import netifaces
import socket
import select

for interface in netifaces.interfaces():
   ifaddrs=netifaces.ifaddresses(interface)
   if not netifaces.AF_INET in ifaddrs:
      continue
   for ifaddr in ifaddrs[netifaces.AF_INET]:
      if not "addr" in ifaddr or not "broadcast" in ifaddr:
         continue
      sock = socket.socket(
          socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
      sock.setblocking(0)
      sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
      sock.bind((ifaddr["addr"], 0))
      sock.sendto(bytes('!xESP8266', 'utf-8'), (ifaddr["broadcast"], 5000))

      while True:
         ready = select.select([sock], [], [], 3000)
         if not ready[0]:
            break
         data, addr = sock.recvfrom(1024)
         print(data, addr)

      sock.close()
```

Java code to discover ESP8266 in your network:
```
    import java.io.IOException;
    import java.net.DatagramPacket;
    import java.net.DatagramSocket;
    import java.net.InetAddress;

    public class DiscoverESP8266 {

        private static String datagram = "!xESP8266";
        private static byte[] broadcast = { (byte) 255, (byte) 255, (byte) 255, (byte) 255 };

        public static void main(String[] args) {
            DatagramSocket udpSocket = null;
            try {
                udpSocket = new DatagramSocket();
                udpSocket.setBroadcast(true);

                byte[] queryDatagram = datagram.getBytes();
                DatagramPacket sendPacket = new DatagramPacket(queryDatagram, queryDatagram.length);
                sendPacket.setAddress(InetAddress.getByAddress(broadcast));
                sendPacket.setPort(5000);
                udpSocket.send(sendPacket);

                byte[] buf = new byte[100];
                DatagramPacket receivePacket = new DatagramPacket(buf, buf.length);
                udpSocket.receive(receivePacket);

                String identifier = new String(buf, 0, receivePacket.getLength());
                System.out.println(String.format("Found ESP8266 with identifier \"%s\" at address: %s", identifier,
                        receivePacket.getSocketAddress()));
            } catch (IOException e) {
                System.err.println("Error: " + e.getMessage());
            } finally {
                udpSocket.close();
            }
        }
    }
```
