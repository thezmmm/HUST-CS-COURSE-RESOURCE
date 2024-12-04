package homework.ch11_13.p4;

import java.util.ArrayList;

/**
 * @author MYH
 */
public class ComponentList extends ArrayList<Component> implements Iterator{

    private int position;

    public ComponentList(){
        super();
        position = 0;
    }


    @Override
    public boolean hasNext() {
        if(position < this.size()){
            return true;
        }
        return false;
    }

    @Override
    public Component next() {
        if(hasNext()){
            return this.get(position++);
        }
        return null;
    }

}
