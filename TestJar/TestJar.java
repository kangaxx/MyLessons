import java.util.Enumeration;
import java.util.Scanner;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;
import java.io.File;
 
/**
 * Created by on 2017/12/16.
 */
public class TestJar {
 
    public static void main(String args[]) {
        try {
            System.out.println("@write by Gu xinxin , usr arg -r to rescrue while local folder to find file that has classname and add one path if you want , ex.  #> java TestJar -r className or #> java TestJar -r className pathname");
            String path = ".";
            if (args[0].equals("-r")){
              File root = null;
              if (args.length > 2)
                root = new File(args[2]);
              else
                root = new File(".");
              if (root.exists()){
                for (File f : root.listFiles())
                {
                  if (f.isFile())
                    ifFileHasClass(f.getAbsolutePath(), args[1]);
                  else if (f.isDirectory())
                    rescureFolder(f, args[1]);
                }
              }  
            }
            else {	    
              JarFile jarFile = new JarFile(args[0]);
              Enumeration enu = jarFile.entries();
              while (enu.hasMoreElements()) {
                JarEntry jarEntry = (JarEntry) enu.nextElement();
                String name = jarEntry.getName();
                if (name.endsWith(".class")) {
                    System.out.println("name=" + name);
                }
              }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void rescureFolder(File root, String className){
       for (File f: root.listFiles()){
	 if (f.isFile())
	   ifFileHasClass(f.getAbsolutePath(), className);
	 else
	   rescureFolder(f, className);

       }
    }


    private static void ifFileHasClass(String fileName,String className){
       try{
//         System.out.println("try file :" + fileName);
         JarFile jf = new JarFile(fileName);
         Enumeration enu = jf.entries();
         while (enu.hasMoreElements()) {
           JarEntry jarEntry = (JarEntry) enu.nextElement();
           String name = jarEntry.getName();
           if (name.endsWith(".class")) {
              if (name.indexOf(className)!= -1)
                System.out.println("file[" + fileName + "] contain class[" + name + "] nearly target class: " + className + " !");

           }

         }
       } catch (Exception e) {
//         e.printStackTrace();
       }

    }
}
