package homework.ch11_13.p2;

import java.util.ArrayList;
import java.util.List;

public class TaskServiceImpl implements TaskService{

    private List<Task> taskList;

    public TaskServiceImpl(){
        taskList = new ArrayList<Task>();
    }
    /**
     * 执行任务接口列表中的每个任务
     */
    @Override
    public void exeuteTasks() {
        for(Task task : taskList){
            task.execute();
        }
    }

    /**
     * 添加任务
     *
     * @param t 新添加的任务
     */
    @Override
    public void addTask(Task t) {
        taskList.add(t);
    }
}
