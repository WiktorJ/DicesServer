package to2.ds.game.controllers;

/**
 * Created by wiktor on 11.12.15.
 */
public class MockedGameController implements Runnable{
    private Observer observer;

    public MockedGameController() {
    }

    public MockedGameController(ObserverImpl observer) {
        this.observer = observer;
    }


    public static void startGameController(MockedGameController mockedGameController) {
        new Thread(mockedGameController).start();

    }

    public void addPlayer(String json) {
        System.out.println("player added");
    }

    public void makeMove(String json) {
        System.out.println("move made");
    }

    public String getInfo() {
        return "some game info";
    }

    @Override
    public void run() {
        int i = 10;
        while (i > 0) {
            try {
                observer.removePlayer("ABC" + i);
                Thread.sleep(500);
                i--;
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }
}
