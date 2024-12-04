package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.Sort;

import java.io.File;
import java.util.*;

/**
 * @author MYH
 */
public class IndexSearcher extends AbstractIndexSearcher {

    /**
     * 从指定索引文件打开索引，加载到index对象里. 一定要先打开索引，才能执行search方法
     *
     * @param indexFile ：指定索引文件
     */
    @Override
    public void open(String indexFile) {
        index.load(new File(indexFile));
        index.optimize();
    }

    /**
     * 根据单个检索词进行搜索
     *
     * @param queryTerm ：检索词
     * @param sorter    ：排序器
     * @return ：命中结果数组
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm, Sort sorter) {
        AbstractPostingList postingList = index.search(queryTerm);
        if(postingList == null){
            return null;
        }
        List<AbstractHit> hits = new ArrayList<>();
        for(int i = 0;i < postingList.size();i++){
            AbstractPosting posting = postingList.get(i);
            AbstractHit hit = new Hit(posting.getDocId(),index.getDocName(posting.getDocId()));
            hit.getTermPostingMapping().put(queryTerm,posting);
            if(sorter != null){
                hit.setScore(sorter.score(hit));
            }
            hits.add(hit);
        }
        if(sorter != null){
            sorter.sort(hits);
        }
        return hits.toArray(new AbstractHit[0]);
    }

    /**
     * 根据二个检索词进行搜索
     *
     * @param queryTerm1 ：第1个检索词
     * @param queryTerm2 ：第2个检索词
     * @param sorter     ：    排序器
     * @param combine    ：   多个检索词的逻辑组合方式
     * @return ：命中结果数组
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm1, AbstractTerm queryTerm2, Sort sorter, LogicalCombination combine) {
        AbstractHit[] hits1 = search(queryTerm1,sorter);
        AbstractHit[] hits2 = search(queryTerm2,sorter);
        AbstractHit[] finalHits = null;

        if (combine == LogicalCombination.AND) {
            finalHits = combineAnd(hits1,hits2,sorter);
        } else if (combine == LogicalCombination.OR) {
            finalHits = combineOr(hits1,hits2,sorter);
        }
        return finalHits;
    }

    private AbstractHit[] combineAnd(AbstractHit[] hits1,AbstractHit[] hits2,Sort sorter){
        List<AbstractHit> finalHits = new ArrayList<>();
        for(AbstractHit hit1 : hits1){
            for(AbstractHit hit2 : hits2){
                if(hit1.getDocId() == hit2.getDocId()){
                    Map<AbstractTerm,AbstractPosting> map = hit1.getTermPostingMapping();
                    map.putAll(hit2.getTermPostingMapping());
                    AbstractHit hit = new Hit(hit1.getDocId(), hit1.getDocPath(),map);
                    if(sorter != null){
                        hit.setScore(sorter.score(hit));
                    }
                    finalHits.add(hit);
                    break;
                }
            }
        }
        if(sorter != null){
            sorter.sort(finalHits);
        }
        return finalHits.toArray(new AbstractHit[0]);
    }
    private AbstractHit[] combineOr(AbstractHit[] hits1,AbstractHit[] hits2,Sort sorter){
        for(AbstractHit hit : hits1){
            if(sorter != null){
                hit.setScore(sorter.score(hit));
            }
        }
        List<AbstractHit> finalHits = new ArrayList<>(Arrays.asList(hits1));
        for(AbstractHit hit2:hits2){
            boolean flag = true;
            for(AbstractHit hit1 : hits1){
                if(hit1.getDocId() == hit2.getDocId()){
                    hit1.getTermPostingMapping().putAll(hit2.getTermPostingMapping());
                    if(sorter != null){
                        hit1.setScore(sorter.score(hit1));
                    }
                    flag = false;
                    break;
                }
            }
            if(flag){
                if(sorter != null){
                    hit2.setScore(sorter.score(hit2));
                }
                finalHits.add(hit2);
            }
        }
        if(sorter != null){
            sorter.sort(finalHits);
        }
        return finalHits.toArray(new AbstractHit[0]);
    }
}
