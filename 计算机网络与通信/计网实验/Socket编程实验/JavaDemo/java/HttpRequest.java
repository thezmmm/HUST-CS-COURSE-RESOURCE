import java.util.HashMap;
import java.util.Map;

public class HttpRequest {

    private String method;
    private String path;
    private String httpVersion;
    private Map<String, String> headers;
    private String body;

    public HttpRequest(String method, String path, String httpVersion) {
        this.method = method;
        this.path = path;
        this.httpVersion = httpVersion;
        this.headers = new HashMap<>();
    }

    public String getMethod() {
        return method;
    }

    public String getPath() {
        return path;
    }

    public String getHttpVersion() {
        return httpVersion;
    }

    public void setHeader(String name, String value) {
        headers.put(name, value);
    }

    public String getHeader(String name) {
        return headers.get(name);
    }

    public void setBody(String body) {
        this.body = body;
    }

    public String getBody() {
        return body;
    }

    private Map<String,String> getHeaders(){
        return headers;
    }

    public String buildRequestString() {
        StringBuilder requestBuilder = new StringBuilder();

        // 构建请求行
        requestBuilder.append(this.getMethod()).append(" ")
                .append(this.getPath()).append(" ")
                .append(this.getHttpVersion()).append("\r\n");

        // 构建请求头部
        for (Map.Entry<String, String> entry : this.getHeaders().entrySet()) {
            requestBuilder.append(entry.getKey()).append(": ")
                    .append(entry.getValue()).append("\r\n");
        }

        // 构建空行
        requestBuilder.append("\r\n");

        // 构建请求体
        if (this.getBody() != null) {
            requestBuilder.append(this.getBody());
        }

        requestBuilder.append("\r\n");
        return requestBuilder.toString();
    }

    public static HttpRequest parseRequestString(String requestString) {
        HttpRequest request = null;

        // 将请求报文按行分割
        String[] lines = requestString.split("\r\n");

        // 解析请求行
        String[] requestLineTokens = lines[0].split(" ");
        if (requestLineTokens.length == 3) {
            String method = requestLineTokens[0];
            String path = requestLineTokens[1];
            String httpVersion = requestLineTokens[2];
            request = new HttpRequest(method, path, httpVersion);
        }

        // 解析请求头部
        int index = 1;
        while (index < lines.length && !lines[index].isEmpty()) {
            String[] headerTokens = lines[index].split(": ", 2);
            if (headerTokens.length == 2) {
                request.setHeader(headerTokens[0], headerTokens[1]);
            }
            index++;
        }

        // 解析请求体
        StringBuilder requestBodyBuilder = new StringBuilder();
        index++;
        while (index < lines.length) {
            requestBodyBuilder.append(lines[index]).append("\r\n");
            index++;
        }
        String requestBody = requestBodyBuilder.toString().trim();
        if (!requestBody.isEmpty()) {
            request.setBody(requestBody);
        }

        return request;
    }
}