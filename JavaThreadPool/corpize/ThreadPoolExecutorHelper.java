package corpize;

import java.lang.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.*;

public class ThreadPoolExecutorHelper
{
  private ThreadPoolExecutor _executor;
  private BlockingQueue<Runnable> _workQueue = new ArrayBlockingQueue<>(2);
  private List<ossResult> _result = new ArrayList<ossResult>();  
  public ThreadPoolExecutorHelper(){
    int corePoolSize = 2;
    int maximumPoolSize = 3;
    long keepAliveTime = 10; //空闲线程保存时间
    ThreadFactory threadFactory = new NameThreadFactory();
    RejectedExecutionHandler handler = new MyIgnorePolicy();

    TimeUnit unit = TimeUnit.SECONDS; //空闲线程保存时间的单位
    
    _executor = new ThreadPoolExecutor(corePoolSize, maximumPoolSize, keepAliveTime, unit,
                    _workQueue, threadFactory, handler);
    _executor.prestartAllCoreThreads(); // 预启动所有核心线程
  }

  public ossResult submit(corpize.callableTest task){
    try {
      Future<ossResult> result = _executor.submit(task);
      return result.get();
    } catch (InterruptedException e) {
      e.printStackTrace();
    } finally {
      return null;
    }
  }

  public List<ossResult> invokeAll(List<callableTest> tasks) 
                                      throws InterruptedException, ExecutionException {
    List<Future<ossResult>> tasksResult = _executor.invokeAll(tasks);
    List<ossResult> resultList = new ArrayList<ossResult>();
    for (Future<ossResult> future : tasksResult) {
      resultList.add(future.get());
    }
    return resultList;
  }

  public <V> List<V> invokeAllTemplate(List<? extends Callable<V>> tasks)
                  throws InterruptedException, ExecutionException {
    List<Future<V>> tasksResult = _executor.invokeAll(tasks);
    List<V> resultList = new ArrayList<V>();
    for (Future<V> future : tasksResult) {
      resultList.add(future.get());
    }
    return resultList;
  }

  static class NameThreadFactory implements ThreadFactory {
    private final AtomicInteger mThreadNum = new AtomicInteger(1);
    @Override
    public Thread newThread(Runnable r) {
      Thread t = new Thread(r, "my-thread-" + mThreadNum.getAndIncrement());
      System.out.println(t.getName() + " has been created");
      return t;
    }
  }

  public static class MyIgnorePolicy implements RejectedExecutionHandler {
    public void rejectedExecution(Runnable r, ThreadPoolExecutor e) {
      doLog(r, e);
    }

    private void doLog(Runnable r, ThreadPoolExecutor e) {
      // 可做日志记录等
      System.err.println( r.toString() + " rejected");
      System.out.println("completedTaskCount: " + e.getCompletedTaskCount());
    }
  }

}
