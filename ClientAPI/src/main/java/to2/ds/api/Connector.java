package to2.ds.api;

import javax.websocket.DeploymentException;
import java.io.IOException;
import java.net.URISyntaxException;

/**
 * Created by wiktor on 07.12.15.
 */
public interface Connector {

    void connect() throws IOException, DeploymentException, URISyntaxException;
    Client addClient(String nickname) throws URISyntaxException;
    void removeClient(Client client);
}
