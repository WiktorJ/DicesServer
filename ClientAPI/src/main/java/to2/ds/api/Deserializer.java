package to2.ds.api;

import org.json.JSONObject;

import java.util.List;
import java.util.ListIterator;

/**
 * Created by wiktor on 08.12.15.
 */
public class Deserializer {

    public static ClientMessageTuple deserializeUser(String json, List<ClientImpl> clients) throws UnexistingClientException {

        JSONObject OneClient = new JSONObject(json);

        String clientId = OneClient.getString("\"clientID\"");
        //  String client = OneClient.getString("client");
        String command = OneClient.getString("\"command\"");
        JSONObject dataJSON = OneClient.getJSONObject("\"data\"");

        ListIterator<ClientImpl> iterator = clients.listIterator();

        while(iterator.hasNext()) {
            if(iterator.next().getId() == clientId){
                ClientMessageTuple tuple = new ClientMessageTuple(dataJSON.toString(), iterator.next());
                return tuple;
            }
        }



        return null;
    }
}



