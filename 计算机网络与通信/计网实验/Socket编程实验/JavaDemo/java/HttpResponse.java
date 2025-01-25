import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

public class HttpResponse {

    private String httpVersion;
    private int statusCode;
    private String statusMessage;
    private Map<String, String> headers;
    private byte[] body;

    public HttpResponse(String httpVersion, int statusCode, String statusMessage) {
        this.httpVersion = httpVersion;
        this.statusCode = statusCode;
        this.statusMessage = statusMessage;
        this.headers = new HashMap<>();
    }

    public String getHttpVersion() {
        return httpVersion;
    }

    public int getStatusCode() {
        return statusCode;
    }

    public String getStatusMessage() {
        return statusMessage;
    }

    public void setHeader(String name, String value) {
        headers.put(name, value);
    }

    public String getHeader(String name) {
        return headers.get(name);
    }

    public void setBody(byte[] body) {
        this.body = body;
    }

    public byte[] getBody() {
        return body;
    }

    public String buildResponseString() {
        StringBuilder sb = new StringBuilder();

        // 添加HTTP版本、状态码和状态消息
        sb.append(httpVersion).append(" ")
                .append(statusCode).append(" ")
                .append(statusMessage).append("\r\n");

        // 添加响应头
        for (Map.Entry<String, String> entry : headers.entrySet()) {
            String name = entry.getKey();
            String value = entry.getValue();
            sb.append(name).append(": ").append(value).append("\r\n");
        }

        // 添加空行和响应体
        sb.append("\r\n");
        if (body != null) {
            sb.append(body.toString());
        }
        sb.append("\r\n");
        return sb.toString();
    }

    public static HttpResponse parseResponseString(String responseString) {
        HttpResponse response = null;

        // 根据换行符分割响应字符串
        String[] lines = responseString.split("\r\n");

        // 解析第一行，获取HTTP版本、状态码和状态消息
        String[] firstLineParts = lines[0].split(" ");
        String httpVersion = firstLineParts[0];
        int statusCode = Integer.parseInt(firstLineParts[1]);
        String statusMessage = firstLineParts[2];

        // 创建HttpResponse对象
        response = new HttpResponse(httpVersion, statusCode, statusMessage);

        // 解析响应头
        int lineIndex = 1;
        while (lineIndex < lines.length && !lines[lineIndex].isEmpty()) {
            String[] headerParts = lines[lineIndex].split(": ");
            String name = headerParts[0];
            String value = headerParts[1];
            response.setHeader(name, value);
            lineIndex++;
        }

        // 解析响应体
        if (lineIndex < lines.length - 1) {
            StringBuilder bodyBuilder = new StringBuilder();
            for (int i = lineIndex + 1; i < lines.length; i++) {
                bodyBuilder.append(lines[i]).append("\r\n");
            }
            response.setBody(bodyBuilder.toString().getBytes(StandardCharsets.UTF_8));
        }

        return response;
    }

    public byte[] buildResponseBytes() {
        StringBuilder sb = new StringBuilder();

        // 添加HTTP版本、状态码和状态消息
        sb.append(httpVersion).append(" ")
                .append(statusCode).append(" ")
                .append(statusMessage).append("\r\n");

        // 添加响应头
        for (Map.Entry<String, String> entry : headers.entrySet()) {
            String name = entry.getKey();
            String value = entry.getValue();
            sb.append(name).append(": ").append(value).append("\r\n");
        }

        // 添加空行
        sb.append("\r\n");

        // 构建响应字节数组
        byte[] headerBytes = sb.toString().getBytes();
        byte[] responseBytes = new byte[headerBytes.length + body.length];
        System.arraycopy(headerBytes, 0, responseBytes, 0, headerBytes.length);
        System.arraycopy(body, 0, responseBytes, headerBytes.length, body.length);

        return responseBytes;
    }

}