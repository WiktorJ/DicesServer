package to2.ds.game.controllers;

import org.json.JSONObject;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;



/**
 * Created by marcinsendera on 10.12.2015.
 */

public class ObserverImpl implements Observer{

    private JSONObject state;
    private boolean gameEnded = false;

    private boolean otherOperation = false;

    public ObserverImpl(){
    }

    @Override
    public synchronized void stateUpdated(JSONObject state) throws InterruptedException {
        while(otherOperation){
            try{
                wait();
            } catch (InterruptedException e) {
            }
        }
        //doing sth
        this.state = new JSONObject();
        state.put("stateUpdated", state.toString());
        otherOperation = true;
        notifyAll();

    }


    @Override
    public synchronized void gameEnded() throws InterruptedException {

        while(otherOperation){
            try{
                wait();
            } catch (InterruptedException e) {
            }
        }
        //doing sth
        this.state = new JSONObject();
        this.state.put("gameEnded", "");
        this.gameEnded = true;

        //prześlij JSONa dalej
        otherOperation = true;

        notifyAll();

    }

    @Override
    public synchronized void removePlayer(String nickname) throws InterruptedException {

        while(otherOperation){
            try{
                wait();
            } catch (InterruptedException e) {
            }
        }
        //doing sth
        this.state = new JSONObject();
        this.state.put("removePlayer", nickname);
        //prześlij tego JSONa dalej

        otherOperation = true;
        notifyAll();

    }

    public synchronized String notifyWaitUntil() throws InterruptedException {

        while (!otherOperation){
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        otherOperation = false;
        notifyAll();
        return state.toString();
    }
    public synchronized boolean isGameEnded() {
        return this.gameEnded;
    }

}
