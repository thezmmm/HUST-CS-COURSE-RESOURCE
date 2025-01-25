package Http;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class HttpClient {
    String request = null; //保存从客户端到Web服务器的HTTP请求报文
    String serverDomainName = null; //Web服务器的域名
    int srvProt = -1; //Web服务器的端口
    Socket socket = null; //Socket对象
    PrintWriter outToServer = null; //向Web服务器发送HTTP请求报文的输出流
    DataInputStream inFromServer = null; //读取Web服务器HTTP响应报文内容的输入流
    DataOutputStream outToFile = null; //将Web服务器HTTP响应报文内容写入另外一个文本文件的输出流
    /**
     * 返回Web服务器域名
     * @return the serverDomainName
     */
    public String getServerDomainName() {
        return serverDomainName;
    }

    /**
     * 设置Web服务器域名
     * @param serverDomainName the serverDomainName to set
     */
    public void setServerDomainName(String serverDomainName) {
        this.serverDomainName = serverDomainName;
    }

    /**
     * 返回Web服务器端口号
     * @return the srvProt
     */
    public int getSrvProt() {
        return srvProt;
    }

    /**
     * 设置Web服务器端口号
     * @param srvProt the srvProt to set
     */
    public void setSrvProt(int srvProt) {
        this.srvProt = srvProt;
    }

    /**
     * 判断是否连接到服务器
     * @return the connected
     */
    public boolean isConnected() {
        if(this.socket == null) return false;
        else return this.socket.isConnected();
    }

    /**
     * 设置HTTP请求报文的内容
     * @param request the request to set
     */
    public void setRequest(String request) {
        this.request = request;
    }

    /**
     * 构造函数
     * @param serverDomainName：服务器域名
     * @param srvProt： 服务器端口
     */
    public HttpClient(String serverDomainName,int srvProt){
        this.serverDomainName = serverDomainName;
        this.srvProt = srvProt;
    }

    /**
     * 连接到服务器
     */
    public void Connect(){
        if(!isConnected()){
            try {
                this.socket = new Socket(serverDomainName,srvProt); //创建Socket对象并连接到指定的域名和端口
                outToServer = new PrintWriter(this.socket.getOutputStream() ,true);
                inFromServer = new DataInputStream(this.socket.getInputStream());
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 断开与服务器的连接
     */
    public void Disconnect(){
        if(isConnected()){
            try {
                this.inFromServer.close();
                this.outToServer.close();
                this.socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 向服务器发送HTTP请求报文
     */
    public void sendHttptRequest(){
        outToServer.println(this.request);
    }

    /**
     * 得到服务器的HTTP响应报文并保存在文件里
     * @param fileName：文件名
     */
    public void getHttpResponse(String fileName){
        try {
            outToFile = new DataOutputStream(new FileOutputStream(fileName));
            Byte b = inFromServer.readByte(); //从服务器的应答中读入一个字节
            while(true){
                outToFile.writeByte(b); //将该字节写入到文件里
                b = inFromServer.readByte();
            }
        } catch(EOFException e){ //当到了服务器应答的末尾，会抛出EOFException异常
            System.out.println("End of Response!");
        }catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }finally{
            try {
                outToFile.close(); //关闭文件输出流
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        HttpClient httpClient = new HttpClient("www.163.com",80);
        httpClient.Connect();
        String request = "GET / HTTP/1.0\r\n" + //构造HTTP请求报文的首部
                "Host: www.163.com\r\n" +
                "Connection: close\r\n" +
                "User-agent: Mozilla/4.0\r\n" +
                "Accept-Language: zh-cn\r\n" +
                "Accept-Charset: GB2312,uft-8\r\n" +
                "\r\n";
        httpClient.setRequest(request);
        httpClient.sendHttptRequest(); //向服务器发出HTTP请求报文
        httpClient.getHttpResponse("response.txt"); //得到Web服务器的响应，并写入当前目录下的文件
        httpClient.Disconnect(); //断开连接
        System.out.println("OK");
    }
}
