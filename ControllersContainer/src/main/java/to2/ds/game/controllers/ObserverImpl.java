package to2.ds.game.controllers;

import org.json.JSONObject;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


/**
 * Created by marcinsendera on 08.12.2015.
 **/


public class ObserverImpl extends Thread implements Observer {


    private JSONObject state;

    private String operation = new String();

    private boolean otherOperation = false;

    private final Lock lock = new ReentrantLock();
    private final Condition noOtherOp = lock.newCondition();
    private final Condition someOtherOp = lock.newCondition();


    private ObserverImpl(){
    }
    public void stateUpdated(JSONObject state) throws InterruptedException {
        lock.lock();
        otherOperation = true;

        try{
            while(otherOperation){
                noOtherOp.await();
            }

            //doing sth
            this.state = state;
            operation = "update";
            otherOperation = true;
            someOtherOp.signal();
        } finally {
            lock.unlock();
        }
    }


    public void gameEnded() throws InterruptedException {

        lock.lock();
        otherOperation = true;

        try{
            while(otherOperation){
                noOtherOp.await();
            }

            //doing sth
            String end = new String("end");
            JSONObject endJSON = new JSONObject();
            endJSON.put("action", end);
            //prześlij JSONa dalej
            operation = "end";

            otherOperation = true;
            someOtherOp.signal();
        } finally {
            lock.unlock();
        }
    }

    public void removePlayer(String nickname) throws InterruptedException {

        lock.lock();
        otherOperation = true;

        try{
            while(otherOperation){
                noOtherOp.await();
            }

            //doing sth

            JSONObject removePlayer = new JSONObject();
            removePlayer.put("remove", nickname);
            operation = "remove";
            //prześlij tego JSONa dalej

            otherOperation = true;
            someOtherOp.signal();
        } finally {
            lock.unlock();
        }

    }

    public void notifyWaitUntil() throws InterruptedException {

        lock.lock();

        try{
            while (!otherOperation) {
                someOtherOp.await();
            }

            //doing nothing
            otherOperation = false;
            noOtherOp.signal();

        } finally {
            lock.unlock();
        }


    }

    public JSONObject getLastOperation(){
        JSONObject lastOperation = new JSONObject();
        lastOperation.put("operation", operation);
        return lastOperation;
    }

}


