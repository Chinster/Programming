import java.io.*;
import java.net.*;
/**
 * TCPServer.java.
 *
 * @author Christopher Chin
 *
 */
public class TCPServer
{
    /**
     * MAIN.
     * 
     * @param args String[]
     */
    public static void main( String[] args ) throws Exception
    {
        //Create socket for server on port 9000
        DatagramSocket serverSocket = new DatagramSocket( 9000 );
        //creates bytes for sending and receiving
        byte[] receiveData = new byte[1024];
        byte[] sendData = new byte[1024];
        while(true)
        {
            //Create UDP packet from received data
            DatagramPacket receivePacket = new DatagramPacket( receiveData, receiveData.length );
            //Receive UDP packet on socket
            serverSocket.receive( receivePacket );
            //Apply UDP input into String variable
            String clientSentence = new String( receivePacket.getData() );
            //Capitalizes input
            String capitalizedSentence = clientSentence.toUpperCase() + '\n';
            //Get address from packet received
            InetAddress IPAddress = receivePacket.getAddress();
            //Get port from packet received
            int port = receivePacket.getPort();
            //Create byte to send from String variable
            sendData = capitalizedSentence.getBytes();
            //Create send UDP packet
            DatagramPacket sendPacket = new DatagramPacker( sendData, sendData.length, IPAddress, port );
            //Send packet into server socket
            serverSocket.send( sendPacket );
        }
    }
}
