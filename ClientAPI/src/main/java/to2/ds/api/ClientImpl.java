package to2.ds.api;


import org.json.JSONObject;

import java.io.IOException;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Queue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;

/**
 * Created by wiktor on 07.12.15.
 */
public class ClientImpl implements Client {

    private BlockingQueue<String> statesQueue = new LinkedBlockingQueue<>();
    private BlockingQueue<String> activeGamesQueue = new LinkedBlockingQueue<>();
    private BlockingQueue<String> serverResponsesQueue = new LinkedBlockingQueue<>();

    private final Map<String, Queue> myMap;



    private String nickname;
    private ConnectorImpl socket;

    public ClientImpl(String nickname, ConnectorImpl socket) {
        this.nickname = nickname;
        this.socket = socket;
        Map<String, Queue> aMap = new HashMap<>();
        aMap.put("activeGames", activeGamesQueue);
        aMap.put("gameState", statesQueue);
        aMap.put("removePlayer", statesQueue);
        myMap = Collections.unmodifiableMap(aMap);
    }

    public String getActiveGames() throws InterruptedException, IOException {//TODO: this json
        JSONObject json = new JSONObject().put("clientID", socket.getClientAddress()).put("type", "request").put("request", new JSONObject().put("clientName", nickname).put("request", new JSONObject().put("command", "activeGames").put("data", "")));

        socket.sendMessage(json.toString());
        return activeGamesQueue.take(); //TODO timeout exception
//        return "";
    }

    public void requestCreate(String JSON) throws IOException {
        JSONObject json = new JSONObject()
                .put("clientID", socket.getClientAddress())
                .put("type", "request")
                .put("request", new JSONObject()
                        .put("clientName", nickname)
                        .put("request", new JSONObject()
                                .put("command", "create")
                                .put("data", new JSONObject(JSON))));

        socket.sendMessage(json.toString());
    }

    public void requestJoinAsPlayer(Integer gameID) throws IOException {
        JSONObject json = new JSONObject()
                .put("clientID", socket.getClientAddress())
                .put("type", "request")
                .put("request", new JSONObject()
                        .put("clientName", nickname)
                        .put("request", new JSONObject()
                                .put("command", "join")
                                .put("data", gameID.toString())));

        socket.sendMessage(json.toString());
    }

    public void requestJoinAsObserver(Integer gameID) throws IOException {
        JSONObject json = new JSONObject()
                .put("clientID", socket.getClientAddress())
                .put("type", "request")
                .put("request", new JSONObject()
                        .put("clientName", nickname)
                        .put("request", new JSONObject()
                                .put("command", "observe")
                                .put("data", gameID.toString())));

        socket.sendMessage(json.toString());
    }

    public void requestMove(String JSON) throws IOException {
        JSONObject json = new JSONObject()
                .put("clientID", socket.getClientAddress())
                .put("type", "request")
                .put("request", new JSONObject()
                        .put("clientName", nickname)
                        .put("request", new JSONObject()
                                .put("command", "move")
                                .put("data", new JSONObject(JSON))));

        socket.sendMessage(json.toString());
    }

    public void requestQuiteGame() throws IOException {
        JSONObject json = new JSONObject()
                .put("clientID", socket.getClientAddress())
                .put("type", "request")
                .put("request", new JSONObject()
                        .put("clientName", nickname)
                        .put("request", new JSONObject()
                                .put("command", "quit")
                                .put("data", "")));

        socket.sendMessage(json.toString());

        // socket.sendMessage(TargetSerializer.serialize("quit", ""));
    }

    public String listen() throws InterruptedException {
        return statesQueue.take();
    }

    @Override
    public String getNickName() {
        return nickname;
    }


    public void stateUpdateAndNotify(JSONObject message) {
        System.out.println("IN UPDATE JSON: " + message);
        Queue queue = myMap.get(message.getString("command"));
        if(queue == null) {
            serverResponsesQueue.add(message.toString());
        } else {
            queue.add(message.get("data").toString());
        }
    }

    public String getId() {
        return nickname;
    }
}
