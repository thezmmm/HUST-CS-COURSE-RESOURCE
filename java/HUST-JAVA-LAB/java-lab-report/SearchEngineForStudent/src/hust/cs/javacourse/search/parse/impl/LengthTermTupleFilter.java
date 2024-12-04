package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StopWords;

/**
 * 基于单词长度的过滤器
 * @author MYH
 */
public class LengthTermTupleFilter extends AbstractTermTupleFilter {
    public LengthTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
        this.maxLength = Config.TERM_FILTER_MAXLENGTH;
        this.minLength = Config.TERM_FILTER_MINLENGTH;
    }

    /**
     * 过滤的长度
     */
    private int minLength;
    private int maxLength;

    /**
     * 获得下一个三元组
     *
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple termTuple = input.next();
        // 需要过滤, 跳过当前三元组返回下一个三元组
        while(termTuple!=null && (termTuple.term.getContent().length() < minLength || termTuple.term.getContent().length() > maxLength)){
            termTuple = input.next();
        }
        return termTuple;
    }
}
