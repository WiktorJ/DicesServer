package to2.ds.api;


import javax.websocket.*;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.LinkedList;
import java.util.List;

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

    private String clientAddress = "cid";

    protected ConnectorImpl() {
    }

    private List<ClientImpl> clientList = new LinkedList<>();

//
//    public static ConnectorImpl connect(String ip, Integer port) throws IOException, DeploymentException, URISyntaxException {
//        ConnectorImpl connector = new ConnectorImpl();
//        WebSocketContainer container = ContainerProvider.getWebSocketContainer();
////            URI uri = new URI(null, null, ip, port, null, null, null);
//        String clientAddres = "cid";
//        URI uri = new URI("ws://localhost:9020?" + clientAddres);
//        Session session = container.connectToServer(connector, uri);
//        connector.session = session;
//        connector.clientAddress = clientAddres;
//        return connector;
//    }

    public Client addClient(String nickname) throws URISyntaxException, IOException {
        ClientImpl client = ClientFactory.getClient(nickname, this);
        clientList.add(client);
        sendMessage("{" +
                "\"clientID\": " + "\"" + clientAddress + "\"" +
                ", \"client\": " + "\"" + nickname + "\"" +
                ", \"command\": \"addClient\"" + "" +
                "}");
        return client;
    }

    @OnOpen
    private void onOpen(Session session) {
        System.out.println("Connected to server");
        this.session = session;

    }

    @OnMessage
    private void onMessage(String json) throws UnexistingClientException {
        ClientMessageTuple client = deserializer.deserializeUser(json, clientList);
        client.getClient().stateUpdateAndNotify(client.getJSON());
    } // {client: clientID, messageWithType: {type: activeGames/gameState, state: {..}}}

    @OnClose
    public void onClose(CloseReason reason, Session session) {
        System.out.println("Closing a WebSocket due to " + reason.getReasonPhrase());
    }

    protected void sendMessage(String message) throws IOException {
        session.getBasicRemote().sendText(message);
    }


    public void removeClient(Client client) {
        throw new UnsupportedOperationException();
    }
}
