package glx.cn.sh;

import glx.cn.sh.*;

public class Parent{
  private static String name = "parent";
  public static void showName(){
    System.out.println(name);
  }

  public void showNameExtends(){
    System.out.println(name);
  }
}
