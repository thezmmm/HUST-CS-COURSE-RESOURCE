package homework.ch11_13.p4;

public class CompositeComponent extends Component{

    protected ComponentList childs;

    public CompositeComponent() {
        childs = new ComponentList();
    }

    public CompositeComponent(int id, String name, double price) {
        super(id, name, price);
        childs = new ComponentList();
    }

    @Override
    public void add(Component component) {
        childs.add(component);
    }

    @Override
    public void remove(Component component) {
        childs.remove(component);
    }

    @Override
    public double calcPrice() {
        int sum = 0;
        for(Component component : childs){
            sum += component.calcPrice();
        }
        return sum;
    }

    @Override
    public Iterator iterator() {
        return new CompositeIterator(childs);
    }

    @Override
    public String toString() {
        return "CompositeComponent{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", price=" + price +
                ", childs=" + childs +
                '}';
    }
}
