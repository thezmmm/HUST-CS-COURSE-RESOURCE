package homework.ch11_13.p3;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * @author MYH
 */
public class Course implements Cloneable{

    private String courseName;
    private List<Person> students;
    private Person teacher;

    public Course(String courseName,Person teacher){
        this.courseName = courseName;
        this.teacher = teacher;
        students = new ArrayList<>();
    }

    public void register(Person student){
        if(!students.contains(student)){
            students.add(student);
        }
    }

    public String getCourseName() {
        return courseName;
    }

    public List<Person> getStudents() {
        return students;
    }

    public Person getTeacher() {
        return teacher;
    }

    public void unregister(Person student){
        if(students.contains(student)) {
            students.remove(student);
        }
    }

    public int getNumberOfStudent(){
        return students.size();
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        Course obj = (Course) super.clone();
        obj.courseName = new String(courseName);
        obj.teacher = (Person) teacher.clone();
        obj.students = new ArrayList<>(students.size());
        for(Person student : students){
            obj.students.add((Person) student.clone());
        }
        return obj;
    }

    @Override
    public String toString() {
        return "Course{" +
                "courseName='" + courseName + '\'' +
                ", students=" + students +
                ", teacher=" + teacher +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Course)) return false;
        Course course = (Course) o;
        return ((Course) o).getNumberOfStudent()==this.getNumberOfStudent()&& ((Course) o).getStudents().containsAll(this.getStudents()) && Objects.equals(getCourseName(), course.getCourseName()) && Objects.equals(getTeacher(), course.getTeacher());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getCourseName(), getStudents(), getTeacher());
    }
}
