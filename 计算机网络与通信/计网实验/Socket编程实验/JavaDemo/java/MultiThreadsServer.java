// MultiThreadsServer.java: The server can communicate with
// multiple clients concurrently using the multiple threads

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class MultiThreadsServer
{
    // Main method
    public static void main(String[] args)
    {
        try
        {
            // Create a server socket
            ServerSocket serverSocket = new ServerSocket(Config.PORT);
            System.out.println(serverSocket.getInetAddress());
            System.out.println(serverSocket.getLocalPort());

            // Number a thread
            int i = 0;

            while (true)
            {
                // Listen for a new connection request
                Socket connectToClient = serverSocket.accept();

                // Print the new connect details on the console
                System.out.println("Accept new connection: ");
                System.out.println("Client Address: " + connectToClient.getInetAddress());
                System.out.println("Client Port: " + connectToClient.getPort());

                // Create a new thread for the connection
                ThreadHandler thread = new ThreadHandler(connectToClient, i);

                // Start the new thread
                thread.start();

                // Increment i to number the next connection
                i++;
            }
        }
        catch(IOException ex)
        {
            System.err.println(ex);
        }
    }
}

// Define the thread class for handling a new connection
class ThreadHandler extends Thread
{
    private Socket connectToClient; // A connected socket
    private int counter; // Number the thread

    // Construct a thread
    public ThreadHandler(Socket socket, int i)
    {
        connectToClient = socket;
        counter = i;
    }

    // Implement the run() method for the thread
    @Override
    public void run()
    {
        try
        {
            // Create data input and print streams
            BufferedReader isFromClient = new BufferedReader(
                    new InputStreamReader(connectToClient.getInputStream()));
            OutputStream osToClient = connectToClient.getOutputStream();

            // Continuously serve the client
            while (true) {
                // Receive and parse HttpRequest from the client in string.
                StringBuilder requestBuilder = new StringBuilder();
                String line;
                while((line=isFromClient.readLine()) != null && !line.isEmpty()){
                    requestBuilder.append(line).append("\r\n");
                }
                System.out.println("Receive HttpRequest from client: \n" + requestBuilder.toString());
                HttpRequest httpRequest = HttpRequest.parseRequestString(requestBuilder.toString());

                // create HttpResponse
                HttpResponse response;

                // handle request
                String fileName = httpRequest.getPath();
                if(FileUtil.checkFile(fileName)){
                    response = new HttpResponse("HTTP/1.1", 200, "OK");
                    // get file content
                    byte[] fileContent = FileUtil.getFileContent(fileName);
//                    String responseBody = new String(fileContent, StandardCharsets.UTF_8);
                    response.setHeader("Content-Type", ContentType.getContentType(fileName).getValue());
                    response.setHeader("Content-Length", String.valueOf(fileContent.length));
                    response.setBody(fileContent);
                }else{
                    // file not found
                    response = new HttpResponse("HTTP/1.1", 404, "NOT FOUND");
                    byte[] fileContent = FileUtil.getFileContent("404.html");
//                    String responseBody = new String(fileContent, StandardCharsets.UTF_8);
                    response.setHeader("Content-Type", ContentType.TEXT_HTML.getValue());
                    response.setHeader("Content-Length", String.valueOf(fileContent.length));
                    response.setBody(fileContent);
                    System.err.println("File: " + fileName + " NOT FOUND");
                }

                // send response to client
                String responseString = response.buildResponseString();
                osToClient.write(response.buildResponseBytes());
                osToClient.flush();
                isFromClient.close();
                osToClient.close();
                System.out.println("Send Response to Client: \n" + responseString);
            }
        } catch(IOException ex) {
            System.err.println(ex);
        }
    }
}