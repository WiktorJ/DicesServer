package to2.ds.game.controllers;

import org.json.JSONObject;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;

/**
 * Created by wiktor on 11.12.15.
 */
public class MockedGameController implements Runnable {
    private Observer observer;

    private final int UPDATES_INTERVAL = 1000; //ms
    private final int UPDATE_COUNT = 3;
    private int clientCount= 2;

    public MockedGameController() {
    }

    public MockedGameController(Observer observer) {
        this.observer = observer;
    }


    public static void startGameController(MockedGameController mockedGameController) {
        new Thread(mockedGameController).start();

    }

    public void addPlayer(String json) {
        System.out.println("Player added\n"+json);
        if(--clientCount == 0) {
            System.out.println("Starting Game");
            new Thread(this).start();
        }
    }

    public void makeMove(String json) {
        System.out.println("move made\n" + json);
    }

    public String getInfo() {
        return "{\n"+
                " \"gameType\": \"N_PLUS\",\n"+
                " \"gameName\": \"some name\",\n"+
                " \"players\": [\n"+
                " \"player1\",\n"+
                " \"bot1\"\n"+
                " ],\n"+
                " \"expectedNumberOfPlayers\": 7,\n"+
                " \"started\": false,\n"+
                " \"pointsToWin\": 1\n"+
                "}";
    }

    @Override
    public void run() {
        try {
            for (int i = 0; i < UPDATE_COUNT; i++) {
                observer.stateUpdated(new JSONObject("{\n"+
                        " \"pointsToWin\": 4,\n"+
                        " \"playerInfos\": [\n"+
                        " {\n"+
                        " \"rollsInRound\": 1,\n"+
                        " \"hand\": {\n"+
                        " \"dices\": [ 5, 5, 5, 5, 5 ],\n"+
                        " \"description\": \"Five of a Kind (5)\"\n"+
                        " },\n"+
                        " \"points\": 4,\n"+
                        " \"nickname\": \"player1\"\n"+
                        " },\n"+
                        " {\n"+
                        " \"rollsInRound\": 2,\n"+
                        " \"hand\": {\n"+
                        " \"dices\": [ 2, 2, 4, 4, 1 ],\n"+
                        " \"description\": \"Two Pair (4, 2)\"\n"+
                        " },\n"+
                        " \"points\": 2,\n"+
                        " \"nickname\": \"bot1\"\n"+
                        " }\n"+
                        " ],\n"+
                        " \"currentPlayer\": null,\n"+
                        " \"roundWinner\": \"player1\",\n"+
                        " \"gameWinner\": null\n"+
                        "}"));
                Thread.sleep(UPDATES_INTERVAL);
            }
            observer.gameEnded();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

}
