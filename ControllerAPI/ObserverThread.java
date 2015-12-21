package to2.ds.api;

import org.json.JSONObject;

/**
 * Created by marcinsendera on 10.12.2015.
 */
public class ObserverThread extends Thread{

    private ClientGroup Clients;
    private ObserverImpl observer;


    private Thread thread;
    private String threadName;


    public void stateUpdated(JSONObject state){
        try {
            observer.stateUpdated(state);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


    public void gameEnded(){

        try {
            observer.gameEnded();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


    public void removePlayer(String nickname){

        try {
            observer.removePlayer(nickname);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



    public void start(){

        thread = new Thread (this, threadName);
        thread.start();
        observer.start();

    }


    public void listen(){

        try {
            observer.notifyWaitUntil();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    public void mystop(){

        thread.stop();
        observer.stop();
    }


}
