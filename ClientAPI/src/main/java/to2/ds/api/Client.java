package to2.ds.api;

import java.io.IOException;

/**
 * Created by wiktor on 07.12.15.
 */
public interface Client {

    String getActiveGames() throws InterruptedException, IOException;
    void requestCreate(String JSON) throws IOException;
    void requestJoinAsPlayer(Integer gameID) throws IOException;
    void requestJoinAsObserver(Integer gameID) throws IOException;
    void requestMove(String JSON) throws IOException;
    void requestQuiteGame() throws IOException;
    String listen() throws InterruptedException;
    String getNickName();

}
