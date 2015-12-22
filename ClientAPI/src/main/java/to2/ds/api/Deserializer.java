package to2.ds.api;

import org.json.JSONObject;

import java.util.List;
import java.util.ListIterator;

/**
 * Created by wiktor on 08.12.15.
 */
public class Deserializer {

    public static ClientMessageTuple deserializeUser(String json, List<ClientImpl> clients) throws UnexistingClientException {

        JSONObject oneclient = new JSONObject(json);
        String clientID = oneclient.getString("clientID");

        JSONObject messageWithType = oneclient.getJSONObject("messageWithType");
        String JSON = messageWithType.getString("state");
        String type = messageWithType.getString("type");

        ListIterator<ClientImpl> iterator = clients.listIterator();

        while (iterator.hasNext()) {

            if (iterator.next().getId() == clientID) {
                ClientMessageTuple tuple = new ClientMessageTuple(JSON, iterator.next());
                return tuple;
            }
        }

        return null;
    }
}



