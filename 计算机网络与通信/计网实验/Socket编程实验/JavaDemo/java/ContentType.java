/**
 * @author MYH
 * @date 2023-10-03
 */

public enum ContentType {
    TEXT_HTML("text/html"),
    TEXT_PLAIN("text/plain"),
    APPLICATION_JSON("application/json"),
    APPLICATION_PDF("application/pdf"),
    IMAGE_JPEG("image/jpeg"),
    IMAGE_PNG("image/png"),
    APPLICATION_OCTET_STREAM("application/octet-stream");

    private final String value;

    ContentType(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    public static ContentType getContentType(String fileName) {
        if(fileName.endsWith(".html")){
            return TEXT_HTML;
        }else if(fileName.endsWith(".png")){
            return IMAGE_PNG;
        }else if(fileName.endsWith(".jpg")){
            return IMAGE_JPEG;
        }
        else {
            return APPLICATION_OCTET_STREAM;
        }
    }
}