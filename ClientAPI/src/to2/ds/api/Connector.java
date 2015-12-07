package to2.ds.api;

/**
 * Created by wiktor on 07.12.15.
 */
public interface Connector {

    void connect(String port, String ip );
    Client addClient(String nickname);
    void removeClient(Client client);
}
