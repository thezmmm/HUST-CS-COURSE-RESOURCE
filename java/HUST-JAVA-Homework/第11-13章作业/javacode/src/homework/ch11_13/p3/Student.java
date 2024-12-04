package homework.ch11_13.p3;

import java.util.Objects;

/**
 * @author MYH
 */
public class Student extends Person{
    private int studentId;
    private String department;
    private String classNo;

    public Student() {
    }

    public Student(String name, int age, int studentId, String department, String classNo) {
        super(name, age);
        this.studentId = studentId;
        this.department = department;
        this.classNo = classNo;
    }

    public int getStudentId() {
        return studentId;
    }

    public void setStudentId(int studentId) {
        this.studentId = studentId;
    }

    public String getDepartment() {
        return department;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public String getClassNo() {
        return classNo;
    }

    public void setClassNo(String classNo) {
        this.classNo = classNo;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name=" + getName() +
                ", age='" + getAge() + '\'' +
                ", studentId=" + studentId + '\'' +
                ", department='" + department + '\'' +
                ", classNo='" + classNo + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Student)) return false;
        if (!super.equals(o)) return false;
        Student student = (Student) o;
        return getStudentId() == student.getStudentId() && Objects.equals(getDepartment(), student.getDepartment()) && Objects.equals(getClassNo(), student.getClassNo());
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), getStudentId(), getDepartment(), getClassNo());
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        Student obj = (Student) super.clone();
        obj.department = new String(this.department);
        obj.classNo = new String(this.classNo);
        return obj;
    }
}
