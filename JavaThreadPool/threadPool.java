import java.util.*;
import java.util.concurrent.*;

import corpize.callableTest;
import corpize.*;
public final class threadPool
{
  public static void main(String[] args){
    ThreadPoolExecutorHelper helper = new ThreadPoolExecutorHelper();
    for (long i = 0L; i < 10L; i++){
      ossResult or = new ossResult(String.format("oss %d", i), 0L);
      callableTest task = new callableTest(or);
      System.out.println(String.format("get callable result : %d",helper.submit(task)));
    }
  }


    
}
