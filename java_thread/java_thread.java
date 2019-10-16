import java.lang.*;
import java.util.*;
import java.util.concurrent.*;

import corpize.callableTest;

public final class java_thread
{
  public static void main(String[] args){
    try{
      callableTest thread = new callableTest(1L);
      ExecutorService executorService= Executors.newCachedThreadPool();
      Future<Long> future = executorService.submit(thread);
      System.out.println(String.format("get return from callable : %d", future.get()));
    } catch (InterruptedException e) {
      e.printStackTrace();
    } catch (ExecutionException e) {
      e.printStackTrace();
    }

  }



}


