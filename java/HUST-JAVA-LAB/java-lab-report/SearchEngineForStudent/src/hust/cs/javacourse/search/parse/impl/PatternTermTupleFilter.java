package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;

/**
 * 基于正则表达式的过滤器
 * @author MYH
 */
public class PatternTermTupleFilter extends AbstractTermTupleFilter {
    public PatternTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
        this.termPattern = Config.TERM_FILTER_PATTERN;
    }

    private String termPattern;

    /**
     * 获得下一个三元组
     *
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple termTuple = input.next();
        // 需要过滤, 跳过当前三元组返回下一个三元组
        while(termTuple!=null && !termTuple.term.getContent().matches(termPattern)){
            termTuple = input.next();
        }
        return termTuple;
    }
}
