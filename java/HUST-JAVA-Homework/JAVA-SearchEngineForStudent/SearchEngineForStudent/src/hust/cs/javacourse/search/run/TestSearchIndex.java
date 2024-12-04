package hust.cs.javacourse.search.run;

import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.impl.IndexSearcher;
import hust.cs.javacourse.search.query.impl.SimpleSorter;

import java.util.Arrays;
import java.util.Scanner;

/**
 * 测试搜索
 */
public class TestSearchIndex {
    /**
     *  搜索程序入口
     * @param args ：命令行参数
     */
    public static void main(String[] args){

        // 倒排索引文件路径
        String indexPath = "./index/index";

        // 构造IndexSearcher对象
        AbstractIndexSearcher indexSearcher = new IndexSearcher();
        indexSearcher.open(indexPath);

        // 输入查询字符串
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the query string: ");
        String queryString = scanner.nextLine();

        // 执行查询
        AbstractHit[] result = indexSearcher.search(new Term(queryString),new SimpleSorter());

        // 输出查询结果
        System.out.println("Search result: \n" + Arrays.toString(result));

    }
}
