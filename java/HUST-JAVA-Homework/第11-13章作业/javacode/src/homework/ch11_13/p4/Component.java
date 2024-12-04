package homework.ch11_13.p4;

import java.util.Objects;

/**
 * @author MYH
 */
public abstract class Component {
    protected int id;
    protected String name;
    protected double price;

    public Component(){

    }
    public Component(int id, String name, double price) {
        this.id = id;
        this.name = name;
        this.price = price;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getPrice() {
        return calcPrice();
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public abstract void add(Component component);

    public abstract void remove(Component component);

    public abstract double calcPrice();

    public abstract Iterator iterator();

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Component)) return false;
        Component component = (Component) o;
        return getId() == component.getId() && Double.compare(component.getPrice(), getPrice()) == 0 && Objects.equals(getName(), component.getName());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getId(), getName(), getPrice());
    }

    @Override
    public String toString() {
        return "Component{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", price=" + price +
                '}';
    }

}
