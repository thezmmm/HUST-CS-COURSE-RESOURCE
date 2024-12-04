package homework.ch11_13.p3;

import java.util.Objects;

/**
 * @author MYH
 */
public class Faculty extends Person{
    private int facultyId;
    private String title;
    private String email;

    public Faculty(){

    }
    public Faculty(String name,int age,int facultyId,String title,String email){
        super(name,age);
        this.facultyId = facultyId;

        this.title = title;
        this.email = email;
    }

    public int getFacultyId() {
        return facultyId;
    }

    public void setFacultyId(int facultyId) {
        this.facultyId = facultyId;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    @Override
    public String toString() {
        return "Faculty{" +
                "name=" + getName() +
                ", age='" + getAge() + '\'' +
                ", facultyId=" + facultyId + '\'' +
                ", title='" + title + '\'' +
                ", email='" + email + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Faculty)) return false;
        if (!super.equals(o)) return false;
        Faculty faculty = (Faculty) o;
        return getFacultyId() == faculty.getFacultyId() && Objects.equals(getTitle(), faculty.getTitle()) && Objects.equals(getEmail(), faculty.getEmail());
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), getFacultyId(), getTitle(), getEmail());
    }

    @Override
    public Object clone() throws CloneNotSupportedException{
        Faculty obj = (Faculty) super.clone();
        obj.email = new String(email);
        obj.title = new String(title);
        return obj;
    }
    public static void main(String[] args){
        Faculty faculty = new Faculty("1",1,1,"1","1");
        try {
            System.out.println(((Faculty)faculty.clone()).getFacultyId() == faculty.getFacultyId());
        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }
    }
}
