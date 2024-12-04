package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleScanner;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.FileUtil;
import hust.cs.javacourse.search.util.StringSplitter;

import java.io.*;
import java.util.LinkedList;
import java.util.Locale;
import java.util.Queue;

/**
 * @author MYH
 */
public class TermTupleScanner extends AbstractTermTupleScanner {
    /**
     * 缺省构造函数
     */
    public TermTupleScanner() {
    }

    /**
     * 构造函数
     *
     * @param input ：指定输入流对象，应该关联到一个文本文件
     */
    public TermTupleScanner(BufferedReader input) {
        super(input);
        splitter = new StringSplitter();
        splitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
    }

    StringSplitter splitter;

    /**
     *  存储缓冲区内的tuple
     */
    private Queue<AbstractTermTuple> tupleQueue = new LinkedList<>();

    /**
     * term 在当前文档中的位置
     */
    private int curPos;
    /**
     * 获得下一个三元组
     *
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() {
        if(tupleQueue.isEmpty()){
            String line = null;
            try {
                line = input.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            if(line != null){
                line = line.trim();
                line = line.toLowerCase();
                for(String str : splitter.splitByRegex(line)){
                    AbstractTerm term = new Term(str);
                    AbstractTermTuple termTuple = new TermTuple(term,curPos++);
                    tupleQueue.add(termTuple);
                }
                // 考虑出现空行的情况
                if(tupleQueue.isEmpty()){
                    return next();
                }
            }
        }
        return tupleQueue.poll();
    }

    public static void main(String[] args){
        BufferedReader input = null;
        try {
            input = new BufferedReader(new FileReader("E:\\Content\\JavaCode\\Java新实验一\\SearchEngineForStudent\\text\\1.txt"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        AbstractTermTupleScanner scanner = new TermTupleScanner(input);
        AbstractTermTuple tuple;
        while((tuple = scanner.next()) != null){
            System.out.println(tuple);
        }
//        System.out.println(Config.class.getResource("").getPath());
//        String filePath = "E:/Content/JavaCode/Java新实验一/实验测试程序包/Experiment1Test/test/config/"+"../"+"/text/"+"2.txt";
//        String content = FileUtil.read(filePath);
//        System.out.println(content);
//        StringSplitter splitter = new StringSplitter();
//        splitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
//        splitter.splitByRegex(content);
    }
}
