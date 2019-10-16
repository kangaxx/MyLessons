package glx.cn.sh;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import glx.cn.sh.TestData;
import com.google.protobuf.InvalidProtocolBufferException;
import com.googlecode.protobuf.format.JsonFormat;
import com.googlecode.protobuf.format.JsonFormat.ParseException;
import glx.cn.sh.TestData.*;

/**
 * Hello world!
 *
 */
public class App 
{
  public static void main( String[] args )
  {
    try{
      LogGroup.Builder builder = LogGroup.newBuilder();
      //String jsonFormat = "{\"LogGroup\":{\"Site\":{\"name\":\"site name\",\"id\":1},\"LogTag\":[{\"Key\":1,\"Value\":154}],\"name\":\"proto_test\"}}";
      builder.setName("LG");
      builder.addTags(LogTag.newBuilder().setKey(1).setValue(100));
      builder.addSite(Site.newBuilder().setName("st").setId(666));
      
      byte[] userBytes = builder.build().toByteArray();
      for(byte b: userBytes){
        System.out.println(b);
      }
      
      LogGroup lg = LogGroup.parseFrom(userBytes);
      System.out.println(String.format("LogGroup...... name : %s", lg.getName()));
      System.out.println("     |");
      System.out.println("     |");
      for (LogTag theTag : lg.getTagsList()){
        System.out.println("     |");
        System.out.println("     |");
        System.out.println("     --Tag......Key : " + theTag.getKey());
        System.out.println("     --Tag......Value : " + theTag.getValue());
      }
      for (Site st : lg.getSiteList()){
        System.out.println("     |");
        System.out.println("     |");
        System.out.println("     --Site......name : " + st.getName());
        System.out.println("     --Site......id : " + st.getId());
      }

      //writeBytesToFile(userBytes);
    }catch(Exception e){
      e.printStackTrace();
    } 
  }   
                                                                             
  private static void writeBytesToFile(byte[] bs) throws IOException{
    OutputStream out = new FileOutputStream("/Users/kangaxxlion/Documents/log");
    out.write(bs);    
    out.close(); 
  }
}
