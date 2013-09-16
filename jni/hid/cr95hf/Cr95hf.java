public class Cr95hf{

    public native String getUID();

    public static void main (String[] args){
        Cr95hf cr95hf = new Cr95hf();
        System.out.println("UID "+cr95hf.getUID());
    }
    static{
        System.loadLibrary("Cr95hf");
    }

}
