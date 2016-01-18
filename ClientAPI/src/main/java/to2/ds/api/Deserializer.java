package to2.ds.api;

import org.json.JSONObject;

import java.util.List;

/**
 * Created by wiktor on 08.12.15.
 */
public class Deserializer {

    public static ClientMessageTuple deserializeUser(String json, List<ClientImpl> clients) throws UnexistingClientException, WrongJSONFormatException {

        JSONObject message = new JSONObject(json);
        JSONObject response = message.getJSONObject("response");
        if(response.has("clientName") && response.has("response")) {
            JSONObject dataJSON = response.getJSONObject("response");
            String clientId = response.getString("clientName");

            for (ClientImpl client : clients) {
                if (client.getId().equals(clientId)) {
                    return new ClientMessageTuple(dataJSON, client);
                }
            }

            throw new UnexistingClientException();

        } else {
            throw new WrongJSONFormatException();
        }
    }


    public static ResponseType getResponseType(String json) {
        System.out.println("GET RESP TYPE: " + json);
        JSONObject message = new JSONObject(json);
        System.out.println("INFO: " + message.getString("type"));
        String info = message.getString("type");
        return ResponseType.valueOf(info);
    }

    public enum ResponseType {
        clientInfo,
        connectorInfo;
    }
}



