package chapter30code;

public class SynThread {
    public static void main(String[] args) {

        Thread t1 = new Thread(() -> {
            // T1 执行代码
            System.out.println("T1 is running");
        });

        Thread t2 = new Thread(() -> {
            try {
                // 等待 T1 执行完成
                t1.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            // T2 执行代码
            System.out.println("T2 is running");
        });

        Thread t3 = new Thread(() -> {
            try {
                // 等待 T2 执行完成
                t2.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            // T3 执行代码
            System.out.println("T3 is running");
        });

        t1.start();
        t2.start();
        t3.start();

        try {
            // 等待 T3 执行完成
            t3.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // 主线程执行代码
        System.out.println("Main thread is running");
    }
}

