package homework.ch11_13.p2;

public class Test {
    public static void main(String[] args){
        Task task1 = new TaskEating();
        Task task2 = new TaskPlay();
        Task task3 = new TaskStudy();
        TaskService ts = new TaskServiceImpl();
        ts.addTask(task1);
        ts.addTask(task2);
        ts.addTask(task3);
        ts.exeuteTasks();
    }
}
