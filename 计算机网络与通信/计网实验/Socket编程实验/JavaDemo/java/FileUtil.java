import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUtil {
    public static void main(String[] args) throws IOException {
        System.out.println(getFileContent("test.html"));
        System.out.println(new String(getFileContent("test.html"), StandardCharsets.UTF_8));
    }

    public static byte[] getFileContent(String fileName) throws IOException {
        Path filePath = Paths.get(Config.ROOT_DIR,fileName);
        byte[] fileContent = Files.readAllBytes(filePath);
        return fileContent;
    }

    public static boolean checkFile(String fileName){
        File file = new File(Config.ROOT_DIR+fileName);
        return file.exists();
    }

}
