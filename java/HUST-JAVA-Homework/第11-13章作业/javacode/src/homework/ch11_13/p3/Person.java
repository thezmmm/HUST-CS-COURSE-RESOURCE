package homework.ch11_13.p3;

import java.util.Objects;

/**
 * @author MYH
 * @date 2023-03-25
 */
public class Person implements Cloneable{
    private String name;
    private int age;

    public Person(){

    }
    public Person(String name,int age){
        this.age = age;
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Person)) return false;
        Person person = (Person) o;
        return getAge() == person.getAge() && Objects.equals(getName(), person.getName());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getName(), getAge());
    }

    @Override
    public Object clone() throws CloneNotSupportedException{
        Person obj = (Person) super.clone();
        obj.name = new String(name);
        return obj;
    }

    public static void main(String[] args){
        Person person = new Person("1",1);
        try {
            System.out.println(((Person)person.clone()).getName() == person.getName());
        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }
    }
}

