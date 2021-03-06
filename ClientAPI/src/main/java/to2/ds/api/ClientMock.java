package to2.ds.api;


import javax.websocket.DeploymentException;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;

/**
 * Created by wiktor on 20.12.15.
 */
public class ClientMock {


    public static void main(String[] args) throws DeploymentException, IOException, URISyntaxException, InterruptedException {


        Connector connector = Connector.connect("localhost", 9020);
        Client test = connector.addClient("test");
        boolean finishFlag = false;

        Thread t = new Thread(() -> {
            try {
                while (true) {
                    String listen = test.listen();
                    System.out.println("RECIVED MESSAGE:\n" + listen);
                }
            } catch (InterruptedException e) {
                System.out.println("Listener terminated");
            }
        });
        t.start();
        Scanner scanner = new Scanner(System.in);
        Path pathToJson = Paths.get(ClientMock.class.getClassLoader().getResource("JSON").toURI());
        System.out.println(pathToJson);


        while (!finishFlag) {

            String s = scanner.nextLine();
            if (s.equals("e")) {
                finishFlag = true;
                connector.removeClient(test);
            }
            String json = new String(Files.readAllBytes(pathToJson));
            switch (s) {
                case "m":
                    test.requestMove(json);
                    break;
                case "c":
                    test.requestCreate(json);
                    break;
                case "j":
                    System.out.println("Podaj GameId");
                    int i = scanner.nextInt();
                    test.requestJoinAsPlayer(i);
                    break;
                case "q":
                    test.requestQuiteGame();
                    break;
                case "a":
                    test.getActiveGames();
                    break;
                default:
                    System.out.println("Wrong command");
            }
        }
        t.interrupt();
        t.join();
        connector.closeConnection();
    }
}
