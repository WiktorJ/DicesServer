package to2.ds.api;

/**
 * Created by wiktor on 08.12.15.
 */
public class ClientFactory {
    public static ClientImpl getClient(String name, ConnectorImpl socket) {
      return new ClientImpl(name, socket);
    }
}
