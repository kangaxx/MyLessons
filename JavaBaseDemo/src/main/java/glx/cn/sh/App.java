package glx.cn.sh;

import glx.cn.sh.*;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        Child chd = new Child();
        chd.showName();
        chd.showNameExtends();
        int i = 3;
        System.out.println(i / 2);
        String s = "1111111111";
        long l = Long.parseLong(s);
        System.out.println(String.format("long l is : %d", l));
        String sl = String.valueOf(l);
        System.out.println(s);
    }

    

}
