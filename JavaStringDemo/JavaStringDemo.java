import java.lang.*;

/**
 *  Created by gxx on 2019/07/25
 */

public class JavaStringDemo {
  public static void main(String args[]) {
    String temp = "aaaa";

    System.out.println(String.format(" string [ %s ] size : %d ", temp, temp.length()));

    byte[] bytes = temp.getBytes();
    int i = 0;
    for (byte bit : bytes)
      System.out.println(String.format(" byte[%d] : %s", i++, bit));
    String test = "a,a,a,";
    System.out.println(test.substring(0, test.length() - 1));
    StringBuilder sb = new StringBuilder(30);
    for (int j = 0; j < 3; ++j){
      sb.append("a");
      sb.append(",");
    }
    System.out.println(sb.toString().substring(0, sb.length() - 1));
  }
}
