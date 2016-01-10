package to2.ds.api;

import javax.websocket.ContainerProvider;
import javax.websocket.DeploymentException;
import javax.websocket.Session;
import javax.websocket.WebSocketContainer;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

/**
 * Created by wiktor on 07.12.15.
 */
public interface Connector {

    Client addClient(String nickname) throws URISyntaxException, IOException;
    static Connector connect(String ip, Integer port) throws IOException, DeploymentException, URISyntaxException {
        ConnectorImpl connector = new ConnectorImpl();
        WebSocketContainer container = ContainerProvider.getWebSocketContainer();
//            URI uri = new URI(null, null, ip, port, null, null, null);
        String clientAddres = "cid";
        URI uri = new URI("ws://localhost:9020?" + clientAddres);
//        URI uri = new URI("ws://localhost:9021/web/echo" + clientAddres);
        Session session = container.connectToServer(connector, uri);
        connector.setSession(session);
        connector.setClientAddress(clientAddres);
        return connector;
    }
    void removeClient(Client client) throws IOException;
    void closeConnection() throws IOException;
}
