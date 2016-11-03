import java.lang.reflect.Constructor;  
import java.lang.reflect.Field;  
import java.lang.reflect.Method;  
  
public class ReflectTester  
{  
    // 该方法实现对Custmoer对象的拷贝  
    public Object copy(Object object) throws Exception  
    {  
        Class<?> classType = object.getClass();  
  
        // Constructor cons = classType.getConstructor(new Class[]{});  
        //        
        // Object obj = cons.newInstance(new Object[]{});  
        // 以上两行代码等价于下面一行，不带参数  
        // Object obj2 = classType.newInstance();  
        Object objectCopy = classType.getConstructor(new Class[] {}).newInstance(new Object[] {});  
          
        Field[] fields = classType.getDeclaredFields();  
          
        for (Field field : fields)  
        {  
            String name = field.getName();  
            String firstLetter = name.substring(0, 1).toUpperCase();  
            String getMethodName = "get" + firstLetter + name.substring(1);  
            String setMethodName = "set" + firstLetter + name.substring(1);  
  
            Method getMethod = classType.getMethod(getMethodName,new Class[] {});  
            Method setMethod = classType.getMethod(setMethodName,new Class[] { field.getType() });  
  
            Object value = getMethod.invoke(object, new Object[] {});  
  
            setMethod.invoke(objectCopy, new Object[] { value });  
        }  
        return objectCopy;  
    }  
  
    public static void main(String[] args) throws Exception  
    {  
        Customer cu = new Customer("tom", 30);  
        cu.setId(1L);  
        ReflectTester test = new ReflectTester();  
        Customer cu1 = (Customer) test.copy(cu);  
  
        System.out.println(cu1.getId() + cu1.getName() + cu1.getAge());  
    }  
}  
  
class Customer  
{  
    private Long id;  
    private String name;  
    private int age;  
  
    public Customer()  
    {  
  
    }  
    public Customer(String name, int age)  
    {  
        this.name = name;  
        this.age = age;  
    }  
  
    public Long getId()  
    {  
        return id;  
    }  
  
    public void setId(Long id)  
    {  
        this.id = id;  
    }  
  
    public String getName()  
    {  
        return name;  
    }  
  
    public void setName(String name)  
    {  
        this.name = name;  
    }  
  
    public int getAge()  
    {  
        return age;  
    }  
  
    public void setAge(int age)  
    {  
        this.age = age;  
    }  
  
}  