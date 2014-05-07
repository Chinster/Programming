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
     * @param argv String
     */
    public static void main( String argv ) throws Exception
    {
        //Create a server socket that listens on port 8000
        ServerSocket welcomeSocket = new ServerSocket(8000);
        while(true)
        {
            //Creates a socket when a message comes from welcomeSocket
            Socket connectionSocket = welcomeSocket.accept();
            //Creates a reader on a stream reading what was received
            BufferedReader inFromClient = new BufferedReader( new InputStreamreader( connectionSocket.getInputStream() ) );
            //Creates a stream for the connection socket stream
            DataOutputStream outToClient = new DataOutputStream( connectionSocket.getOutputStream() ) ;
            //Gets the data from the reader of the input stream
            String clientSentence = inFromClient.readLine();
            //Capitalizes input
            String capitalizedSentence = clientSentence.toUpperCase() + '\n';
            //Sends the string into the output stream
            outToClient.writeBytes( capitalizedSentence );
        }
    }
}
