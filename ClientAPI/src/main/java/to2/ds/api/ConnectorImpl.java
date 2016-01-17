package to2.ds.api;


import jdk.nashorn.api.scripting.JSObject;
import org.json.JSONObject;

import javax.websocket.*;
import java.io.IOException;
import java.net.URISyntaxException;
import java.util.LinkedList;
import java.util.List;
import java.util.UUID;

/**
 * Created by wiktor on 07.12.15.
 */
@ClientEndpoint
public class ConnectorImpl implements Connector {

    private Session session = null;
    private Deserializer deserializer = new Deserializer();

    public void setClientAddress(String clientAddress) {
        this.clientAddress = clientAddress;
    }

    public void setSession(Session session) {

        this.session = session;
    }

    public String getClientAddress() {
        return clientAddress;
    }

    private String clientAddress = UUID.randomUUID().toString();

    protected ConnectorImpl() {
    }

    private List<ClientImpl> clientList = new LinkedList<>();


    public Client addClient(String nickname) throws URISyntaxException, IOException {
        ClientImpl client = ClientFactory.getClient(nickname, this);
        clientList.add(client);
        JSONObject json = new JSONObject().put("clientID", clientAddress).put("type", "addClient").put("request", new JSONObject().put("clientName", nickname));
        sendMessage(json.toString());

        return client;
    }

    @OnOpen
    public void onOpen(Session session) {
        System.out.println("Connected to server");
        this.session = session;

    }

    @OnMessage
    public void onMessage(String json)  {
        System.out.println(json);

//        try {
//            ClientMessageTuple client = deserializer.deserializeUser(json, clientList);
//            client.getClient().stateUpdateAndNotify(client.getJSON());
//        } catch (UnexistingClientException e) {
//            e.printStackTrace(); //TODO This has to be handled on client site!
//        }
    } // {client: clientID, messageWithType: {type: activeGames/gameState, state: {..}}}

    @OnClose
    public void onClose(CloseReason reason, Session session) throws IOException {
        System.out.println("Closing a WebSocket due to " + reason.getReasonPhrase());
    }


    @OnError
    public void onError(Throwable t) {
        t.printStackTrace();
    }

    protected void sendMessage(String message) throws IOException {
        System.out.println(message);
        session.getBasicRemote().sendText(message);
    }


    public void removeClient(Client client) throws IOException {
        clientList.remove(client);
        JSONObject json = new JSONObject().put("clientID", clientAddress).put("type", "removeClient").put("request", new JSONObject().put("clientName", client.getNickName()));
        sendMessage(json.toString());
    }

    @Override
    public void closeConnection() throws IOException {
        session.close();
    }
}
