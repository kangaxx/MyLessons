public class TestMain{
  static {
    System.loadLibrary("native");
  }

  public static native info getInfo(String input);
  public static void main(String [] arg){
//    System.out.print(System.getProperty("java.library.path"));
    info theInfo = getInfo("input");
    System.out.println(theInfo._name);
  }
}


