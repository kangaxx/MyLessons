package corpize;

import java.lang.*;
public final class ossResult
{
  private String _name;
  private long _value;
  public ossResult(String name, long value){
    _name = name;
    _value = value;
  }

  public ossResult(){}

  public void setName(String name){ _name = name;}
  public void setValue(long value){ _value = value;}

  public String getName(){ return _name; }
  public long getValue() { return _value; }


}
