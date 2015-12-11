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

    private String operation = new String();

    private boolean otherOperation = false;


    private final Lock lock = new ReentrantLock();
    private final Condition noOtherOp = lock.newCondition();
    private final Condition someOtherOp = lock.newCondition();
    private int id;

    public ObserverImpl(int id){
        this.id = id;
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
        this.state = state;
        operation = "update";
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
        String end = new String("end");
        JSONObject endJSON = new JSONObject();
        endJSON.put("action", end);

        //prześlij JSONa dalej

        operation = "end";
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
//        JSONObject removePlayer = new JSONObject();
//        removePlayer.put("remove", nickname);
        operation = "remove";
        //prześlij tego JSONa dalej

        otherOperation = true;
        notifyAll();

    }

    public synchronized void notifyWaitUntil() throws InterruptedException {

        while (!otherOperation){
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        otherOperation = false;
        notifyAll();
    }

    public String getLastOperation(){
//        JSONObject lastOperation = new JSONObject();
//        lastOperation.put("operation", operation);
//        return lastOperation.toString();
        return "sth" + id + "\n";

    }
}
