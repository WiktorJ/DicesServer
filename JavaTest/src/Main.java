import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by wiktor on 23.11.15.
 */

public class Main {
    public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
        PrintWriter writer = new PrintWriter(args[0], "UTF-8");
        writer.println(args[0]);
        System.out.printf("xDDDDD");
        writer.println("The first line");
        writer.println("The second line");
        List<String> l = new LinkedList<>();
        l.add("A");
        l.add("B");
        l.add("C");
        l.stream().forEach(e -> System.out.println(e));
        writer.close();
    }

}
