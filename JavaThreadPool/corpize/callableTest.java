package corpize;

import java.lang.*;
import java.util.*;
import java.util.concurrent.*;
import corpize.*;

public class callableTest implements Callable<ossResult>{
  private ossResult _result = new ossResult();
  public callableTest(ossResult o){
    _result.setName(o.getName());
  }

  @Override
  public ossResult call() throws Exception{
    System.out.println(String.format("system num : %s", _result.getName()));
    Thread.sleep(10000);
    _result.setValue((long)(Math.random() * (100 - 1) + 1));
    return _result;
  }

}


