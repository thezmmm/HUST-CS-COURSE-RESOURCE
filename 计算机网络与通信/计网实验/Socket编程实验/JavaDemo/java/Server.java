// Server.java: The server accepts data from the client, processes it
// and returns the result back to the client
import java.io.*;
import java.net.*;
import java.util.*;

public class Server
{
    // Main method
    public static void main(String[] args)
    {
        try
        {
            // Create a server socket
            ServerSocket serverSocket = new ServerSocket(8000);

            // Start listening for connections on the server socket
            Socket connectToClient = serverSocket.accept();

            // Create a buffered reader stream to get data from the client
            BufferedReader isFromClient = new BufferedReader(new
                    InputStreamReader(connectToClient.getInputStream()));

            // Create a buffered writer stream to send data to the client
            PrintWriter osToClient = new PrintWriter(
                    connectToClient.getOutputStream(), true);

            // Continuously read from the client and process it,
            // and send result back to the client
            while (true)
            {
                // Read a line and create a string tokenizer
                StringTokenizer st = new StringTokenizer
                        (isFromClient.readLine());

                // Convert string to double
                double radius = new Double(st.nextToken()).doubleValue();

                // Display radius on console
                System.out.println("radius received from client: "
                        +radius);

                // Compute area
                double area = radius*radius*Math.PI;

                // Send the result to the client
                osToClient.println(area);

                // Print the result to the console
                System.out.println("Area found: "+area);
            }
        }
        catch(IOException ex)
        {
            System.err.println(ex);
        }
    }
}