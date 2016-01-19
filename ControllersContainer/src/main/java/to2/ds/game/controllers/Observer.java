package to2.ds.game.controllers;

import org.json.JSONObject;

/**
 * Created by marcinsendera on 08.12.2015.
 */
//import java.util.Observable;
//import java.util.Observer;

public interface Observer {

    //private String state;

    public void stateUpdated(String state) throws InterruptedException;   //docelowo stateUpdated(GameState state)
    public void gameEnded() throws InterruptedException;
    public void removePlayer(String nickname) throws InterruptedException;

}
