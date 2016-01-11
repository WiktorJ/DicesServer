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

    public String getActiveGames() throws InterruptedException, IOException {//TODO: this json
        socket.sendMessage("{" +
                "\"clientID\": " + "\"" + socket.getClientAddress()+ "\"" +
                ", \"client\": " + "\"" + nickname + "\"" +
                ", \"command\": \"request\"" + "" +
                ", \"data\": " + "{\"command\": \"activeGames\", \"data\": {}}"  +
                "}");
        return activeGamesQueue.poll(2, TimeUnit.SECONDS);
    }

    public void requestCreate(String JSON) throws IOException {

        String createGame =
                "{" +
                        "\"clientID\": " + "\"" + socket.getClientAddress()+ "\"" +
                        ", \"client\": " + "\"" + nickname + "\"" +
                        ", \"command\": \"request\"" + "" +
                        ", \"data\": " + "{\"command\": \"createGame\", \"data\": {"+JSON+"}}"  +
                        "}";
        socket.sendMessage(createGame);
    }

    public void requestJoinAsPlayer(Integer gameID) throws IOException {
        String requestJoinAsPlayer =
                "{" +
                        "\"clientID\": " + "\"" + socket.getClientAddress()+ "\"" +
                        ", \"client\": " + "\"" + nickname + "\"" +
                        ", \"command\": \"request\"" + "" +
                        ", \"data\": " + "{\"command\": \"join\", \"gameId\": \""+gameID.toString()+"\" ,\"data\":  {}}"  +
                        "}";

        socket.sendMessage(requestJoinAsPlayer);
    }

    public void requestJoinAsObserver(Integer gameID) throws IOException {
        String requestJoinAsObserver =
                "{" +
                        "\"clientID\": " + "\"" + socket.getClientAddress()+ "\"" +
                        ", \"client\": " + "\"" + nickname + "\"" +
                        ", \"command\": \"request\"" + "" +
                        ", \"data\": " + "{\"command\": \"observe\", \"gameId\": \""+gameID.toString()+"\" ,\"data\":  {}}"  +
                        "}";

        //  socket.sendMessage(TargetSerializer.serialize("observe", requestJoinAsObserver));

        socket.sendMessage(requestJoinAsObserver);
    }

    public void requestMove(String JSON) throws IOException {
        String requestMove =
                "{" +
                        "\"clientID\": " + "\"" + socket.getClientAddress()+ "\"" +
                        ", \"client\": " + "\"" + nickname + "\"" +
                        ", \"command\": \"request\"" + "" +
                        ", \"data\": " + "{\"command\": \"move\", \"data\": {"+JSON+"}"  +
                        "}";
        socket.sendMessage(requestMove);
    }

    public void requestQuiteGame() throws IOException {
        String requestQuit =
                "{" +
                        "\"clientID\": " + "\"" + socket.getClientAddress()+ "\"" +
                        ", \"client\": " + "\"" + nickname + "\"" +
                        ", \"command\": \"request\"" + "" +
                        ", \"data\": " + "{\"command\": \"quit\", \"data\":  {}}"  +
                        "}";

        socket.sendMessage(requestQuit);

        // socket.sendMessage(TargetSerializer.serialize("quit", ""));
    }

    public String listen() throws InterruptedException {
        return statesQueue.take();
    }

    @Override
    public String getNickName() {
        return nickname;
    }


    public void stateUpdateAndNotify(String message) {
        JSONObject jsonObject = new JSONObject(message);
        Queue queue = myMap.get((String) jsonObject.get("\"command\""));
        queue.add(message);
    }

    public String getId() {
        return nickname;
    }
}
