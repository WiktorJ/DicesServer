package to2.ds.api;

/**
 * Created by wiktor on 07.12.15.
 */
public interface Client {

    String getActiveGames();
    void requestCreate(String JSON);
    void requestJoinAsPlayer(Integer gameID);
    void requestJoinAsObserver(Integer gameID);
    void requestMove(String JSON);
    void requestQuiteGame();
    String listen();

}
