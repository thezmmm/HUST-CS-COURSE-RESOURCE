package chapter30code;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * 一个线程安全同步队列，模拟多线程环境下的生产者消费者机制
 * 一个生产者线程通过 produce 方法向队列里产生元素
 * 一个消费者线程通过 consume 方法从队列里消费元素
 * @param <T> 元素类型
 */
public class SyncQueue1<T> {
    /**
     * 保存队列元素
     */
    private ArrayList<T> list = new ArrayList<>();

    /**
     * produce和consume互斥锁
     */
    private final Object lock = new Object();


//TODO 这里加入需要的数据成员
    /**
     * 生产数据
     * @param elements 生产出的元素列表，需要将该列表元素放入队列
     * @throws InterruptedException
     */
    public void produce(List<T> elements) throws InterruptedException {
//TODO 这里需要实现代码
        synchronized (lock){
            while(list.size() != 0){
                lock.wait();
            }
            list.addAll(elements);
            System.out.println("Produce elements: " + elements);
            lock.notifyAll();
        }
    }
    /**
     * 消费数据
     * @return 从队列中取出的数据
     * @throws InterruptedException
     */
    public List<T> consume() throws InterruptedException {
//TODO 这里需要实现代码
        synchronized (lock){
            while(list.size() == 0){
                lock.wait();
            }
            List<T> ret = new ArrayList<>(list);
            list.clear();
            lock.notifyAll();
            System.out.println("Consume elements: " + ret);
            return ret;
        }
    }
}