import org.junit.jupiter.api.Test;

/**
 * @Date: 2023-03-15
 * @author MYH
 */
public class Fan {

    // data
    final int SLOW = 1, MEDIUM=2, FAST=3;
    private int speed;
    private boolean on;
    private double radius;
    private String color;

    // getter and setter
    public int getSpeed() {
        return speed;
    }

    public void setSpeed(int speed) {
        if (speed != SLOW && speed != MEDIUM && speed != FAST) {
            throw new IllegalArgumentException("Speed must be one of the following values: SLOW, MEDIUM, or FAST.");
        }
        this.speed = speed;
    }

    public boolean isOn() {
        return on;
    }

    public void setOn(boolean on) {
        this.on = on;
    }

    public double getRadius() {
        return radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    // default constructor with default parameters
    Fan(){
        speed = SLOW;
        on = false;
        radius = 5.0;
        color = "blue";
    }

    @Override
    public String toString(){
        if(on) {
            return "speed:" + speed + " ,color:" + color + " ,radius:" + radius;
        }else{
            return "fan is off." +  " color:" + color + " ,radius:" + radius;
        }
    }

}

class FanTest {
    @Test
    public void test(){
        Fan fan1 = new Fan();
        Fan fan2 = new Fan();

        fan1.setSpeed(3);
        fan1.setRadius(10.0);
        fan1.setColor("yellow");
        fan1.setOn(true);
        System.out.println(fan1.toString());

        fan2.setSpeed(2);
        fan2.setRadius(5.0);
        fan2.setColor("blue");
        fan2.setOn(false);
        System.out.println(fan2.toString());
    }
}


