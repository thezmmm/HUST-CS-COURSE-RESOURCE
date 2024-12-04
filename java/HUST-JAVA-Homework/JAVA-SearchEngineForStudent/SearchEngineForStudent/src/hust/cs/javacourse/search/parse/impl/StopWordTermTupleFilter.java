package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StopWords;

import java.util.HashSet;
import java.util.Set;

/**
 * 基于停用词的过滤器
 * @author MYH
 */
public class StopWordTermTupleFilter extends AbstractTermTupleFilter {

    public StopWordTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
        this.stopWordsTable = new HashSet(StopWords.STOP_WORDS.length);

        for(int i = 0; i < StopWords.STOP_WORDS.length; ++i) {
            this.stopWordsTable.add(Config.IGNORE_CASE ? StopWords.STOP_WORDS[i].toLowerCase() : StopWords.STOP_WORDS[i]);
        }
    }

    private Set<String> stopWordsTable;
    /**
     * 获得下一个三元组
     *
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple termTuple = input.next();
        // 需要过滤, 跳过当前三元组返回下一个三元组
        while(termTuple!=null && this.stopWordsTable.contains(termTuple.term.getContent())){
            termTuple = input.next();
        }
        return termTuple;
    }
}
