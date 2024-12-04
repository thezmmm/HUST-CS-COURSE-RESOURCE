public class TwoTuple<T1 extends Comparable<T1>,T2 extends Comparable<T2>> implements Comparable<TwoTuple<T1,T2>>{

    private T1 first;
    private T2 second;

    public TwoTuple(T1 first, T2 second) {
        this.first = first;
        this.second = second;
    }

    public T1 getFirst() {
        return first;
    }

    public void setFirst(T1 first) {
        this.first = first;
    }

    public T2 getSecond() {
        return second;
    }

    public void setSecond(T2 second) {
        this.second = second;
    }

    @Override
    public int compareTo(TwoTuple<T1, T2> o) {
        return first.compareTo(o.getFirst()) == 0 ?second.compareTo(o.getSecond()) : first.compareTo(o.getFirst());
    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof TwoTuple){
            return first.equals(((TwoTuple<?, ?>) obj).getFirst()) && second.equals(((TwoTuple<?, ?>) obj).getSecond());
        }
        return false;
    }

    @Override
    public String toString() {
        return "(" + first + "," + second + ")";
    }
}
