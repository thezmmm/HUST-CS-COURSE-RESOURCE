package hust.cs.javacourse.search.run;

import hust.cs.javacourse.search.index.AbstractIndex;
import hust.cs.javacourse.search.index.impl.DocumentBuilder;
import hust.cs.javacourse.search.index.impl.IndexBuilder;

import java.io.File;

public class TestBuildIndex {

    public static void main(String[] args) {

        // 输入文本文件路径
        String rootPath = "./text";

        // 文本文件转为文档对象
        DocumentBuilder documentBuilder = new DocumentBuilder();

        // 建立倒排索引
        String indexPath = "./index/index";
        File indexFile = new File(indexPath);
        IndexBuilder indexBuilder = new IndexBuilder(documentBuilder);
        AbstractIndex index = indexBuilder.buildIndex(rootPath);
        index.save(indexFile);

        // 输出倒排索引
        System.out.println("Inverted index: \n" + index);
    }
}
