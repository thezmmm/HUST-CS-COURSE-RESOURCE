package SMTP;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

import sun.misc.BASE64Encoder;

public class SMTPClient {
    String mailContent = null; // 邮件正文
    String mailServer = null; // 发送者邮件服务器域名
    int port = -1; // 邮件服务器端口
    String mailSender = null; // 发送者邮箱
    String mailReceiver = null; // 邮件接收者信箱
    Socket socket = null; // Socket对象
    PrintWriter outToServer = null; // 向SMTP服务器发送报文的输出流
    BufferedReader inFromServer = null; // 从SMTP服务器接收响应的输入流
    String userName = null; // 邮件发送者的账号
    String pwd = null; // 邮件发送者的账号密码

    public SMTPClient(String mailServer, int port, String userName, String pwd) {
        this.mailServer = mailServer;
        this.port = port;
        this.userName = userName;
        this.pwd = pwd;
    }

    public String getMailContent() {
        return mailContent;
    }

    public void setMailContent(String mailContent) {
        this.mailContent = mailContent;
    }

    public String getMailServer() {
        return mailServer;
    }

    public void setMailServer(String mailServer) {
        this.mailServer = mailServer;
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public String getMailSender() {
        return mailSender;
    }

    public void setMailSender(String mailSender) {
        this.mailSender = mailSender;
    }

    public String getMailReceiver() {
        return mailReceiver;
    }

    public void setMailReceiver(String mailReceiver) {
        this.mailReceiver = mailReceiver;
    }

    boolean isConnected() {
        if (this.socket == null)
            return false;
        else
            return this.socket.isConnected();
    }

    public void connect() {
        if (!isConnected()) {
            try {
                this.socket = new Socket(mailServer, port);
                this.inFromServer = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
                this.outToServer = new PrintWriter(this.socket.getOutputStream(), true);
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void disconnect() {
        if (isConnected()) {
            try {
                this.inFromServer.close();
                this.outToServer.close();
                this.socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void getResponse() {
        try {
            String response = this.inFromServer.readLine();
            System.out.println("MAILServer: " + response);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendCommand(String cmd) {
        this.outToServer.println(cmd);
        System.out.println("Client: " + cmd);
    }

    public void sendMail() {
        try {
            getResponse();
            BASE64Encoder encoder = new BASE64Encoder();
            String encodedUserName = encoder.encode(this.userName.getBytes());
            String encodedPwd = encoder.encode(this.pwd.getBytes());

            String hostName = InetAddress.getLocalHost().getHostName();
            sendCommand("EHLO " + hostName);
            for (int i = 0; i < 5; i++) {
                getResponse();
            }

            sendCommand("AUTH LOGIN");
            getResponse();

            sendCommand(encodedUserName);
            getResponse();

            sendCommand(encodedPwd);
            getResponse();

            sendCommand("MAIL FROM: <" + this.mailSender + ">");
            getResponse();

            sendCommand("RCPT TO: <" + this.mailReceiver + ">");
            getResponse();

            sendCommand("DATA");
            getResponse();

            sendCommand(mailContent);
            sendCommand(".");
            sendCommand("QUIT");
            getResponse();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        SMTPClient smtpClient = new SMTPClient("smtp.163.com", 25, "hustnetwork", "network123");
        smtpClient.setMailSender("hustnetwork@163.com");
        smtpClient.setMailReceiver("hustnetwork@163.com");
        smtpClient.setMailContent("From: " + smtpClient.getMailSender() + "\n" + "To: " + smtpClient.getMailReceiver()
                + "\n" + "Subject: " + "Test" + "\n\n" +
                "Hi\nIt's a test mail!\n");
        smtpClient.connect();
        smtpClient.sendMail();
        smtpClient.disconnect();
        System.out.println("OK");
    }
}