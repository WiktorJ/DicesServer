package to2.ds.api;


import org.json.JSONObject;

import java.io.IOException;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Queue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * Created by wiktor on 07.12.15.
 */
public class ClientImpl implements Client {

    private BlockingQueue<String> statesQueue = new LinkedBlockingQueue<>();
    private BlockingQueue<String> activeGamesQueue= new LinkedBlockingQueue<>();

    private final Map<String, Queue> myMap;



    private String nickname;
    private ConnectorImpl socket;

    public ClientImpl(String nickname, ConnectorImpl socket) {
        this.nickname = nickname;
        this.socket = socket;
        Map<String, Queue> aMap = new HashMap<>();
        aMap.put("activeGames", activeGamesQueue);
        aMap.put("gameState", statesQueue);
        myMap = Collections.unmodifiableMap(aMap);
    }

    public String getActiveGames() throws InterruptedException, IOException {
        socket.sendMessage(TargetSerializer.serialize("getActiveGames", ""));
        return activeGamesQueue.take();
    }

    public void requestCreate(String JSON) throws IOException {
        String createGame = TargetSerializer.serialize("create", JSON);
        socket.sendMessage(createGame);
    }

    public void requestJoinAsPlayer(Integer gameID) throws IOException {
        String jsonString = new JSONObject()
                            .put("gameId", gameID)
                            .put("clientId", nickname)
                            .toString();

        socket.sendMessage(TargetSerializer.serialize("create", jsonString));
    }

    public void requestJoinAsObserver(Integer gameID) throws IOException {
        String jsonString = new JSONObject()
                .put("gameId", gameID)
                .put("clientId", nickname)
                .toString();

        socket.sendMessage(TargetSerializer.serialize("observe", jsonString));

    }

    public void requestMove(String JSON) throws IOException {
        socket.sendMessage(TargetSerializer.serialize("move", JSON));
    }

    public void requestQuiteGame() throws IOException {
        socket.sendMessage(TargetSerializer.serialize("quit", ""));
    }

    public String listen() throws InterruptedException {
        return statesQueue.take();
    }


    public void stateUpdateAndNotify(String message) {
        JSONObject jsonObject = new JSONObject(message);
        Queue queue = myMap.get((String) jsonObject.get("type"));
        queue.add(message);
    }

    public String getId() {
        return nickname;
    }
}
