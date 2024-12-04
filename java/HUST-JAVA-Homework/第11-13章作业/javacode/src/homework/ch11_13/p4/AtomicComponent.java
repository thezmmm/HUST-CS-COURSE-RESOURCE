package homework.ch11_13.p4;


/**
 * @author MYH
 */
public class AtomicComponent extends Component{

    public AtomicComponent() {
    }

    public AtomicComponent(int id, String name, double price) {
        super(id, name, price);
    }

    @Override
    public void add(Component component) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void remove(Component component) {
        throw new UnsupportedOperationException();
    }

    @Override
    public double calcPrice() {
        return price;
    }

    @Override
    public Iterator iterator() {
        return new NullIterator();
    }
}
