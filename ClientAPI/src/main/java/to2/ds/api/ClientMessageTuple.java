package to2.ds.api;

import org.json.JSONObject;

/**
 * Created by wiktor on 08.12.15.
 */
public class ClientMessageTuple {
    private JSONObject JSON;
    private ClientImpl client;

    public ClientImpl getClient() {
        return client;
    }

    public JSONObject getJSON() {
        return JSON;
    }

    public ClientMessageTuple(JSONObject JSON, ClientImpl client) {
        this.JSON = JSON;
        this.client = client;
    }
}
