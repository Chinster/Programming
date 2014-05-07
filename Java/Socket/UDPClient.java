import java.io.*;
import java.net.*;
/**
 * UDPClient.java.
 *
 * @author Christopher Chin
 *
 */
public class UDPClient
{

    /**
     * Sends a line to a server, receives a modified line.
     * 
     * @param argv[] String
     */
    public static void main( String argv[] ) throws Exception
    {
        //Creates a reader of a stream of System.in (input from keyboard)
        BufferedReader inFromUser = new BufferedReader( new InputStreamReader(System.in) );
        //Opens a UDP socket
        DatagramSocket clientSocket = new DatagramSocket();
        //Gets address of a hostname through DNS
        InetAddress IPAddress = InetAddress.getByName( "hostname" );
        //Creates a byte for sending
        byte[] sendData = new byte[1024];
        //Creates a byte for receiving
        byte[] receiveData = new byte[1024];
        //Applies the input from user into the String variable
        String sentence = inFromUser.readLine();
        //Inserts the string variable into the send datagram
        sendData = sentence.getBytes();
        //Creates UDP packet for sending
        DatagramPacket sendPacket = new DatagramPacket( sendData, sendData.length, IPAddress, 9000 );
        //Sends the UDP packet through the socket
        clientSocket.send( sendPacket );
        //Creatse UDP packet for receiving
        DatagramPacket receivePacket = new DatagramPacket( receiveData, receiveData.length );
        //Applies the input from the server into the String variable
        String modifiedSentence = new String( receivePacket.getData() );
        //Prints modified input
        System.out.println( "FROM SERVER: " + modifiedSentence );
        //closes socket.
        clientSocket.close();
        
    }
}
