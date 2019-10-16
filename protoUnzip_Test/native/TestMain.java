import org.apache.aichina.common.java.*;
public class TestMain{
  static {
    System.loadLibrary("protoUnzip");
  }

  public static native String getWords();
  public static native info unzipInfo(String input);
  public static native void unzipNull();
  public static void main(String [] arg){
//    System.out.print(System.getProperty("java.library.path"));
    String words = getWords();
    int num = 10000 * 1000;
    final int num_const = num;
    common_java_timer jt = new common_java_timer();
    while (num-- >= 0){
      //info ifo = unzipInfo(words);
      unzipNull();
      if (num % 100000 == 0){
        System.out.print(String.format("   "));
        System.out.print(String.format("   "));
        System.out.print(String.format("   "));
      }
    }
    jt.setEnd();
    System.out.println("run unzip begin at: " + jt.getBeginDate());
    System.out.println("run unzip end at " + jt.getEndDate());
    System.out.println(String.format("run unzip loop [%d] time : %s ", num_const, jt.duration()));

  }
}


