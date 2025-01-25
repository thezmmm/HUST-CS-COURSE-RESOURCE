// Client.java: The client sends the input to the server and receives
// result back from the server
import java.io.*;
import java.net.*;
import java.util.*;

public class Client
{
    static Scanner scanner = new Scanner(System.in);

    // Main method
    public static void main(String[] args)
    {
        try
        {
            // Create a socket to connect to the server
            Socket connectToServer = new Socket(Config.HOST, Config.PORT);

            // Create a buffered input stream to receive data
            // from the server
            BufferedReader isFromServer = new BufferedReader(
                    new InputStreamReader(connectToServer.getInputStream()));

            // Create a buffered output stream to send data to the server
            PrintWriter osToServer =
                    new PrintWriter(connectToServer.getOutputStream(), true);

            // Continuously send radius and receive area
            // from the server
            while (true)
            {
                // 创建HttpRequest对象
                HttpRequest request = new HttpRequest("GET", "/test.html", "HTTP/1.1");

                // 设置请求头部
                request.setHeader("Host", "example.com");
                request.setHeader("Connection", "close");
//                request.setBody("Test Request Body\r\n");

                // 发送请求报文
                String requestString = request.buildRequestString();
                osToServer.write(requestString);
                osToServer.flush();
                System.out.println("Send HttpRequest: \n" + requestString);


//                 Receive and parse HttpResponse from the server in string.
                StringBuilder responseBuilder = new StringBuilder();
                String line;
                while((line=isFromServer.readLine()) != null && !line.isEmpty()){
                    responseBuilder.append(line).append("\r\n");
                }
                responseBuilder.append("\r\n");
                while((line=isFromServer.readLine()) != null && !line.isEmpty()){
                    responseBuilder.append(line).append("\r\n");
                }
                System.out.println("Receive HttpResponse from server: \n" + responseBuilder.toString());
                HttpResponse httpResponse = HttpResponse.parseResponseString(responseBuilder.toString());

                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
        catch (IOException ex)
        {
            System.err.println(ex);
        }
    }
}