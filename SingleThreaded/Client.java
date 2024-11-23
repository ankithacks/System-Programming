import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class Client {
    public void run() throws UnknownHostException, IOException {
        int port = 8010; // Make sure this matches the server's port
        InetAddress address = InetAddress.getByName("localhost"); // Corrected line
        Socket socket = new Socket(address, port);

        // Sending the request to the server
        PrintWriter toSocket = new PrintWriter(socket.getOutputStream(), true); // Auto-flush enabled
        BufferedReader fromSocket = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        String line = fromSocket.readLine();
        System.out.println("Response from the socket is: " + line);

        // Close the streams and socket
        fromSocket.close();
        toSocket.close();
        socket.close();
    }

    public static void main(String[] args) {
        try {
            Client client = new Client();
            client.run();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
