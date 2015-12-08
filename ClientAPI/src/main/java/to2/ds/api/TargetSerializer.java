package to2.ds.api;

import org.json.JSONObject;

/**
 * Created by wiktor on 08.12.15.
 */
public class TargetSerializer {
    public static String serialize(String headerToAdd, String message) {
        return new JSONObject().put(headerToAdd, message).toString();
    }
}
