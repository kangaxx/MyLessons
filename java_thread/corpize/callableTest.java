package corpize;
import java.lang.*;
import java.util.*;
import java.util.concurrent.*;


public class callableTest implements Callable<Long>{
  private long _num;
  public callableTest(long num){
    _num = num;
  }

  @Override
  public Long call() throws Exception{
    System.out.println(String.format("system num : %d", _num));
    return (Long)_num;
  }

}


