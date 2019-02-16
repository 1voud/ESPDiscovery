# ESPDiscovery
Discover ESP8266 in local network using UDP

```
Java code to discover ESP8266 in your network:

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
