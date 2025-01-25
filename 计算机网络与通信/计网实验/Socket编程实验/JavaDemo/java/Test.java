//// MultiThreadsServer.java: The server can communicate with
//// multiple clients concurrently using the multiple threads
//import java.io.*;
//import java.net.*;
//import java.nio.file.Files;
//import java.nio.file.Path;
//import java.nio.file.Paths;
//import java.util.*;
//
//public class Test
//{
//    // Main method
//    public static void main(String[] args)
//    {
//        Scanner scan = new Scanner(System.in);
//        int port=8080;
//        String path="/source";
//        try
//        {
//            // Create a server socket
//            System.out.println("serve is running now.You need to init first");
//            System.out.print("port(default: 8000): ");
//            port = scan.nextInt();
//            scan.nextLine();
//            System.out.println("server bind to port:"+port+" successfully");
//            System.out.print("source(default: source): ");
//            path = scan.nextLine();
//            System.out.println("server bind to directory:"+path+" successfully");
//            System.out.println("server socket is running");
//            /**
//             * ���ɷ������˵�socket����
//             */
//            ServerSocket serverSocket = new ServerSocket(port);
//            // Number a thread
//            int i = 0;
//
//            while (true)
//            {
//                // Listen for a new connection request
//                Socket connectToClient = serverSocket.accept();
//                /**
//                 * ���ͻ�������ʱ����һ��socket����
//                 */
//                // Print the new connect number on the console
//                //System.out.println("Starting thread "+i);
//                System.out.println("����������:");
//                System.out.println("�ͻ��˵�ַ: " + connectToClient.getInetAddress());
//                System.out.println("�ͻ��˶˿�: " + connectToClient.getPort());
//                /**
//                 * �Ѷ��������߳�
//                 */
//                ThreadHandler thread = new ThreadHandler(connectToClient, i,path);
//                /**
//                 * �������߳�
//                 */
//                // Start the new thread
//                thread.start();
//
//                // Increment i to number the next connection
//                i++;
//            }
//        }
//        catch(IOException ex)
//        {
//            System.err.println(ex);
//        }
//    }
//}
//
//// Define the thread class for handling a new connection
//class ThreadHandler extends Thread
//{
//    private Socket connectToClient; // A connected socket
//    private int counter; // Number the thread
//    private String directory;
//    // Construct a thread
//    public ThreadHandler(Socket socket, int i,String path)
//    {
//        connectToClient = socket;
//        counter = i;
//        directory = path;
//    }
//    private static String getContentType(Path filePath) {
//        String fileName = filePath.getFileName().toString();
//        if (fileName.endsWith(".html")) {
//            return "text/html";
//        } else if (fileName.endsWith(".css")) {
//            return "text/css";
//        } else if (fileName.endsWith(".js")) {
//            return "application/javascript";
//        } else {
//            return "application/octet-stream"; // Ĭ�������ʹ�ö�������
//        }
//    }
//    // Implement the run() method for the thread
//    @Override
//    public void run()
//    {
//        try
//        {
//            // Create data input and print streams
////            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
////            OutputStream out = clientSocket.getOutputStream();
//            /**
//             * ��ʼ���������������
//             */
//            BufferedReader in = new BufferedReader(new InputStreamReader(connectToClient.getInputStream()));
//            OutputStream out = connectToClient.getOutputStream();
//            // Continuously serve the client
////            while (true)
////            {
////                // Receive data from the client in string
//////                StringTokenizer st = new StringTokenizer
//////                        (isFromClient.readLine());
//////                String requestLine = isFromClient.readLine();
//////                if(requestLine != null){
//////                    System.out.println("�ܵ�http���� "+requestLine);
//////
//////                    if(requestLine.startsWith("GET")){
//////                        String[] requestParts = requestLine.split(" ");
//////                        String requestUrl = requestParts[1];
//////
//////                        String filePath = directory+requestUrl;
//////                        File file = new File(filePath);
//////                        try {
//////                            FileInputStream fileInputStream = new FileInputStream(filePath);
//////                            byte[] buffer = new byte[1024];
//////                            int bytesRead;
//////
//////                            osToClient.write("HTTP/1.1 200 OK\r\n".getBytes());
//////                            osToClient.write("Content-Type: application/octet-stream\r\n".getBytes());
//////                            osToClient.write("\r\n".getBytes());
//////
//////                            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
//////                                osToClient.write(buffer, 0, bytesRead);
//////                            }
//////
//////                            fileInputStream.close();
//////                        } catch (FileNotFoundException e) {
//////                            // �ļ������ڣ�����404����
//////                            String notFoundResponse = "HTTP/1.1 404 Not Found\r\n"
//////                                    + "Content-Type: text/plain\r\n"
//////                                    + "\r\n"
//////                                    + "�ļ�δ�ҵ�: " + requestUrl;
//////
//////                            osToClient.write(notFoundResponse.getBytes("UTF-8"));
//////                        }
//////
//////                    }
//////
//////
//////                }
////                String requestLine = isFromClient.readLine();
////                if(requestLine != null){
////                    System.out.println("�յ�HTTP���� " + requestLine);
////
////                    if(requestLine.startsWith("GET")){
////                        String[] requestParts = requestLine.split(" ");
////                        String requestUrl = requestParts[1];
////                        String filepath = directory + requestUrl;
////                        File file = new File(filepath);
////                        try {
////                            FileInputStream fileInputStream = new FileInputStream(filepath);
////                            byte[] buffer = new byte[1024];
////                            int bytesRead;
////
////                            osToClient.write("HTTP/1.1 200 OK\r\n".getBytes());
////                            osToClient.write("Content-Type: application/octet-stream; charset=utf-8\r\n".getBytes());
////                            osToClient.write("\r\n".getBytes());
////
////                            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
////                                osToClient.write(buffer, 0, bytesRead);
////                            }
////
////                            fileInputStream.close();
////                        } catch(FileNotFoundException e){
////                            String notFoundResponse = "HTTP/1.1 404 Not Found\r\n"
////                                    + "Content-Type: text/plain; charset=utf-8\r\n"
////                                    + "\r\n"
////                                    + "�ļ�δ�ҵ�: " + requestUrl;
////
////                            osToClient.write(notFoundResponse.getBytes("UTF-8"));
////                        }
////                    }
////                }
////            }
//            String requestLine = in.readLine();
//            System.out.println("�ͻ�������: " + requestLine);
//            if (requestLine == null) {
//                throw new NullPointerException("requestLine is null");
//            }
//            String[] requestParts = requestLine.split(" ");
//            if (requestParts.length >= 2) {
//                String requestedFile = requestParts[1];
//                Path filePath = Paths.get(directory, requestedFile.substring(1));
//
//                if (Files.exists(filePath) && !Files.isDirectory(filePath)) {
//                    // ��ȡ�ļ����ݲ�������Ӧ
//                    byte[] fileContent = Files.readAllBytes(filePath);
//                    String contentType = getContentType(filePath);
//                    /**
//                     * ����ظ�����
//                     */
//                    String response = "HTTP/1.1 200 OK\r\n"
//                            + "Content-Type: " + contentType + "\r\n"
//                            + "Content-Length: " + fileContent.length + "\r\n"
//                            + "\r\n";
//                    out.write(response.getBytes("UTF-8"));
//                    out.write(fileContent);
//                    out.flush();
//                    System.out.println("�ظ��ɹ�");
//                } else {
//                    /**
//                     * ����404����
//                     */
//                    // �ļ������ڣ�����404��Ӧ
//                    String notFoundResponse = "HTTP/1.1 404 Not Found\r\n\r\n";
//                    out.write(notFoundResponse.getBytes("UTF-8"));
//                    out.flush();
//                    System.err.println("��Ӧ�ļ�������");
//                }
//            }
//
//            // �ر��������������
//            in.close();
//            out.close();
//        }
//        catch(IOException ex) {
//            System.err.println(ex);
//        } catch (NullPointerException e) {
//            // ���� NullPointerException ����� "404"
//            System.err.println("��Ӧ�ļ�������");
//        }
//    }
//}
////public class LocalFileServer {
////    public static void main(String[] args) throws IOException {
////        int port = 8080; // ѡ��һ���˿ںţ�ͨ��ʹ��8080��80
////
////        ServerSocket serverSocket = new ServerSocket(port);
////        System.out.println("HTTP���������ڼ����˿� " + port);
////
////        while (true) {
////            try (Socket clientSocket = serverSocket.accept()) {
////                BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
////                OutputStream out = clientSocket.getOutputStream();
////
////                String requestLine = in.readLine();
////                if (requestLine != null) {
////                    System.out.println("�յ�HTTP����: " + requestLine);
////
////                    if (requestLine.startsWith("GET")) {
////                        String[] requestParts = requestLine.split(" ");
////                        String requestUrl = requestParts[1];
////
////                        // �������URL·��ӳ�䵽�����ļ�·��
////                        String filePath = "webroot" + requestUrl;
////
////                        try {
////                            FileInputStream fileInputStream = new FileInputStream(filePath);
////                            byte[] buffer = new byte[1024];
////                            int bytesRead;
////
////                            out.write("HTTP/1.1 200 OK\r\n".getBytes());
////                            out.write("Content-Type: application/octet-stream\r\n".getBytes());
////                            out.write("\r\n".getBytes());
////
////                            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
////                                out.write(buffer, 0, bytesRead);
////                            }
////
////                            fileInputStream.close();
////                        } catch (FileNotFoundException e) {
////                            // �ļ������ڣ�����404����
////                            String notFoundResponse = "HTTP/1.1 404 Not Found\r\n"
////                                    + "Content-Type: text/plain\r\n"
////                                    + "\r\n"
////                                    + "�ļ�δ�ҵ�: " + requestUrl;
////
////                            out.write(notFoundResponse.getBytes("UTF-8"));
////                        }
////                    }
////                }
////            } catch (IOException e) {
////                System.err.println("����HTTP����ʱ����: " + e.getMessage());
////            }
////