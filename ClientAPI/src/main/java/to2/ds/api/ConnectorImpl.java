package to2.ds.api;


import javax.websocket.*;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

/**
 * Created by wiktor on 07.12.15.
 */
@ClientEndpoint
public class ConnectorImpl implements Connector {

    private final String ip;
    private final Integer port;
    private Session userSession = null;

    public ConnectorImpl(String ip, Integer port) {
        this.ip = ip;
        this.port = port;
    }

    public void connect() throws IOException, DeploymentException, URISyntaxException {
        WebSocketContainer container = ContainerProvider.getWebSocketContainer();
            URI uri = new URI(null, null, ip, port, "client", null, null);
            userSession = container.connectToServer(this, uri);
    }

    public Client addClient(String nickname) throws URISyntaxException {
        URI uri = new URI(null, null, ip, port, "client/" + nickname, null, null);
        return new ClientImpl(uri, nickname);
    }

    public void removeClient(Client client) {
        throw new UnsupportedOperationException();
    }
}
