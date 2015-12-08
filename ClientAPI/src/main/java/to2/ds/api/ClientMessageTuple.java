package to2.ds.api;

/**
 * Created by wiktor on 08.12.15.
 */
public class ClientMessageTuple {
    private String JSON;
    private ClientImpl client;

    public ClientImpl getClient() {
        return client;
    }

    public String getJSON() {
        return JSON;
    }

    public ClientMessageTuple(String JSON, ClientImpl client) {
        this.JSON = JSON;
        this.client = client;
    }
}
