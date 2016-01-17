package to2.ds.game.controllers;

/**
 * Created by wiktor on 16.01.16.
 */
public class MockedGameFactory {

    public static MockedGameController createGame(String descriptionString, Observer observer) {
        return new MockedGameController(observer);
    }

}
