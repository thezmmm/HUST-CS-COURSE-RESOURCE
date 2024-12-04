package homework.ch11_13.p4;

import java.util.ArrayList;
import java.util.List;

/**
 * @author MYH
 */
public class CompositeIterator implements Iterator{

    protected List<Iterator> iterators;

    public CompositeIterator(Iterator iterator){
        iterators = new ArrayList<>();
        iterators.add(iterator);
    }

    @Override
    public boolean hasNext() {
        while(!iterators.isEmpty()){
            if(iterators.get(0).hasNext()){
                break;
            }
            iterators.remove(0);
        }
        return !iterators.isEmpty();
    }

    @Override
    public Component next() {
        if(!hasNext()){
            return null;
        }
        Component component = iterators.get(0).next();
        iterators.add(component.iterator());
        return component;
    }
}
